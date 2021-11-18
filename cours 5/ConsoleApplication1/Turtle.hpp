#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Main.hpp>
#include <SFML/Window.hpp>

#include "SFML/Graphics/RenderWindow.hpp"
#include "SFML/Graphics/CircleShape.hpp"
#include "SFML//Graphics/Sprite.hpp"

class Turtle {

public:


	sf::CircleShape body;
	sf::CircleShape head;
	
	sf::Vector2f getPosition() {
		return head.getPosition();
		return body.getPosition();
	}

	void setPosition(sf::Vector2f pos) {
		return head.setPosition(pos);
		return body.setPosition(pos);
	}
	virtual void update(double dt);
	virtual void draw(sf::RenderWindow& win);
};