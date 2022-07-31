#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>
#include "../include/cube.h"
#include "../include/constants.h"


using namespace glMath;

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

struct cameraArgs
{
    glMath::vec3f cameraPos;
    glMath::vec3f cameraFront;
    glMath::vec3f cameraUp;
    cameraArgs(glMath::vec3f cp, glMath::vec3f cf, glMath::vec3f cu) : cameraPos(cp), cameraFront(cf), cameraUp(cu) {}
};

void checkCameraMovement(cameraArgs &cargs)
{
    float camSpeed = 0.001f;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
    {
        cargs.cameraPos += cargs.cameraFront * camSpeed;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
    {
        cargs.cameraPos -= cargs.cameraFront * camSpeed;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
    {
        cargs.cameraPos -= glMath::normalize(glMath::cross(cargs.cameraFront, cargs.cameraUp)) * camSpeed;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
    {
        cargs.cameraPos += glMath::normalize(glMath::cross(cargs.cameraFront, cargs.cameraUp)) * camSpeed;
    }
}

int main()
{
    sf::RenderWindow window(sf::VideoMode(constants::SCREEN_WIDTH, constants::SCREEN_HEIGHT), "SFML works!");
    auto desktop = sf::VideoMode::getDesktopMode();
    window.setPosition(sf::Vector2i(desktop.width / 2.0f - window.getSize().x / 2, desktop.height / 2 - window.getSize().y / 2));
    // window.setFramerateLimit(240);
    cameraArgs cargs(vec3f(0.0f, 0.0f, 3.0f), vec3f(0.0f, 0.0f, -3.0f), vec3f(0.0f, 1.0f, 0.0f));
    persArgs pargs(45.0f, constants::SCREEN_WIDTH, constants::SCREEN_HEIGHT, 0.1f, 100.0f);
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

        // cube.scale(glMath::vec3f(0.5, 0.5, 0.5));
        cube.translate(glMath::vec3f(140.0f,0.0,-5.0f));
        // -----------------------------
        // change view matrix here
        // -----------------------------
        cube.lookAt(cargs.cameraPos, cargs.cameraPos + cargs.cameraFront, cargs.cameraUp);
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
        // keyboard management
        checkCameraMovement(cargs);
        window.clear();
        cube.updateVertices();
        cube.render();
        window.display();
    }
}