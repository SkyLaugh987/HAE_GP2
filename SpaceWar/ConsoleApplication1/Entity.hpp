#pragma once
#include "SFML/Graphics/Shape.hpp"
#include "SFML/Graphics/Rect.hpp"
#include "SFML/Graphics/RenderWindow.hpp"
#include "SFML/Graphics/CircleShape.hpp"

enum EType {
	PlayerObject,
	Ennemy,
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


///// P L A Y E R /////
class Player : public Entity {
public:

	bool hit  = false;
	int HP = 5;
	float						timer = 0;

	Player(EType type, sf::Shape* _spr) : Entity(type, _spr) {

	}


	virtual void update(double dt);
	virtual void draw(sf::RenderWindow& win);
};


///// B U L L E T /////
class BulletEntity : public Entity {
public:

	float radius = 10;

	std::vector<float>	px;
	std::vector<float>	py;

	std::vector<float>	dx;
	std::vector<float>	dy;

	std::vector<sf::Vector2f>	lastGoodPosition_B;

	std::vector<bool>	alive;
	std::vector<bool>	hit;

	BulletEntity(EType _type, sf::Shape* b) : Entity(type, spr) {
		type = _type;
		spr = b;
	}

	void create(float px, float py, float dx, float dy);
	void update(double dt);

	void draw(sf::RenderWindow& win);

};


////// E N  E M Y /////
class EnnemyEntity : public Entity {
public:

	float radius = 10;

	std::vector<float>	px;
	std::vector<float>	py;

	std::vector<float>	dx;
	std::vector<float>	dy;

	std::vector<sf::Vector2f>	lastGoodPosition_E;

	std::vector<bool>	alive;



	EnnemyEntity(EType _type, sf::Shape* _e) : Entity(type, spr) {
		type = _type;
		spr = _e;
	}

	void create(float px, float py, float dx, float dy);
	void update(double dt);

	void draw(sf::RenderWindow& win);

};