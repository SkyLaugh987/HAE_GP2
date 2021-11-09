#include "Projectile.hpp"

Projectile::Projectile() {
	p = sf::CircleShape(20);
	p.setOutlineThickness(4);
	p.setFillColor(sf::Color::Blue);
	p.setOutlineColor(sf::Color::White);
	p.setOrigin(sf::Vector2f(40, 40));
}

void Projectile::create(float _px, float _py, float _dx, float _dy) {
	for (int i = 0; i < px.size(); i++)
	{
		if (!alive[i]) {
			px[i] = _px;
			py[i] = _py;
			dx[i] = _dx;
			dy[i] = _dy;
			alive[i] = true;
			return;
		}
	}
	px.push_back(_px);
	py.push_back(_py);
	dx.push_back(_dx);
	dy.push_back(_dy);
	alive.push_back(true);

}


void Projectile:: update(double dt) {
	for (int i = 0; i < px.size(); i++)
	{
		if (alive[i]) {
			px[i] = dx[i] * dt;
			py[i] = dy[i] * dt;
			if (
				px[i] > 3000 || (px[i] < -100) ||
				py[i] > 3000 || (py[i] < -100)
				) {
				alive[i] = false;
			}
		}
	}
}

void Projectile::draw(sf::RenderWindow& win) {
	int idx = 0;
	const int sz = px.size();
	while (idx < sz) {
		if (alive[idx]) {
			p.setPosition(px[idx], py[idx]);
		}
	}
	win.draw(p);
}