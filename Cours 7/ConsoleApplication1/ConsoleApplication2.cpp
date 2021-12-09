#include"imgui.h"
#include "imgui-SFML.h"

#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <vector>
#include <cstdint>
#include <iomanip>
#include <math.h>

#include <SFML/Graphics.hpp>
#include <SFML/Main.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>

#include <algorithm>
#include "Tool.hpp"
#include "Particle.hpp"
#include "NuEntity.hpp"
#include "World.hpp"
#include "Game.hpp"

float clamp(float val, float a, float b) {
	if (val < a)
		val = a;
	if (val > b)
		val = b;
	return val;
}
int main() {

	float ScreenWidth = 1280;
	float ScreenHeight = 720;

	sf::RenderWindow window(sf::VideoMode(ScreenWidth, ScreenHeight), "SFML works!");
	window.setVerticalSyncEnabled(true);
	window.setFramerateLimit(60);

	sf::RectangleShape* shape = new sf::RectangleShape(sf::Vector2f(20,60));
	shape->setFillColor(sf::Color::Green);
	shape->setOutlineColor(sf::Color::Red);
	shape->setOutlineThickness(2);
	NuEntity* player = new NuEntity (shape, 4.0f, 8.0f);
	player->cx = 5;
	player->cy = 5;
	player->syncSprite();
	
	ImGui::SFML::Init(window);


	double tStart = getTimeStamp();
	double tEnterFrame = getTimeStamp();
	double tExitFrame = getTimeStamp();

	bool mouseLeftWasPressed = false;
	double timer = 0.0;

	sf::Vector2i winPos = window.getPosition();


	while (window.isOpen()) {
		sf::Event event;
		double dt = tExitFrame - tEnterFrame;
		tEnterFrame = getTimeStamp();

		while (window.pollEvent(event)) {

			ImGui::SFML::ProcessEvent(window, event);

			if (event.type == sf::Event::Closed)
				window.close();

			if (event.type == sf::Event::MouseButtonPressed) {
				auto cx = event.mouseButton.x / NuEntity::stride;
				auto cy = event.mouseButton.y / NuEntity::stride;
				int pos = -1;
				int idx = 0;

				for (auto& v : Game::walls) {
					if (v.x == cx && v.y == cy)
						pos = idx;
					idx++;
				}

				if (pos < 0)
					Game::walls.push_back(sf::Vector2i(cx, cy));
				else
					Game::walls.erase(Game::walls.begin() + pos);
			}
		}
		

		bool mouseLeftIsPressed = sf::Mouse::isButtonPressed(sf::Mouse::Left);
		bool mouseIsReleased = (!mouseLeftIsPressed && mouseLeftWasPressed);

		sf::Vector2f mousePos = sf::Vector2f(sf::Mouse::getPosition(window));

		if (mouseLeftIsPressed && !mouseLeftWasPressed) {

		}

		
		auto pos = player->getPosition();
		/*float deltaX = dt * 450;
		float deltaY = dt * 450;*/
		bool keyHit = false;
		float max_speed_x = 10;
		float max_speed_y = 10;


		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::Q)) {
			keyHit = true;
			player->dx -= 10;
						
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
			keyHit = true;
			player->dx += 10;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) || sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
			keyHit = true;
			player->dy += 10;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) || sf::Keyboard::isKeyPressed(sf::Keyboard::Z)) {
			keyHit = true;
			player->dy -= 20000;
		}


		player->dx = clamp(player->dx, -10, 10);
		player->dy = clamp(player->dy, -10, 10);

		if (mouseLeftIsPressed)
			mouseLeftWasPressed = true;
		else
			mouseLeftWasPressed = false;


		ImGui::SFML::Update(window, sf::milliseconds((int)(dt * 1000)));
		player->im();
		player->update(dt);

		
		window.clear();


		player->draw(window);
		Game::render(window);

		ImGui::SFML::Render(window);
		window.display();
		tExitFrame = getTimeStamp();

	}
	return 0;
	ImGui::SFML::Shutdown();
}