#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Main.hpp>
#include <SFML/Window.hpp>

#include "SFML/Graphics/RenderWindow.hpp"
#include "SFML/Graphics/CircleShape.hpp"
#include "SFML//Graphics/Sprite.hpp"

enum CmdType {
	Advance,
	Rotate,
	PenDown,
	PenUp
	
};

struct Cmd
{
	CmdType type = Advance;
	float originalValue = 0.0f;
	float currentValue = 0.0f;
	sf::Color col;
	Cmd* next = nullptr;

	Cmd(CmdType t, float value = 0.0) {
		type = t;
		originalValue = value;
	}

	
};

class Turtle {

public:


	sf::CircleShape comps[3];
	sf::RectangleShape dir;
	sf::Transform trs;
	sf::RenderTexture tex;
	
	
	Turtle();
	virtual void update(double dt);
	virtual void draw(sf::RenderWindow& win);

	Cmd* append(Cmd* nu) {
		if ();
	}

	Cmd* applyCmd(Cmd* cmd);
protected: 


};