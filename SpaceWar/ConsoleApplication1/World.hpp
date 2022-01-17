#pragma once
#include <vector>
#include "Entity.hpp"
#include "SFML/Audio/Sound.hpp"
#include "SFML/Audio/SoundBuffer.hpp"
#include "SFML/Audio/Music.hpp"

class Audio {
public:
	Audio();

	sf::Sound		hitSound;
	sf::SoundBuffer hitSoundBuffer;

	sf::Sound		killSound;
	sf::SoundBuffer killSoundBuffer;

	sf::Sound		laserShot;
	sf::SoundBuffer laserShotBuffer;

	sf::Sound		healthPackSound;
	sf::SoundBuffer healthPackSoundBuffer;

	sf::Sound		lostSound;
	sf::SoundBuffer lostSoundBuffer;

	sf::Music		mix;
};

class World {
public:
	Audio*					audio = nullptr;
	std::vector<Entity*>	data;

	void update(double dt);
	void draw(sf::RenderWindow& win);

	void collideWallBullet(Entity* wall, BulletEntity* ball);
	void collideWallEnnemy(Entity* wall, EnnemyEntity* ball);
	void collideEnnemyBullet(EnnemyEntity* wall, BulletEntity* ball);
	void collidePlayerEnnemy(Player* player, EnnemyEntity* ennemy);
	void collideEnnemyEnnemy(EnnemyEntity* A, EnnemyEntity* B);
	//void collideHealthPackPlayer( Player* player, HealthPackEntity* pack);

	std::vector<Entity*> toBreakEntity;
};