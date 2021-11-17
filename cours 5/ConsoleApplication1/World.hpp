#pragma once
#include "Entity.hpp"
#include <vector>

class World {
public:
	std::vector<Entity*> data;
	void update(double dt);
	void draw(sf::RenderWindow& win);

	void CollideWallBall(Entity* wall, Entity* ball);
	void CollideBrickBall(Entity* brick, Entity* ball);
};
