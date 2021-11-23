#include "Turtle.hpp"
#include "SFML/Graphics/Rect.hpp"

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
	head.setOrigin(cos(3.14 * 0.4) * 50 + 20, sin(3.14 * 0.4) * 50 + 20);
	
}

void Turtle::update(double dt) {

}

void Turtle::draw(sf::RenderWindow& win) {

	for (auto& c : comps)
		win.draw(c, trs);
	win.draw(dir, trs);
}
