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
	ship->setOrigin(20, 20);

	sf::RectangleShape* canon = new sf::RectangleShape(sf::Vector2f(5, 35));
	canon->setFillColor(sf::Color::Magenta);
	canon->setOutlineThickness(2);
	canon->setOutlineColor(sf::Color::Cyan);
	canon->setOrigin(2, 0);

	int ballSize = 6;
	sf::CircleShape* ballShape = new sf::CircleShape(ballSize);
	ballShape->setOrigin(ballSize, ballSize);
	ballShape->setOutlineThickness(2);
	ballShape->setFillColor(sf::Color::Yellow);
	ballShape->setOutlineColor(sf::Color::Red);


	double tStart = getTimeStamp();
	double tEnterFrame = getTimeStamp();
	double tExitFrame = getTimeStamp();


	Player* player = new Player(EType::PlayerObject, ship);
	Entity* ball = new Entity(EType::Ball, ballShape);
	ball->setPosition(player->getPosition());


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
	world.data.push_back(ball);

	while (window.isOpen()) {
		sf::Event event;
		double dt = tExitFrame - tEnterFrame;
		tEnterFrame = getTimeStamp();

		while (window.pollEvent(event)) {

			ImGui::SFML::ProcessEvent(window, event);

			if (event.type == sf::Event::Closed)
				window.close();
		}
		









		ImGui::SFML::Update(window, sf::milliseconds((int)(dt * 1000)));
		window.clear();

		///// U P D A T E /////
		Game::parts.update(dt);
		world.update(dt);

		world.draw(window);

		

		ImGui::SFML::Render(window);
		window.display();
		tExitFrame = getTimeStamp();

	}
	return 0;
	ImGui::SFML::Shutdown();
}