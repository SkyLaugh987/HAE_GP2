#include "SFML/Graphics/RenderWindow.hpp"
#include "Entity.hpp"
#include "World.hpp"

void World::update(double dt) {
	for (auto i : data)
		i->update(dt);	
}

void World::draw(sf::RenderWindow& win) {
	for (auto i : data)
		i->draw(win);
}