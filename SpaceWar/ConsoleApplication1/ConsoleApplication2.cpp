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


	double tStart = getTimeStamp();
	double tEnterFrame = getTimeStamp();
	double tExitFrame = getTimeStamp();




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
		ImGui::SFML::Render(window);
		window.display();
		tExitFrame = getTimeStamp();

	}
	return 0;
	ImGui::SFML::Shutdown();
}