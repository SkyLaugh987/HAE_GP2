#pragma once
#include <vector>
#include "Entity.hpp"
#include "SFML/Audio/Sound.hpp"
#include "SFML/Audio/SoundBuffer.hpp"

class Audio {
public:
	Audio();
	sf::Sound		ballPong;
	sf::SoundBuffer ballPongBuffer;

	sf::Sound		goth;
	sf::SoundBuffer gothBuffer;
};

class World {
public:
	Audio*					audio = nullptr;
	std::vector<Entity*>	data;

	void update(double dt);
	void draw(sf::RenderWindow& win);

	void collideWallBullet(Entity* wall, BulletEntity* ball);
	void collideWallEnnemy(Entity* wall, EnnemyEntity* ball);
	void collideEnnemyBullet(Entity* wall, Entity* ball);
	void collidePlayerEnnemy(Entity* player, Entity* ennemy);
	void collideEnnemyEnnemy(Entity* A, Entity* B);

	std::vector<Entity*> toBreakEntity;
};