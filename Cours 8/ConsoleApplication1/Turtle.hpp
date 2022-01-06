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
	PenUp,
	PenColor
};

struct Cmd
{
	CmdType type = Advance;
	float timer = 0.0f;
	float maxDuration = 0.333f;
	float value = 0.0f;
	float originalValue = 0.0f;
	sf::Color col;
	Cmd* next = nullptr;

	Cmd(CmdType t, float _value = 0.0) {
		type = t;
		value = _value;
		originalValue = _value;
	}

	Cmd* append(Cmd* nu) {
		if (next == nullptr)
			next = nu;
		else
			next = next->append(nu);
		return this;
	};

	Cmd* popFirst() {
		Cmd* nu = next;
		delete this;
		return nu;
	};
};

class Turtle {

public:


	sf::CircleShape comps[3];
	sf::RectangleShape dir;
	sf::RenderTexture tex;
	
	bool penEnabled = false;
	sf::Color penColor;

	Turtle();
	void reset();
	virtual void update(double dt);
	virtual void draw(sf::RenderWindow& win);


	void write(FILE* f, Cmd* cmd);
	void appendCmd(Cmd* cmd);
	void translate(float value) { appendCmd(new Cmd(Advance, value)); };
	void rotate(float value) { appendCmd(new Cmd(Rotate, value)); };


	void setPen(bool value) {
		
		if (value)
			appendCmd(new Cmd(PenDown));
		else
			appendCmd(new Cmd(PenUp));
	};


	void setPenColor(sf::Color col) {

		auto colCmd = new Cmd(PenColor);
		colCmd->col = col;
		appendCmd(colCmd);
	};


	void writeCommands(const char* fname);
	sf::Vector2f getPosition() { return trs.transformPoint(sf::Vector2f()); };
	Cmd* cmds = nullptr;

protected: 
	sf::Transform trs;
	Cmd* applyCmd(Cmd* cmd);
	Cmd* applyCmdInterp(Cmd* cmd, double dt);
};

