#pragma once

#include "SFML/Graphics/RenderWindow.hpp"
#include "SFML/Graphics/CircleShape.hpp"
#include "SFML//Graphics/Sprite.hpp"


class NuEntity {
public:

	sf::Shape		 spr;


	sf::Vector2f lastGoodPosition;
	
	///////////////////
	//Coordonn�es
	int cx;
	int cy;
	float xr;
	float yr;

	///////////////////
	//Coordonn�es res
	float xx;
	float yy;

	float dx;
	float dy;

	void update();
};