#pragma once
#include "SFML/Graphics/Shape.hpp"
#include "SFML/Graphics/Rect.hpp"
#include "SFML/Graphics/RenderWindow.hpp"
#include "SFML/Graphics/CircleShape.hpp"

enum EType {
	PlayerObject,
	Brick,
	Wall,
	Bullet,
};

class Entity {
public:
	sf::Shape*		spr = nullptr;
	EType			type;

	bool visible = true;
	float dx = 0.0f;
	float dy = 0.0f;

	sf::Vector2f	lastGoodPosition;

	Entity(EType _type, sf::Shape* _spr) {
		type = _type;
		spr = _spr;
	}
	Entity();

	~Entity() {
		if (spr) {
			delete spr;
			spr = nullptr;
		}
	}

	sf::Vector2f getPosition() {
		return spr->getPosition();
	}

	void setPosition(sf::Vector2f pos) {
		return spr->setPosition(pos);
	}

	sf::FloatRect getBoundingBox() {
		return spr->getGlobalBounds();
	}

	virtual void update(double dt);
	virtual void draw(sf::RenderWindow& win);
};

class Player : public Entity {
public:

	

	Player(EType type, sf::Shape* _spr) : Entity(type, _spr) {

	}


	virtual void update(double dt);
	virtual void draw(sf::RenderWindow& win);
};

class BulletEntity : public Entity {
public:

	sf::CircleShape b;

	std::vector<float>	px;
	std::vector<float>	py;

	std::vector<float>	dx;
	std::vector<float>	dy;

	std::vector<bool>	alive;

	BulletEntity();

	void create(float px, float py, float dx, float dy);
	void update(double dt);

	void draw(sf::RenderWindow& win);

};