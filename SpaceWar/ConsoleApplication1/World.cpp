#include "SFML/Graphics/RenderWindow.hpp"

#include "Entity.hpp"
#include "World.hpp"
#include "Game.hpp"

using namespace sf;
void World::update(double dt) {
	if (audio == nullptr)
		audio = new Audio();

	Player* player =					nullptr;
	BulletEntity* bullet =				nullptr;
	EnnemyEntity* ennemy =				nullptr;
	//HealthPackEntity* pack =			nullptr;


	for (auto e : data) {
		Vector2f predPos = e->getPosition();

		e->lastGoodPosition = e->getPosition();

		e->update(dt);

		if (e->type == PlayerObject)
			player = (Player*)e;
	
		if(player != nullptr)
		if (player->playerHP <= 0) {
			audio->lostSound.play();
			audio->mix.stop();
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

		///// H E A L T H   P A C K /////
		/*if (e->type == HealthPack) {
			pack = (HealthPackEntity*)e;
			for (int i = 0; i < bullet->px.size(); i++)
			{
				pack->lastGoodPosition_H[i] = Vector2f(pack->px[i], bullet->py[i]);
			}
			for (int j = 0; j < data.size(); ++j) {
				auto oe = data[j];
				if (oe->type == PlayerObject) {
					collideHealthPackPlayer((Player*)oe, pack);
				}
			}
		}*/
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


///// B U L L E T  vs  W A L L /////
void World::collideWallBullet(Entity* wall, BulletEntity* bullet) {
	auto oe = wall;
	auto e = bullet;
	for (int i = 0; i < e->px.size(); i++)
	{
		Vector2f bulletPos = Vector2f(e->px[i], e->py[i]);
		if (oe->getBoundingBox().contains(bulletPos)) {
			e->rebound[i] += 1;

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


///// E N E M Y  vs  W A L L /////
void World::collideWallEnnemy(Entity* wall, EnnemyEntity* ennemy) {
	auto oe = wall;
	auto e = ennemy;
	for (int i = 0; i < e->px.size(); i++)
	{
		Vector2f ennemyPos = Vector2f(e->px[i], e->py[i]);
		if (oe->getBoundingBox().contains(ennemyPos)) {

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


///// E N E M Y  vs  B U L L E T /////
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


							for (int i = 0; i < 12; ++i)
								Game::particlesAt(Vector2f(oe->px[j], oe->py[j]));
							Game::score += 100;
							Game::shake = 30;

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


///// E N E M Y  vs  P L A Y E R /////
void World::collidePlayerEnnemy(Player* player, EnnemyEntity* ennemy) {
	auto oe = ennemy;
	auto e = player;
	if (player == nullptr) return;
	Vector2f playerPos = e->getPosition();
	if (ennemy == nullptr) return;

		for (size_t j = 0; j < ennemy->px.size(); j++)
		{
			if (player->timerHit >= 3.0f) {
				// Real distance check
				auto dist = sqrt((playerPos.x - ennemy->px[j])*(playerPos.x - ennemy->px[j]) + (playerPos.y - ennemy->py[j])*(playerPos.y - ennemy->py[j]));
				if (dist <= 20 /*radiusEnnemy*/ + 30 /*radiusPlayer*/) { //il y a overlapp
					
					if (oe->type == Ennemy) {
						audio->hitSound.play();

						for (int i = 0; i < 12; ++i)
							Game::particlesAt(Vector2f(oe->px[j], oe->py[j]));
						Game::shake = 30;

						player->playerHP -= 1;
						ennemy->alive[j] = false;						
						player->timerHit = 0;
					}
				}
			}
			
		}
	
}


///// E N E M Y  vs  E N E M Y /////
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


///// P A C K  vs  P L A Y E R /////
/*void World::collideHealthPackPlayer(Player* player, HealthPackEntity* pack) {
	auto oe = pack;
	auto e = player;
	if (player == nullptr) return;
	Vector2f playerPos = e->getPosition();
	if (pack == nullptr) return;

	for (size_t j = 0; j < pack->px.size(); j++)
	{
		// Real distance check
		auto dist = sqrt((playerPos.x - pack->px[j])*(playerPos.x - pack->px[j]) + (playerPos.y - pack->py[j])*(playerPos.y - pack->py[j]));
		if (dist <= 30 /*radiusPack*/ //+ 30 /*radiusPlayer*/) { //il y a overlapp

/*			if (oe->type == HealthPack) {

				audio->healthPackSound.play();
				player->playerHP += 5;
				pack->alive[j] = false;
			}
		}
	}

}*/


void World::draw(sf::RenderWindow& win)
{
	for (auto e : data)
		e->draw(win);
}

Audio::Audio() {
	if (laserShotBuffer.loadFromFile("res/LaserShot.wav"))
		laserShot.setBuffer(laserShotBuffer);

	if (healthPackSoundBuffer.loadFromFile("res/HPack.wav"))
		healthPackSound.setBuffer(healthPackSoundBuffer);

	if (hitSoundBuffer.loadFromFile("res/Hit.wav"))
		hitSound.setBuffer(hitSoundBuffer);

	if (lostSoundBuffer.loadFromFile("res/Lost.wav"))
		lostSound.setBuffer(lostSoundBuffer);

	if (mix.openFromFile("res/Light_It_Up.wav")) {
		mix.play();
		mix.setVolume(8.0f);
		mix.setLoop(true);

	}
		
}
