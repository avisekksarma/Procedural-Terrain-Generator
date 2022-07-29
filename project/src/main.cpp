#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>
#include "../include/cube.h"

#define SCREEN_WIDTH 1080
#define SCREEN_HEIGHT 720

struct persArgs
{
    float fov;
    float sw;
    float sh;
    float nearZ;
    float farZ;
    persArgs(float f, float sw, float sh, float nz, float fz)
    {
        fov = f;
        this->sw = sw;
        this->sh = sh;
        nearZ = nz;
        farZ = fz;
    }
};
int main()
{
    sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "SFML works!");
    auto desktop = sf::VideoMode::getDesktopMode();
    window.setPosition(sf::Vector2i(desktop.width / 2.0f - window.getSize().x / 2, desktop.height / 2 - window.getSize().y / 2));
    // window.setFramerateLimit(240);
    persArgs pargs(45.0f, SCREEN_WIDTH, SCREEN_HEIGHT, 0.1f, 100.0f);
    Cube cube(window);
    // cube.rotate(glMath::vec3f(1,1, 0), 45.f);
    float angle = 0;
    const float radius = 10.0f;
    sf::Clock clock; // starts the clock
    while (window.isOpen())
    {
        cube.model = glMath::mat4f(1.0f);
        cube.view = glMath::mat4f(1.0f);
        cube.proj = glMath::mat4f(1.0f);
        angle += 0.1;

        // -----------------------------
        // change model matrix here
        // -----------------------------

        cube.translate(glMath::vec3f(-0.4f,0.5,-3.0f));
        // cube.scale(glMath::vec3f(0.5, 0.5, 0.5));

        // -----------------------------
        // change view matrix here
        // -----------------------------

        // sf::Time elapsed1 = clock.getElapsedTime();
        // float camZ = sin(elapsed1.asSeconds() ) * radius;
        // float camX = cos(elapsed1.asSeconds() ) * radius;
        // cube.lookAt(glMath::vec3f(3.0f, 0.0, -2.0f), glMath::vec3f(0.0, 0.0, 0.0), glMath::vec3f(0.0, 1.0, 0.0));
        // cube.lookAt(glMath::vec3f(camX, 0.0, camZ), glMath::vec3f(0.0, 0.0, 0.0), glMath::vec3f(0.0, 1.0, 0.0));

        // -----------------------------
        // change proj matrix here
        // -----------------------------
        cube.perspective(pargs.fov, pargs.sw, pargs.sh, pargs.nearZ, pargs.farZ);

        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        window.clear();
        cube.updateVertices();
        cube.render();
        window.display();
    }
}