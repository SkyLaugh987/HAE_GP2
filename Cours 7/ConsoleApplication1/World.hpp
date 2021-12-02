#pragma once
#include "NuEntity.hpp"
#include <vector>

class World {
public:

	std::vector<NuEntity*> data;
	void update(double dt);
	void draw(sf::RenderWindow& win);

	std::vector<NuEntity*> ToBreak;


};
