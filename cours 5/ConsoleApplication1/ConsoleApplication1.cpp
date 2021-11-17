
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
//////////////////////////////////////
// M O U N T A I N

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
/////////////////////////////
// G R O U N D

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


	////////////////////////////////
	////////// G U N
	/*sf::RectangleShape gun(sf::Vector2f(8, 32));
	gun.setFillColor(sf::Color(	0xFF,0x00,0x00));
	gun.setOrigin(4,0);
	gun.setPosition(800, 600);*/

	///////////////////////////////
	/////T E X T
	sf::Font fArial;
	if (!fArial.loadFromFile("res/arial.ttf"))	
		cout << "font not loaded" << endl;
	sf::Text tDt;
	tDt.setFont(fArial);
	tDt.setFillColor(sf::Color::White);
	tDt.setCharacterSize(45);

	///////////////////////////////
	/////////P O I N T E U R
	sf::CircleShape ptr(8);
	ptr.setFillColor(sf::Color::Cyan);
	ptr.setOrigin(4, 4);

	double tStart = getTimeStamp();
	double tEnterFrame = getTimeStamp();
	double tExitFrame = getTimeStamp();

	//////////////////////////
	/////// BULLET
	Bullet bullets;
	bool mouseLeftWasPressed = false;
	Curve c;

	/////////////////////////
	/////////// BALL 
	int ballSize = 6;
	sf::CircleShape* ballShape = new sf::CircleShape(ballSize);
	ballShape->setOrigin(ballSize, ballSize);
	ballShape->setOutlineThickness(2);
	ballShape->setFillColor(sf::Color::Blue);
	ballShape->setOutlineColor(sf::Color::Magenta);

	/////////////////////////
	/////// PLAYER 
	PlayerPad* playerPad = new PlayerPad(EType::PlayerObject, player);
	Entity* ball = new Entity(EType::Ball, ballShape);
	ball->setPosition(playerPad->getPosition());

	auto wallShapeLeft = new sf::RectangleShape(sf::Vector2f(16, 2048));
	wallShapeLeft->setOrigin(8, 0);
	wallShapeLeft->setFillColor(sf::Color::Blue);
	auto wallShapeRight = new sf::RectangleShape(*wallShapeLeft);

	Entity* leftWall = new Entity(EType::Wall, wallShapeLeft);
	Entity* rightWall = new Entity(EType::Wall, wallShapeLeft);
	rightWall->setPosition(sf::Vector2f(1280, 0));

	auto wallShapeTop = new sf::RectangleShape(sf::Vector2f(2048, 16));
	wallShapeTop->setOrigin(0,8);
	wallShapeTop->setFillColor(sf::Color::Blue);

	Entity* topWall = new Entity(EType::Wall, wallShapeTop);
	topWall->setPosition(sf::Vector2f(0, 0));

	World world;
	world.data.push_back(leftWall);
	world.data.push_back(rightWall);
	world.data.push_back(topWall);
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



		if (keyHit) {
			if (pos.x < 0)
				pos.x = 0;
			if (pos.x > window.getSize().x)
				pos.x = window.getSize().x;
			playerPad->setPosition(pos);

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
			//bullets.create(pos.x, pos.y, dxy.x, dxy.y);

			if (playerPad->currentBall) {
				auto ball = playerPad->currentBall;
				ball->dx = dxy.x;
				ball->dy = dxy.y;
				float push = 0.1;
				ball->setPosition(sf::Vector2f(ball->getPosition().x, 
									playerPad->getPosition().y - 16));
			}
			playerPad->currentBall = nullptr;
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
		ptr.setPosition(mousePos);
		tDt.setString( to_string(dt)+" FPS:"+ to_string((int)(1.0f / dt)));
		

		///////////////////////////
		//C L E A R
		window.clear();
		

		///////////////////////////
		//U P D A T E
		//bullets.update(dt);
		world.update(dt);

		///////////////////////////
		//////////D R A W
		//bullets.draw(window);
		drawMountain(window);
		drawGround(window);

		world.draw(window);
		//window.draw(gun);

		c.draw(window);
		window.draw(ptr);

		///////////////////////////
		//UI
		window.draw(tDt);

		window.display();
		tExitFrame = getTimeStamp();
	}

	return 0;
}