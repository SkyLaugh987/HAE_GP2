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

		if (e->type == Ennemy)
			ennemy = (EnnemyEntity*)e;
		
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

		/*if (e->type == Bullet) {
			for (int j = 0; j < data.size(); ++j) {
				auto oe = data[j];
				if (oe->type == Ennemy) {
					collideEnnemyBullet(oe, e);
				}
			}
		}
		if (e->type == Ennemy) {
			for (int j = 0; j < data.size(); ++j) {
				auto oe = data[j];
				if (oe->type == PlayerObject) {
					collidePlayerEnnemy(oe, e);
				}
			}
		}*/

		for (auto e : data) {
			if (e->type == Bullet) {
				if (e->getPosition().y > 1024) {
					toBreakEntity.push_back(bullet);
				};
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


void World::collideEnnemyBullet(Entity* ennemy, Entity* bullet) {
	sf::Vector2f pos = bullet->getPosition();
	if (ennemy->getBoundingBox().contains(pos)) {
		
		audio->ballPong.play();
		toBreakEntity.push_back(bullet);
		toBreakEntity.push_back(ennemy);
		for (int i = 0; i < 12; ++i)
			Game::particlesAt(ennemy->getPosition());
		Game::score += 100;
		Game::shake = 30;
		audio->ballPong.play();

	}
}


void World::collidePlayerEnnemy(Entity* player, Entity* ennemy) {
	sf::Vector2f pos = player->getPosition();
	if (ennemy->getBoundingBox().contains(pos)) {

		audio->ballPong.play();
		toBreakEntity.push_back(player);
		toBreakEntity.push_back(ennemy);
		for (int i = 0; i < 12; ++i)
			Game::particlesAt(ennemy->getPosition());
		Game::score += 100;
		Game::shake = 30;
		audio->ballPong.play();

	}
}


void World::collideEnnemyEnnemy(Entity* A, Entity* B) {
	sf::Vector2f pos = B->getPosition();
	if (A->getBoundingBox().contains(pos)) {
		auto oldPos = B->lastGoodPosition;
		auto box = A->getBoundingBox();
		if ((oldPos.y < box.top) || (oldPos.y > (box.top + box.height))) {
			B->dy = -B->dy;
		}
		else {
			B->dx = -B->dx;
		}


		B->setPosition(B->lastGoodPosition);
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
	if (gothBuffer.loadFromFile("res/loligoth.ogg"))
		goth.setBuffer(gothBuffer);
	goth.play();
	goth.setLoop(true);
}
