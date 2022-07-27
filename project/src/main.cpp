#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>
#include "../include/Cube.h"

#define SCREEN_WIDTH 1080 
#define SCREEN_HEIGHT 720

int main()
{
    sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "SFML works!");
    auto desktop = sf::VideoMode::getDesktopMode();
    window.setPosition(sf::Vector2i(desktop.width / 2.0f - window.getSize().x / 2, desktop.height / 2 - window.getSize().y / 2));
    Cube cube(window);
    cube.translate(glMath::vec3f(200,200,0));
    cube.rotate(glMath::vec3f(0,0,1), 20.f);
    cube.updateVertices();
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        window.clear();
        cube.render();
        window.display();
    }
}