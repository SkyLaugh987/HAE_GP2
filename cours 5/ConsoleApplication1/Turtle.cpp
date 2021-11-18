#include "Turtle.hpp"
#include "SFML/Graphics/Rect.hpp"

Turtle::Turtle() {

	sf::CircleShape body(50);
	body.setFillColor(sf::Color::Green);

	sf::CircleShape head(20);
	head.setFillColor(sf::Color::Cyan);
	
}

void Turtle::update(double dt) {

}
void Turtle::draw(sf::RenderWindow& win) {
	
}
