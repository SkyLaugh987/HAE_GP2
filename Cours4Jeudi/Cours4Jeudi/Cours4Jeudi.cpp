// Cours4Jeudi.cpp : Ce fichier contient la fonction 'main'. L'exécution du programme commence et se termine à cet endroit.
//

#include <iostream>
#include <SFML/Graphics.hpp>
#include "Curve.hpp"
#include "tools.hpp"

float catmull(float p0, float p1, float p2, float p3, float t){
		auto q = 2.0 * p1;
		auto t2 = t * t;

		q += (-p0 + p2) 					* t;
		q += (2.0*p0 - 5.0*p1 + 4 * p2 - p3) 	* t2;
		q += (-p0 + 3 * p1 - 3 * p2 + p3) 	* t2 * t;

		return 0.5 * q;
};

void drawMountain(sf::RenderWindow& window) {

	sf::VertexArray arr;
	arr.setPrimitiveType(sf::LineStrip);
	sf::Color col = sf::Color::Green;

	float baseline = 350;

	sf::Vector2f a(0, baseline + 50);
	sf::Vector2f b(400, baseline - 150);
	sf::Vector2f c(1100, baseline + 32);
	sf::Vector2f d(window.getSize().x, baseline);
	col.a = 100;

	arr.append(sf::Vertex(a, col));
	arr.append(sf::Vertex(b, col));
	arr.append(sf::Vertex(c, col));
	arr.append(sf::Vertex(d, col));
	window.draw(arr);

	arr.clear();
	col = sf::Color:: Red;

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
		arr.append(sf::Vertex(sf::Vector2f(x, y), col));
	}

	for (int i = 0; i < 256; ++i) {
		float t = 1.0f * i / 256;
		float x = catmull(a.x, b.x, c.x, d.x, t);
		float y = catmull(a.y, b.y, c.y, d.y, t);
		arr.append(sf::Vertex(sf::Vector2f(window.getSize().x, baseline), col));
	}

	window.draw(arr);
}


void drawGround(sf::RenderWindow& window) {
	sf::VertexArray arr;
	arr.setPrimitiveType(sf::LineStrip);
	sf::Color col = sf::Color::Yellow;

	float baseline = 800;

	sf::Vector2f a(0, baseline);
	sf::Vector2f b(window.getSize().x,baseline);

	arr.append(sf::Vertex(a, col));
	arr.append(sf::Vertex(b, col));

	window.draw(arr);
}


int main()
{
    sf::RenderWindow window(sf::VideoMode(1920, 1000), "SFML works!");
    //sf::CircleShape shape(50.f);
    
    sf::RectangleShape canon(sf::Vector2f(8,32));
    sf::RectangleShape perso(sf::Vector2f(50, 60));
    sf::RectangleShape target(sf::Vector2f(8, 8));
;
    canon.setFillColor(sf::Color::Red);
    perso.setFillColor(sf::Color::White);
    target.setFillColor(sf::Color::Yellow);
	bool mouseLeftWasPressed = false;
	Curve c;
    
    while (window.isOpen())
    {

        sf::Event event;
        float tEnterFrame = getTimeStamp();
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed) {
                window.close();
            }       
        }
        float tExitFrame = getTimeStamp();

        float dt = tExitFrame - tEnterFrame;
        float deltaX = dt * 40;
        float deltaY = dt * 40;

        canon.setPosition(perso.getPosition());
        

        //auto pos = shape.getPosition();
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
            //pos.y-= deltaY;
            perso.move(0,-1);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
           //pos.y+= deltaY;
            perso.move(0,1);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
            //pos.x-= deltaX;
            perso.move(-1,0);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
            //pos.x+= deltaX;
            perso.move(1,0);
        }

		bool mouseLeftIsPressed = sf::Mouse::isButtonPressed(sf::Mouse::Left);
		bool mouseIsReleased = (mouseLeftIsPressed && !mouseLeftWasPressed);

		sf::Vector2f mousePos = sf::Vector2f(sf::Mouse::getPosition(window));

		if (false) {
			if (mouseIsReleased) c.addpPoint(mousePos);
		}
        
        sf::Vector2f canonPos = canon.getPosition();
        sf::Vector2i mousepos = sf::Mouse::getPosition(window);
        target.setPosition(sf::Vector2f(mousepos));

		sf::Vector2f characterToMouse(
			mousepos.y - canonPos.y,
			mousepos.x - canonPos.x);

		float radToDeg = 57.2958;
		float angleC2M = atan2(characterToMouse.y, characterToMouse.x);
		canon.setRotation(-angleC2M * radToDeg);
		canon.setPosition(canonPos + sf::Vector2f(8, 16));


		
        window.clear();
		drawGround(window);
		drawMountain(window);
        window.draw(perso);
        window.draw(canon);
        window.draw(target);
        window.display();
		
    }

    return 0;
}



