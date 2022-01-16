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
	sf::Clock                    clock;
	sf::Time                    elapsedTime;
	float                        dt = 0;
	float						timer = 0;


	sf::Font fArial;
	if(!fArial.loadFromFile("res/arial.ttf"))
		cout << "font not loaded" << endl;

	float ScreenWidth = 1280;
	float ScreenHeight = 720;

	sf::RenderWindow window(sf::VideoMode(ScreenWidth, ScreenHeight), "SFML works!");
	window.setVerticalSyncEnabled(true);
	window.setFramerateLimit(60);
	ImGui::SFML::Init(window);


	///// V A R I A B L E S /////
	sf::CircleShape* ship = new sf::CircleShape(30);
	ship->setFillColor(sf::Color::Cyan);
	ship->setOutlineThickness(2);
	ship->setOutlineColor(sf::Color::Magenta);
	ship->setPosition(800, 600);
	ship->setOrigin(30, 30);

	sf::RectangleShape* canon = new sf::RectangleShape(sf::Vector2f(20, 50));
	canon->setFillColor(sf::Color::Magenta);
	canon->setOutlineThickness(2);
	canon->setOutlineColor(sf::Color::Cyan);
	canon->setOrigin(10, 0);

	int t = 10;
	sf::CircleShape* bullets = new sf::CircleShape(t);
	bullets->setOutlineThickness(2);
	bullets->setFillColor(sf::Color::Blue);
	bullets->setOutlineColor(sf::Color::Yellow);
	bullets->setOrigin(sf::Vector2f(t, t));

	int p = 20;
	sf::CircleShape* ennemies = new sf::CircleShape(p);
	ennemies->setOutlineThickness(2);
	ennemies->setFillColor(sf::Color::Yellow);
	ennemies->setOutlineColor(sf::Color::Red);
	ennemies->setOrigin(sf::Vector2f(p, p));


	sf::CircleShape ptr(8);
	ptr.setFillColor(sf::Color::Cyan);
	ptr.setOrigin(4, 4);


	int score = 0;
	sf::Text scoreTxt;
	scoreTxt.setPosition(48, 16);
	scoreTxt.setFont(fArial);
	scoreTxt.setFillColor(sf::Color::White);
	scoreTxt.setOutlineColor(sf::Color::Magenta);
	scoreTxt.setOutlineThickness(2);
	scoreTxt.setCharacterSize(45);

	
	sf::Text hpTxt;
	hpTxt.setPosition(1032, 16);
	hpTxt.setFont(fArial);
	hpTxt.setFillColor(sf::Color::White);
	hpTxt.setOutlineColor(sf::Color::Magenta);
	hpTxt.setOutlineThickness(2);
	hpTxt.setCharacterSize(45);


	sf::Vector2i winPos = window.getPosition();


	double tStart = getTimeStamp();
	double tEnterFrame = getTimeStamp();
	double tExitFrame = getTimeStamp();

	
	Player* player = new Player(EType::PlayerObject, ship);
	BulletEntity* bullet = new BulletEntity(EType::Bullet, bullets);
	EnnemyEntity* ennemy = new EnnemyEntity(EType::Ennemy, ennemies);


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

	auto vWallShapeBot = new sf::RectangleShape(*vWallShapeTop);

	Entity* topWall = new Entity(EType::Wall, vWallShapeTop);
	Entity* botWall = new Entity(EType::Wall, vWallShapeBot);
	topWall->setPosition(sf::Vector2f(0, 0));
	botWall->setPosition(sf::Vector2f(0, 720));


	Audio audio;


	World world;
	world.data.push_back(leftWall);
	world.data.push_back(rightWall);
	world.data.push_back(topWall);
	world.data.push_back(botWall);
	world.data.push_back(player);
	world.data.push_back(bullet);
	world.data.push_back(ennemy);

	
	bool mouseLeftWasPressed = false;
	Curve c;


	///// W I N D O W   ///   O P E N /////
	while (window.isOpen()) {

		elapsedTime = clock.restart();
		dt = elapsedTime.asSeconds();

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


		///// P L A Y E R /////
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
			if (pos.x - 40 < 0)
				pos.x = 40;

			if (pos.x + 40 > window.getSize().x)
				pos.x = window.getSize().x - 40;

			if (pos.y - 40 < 0)
				pos.y = 40;

			if (pos.y + 40 > window.getSize().y)
				pos.y = window.getSize().y - 40;

			player->setPosition(pos);
		}

		if (player->wasHit == true) {
			ship->setFillColor(sf::Color::Magenta);
		}
		if (player->wasHit == false) {
			ship->setFillColor(sf::Color::Cyan);

		}


		///// S H O O T /////
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

			dxy *= 60.0f * 30;
			bullet->create(pos.x, pos.y, dxy.x, dxy.y);
			audio.laserShot.play();
			
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


		///// E N N E M I E S /////
		
		if (timer >= 5.0f ) {

			for (size_t i = 0; i < 5; i++)
			{
			sf::Vector2f randPos1(rand()%1200, rand()%700);
			sf::Vector2f randPos2(rand() % 1200, rand() % 700);

			auto dir = randPos2 - randPos1  ;
			float dirLen = std::sqrt(dir.x * dir.x + dir.y * dir.y);
			sf::Vector2f dxy(1, 0);

			if (dirLen) {
				dxy = dir / dirLen;
			}

			dxy *= 60.0f * 3;
				
				ennemy->create(randPos1.x, randPos1.y, dxy.x, dxy.y);
			}

			timer = 0;
		}


		scoreTxt.setString("SCORE :" + to_string(Game::score));
		hpTxt.setString("HP :" + to_string(player->playerHP));

		timer += dt;

		ImGui::SFML::Update(window, sf::milliseconds((int)(dt * 1000)));
		window.clear();

		///// U P D A T E /////
		Game::parts.update(dt);
		world.update(dt);



		///// D R A W /////
		world.draw(window);
		if(player->playerHP >= 0)
			window.draw(*canon);

		c.draw(window);
		window.draw(ptr);

		Game::parts.draw(window);

		///// U I /////
		window.draw(scoreTxt);
		window.draw(hpTxt);

		///// S H A K E /////
		if (Game::shake > 0)
			window.setPosition(winPos + sf::Vector2i(0 + rand() % 5, 0 + rand() % 5));
		else
			window.setPosition(winPos);
		Game::shake--;

		ImGui::SFML::Render(window);
		window.display();
		tExitFrame = getTimeStamp();

	}
	return 0;
	ImGui::SFML::Shutdown();
}