#pragma once
#include "Entity.hpp"
#include <vector>

class World {
public:
	std::vector<Entity*> data;
	void update(double dt);
	void draw(sf::RenderWindow& win);
};
