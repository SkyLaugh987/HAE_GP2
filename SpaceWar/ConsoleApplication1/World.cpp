#include "SFML/Graphics/RenderWindow.hpp"

#include "Entity.hpp"
#include "World.hpp"
#include "Game.hpp"

using namespace sf;
void World::update(double dt) {
	if (audio == nullptr)
		audio = new Audio();

	Player* player = nullptr;
	BulletEntity* bullet = nullptr;
	EnnemyEntity* ennemy = nullptr;


	for (auto e : data) {
		Vector2f predPos = e->getPosition();

		e->lastGoodPosition = e->getPosition();

		e->update(dt);

		if (e->type == PlayerObject)
			player = (Player*)e;
	
		if(player != nullptr)
		if (player->HP <= 0) {
			return;
		}


		if (e->type == Ennemy)
			ennemy = (EnnemyEntity*)e;
		if (e->type == Bullet)
			bullet = (BulletEntity*)e;

		///// E N N E M Y /////
		if (e->type == Ennemy) {
			ennemy = (EnnemyEntity*)e;
			for (int i = 0; i < ennemy->px.size(); i++)
			{
				ennemy->lastGoodPosition_E[i] = Vector2f(ennemy->px[i], ennemy->py[i]);
			}
			for (int j = 0; j < data.size(); ++j) {
				auto oe = data[j];
				if (oe->type == Wall) {
					collideWallEnnemy(oe, ennemy);
				}
				else if (oe->type == PlayerObject) 
				{
					collidePlayerEnnemy(player = (Player*)oe, ennemy);
				}
				else if (oe->type == Ennemy) {

					collideEnnemyEnnemy((EnnemyEntity*)oe, (EnnemyEntity*)e);
				}
			}
		}
		
		///// B U L L E T /////
		if (e->type == Bullet) {
			 bullet = (BulletEntity*)e;
			 for (int i = 0; i < bullet->px.size(); i++)
			 {
				 bullet->lastGoodPosition_B[i] = Vector2f(bullet->px[i], bullet->py[i]);
			 }
			for (int j = 0; j < data.size(); ++j) {
				auto oe = data[j];
				if (oe->type == Wall) {
					collideWallBullet(oe, bullet);
				}
			}

		}


		if (e->type == Bullet) {			
			bullet = (BulletEntity*)e;
			for (int i = 0; i < bullet->px.size(); i++)
			{
				bullet->lastGoodPosition_B[i] = Vector2f(bullet->px[i], bullet->py[i]);
			}
			for (int j = 0; j < data.size(); ++j) {
				auto oe = data[j];
				if (oe->type == Ennemy) {
					collideEnnemyBullet((EnnemyEntity*)oe, bullet);
				}
			}
		}
		
	}


	if (toBreakEntity.size()) {
		for (auto b : toBreakEntity) {
			auto iter = std::find(data.begin(), data.end(), b);
			if (iter != data.end())
				data.erase(iter);
			delete b;
		}
		toBreakEntity.clear();
	}
}


void World::collideWallBullet(Entity* wall, BulletEntity* bullet) {
	auto oe = wall;
	auto e = bullet;
	for (int i = 0; i < e->px.size(); i++)
	{
		Vector2f bulletPos = Vector2f(e->px[i], e->py[i]);
		if (oe->getBoundingBox().contains(bulletPos)) {
			audio->ballPong.play();
			//determiner si le rebond est sur l'axe vert ou horiz
			e->px[i] = e->lastGoodPosition_B[i].x;
			e->py[i] = e->lastGoodPosition_B[i].y;

			if (oe->spr->getGlobalBounds().width > oe->spr->getGlobalBounds().height) {
				//mur haut bass
				e->dy[i] = -e->dy[i];
			}
			else {
				//mur gauche droite
				e->dx[i] = -e->dx[i];
			}
		}

	}
}

void World::collideWallEnnemy(Entity* wall, EnnemyEntity* ennemy) {
	auto oe = wall;
	auto e = ennemy;
	for (int i = 0; i < e->px.size(); i++)
	{
		Vector2f ennemyPos = Vector2f(e->px[i], e->py[i]);
		if (oe->getBoundingBox().contains(ennemyPos)) {
			audio->ballPong.play();
			//determiner si le rebond est sur l'axe vert ou horiz
			e->px[i] = e->lastGoodPosition_E[i].x;
			e->py[i] = e->lastGoodPosition_E[i].y;

			if (oe->spr->getGlobalBounds().width > oe->spr->getGlobalBounds().height) {
				//mur haut bas
				e->dy[i] = -e->dy[i];
			}
			else {
				//mur gauche droite
				e->dx[i] = -e->dx[i];
			}
		}

	}
}


void World::collideEnnemyBullet(EnnemyEntity* ennemy, BulletEntity* bullet) {
	auto oe = ennemy;
	auto e = bullet;
	if (ennemy == nullptr) return;

	for (size_t i = 0; i < bullet->px.size(); i++)
	{
		for (size_t j = 0; j < ennemy->px.size(); j++)
		{
			if (!bullet->hit[i]) {
				if (ennemy->alive[j] == true) {

					// Real distance check
					auto dist = sqrt((bullet->px[i] - ennemy->px[j])*(bullet->px[i] - ennemy->px[j]) + (bullet->py[i] - ennemy->py[j])*(bullet->py[i] - ennemy->py[j]));
					if (dist <= 20 /*radiusEnnemy*/ + 10 /*radiusBullet*/) { //il y a overlapp

						if (oe->type == Ennemy) {
							audio->ballPong.play();


							for (int i = 0; i < 12; ++i)
								Game::particlesAt(Vector2f(oe->px[j], oe->py[j]));
							Game::score += 100;
							Game::shake = 30;
							audio->ballPong.play();
							bullet->hit[i] = true;
							bullet->alive[i] = false;
							ennemy->alive[j] = false;
						}
					}
				}

			}
		}
	}
}


void World::collidePlayerEnnemy(Player* player, EnnemyEntity* ennemy) {
	auto oe = ennemy;
	auto e = player;
	if (player == nullptr) return;
	Vector2f playerPos = e->getPosition();
	if (ennemy == nullptr) return;

		for (size_t j = 0; j < ennemy->px.size(); j++)
		{
			if (player->timerHit >= 2.0f) {
				// Real distance check
				auto dist = sqrt((playerPos.x - ennemy->px[j])*(playerPos.x - ennemy->px[j]) + (playerPos.y - ennemy->py[j])*(playerPos.y - ennemy->py[j]));
				if (dist <= 20 /*radiusEnnemy*/ + 40 /*radiusPlayer*/) { //il y a overlapp
					
					if (oe->type == Ennemy) {
						audio->ballPong.play();

						for (int i = 0; i < 12; ++i)
							Game::particlesAt(Vector2f(oe->px[j], oe->py[j]));
						Game::shake = 30;
						audio->ballPong.play();
						player->HP -= 1;
						ennemy->alive[j] = false;						
						player->timerHit = 0;
					}
				}

			}
			
		}
	
}


void World::collideEnnemyEnnemy(EnnemyEntity* ennemy1, EnnemyEntity* ennemy2) {
	auto oe = ennemy1;
	auto e = ennemy2;
	for (size_t i = 0; i < ennemy1->px.size(); i++)
	{
		for (size_t j = 0; j < ennemy2->px.size(); j++)
		{
			auto dist = sqrt((oe->px[i] - e->px[j])*(oe->px[i] - e->px[j]) + (oe->py[i] - e->py[j])*(oe->py[i] - e->py[j]));
			if (dist <= 20 /*radiusEnnemy*/ + 20 /*radiusEnnemy*/) { //il y a overlapp
				auto ang = atan2((oe->py[i] - e->py[j]), (oe->px[i] - e->px[j]));
				auto force = 300;
				auto repelPower = (20 /*radiusEnnemy*/ + 20 /*radiusEnnemy*/ - dist) / (20 /*radiusEnnemy*/ + 20 /*radiusEnnemy*/);
				e->dx[i] -= cos(ang) * repelPower * force;
				e->dy[i] -= sin(ang) * repelPower * force;
				oe->dx[j] += cos(ang) * repelPower * force;
				oe->dy[j] += sin(ang) * repelPower * force;

			}
		}
	}
}


void World::draw(sf::RenderWindow& win)
{
	for (auto e : data)
		e->draw(win);
}

Audio::Audio() {
	if (ballPongBuffer.loadFromFile("res/ball_pong.wav"))
		ballPong.setBuffer(ballPongBuffer);
	if (mix.openFromFile("res/MixDubStep.wav")) {
		mix.play();
		mix.setVolume(8.0f);
		mix.setLoop(true);

	}
		
}
