#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Main.hpp>
#include <SFML/Window.hpp>

#include "SFML/Graphics/RenderWindow.hpp"
#include "SFML/Graphics/CircleShape.hpp"
#include "SFML//Graphics/Sprite.hpp"

class NuEntity;

class State {
public:
	NuEntity* e = nullptr;

	virtual void onEnter() = 0;
	virtual void onUpdate(double dt) = 0;
};


class IdleState : public State {
public:
	IdleState(NuEntity*_e) {
		e = _e;
	};

	virtual void onEnter();
	virtual void onUpdate(double dt);
};

class WalkState : public State {
public: 
	WalkState(NuEntity*_e) {
		e = _e;
	}

	virtual void onEnter();
	virtual void onUpdate(double dt); //c shlag de juste refaire  mais bon 
};

class RunState : public State {
public:
	RunState(NuEntity* _e) {
		e = _e;
	};

	virtual void onEnter();
	virtual void onUpdate(double dt);
};

class CoverState : public State {
public:
	CoverState(NuEntity*_e) {
		e = _e;
	};

	virtual void onEnter();
	virtual void onUpdate(double dt);
};

class NuEntity {
public:

	sf::Shape*		 spr = nullptr;
	float fric_x = 0.98f;
	float fric_y = 0.98f;

	sf::Vector2f lastGoodPosition;
	
	///////////////////
	//Coordonnées
	float		 cx = 0;
	float		 cy = 0;
	float	 rx=0;
	float	 ry=0;
	double	 px=0;
	double	 py=0;
			   
	///////////////////
	//Coordonnées res
	float xx;
	float yy;

	float dx = 0;
	float dy = 0;

	float gx = 9.8f;
	const  static int stride = 32;

	State*			current = nullptr;

	NuEntity(sf::Shape* _spr, float _cx, float _cy) {
		spr = _spr;
		cx = _cx;
		cy = _cy;
		syncSprite();
	}

	~NuEntity() {
		if (spr) {
			delete spr;
			spr = nullptr;
		}
	}

	void SetState(State * state);
	void syncSprite();

	void im();

	sf::Vector2f getPosition() {
		return spr->getPosition();
	}

	void setPosition(sf::Vector2f pos) {
		return spr->setPosition(pos);
	}

	bool isColliding(int _cx, int _cy);
	virtual void update(double dt);
	virtual void draw(sf::RenderWindow& win);

};