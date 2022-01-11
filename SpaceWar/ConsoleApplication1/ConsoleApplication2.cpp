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
#include "Entity.hpp"
#include "Game.hpp"
#include "World.hpp"
#include "Curve.hpp"




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
	ImGui::SFML::Init(window);


	sf::CircleShape* ship = new sf::CircleShape(40);
	ship->setFillColor(sf::Color::Cyan);
	ship->setOutlineThickness(2);
	ship->setOutlineColor(sf::Color::Magenta);
	ship->setPosition(800, 600);
	ship->setOrigin(40, 40);

	sf::RectangleShape* canon = new sf::RectangleShape(sf::Vector2f(20, 50));
	canon->setFillColor(sf::Color::Magenta);
	canon->setOutlineThickness(2);
	canon->setOutlineColor(sf::Color::Cyan);
	canon->setOrigin(10, 0);

	sf::CircleShape ptr(8);
	ptr.setFillColor(sf::Color::Cyan);
	ptr.setOrigin(4, 4);


	double tStart = getTimeStamp();
	double tEnterFrame = getTimeStamp();
	double tExitFrame = getTimeStamp();

	
	Player* player = new Player(EType::PlayerObject, ship);
	BulletEntity bullets;


	auto vWallShapeLeft = new sf::RectangleShape(sf::Vector2f(16, 2048));
	vWallShapeLeft->setOrigin(8, 0);
	vWallShapeLeft->setFillColor(sf::Color::Green);

	auto vWallShapeRight = new sf::RectangleShape(*vWallShapeLeft);

	Entity* leftWall = new Entity(EType::Wall, vWallShapeLeft);
	Entity* rightWall = new Entity(EType::Wall, vWallShapeRight);
	rightWall->setPosition(sf::Vector2f(1280, 0));

	auto vWallShapeTop = new sf::RectangleShape(sf::Vector2f(2048, 16));
	vWallShapeTop->setOrigin(0, 8);
	vWallShapeTop->setFillColor(sf::Color::Green);

	Entity* topWall = new Entity(EType::Wall, vWallShapeTop);
	topWall->setPosition(sf::Vector2f(0, 0));

	World world;
	world.data.push_back(topWall);
	world.data.push_back(rightWall);
	world.data.push_back(leftWall);
	world.data.push_back(player);


	
	bool mouseLeftWasPressed = false;
	Curve c;


	while (window.isOpen()) {
		sf::Event event;
		double dt = tExitFrame - tEnterFrame;
		tEnterFrame = getTimeStamp();

		while (window.pollEvent(event)) {

			ImGui::SFML::ProcessEvent(window, event);

			if (event.type == sf::Event::Closed)
				window.close();
		}
		
		auto pos = player->getPosition();
		float deltaX = dt * 160 * 6;
		float deltaY = dt * 160 * 6;
		bool keyHit = false;


		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::Q)) {
			pos.x -= deltaX;
			keyHit = true;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
			pos.x += deltaX;
			keyHit = true;
		}if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::Z)) {
			pos.y -= deltaX;
			keyHit = true;
		}if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
			pos.y += deltaX;
			keyHit = true;
		}


		if (keyHit) {
			if (pos.x < 0)
				pos.x = 0;
			if (pos.x > window.getSize().x)
				pos.x = window.getSize().x;
			player->setPosition(pos);
		}


		bool mouseLeftIsPressed = sf::Mouse::isButtonPressed(sf::Mouse::Left);
		bool mouseIsReleased = (!mouseLeftIsPressed && mouseLeftWasPressed);


		sf::Vector2f mousePos = sf::Vector2f(sf::Mouse::getPosition(window));


		if (false) {
			if (mouseIsReleased) c.addPoint(mousePos);
			if (sf::Mouse::isButtonPressed(sf::Mouse::Right)) c.clear();
		}

		if (mouseLeftIsPressed && !mouseLeftWasPressed) {
			auto pos = canon->getPosition();
			auto dir = mousePos - pos;
			float dirLen = std::sqrt(dir.x * dir.x + dir.y * dir.y);
			sf::Vector2f dxy(1, 0);

			if (dirLen) {
				dxy = dir / dirLen;
			}

			dxy *= 60.0f * 10;
			bullets.create(pos.x, pos.y, dxy.x, dxy.y);

			
		}


		if (mouseLeftIsPressed)
			mouseLeftWasPressed = true;
		else
			mouseLeftWasPressed = false;


		sf::Vector2f characterToMouse(
			mousePos.y - ship->getPosition().y,
			mousePos.x - ship->getPosition().x);

		float radToDeg = 57.2958;
		float angleC2M = atan2(characterToMouse.y, characterToMouse.x);
		canon->setRotation(-angleC2M * radToDeg);
		canon->setPosition(ship->getPosition());
		ptr.setPosition(mousePos);






		ImGui::SFML::Update(window, sf::milliseconds((int)(dt * 1000)));
		window.clear();

		///// U P D A T E /////
		Game::parts.update(dt);
		world.update(dt);
		bullets.update(dt);


		///// D R A W /////
		world.draw(window);
		bullets.draw(window);
		window.draw(*canon);

		c.draw(window);
		window.draw(ptr);

		ImGui::SFML::Render(window);
		window.display();
		tExitFrame = getTimeStamp();

	}
	return 0;
	ImGui::SFML::Shutdown();
}