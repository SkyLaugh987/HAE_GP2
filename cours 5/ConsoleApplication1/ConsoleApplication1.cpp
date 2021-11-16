
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include "Int64Array.hpp"
#include "Tool.hpp"
#include "List.hpp"
#include <algorithm>
#include <vector>
#include "Tree.hpp"

#include <SFML/Graphics.hpp>
#include <SFML/Main.hpp>
#include <SFML/Window.hpp>

#include "Curve.hpp"
#include "Bullet.hpp"
#include "Entity.hpp"
#include "World.hpp"

float catmull(float p0 , float p1 , float p2,float p3 , float t ) {
	auto q = 2.0f * p1;
	auto t2 = t * t;

	q += (-p0 + p2) * t;
	q += (2.0f * p0 - 5.0f * p1 + 4.0f * p2 - p3) * t2;
	q += (-p0 + 3 * p1 - 3 * p2 + p3) * t2 * t;

	return 0.5f * q;
}
// -----------------------------------------------------Moutain-----------------------------------
void drawMountain(sf::RenderWindow& window) {

	sf::VertexArray arr;
	arr.setPrimitiveType(sf::LineStrip);
	sf::Color col = sf::Color::Green;

	float baseline = 350;

	sf::Vector2f a(0, baseline+50);
	sf::Vector2f b(400, baseline-150);
	sf::Vector2f c(1100, baseline +32);
	sf::Vector2f d(window.getSize().x, baseline);
	col.a = 100;

	col = sf::Color::Magenta;
	for (int i = 0; i < 256; ++i) {
		float t = 1.0f * i / 256;
		float x = catmull(a.x, a.x, b.x, c.x, t);
		float y = catmull(a.y, a.y, b.y, c.y, t);
		arr.append(sf::Vertex(sf::Vector2f(x, y), col));
	}
	for (int i = 0; i < 256; ++i) {
		float t = 1.0f * i / 256;
		float x = catmull(a.x, b.x, c.x, d.x, t);
		float y = catmull(a.y, b.y, c.y, d.y, t);
		arr.append(sf::Vertex( sf::Vector2f(x,y), col));
	}

	for (int i = 0; i < 256; ++i) {
		float t = 1.0f * i / 256;
		float x = catmull(b.x, c.x, d.x, d.x, t);
		float y = catmull(b.y, c.y, d.y, d.y, t);
		arr.append(sf::Vertex(sf::Vector2f(x, y), col));
	}
	window.draw(arr);
}
//----------------------------------------------------------------------Ground----------------------------------------------------
void drawGround(sf::RenderWindow& window) {
	sf::VertexArray arr;
	arr.setPrimitiveType(sf::LineStrip);
	sf::Color col = sf::Color::Red;

	float baseline = 600+60;

	sf::Vector2f a(0, baseline);
	sf::Vector2f b(window.getSize().x, baseline);

	arr.append(sf::Vertex(a, col));
	arr.append(sf::Vertex(b, col));

	window.draw(arr);
}

int main()
{
	float ScreenWidth = 600;
	float ScreenHeight = 720;

	sf::RenderWindow window(sf::VideoMode(ScreenWidth, ScreenHeight), "SFML works!");
	window.setVerticalSyncEnabled(true);
	window.setFramerateLimit(60);

	sf::RectangleShape* player = new sf::RectangleShape(sf::Vector2f(200, 20));
	player->setFillColor(sf::Color::Green);
	player->setPosition(300, 600);
	player->setOrigin(100, 0);
	sf::FloatRect nextPos;

	// Wall
	sf::RectangleShape wall;

	////////// GUN /////////////
	/*sf::RectangleShape gun(sf::Vector2f(8, 32));
	gun.setFillColor(sf::Color(	0xFF,0x00,0x00));
	gun.setOrigin(4,0);
	gun.setPosition(800, 600);*/

	////////////////// TEXT /////////////////
	sf::Font fArial;
	if (!fArial.loadFromFile("res/arial.ttf"))	
		cout << "font not loaded" << endl;
	sf::Text tDt;
	tDt.setFont(fArial);
	tDt.setFillColor(sf::Color::White);
	tDt.setCharacterSize(45);

	////////////////POINTEUR/////////////////
	sf::CircleShape ptr(8);
	ptr.setFillColor(sf::Color::Cyan);
	ptr.setOrigin(4, 4);

	double tStart = getTimeStamp();
	double tEnterFrame = getTimeStamp();
	double tExitFrame = getTimeStamp();

	/////// BULLET////////////

	Bullet bullets;
	bool mouseLeftWasPressed = false;
	Curve c;

	/////////// BALL /////////
	int ballSize = 6;
	sf::CircleShape* ballShape = new sf::CircleShape(ballSize);
	ballShape->setOrigin(ballSize, ballSize);
	ballShape->setOutlineThickness(2);
	ballShape->setFillColor(sf::Color::Blue);
	ballShape->setOutlineColor(sf::Color::Magenta);

	////////////// PLAYER ///////
	PlayerPad* playerPad = new PlayerPad(EType::PlayerObject, player);
	Entity* ball = new Entity(EType::Ball, ballShape);

	World world;
	world.data.push_back(playerPad);
	world.data.push_back(ball);
	playerPad->currentBall = ball;

	while (window.isOpen()){
		sf::Event event;
		double dt = tExitFrame - tEnterFrame;
		tEnterFrame = getTimeStamp();

		while (window.pollEvent(event)){
			if (event.type == sf::Event::Closed)
				window.close();
		}

		auto pos = player->getPosition();
		float deltaX = dt * 450;
		float deltaY = dt * 450;
		bool keyHit = false;


		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)|| sf::Keyboard::isKeyPressed(sf::Keyboard::Q)) {
			pos.x -= deltaX;
			keyHit = true;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
			pos.x += deltaX;
			keyHit = true;
		}
		
		//Collision with screen

		

		if (keyHit) {
			if (pos.x < 0)
				pos.x = 0;
			if (pos.x > window.getSize().x)
				pos.x = window.getSize().x;
			playerPad->setPosition(pos);

			/*if (player->getPosition().x < 0.f)
				player->setPosition(0.f, player->getPosition().y);

			if (player->getPosition().x + player->getGlobalBounds().width > ScreenWidth)
				player->setPosition(ScreenWidth - player->getGlobalBounds().width, player->getPosition().y);*/
		}


		bool mouseLeftIsPressed = sf::Mouse::isButtonPressed(sf::Mouse::Left);
		bool mouseIsReleased = (!mouseLeftIsPressed && mouseLeftWasPressed);

		sf::Vector2f mousePos = sf::Vector2f(sf::Mouse::getPosition(window));

		if (false) {
			if (mouseIsReleased) c.addPoint(mousePos);
			if (sf::Mouse::isButtonPressed(sf::Mouse::Right)) c.clear();
		}

		if (mouseLeftIsPressed && !mouseLeftWasPressed) {
			//auto pos = gun.getPosition();
			auto dir = mousePos - pos;
			float dirLen = std::sqrt(dir.x * dir.x + dir.y * dir.y);
			sf::Vector2f dxy(1, 0);
			if (dirLen) {
				dxy = dir / dirLen;
			}
			dxy *= 60.0f * 6;
			bullets.create(pos.x, pos.y, dxy.x, dxy.y);
		}

		if (mouseLeftIsPressed) 
			mouseLeftWasPressed = true;
		else
			mouseLeftWasPressed = false;

		//calculate angle from char to mouse
		sf::Vector2f characterToMouse(
			mousePos.y - player->getPosition().y,
			mousePos.x - player->getPosition().x);

		float radToDeg = 57.2958;
		float angleC2M = atan2(characterToMouse.y, characterToMouse.x);
		//gun.setRotation(-angleC2M * radToDeg);
		//gun.setPosition(shape.getPosition() + sf::Vector2f(8, 16));
		///

		ptr.setPosition(mousePos);
		tDt.setString( to_string(dt)+" FPS:"+ to_string((int)(1.0f / dt)));
		


		//CLEAR
		window.clear();
		


		//UPDATE
		bullets.update(dt);
		world.update(dt);


		///////////////DRAW///////////////
		bullets.draw(window);
		drawMountain(window);
		drawGround(window);

		world.draw(window);
		//window.draw(gun);

		c.draw(window);
		window.draw(ptr);

		//ui
		window.draw(tDt);

		window.display();
		tExitFrame = getTimeStamp();
	}

	return 0;
}