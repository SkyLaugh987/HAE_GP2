// Cours4Jeudi.cpp : Ce fichier contient la fonction 'main'. L'exécution du programme commence et se termine à cet endroit.
//

#include <iostream>
#include <SFML/Graphics.hpp>
#include "tools.hpp"


int main()
{
    sf::RenderWindow window(sf::VideoMode(1000, 1000), "SFML works!");
    //sf::CircleShape shape(50.f);
    
    sf::RectangleShape canon(sf::Vector2f(8,32));
    sf::RectangleShape perso(sf::Vector2f(50, 150));
    sf::RectangleShape target(sf::Vector2f(8, 8));

    canon.setFillColor(sf::Color::Red);
    perso.setFillColor(sf::Color::White);
    target.setFillColor(sf::Color::Yellow);

    
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

        
        sf::Vector2f canonPos = canon.getPosition();
        sf::Vector2i mousepos = sf::Mouse::getPosition(window);
        target.setPosition(sf::Vector2f(mousepos));

        const float PI = 3.14159265;
        float dx = canonPos.x - mousepos.x;
        float dy = canonPos.y - mousepos.y;

        float rotation = (atan2(dy, dx)) * 180 / PI;
        canon.setRotation(rotation);

        window.clear();
        window.draw(perso);
        window.draw(canon);
        window.draw(target);
        window.display();
    }

    return 0;
}



