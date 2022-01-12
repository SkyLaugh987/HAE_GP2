#include "Entity.hpp"
#include "SFML/Graphics/RenderWindow.hpp"

using namespace sf;



void Entity::update(double dt) {
	auto pos = getPosition();
	pos.x += dx * dt;
	pos.y += dy * dt;
	spr->setPosition(pos);
}

void Entity::draw(sf::RenderWindow& win) {
	if (visible)
		win.draw(*spr);
}

void Player::update(double dt) {
	Entity::update(dt);
	
}

void Player::draw(sf::RenderWindow& win) {
	Entity::draw(win);

}


void BulletEntity::create(float _px, float _py, float _dx, float _dy) {
	for (int i = 0; i < px.size(); ++i) {
		if (!alive[i]) {
			px[i] = _px;
			py[i] = _py;
			dx[i] = _dx;
			dy[i] = _dy;
			alive[i] = true;
			lastGoodPosition_B[i] = sf::Vector2f(_px, _py);
			return;
		}
	}
	px.push_back(_px);
	py.push_back(_py);
	dx.push_back(_dx);
	dy.push_back(_dy);
	lastGoodPosition_B.push_back(sf::Vector2f(_px, _py));
	alive.push_back(true);
}

void BulletEntity::update(double dt) {
	for (int i = 0; i < px.size(); ++i) {
		if (alive[i]) {
			px[i] += dx[i] * dt;
			py[i] += dy[i] * dt;
			if (
				(px[i] > 3000) || (px[i] < -100) ||
				(py[i] > 3000) || (py[i] < -100)
				) {
				alive[i] = false;
			}
		}
	}
}
void BulletEntity::draw(sf::RenderWindow& win) {
	int idx = 0;
	const int sz = px.size();
	while (idx < sz) {
		if (alive[idx]) {
			spr->setPosition(px[idx], py[idx]);
			win.draw(*spr);
		}
		idx++;
	}
}