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


///// P L A Y E R /////
void Player::update(double dt) {
	timerHit += dt;
	Entity::update(dt);
	if (timerHit < 3.0f)
		wasHit = true;
	else wasHit = false;

	
}

void Player::draw(sf::RenderWindow& win) {

	Entity::draw(win);

}


///// B U L L E T /////
void BulletEntity::create(float _px, float _py, float _dx, float _dy) {
	for (int i = 0; i < px.size(); ++i) {
		if (!alive[i]) {
			px[i] = _px;
			py[i] = _py;
			dx[i] = _dx;
			dy[i] = _dy;
			alive[i] = true;
			hit[i] = false;
			rebound[i] = 0;
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
	hit.push_back(false);
	rebound.push_back(0);
}

void BulletEntity::update(double dt) {
	for (int i = 0; i < px.size(); ++i) {
		if (alive[i]) {
			px[i] += dx[i] * dt;
			py[i] += dy[i] * dt;
			if ((rebound[i] >= 2) || 
				(px[i] > 3000) || 
				(px[i] < -100) ||
				(py[i] > 3000) || 
				(py[i] < -100)) {
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

///// E N E M Y /////
void EnnemyEntity::create(float _px, float _py, float _dx, float _dy) {
	for (int i = 0; i < px.size(); ++i) {
		if (!alive[i]) {
			px[i] = _px;
			py[i] = _py;
			dx[i] = _dx;
			dy[i] = _dy;
			alive[i] = true;
			lastGoodPosition_E[i] = sf::Vector2f(_px, _py);
			return;
		}
	}
	px.push_back(_px);
	py.push_back(_py);
	dx.push_back(_dx);
	dy.push_back(_dy);
	lastGoodPosition_E.push_back(sf::Vector2f(_px, _py));
	alive.push_back(true);
}


void EnnemyEntity::update(double dt) {
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


void EnnemyEntity::draw(sf::RenderWindow& win) {
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


///// H E A L T H   P A C K /////
/*void HealthPackEntity::create(float _px, float _py) {
	for (int i = 0; i < px.size(); ++i) {
		if (!alive[i]) {
			px[i] = _px;
			py[i] = _py;

			alive[i] = true;
			lastGoodPosition_H[i] = sf::Vector2f(_px, _py);
			return;
		}
	}
	px.push_back(_px);
	py.push_back(_py);

	alive.push_back(true);
	lastGoodPosition_H.push_back(sf::Vector2f(_px, _py));

}

void HealthPackEntity::update(double dt) {
	Entity::update(dt);
}

void HealthPackEntity::draw(sf::RenderWindow& win) {
	int idx = 0;
	const int sz = px.size();
	while (idx < sz) {
		if (alive[idx]) {
			spr->setPosition(px[idx], py[idx]);
			win.draw(*spr);
		}
		idx++;
	}
}*/