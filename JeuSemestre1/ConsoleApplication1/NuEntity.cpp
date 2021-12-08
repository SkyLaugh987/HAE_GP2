#include "NuEntity.hpp"
#include "SFML/Graphics/Rect.hpp"
#include <vector>
#include"imgui.h"
#include "imgui-SFML.h"


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
	if (modified) {
		syncSprite();
	}
	Value("px", float(px));
	Value("py", float(py));

}

void NuEntity:: update(double dt) {


	dx *= fric;
	rx = dx * dt;


	while (rx > 1) {
		rx--;
		cx++;
	}
	while (rx < 0) {
		rx++;
		cx--;
	}

	/*dy *= fric;
	ry = dy * dt;

	while (ry > 1) {
		ry--;
		cy++;
	}
	while (ry < 0) {
		ry++;
		cy--;
	}*/

	syncSprite();
}


void NuEntity::draw(sf::RenderWindow& win) {
	win.draw(*spr);
}
