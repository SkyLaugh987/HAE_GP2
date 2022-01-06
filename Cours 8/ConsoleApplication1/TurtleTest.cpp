#include "TurtleTest.hpp"
#include "SFML/Graphics/RenderWindow.hpp"

using namespace sf;

void TurtleTest::update(double dt) {
	auto pos = getPosition();
	pos.x += dx * dt;
	pos.y += dy * dt;
	body->setOrigin(48, 48);
	head->setOrigin(cos(3.14*0.4) * 48 + 8, sin(3.14 * 0.4) * 48 + 8);
	body->setPosition(pos);

}

void TurtleTest::draw(sf::RenderWindow& win) {
	if (visible) {
		win.draw(*body);
		win.draw(*head);
	}
}