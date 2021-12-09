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
