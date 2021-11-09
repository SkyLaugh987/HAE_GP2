#pragma once
#include "SFML/Graphics/RenderWindow.hpp"
#include "SFML/Graphics/CircleShape.hpp"

class Projectile {
public:
	sf::CircleShape p;
	
	std::vector<float> px;
	std::vector<float> py;

	std::vector<float> dx;
	std::vector<float> dy;

	std::vector<bool> alive;

	Projectile();

	void create(float px, float py, float dx, float dy);
	void update(double dt);
	void draw(sf::RenderWindow& win);
};