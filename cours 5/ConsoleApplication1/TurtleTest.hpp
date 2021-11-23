#pragma once
#include "SFML/Graphics/Shape.hpp"
#include "SFML/Graphics/Rect.hpp"
#include "SFML/Graphics/RenderWindow.hpp"



class TurtleTest {

public:
	sf::Shape*		body = nullptr;
	sf::Shape*		head = nullptr;


	bool visible = true;
	float dx = 0.0f;
	float dy = 0.0f;

	sf::Vector2f	lastGoodPosition;

	TurtleTest(sf::Shape* _body, sf::Shape* _head ) {
		body = _body;
		head = _head;
	}

	~TurtleTest() {
		if (body && head) {
			delete body, head;
			body = nullptr;
			head = nullptr;
		}
	}

	sf::Vector2f getPosition() {
		return body->getPosition();
		return head->getPosition();
	}

	void setPosition(sf::Vector2f pos) {
		return body->setPosition(pos);
		return head->setPosition(pos);

	}

	sf::FloatRect getBoundingBox() {
		return body->getGlobalBounds();
		return head->getGlobalBounds();

	}

	virtual void update(double dt);
	virtual void draw(sf::RenderWindow& win);
};