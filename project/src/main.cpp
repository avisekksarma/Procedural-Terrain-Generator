#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>
#include "../include/cube.h"

#define SCREEN_WIDTH 1080 
#define SCREEN_HEIGHT 720

int main()
{
    sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "SFML works!");
    auto desktop = sf::VideoMode::getDesktopMode();
    window.setPosition(sf::Vector2i(desktop.width / 2.0f - window.getSize().x / 2, desktop.height / 2 - window.getSize().y / 2));
    window.setFramerateLimit(240);
    Cube cube(window);
    // cube.rotate(glMath::vec3f(1,1, 0), 45.f);
    float angle =0;
    // // transformation part
    // // cube.rotate(glMath::vec3f(0,0,1), 20.f);
    // cube.translate(glMath::vec3f(50,100,0.0));
    // // view part
    // cube.translate(glMath::vec3f(0.0f,0.0f,-10.0f));
    // // projection part
    
    // cube.updateVertices();
    while (window.isOpen())
    {
        cube.model = glMath::mat4f (1.0f);
        cube.scale(glMath::vec3f(0.5,0.5,0.5));
        // cube.translate(glMath::vec3f(100,0,0));
        angle+=0.1;
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        window.clear();
        cube.rotate(glMath::vec3f(1,0,1), angle);
        // cube.BLA(0,200,1080,100,1);
        cube.updateVertices();
        cube.render();
        window.display();
    }
}