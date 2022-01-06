#include "NuEntity.hpp"
#include "SFML/Graphics/Rect.hpp"
#include <vector>
#include"imgui.h"
#include "imgui-SFML.h"
#include"Game.hpp"


/*NuEntity::NuEntity() {

	sf::RectangleShape player(sf::Vector2f(20, 60));
	player.setFillColor(sf::Color::Green);
	player.setOutlineColor(sf::Color::Red);
	player.setOutlineThickness(2);
}*/

inline float clamp(float val, float a, float b) {
	if (val < a)
		val = a;
	if (val > b)
		val = b;
	return val;
}

void NuEntity::syncSprite() {
	xx = (cx + rx) * 16;
	yy = (cy + ry) * 16;
	spr->setPosition(xx, yy);
}
void NuEntity::im() {
	using namespace ImGui;

	bool modified = false;
	modified |= DragFloat("cx", &cx, 1.0);
	modified |= DragFloat("cy", &cy, 1.0);
	modified |= DragFloat("rx", &rx, 0.05);
	modified |= DragFloat("ry", &ry, 0.05);
	modified |= DragFloat("dx", &dx, 0.05);
	modified |= DragFloat("dy", &dy, 0.05);
	modified |= DragFloat("fric_x", &fric_x, 0.05);
	modified |= DragFloat("fric_y", &fric_y, 0.05);
	modified |= DragFloat("gx", &gx, 1.0);


	if (modified) {
		syncSprite();
	}
	Value("px", float(px));
	Value("py", float(py));

}
bool NuEntity:: isColliding(int ccx, int ccy) {
	if (ccx < 0) {
		return true;
	}
	if (ccx > 1280 / stride) {
		return true;
	}
	if (ccy < 0) {
		return true;
	}
	if (ccy > 720 / stride) {
		return true;
	}

	for(auto& vi : Game::walls )
		if ((vi.x == ccx) && (vi.y == ccy)) {
			return true;
		}
	return false;
}
void NuEntity:: update(double dt) {

	

	rx += dx * dt;


	while (rx >= 1) {
		if (isColliding(cx + 1, cy)) {
			dx = 0;
			rx = 0.9;
		}
		else {
			rx--;
			cx++;
		}
	}

	while (rx <= 0) {
		if (isColliding(cx - 1, cy)) {
			dx = 0;
			rx = 0.1;
		}

		else {
			rx++;
			cx--;
		}
	}
	dx *= pow(fric_x, dt * 60);

	
	ry += dy * dt;

	while (ry >= 1) {
		if (isColliding(cx, cy + 1)) {
			dy = 0;
			ry = 0.9;
		}
		else {
			
			ry--;
			cy++;
		}
	}
	while (ry <= 0) {
		if (isColliding(cx, cy - 1)) {
			dy = 0;
			ry = 0.1;
		}
		else {

			ry++;
			cy--;
		}
	}
	dy *= pow(fric_y, dt * 60);
	dy += gx;
	syncSprite();
}


void NuEntity::draw(sf::RenderWindow& win) {
	win.draw(*spr);
}

void NuEntity::SetState(State * state) {
	if (current)
		delete current;
	current = state;
	current->onEnter();
}


void IdleState::onEnter() {
	if (e->spr != nullptr)
		delete e->spr;
	sf::RectangleShape* spr = new sf::RectangleShape(sf::Vector2f(12, 28));
	spr->setFillColor(sf::Color::Red);
	spr->setOutlineThickness(4);
	spr->setOrigin(spr->getSize().x * 0.5, spr->getSize().y);

	spr->setOutlineColor(sf::Color::Yellow);
	e->spr = spr;
}

void IdleState::onUpdate(double dt) {
	float max_speed = 10;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
		e->dx -= max_speed * 0.5;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
		e->dx += max_speed * 0.5;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
		e->dy -= max_speed * 0.5;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
		e->dy += max_speed * 0.5;
	}

	e->dx = clamp(e->dx, -max_speed, max_speed);
	e->dy = clamp(e->dy, -max_speed, max_speed);
}


// je crois que g oublier de faire un truc dans la console xD
// g  tjrs l'anciens player
void WalkState::onEnter() {
	if (e->spr != nullptr)
		delete e->spr;
	sf::RectangleShape* spr = new sf::RectangleShape(sf::Vector2f(12, 28));
	spr->setFillColor(sf::Color::Blue);
	spr->setOutlineThickness(4);
	spr->setOrigin(spr->getSize().x * 0.5, spr->getSize().y);

	spr->setOutlineColor(sf::Color::Magenta);
	e->spr = spr;
}

void WalkState::onUpdate(double dt) {
	float max_speed = 10;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
		e->dx -= max_speed * 0.5;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
		e->dx += max_speed * 0.5;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
		e->dy -= max_speed * 0.5;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
		e->dy += max_speed * 0.5;
	}

	e->dx = clamp(e->dx, -max_speed, max_speed);
	e->dy = clamp(e->dy, -max_speed, max_speed);

	if ((abs(e->dx) < 1) && (abs(e->dy))) {
		e->SetState(new IdleState(e));
	}

}
	void CoverState::onEnter() {
		if (e->spr != nullptr)
			delete e->spr;
		sf::RectangleShape* spr = new sf::RectangleShape(sf::Vector2f(12, 28));
		spr->setFillColor(sf::Color::Red);
		spr->setOutlineThickness(4);
		spr->setOrigin(spr->getSize().x * 0.5, spr->getSize().y);

		spr->setOutlineColor(sf::Color::Black);
		e->spr = spr;
	}

	void CoverState::onUpdate(double dt) {
		/*float max_speed = 10;

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
			e->dx -= max_speed * 0.5;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
			e->dx += max_speed * 0.5;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
			e->dy -= max_speed * 0.5;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
			e->dy += max_speed * 0.5;
		}

		e->dx = clamp(e->dx, -max_speed, max_speed);
		e->dy = clamp(e->dy, -max_speed, max_speed);

		if ((abs(e->dx) < 1) && (abs(e->dy))) {
			e->SetState(new IdleState(e));
		}*/
	}
