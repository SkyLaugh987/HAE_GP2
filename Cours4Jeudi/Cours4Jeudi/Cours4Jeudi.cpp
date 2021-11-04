// Cours4Jeudi.cpp : Ce fichier contient la fonction 'main'. L'exécution du programme commence et se termine à cet endroit.
//

#include <iostream>
#include <SFML/Graphics.hpp>


int main()
{
    sf::RenderWindow window(sf::VideoMode(1000, 1000), "SFML works!");
    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed) {
                window.close();
            }       
        }
        auto pos = shape.getPosition();
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
            pos.y--;
            shape.setPosition(pos);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
            pos.y++;
            shape.setPosition(pos);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
            pos.x--;
            shape.setPosition(pos);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
            pos.x++;
            shape.setPosition(pos);
        }


        window.clear();
        window.draw(shape);
        window.display();
    }

    return 0;
}



