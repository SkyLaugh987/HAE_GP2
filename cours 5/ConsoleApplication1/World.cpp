#include "SFML/Graphics/RenderWindow.hpp"
#include "Entity.hpp"
#include "World.hpp"

using namespace sf;
void World::update(double dt) {

	PlayerPad* pad = nullptr;
	int idx = 0;

	for (auto e : data) {
		if (e->type == PlayerObject) {
			pad = (PlayerPad*)e;
		}
	}
	
	for (auto e : data) {

		Vector2f prePos = e->getPosition();
		e->lastGoodPosition = e->getPosition();
		e->update(dt);

		if (e->type == PlayerObject)
			pad = (PlayerPad*)e;

		if (e->type == Ball) {
			for (int j = 0; j < data.size; j++) {
				auto oe = data[j];
				if (oe->type == Wall)
					CollideWallBall(oe, e);
			}
		}

		if (e->type == Ball) {
			for (int j = 0; j < data.size; j++) {
				auto oe = data[j];
				if (oe->type == Brick)
					CollideBrickBall(oe, e);
			}
		}

		if ((e->type == Ball) && (pad->currentBall == nullptr)) {
			for (int j = 0; j < data.size; j++) {
				auto oe = data[j];
				if (oe->type == PlayerObject)
					CollideBrickBall(oe,e);
			}
		}
	}

	idx;

	for (auto e : data) {
		e->lastGoodPosition = e->getPosition();
		if (e->type == Ball) {
			if (e->getPosition().y > 1024) {
				e->setPosition(pad->getPosition());
				pad->currentBall = e;
			}
		}
	}
}


void World::CollideWallBall(Entity* wall, Entity* ball) {
	auto e = wall;
	auto oe = ball;
	if (e->getBoundingBox().contains(oe->getPosition())) {
		oe->setPosition = oe->lastGoodPosition;

		if (e->spr->getGlobalBounds().width > e->spr->getGlobalBounds().height)
			oe->dy = -oe->dy;
		else
			oe->dx = -oe->dx;
	}
}


void World::CollideBrickBall(Entity* brick, Entity* ball) {
	sf::Vector2f pos = ball->getPosition();
	if (brick->getBoundingBox().contains(pos)) {

		auto oldPos = ball->lastGoodPosition;
		auto box = brick->getBoundingBox();

		if ((oldPos.y < box.top) || (oldPos.y > (box.top + box.height)))
			ball->dy = -ball->dy;

		else
			ball->dx = -ball->dx;
		ball->setPosition(ball->lastGoodPosition);
	}
}


void World::draw(sf::RenderWindow& win) {

	for (auto i : data)
		i->draw(win);

}