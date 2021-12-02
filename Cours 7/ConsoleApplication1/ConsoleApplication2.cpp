#include"imgui.h"
#include "imgui-SFML.h"

#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include <SFML/Graphics.hpp>
#include <SFML/Main.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>

#include <algorithm>
#include "Tool.hpp"
#include "Particle.hpp"
#include "NuEntity.hpp"
#include "World.hpp"


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

	
	
	ImGui::SFML::Init(window);


	double tStart = getTimeStamp();
	double tEnterFrame = getTimeStamp();
	double tExitFrame = getTimeStamp();
	sf::Vector2i winPos = window.getPosition();


	while (window.isOpen()) {
		sf::Event event;
		double dt = tExitFrame - tEnterFrame;
		tEnterFrame = getTimeStamp();

		while (window.pollEvent(event)) {
			ImGui::SFML::ProcessEvent(window, event);
			if (event.type == sf::Event::Closed)
				window.close();
		}
		
		
		//auto pos = shape->getPosition();
		float deltaX = dt * 450;
		float deltaY = dt * 450;
		bool keyHit = false;


		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::Q)) {
			keyHit = true;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
			keyHit = true;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) || sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
			keyHit = true;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) || sf::Keyboard::isKeyPressed(sf::Keyboard::Z)) {
			keyHit = true;
		}
		if (keyHit) {
			

		}
		ImGui::SFML::Update(window, sf::milliseconds((int)(dt * 1000)));
		player->im();
		player->update(dt);

		
		window.clear();
		player->draw(window);
		ImGui::SFML::Render(window);
		window.display();
		tExitFrame = getTimeStamp();

	}
	return 0;
	ImGui::SFML::Shutdown();
}