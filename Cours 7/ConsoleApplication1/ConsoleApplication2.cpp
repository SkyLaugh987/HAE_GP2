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
#include "Entity.hpp"


int main() {

	float ScreenWidth = 1280;
	float ScreenHeight = 720;

	sf::RenderWindow window(sf::VideoMode(ScreenWidth, ScreenHeight), "SFML works!");
	window.setVerticalSyncEnabled(true);
	window.setFramerateLimit(60);

	sf::RectangleShape player(sf::Vector2f(20, 60));
	player.setFillColor(sf::Color::Green);



	double tStart = getTimeStamp();
	double tEnterFrame = getTimeStamp();
	double tExitFrame = getTimeStamp();
	sf::Vector2i winPos = window.getPosition();

	while (window.isOpen()) {
		sf::Event event;
		double dt = tExitFrame - tEnterFrame;
		tEnterFrame = getTimeStamp();

		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed)
				window.close();
		}
		window.clear();


		window.draw(player);
		window.display();
		tExitFrame = getTimeStamp();

	}
	return 0;
}