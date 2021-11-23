#include "Turtle.hpp"
#include "SFML/Graphics/Rect.hpp"
#include <vector>

Turtle::Turtle() {

	auto& bdy = comps[0];
	bdy = sf::CircleShape(50);
	bdy.setFillColor(sf::Color::Green);
	bdy.setOutlineColor(sf::Color::White);
	bdy.setOutlineThickness(2);
	bdy.setOrigin(48, 48);

	auto& head = comps[1];
	head = sf::CircleShape(20);
	head.setFillColor(sf::Color::Cyan);
	head.setOutlineColor(sf::Color::Black);
	head.setOutlineThickness(1);
	head.setOrigin(bdy.getPosition() + sf::Vector2f(15, 70));

	auto& trail = comps[2];
	trail = sf::CircleShape(10);
	trail.setFillColor(sf::Color::Yellow);
	trail.setOutlineColor(sf::Color::White);
	trail.setOutlineThickness(1);
	trail.setOrigin(bdy.getPosition() + sf::Vector2f(8, -35));

	tex.create(2048, 2048);
	tex.clear(sf::Color(0,0,0,0));
	
}


void Turtle::update(double dt) {

}

void Turtle::draw(sf::RenderWindow& win) {
	tex.display();
	sf::Sprite sprite(tex.getTexture());
	win.draw(sprite);
	for (auto& c : comps)
		win.draw(c, trs);
	win.draw(dir, trs);
	
}
