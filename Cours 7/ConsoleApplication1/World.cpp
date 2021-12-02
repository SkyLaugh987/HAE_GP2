#include "SFML/Graphics/RenderWindow.hpp"
#include "Entity.hpp"
#include "NuEntity.hpp"
#include "World.hpp"

using namespace sf;
void World::update(double dt) {

}


void World::draw(sf::RenderWindow& win) {

	for (auto i : data)
		i->draw(win);

}