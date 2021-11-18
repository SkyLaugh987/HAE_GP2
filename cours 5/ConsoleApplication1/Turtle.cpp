#include "Turtle.hpp"
#include "SFML/Graphics/Rect.hpp"

Turtle::Turtle() {

	sf::CircleShape body(50);
	body.setFillColor(sf::Color::Green);
	body.setOrigin(sf::Vector2f(25,25));
	sf::Vector2f bdyOrigin = body.getOrigin();
	sf::CircleShape head(20);
	head.setFillColor(sf::Color::Cyan);
	head.setOrigin(bdyOrigin);
	head.setPosition(sf::Vector2f(25, 0));
	
}

void Turtle::update(double dt) {

}
void Turtle::draw(sf::RenderWindow& win) {
	win.draw(body);
	win.draw(head);
}
