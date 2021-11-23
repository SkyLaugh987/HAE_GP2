#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Main.hpp>
#include <SFML/Window.hpp>

#include "SFML/Graphics/RenderWindow.hpp"
#include "SFML/Graphics/CircleShape.hpp"
#include "SFML//Graphics/Sprite.hpp"

class Turtle {

public:


	sf::CircleShape comps[2];
	sf::RectangleShape dir;
	sf::Transform trs;
	
	
	Turtle();
	virtual void update(double dt);
	virtual void draw(sf::RenderWindow& win);

	/*sf::Vector2f getRotation() {
		for (auto& c : comps)
		{
			return c.getRotation();
		}
	}
	
	void setRotation(sf::Vector2f rot) {
		for (auto& c : comps) {

			return c.setRotation(rot);
		}
	}
	*/
	sf::Vector2f getPosition() {
		for (auto& c : comps) {

			return c.getPosition();
		}
	}
	
	void setPosition(sf::Vector2f pos) {
		for (auto& c : comps) {

			return c.setPosition(pos);
		}
	}

};