#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>
#include "../include/cube.h"
#include "../include/constants.h"
#include "../include/arguments.h"
#include "../include/terrain.h"

using namespace std;

void checkCameraMovement(cameraArgs &cargs)
{
    float camSpeed = 0.1f;
    glMath::vec3f yComp(0.0, 2.0f, 0.0f);
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
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
    {
        cargs.cameraPos += yComp * camSpeed;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
    {
        cargs.cameraPos -= yComp * camSpeed;
    }
}

void handleMouseMovement(mouseArgs &margs, cameraArgs &cargs, sf::RenderWindow &window)
{
    sf::Mouse m;
    sf::Vector2i currPos = m.getPosition(window);
    double xpos, ypos;
    xpos = currPos.x;
    ypos = currPos.y;

    if (margs.firstMouse)
    {
        margs.lastX = xpos;
        margs.lastY = ypos;
        margs.firstMouse = false;
    }

    float xoffset = xpos - margs.lastX;
    float yoffset = margs.lastY - ypos;
    margs.lastX = xpos;
    margs.lastY = ypos;

    float sensitivity = 0.01f;
    xoffset *= sensitivity;
    yoffset *= sensitivity;

    margs.yaw += xoffset;
    margs.pitch += yoffset;

    if (margs.pitch > 89.0f)
        margs.pitch = 89.0f;
    if (margs.pitch < -89.0f)
        margs.pitch = -89.0f;

    glMath::vec3f direction;
    direction.x = cos(glMath::degToRadians(margs.yaw)) * cos(glMath::degToRadians(margs.pitch));
    direction.y = sin(glMath::degToRadians(margs.pitch));
    direction.z = sin(glMath::degToRadians(margs.yaw)) * cos(glMath::degToRadians(margs.pitch));

    cargs.cameraFront = glMath::normalize(direction);
}

void handleMouseScroll(persArgs &pargs, int delta)
{
    pargs.fov -= (float)delta;
    if (pargs.fov < 1.0f)
        pargs.fov = 1.0f;
    if (pargs.fov > 45.0f)
        pargs.fov = 45.0f;
}

int main()
{
    sf::RenderWindow window(sf::VideoMode(constants::SCREEN_WIDTH, constants::SCREEN_HEIGHT), "SFML works!");
    auto desktop = sf::VideoMode::getDesktopMode();
    window.setPosition(sf::Vector2i(desktop.width / 2.0f - window.getSize().x / 2, desktop.height / 2 - window.getSize().y / 2));
    sf::Mouse::setPosition(sf::Vector2i(constants::SCREEN_WIDTH/2.f, constants::SCREEN_HEIGHT/2.f), window);
    // window.setFramerateLimit(240);

    // -----------------------------
    //  initialize here
    // -----------------------------
    // cameraArgs cargs(glMath::vec3f(0.0f, 0.71f,-0.704998f), glMath::vec3f(0.0f, -1.0f, -1.5f), glMath::vec3f(0.0f, 1.0f, 0.0f));
    // cameraArgs cargs(glMath::vec3f(0.0f, 0.71f,-0.704998f), glMath::vec3f(0.0f, -1.0f, -1.5f), glMath::vec3f(0.0f, 1.0f, 0.0f));
    // camera and clipping works version
    cameraArgs cargs(glMath::vec3f(0.0f, 0.71f,1.605f), glMath::vec3f(0.0f, -1.0f, -1.5f), glMath::vec3f(0.0f, 1.0f, 0.0f));
    persArgs pargs(45.0f, constants::SCREEN_WIDTH, constants::SCREEN_HEIGHT, -0.1f, -100.0f);
    mouseArgs margs(true, -90.f, 0.0f, (constants::SCREEN_WIDTH / 2.0f), (constants::SCREEN_HEIGHT / 2.0f));
    // Cube cube(window);
    Terrain terrain(window);
    // terrain.generateInitialTerrain(constants::SCREEN_WIDTH / 4.0f, constants::SCREEN_HEIGHT / 4.0f, constants::SCREEN_WIDTH / 2.0f, constants::SCREEN_HEIGHT / 2.0f);
    // terrain.generateInitialTerrain(0.1*constants::SCREEN_WIDTH,0.1*constants::SCREEN_HEIGHT,0.8*constants::SCREEN_WIDTH,0.8f*constants::SCREEN_HEIGHT);
    terrain.generateInitialTerrain(-2.0f*constants::SCREEN_WIDTH,-2.0f*constants::SCREEN_HEIGHT,5*constants::SCREEN_WIDTH,5*constants::SCREEN_HEIGHT);
    sf::Clock clock; // starts the clock
    float angle = 4.0f;

    while (window.isOpen())
    {
        // cube.model = glMath::mat4f(1.0f);
        // cube.view = glMath::mat4f(1.0f);
        // cube.proj = glMath::mat4f(1.0f);
        terrain.model = glMath::mat4f(1.0f);
        terrain.view = glMath::mat4f(1.0f);
        terrain.proj = glMath::mat4f(1.0f);
        // -----------------------------
        // change model matrix here
        // -----------------------------
        // cube.scale(glMath::vec3f(0.5, 0.5, 0.5));
        terrain.translate(glMath::vec3f(0.0f, -200.0, -2.0f));

        // cube.scale(glMath::vec3f(0.5, 0.5, 0.5));
        // cube.rotate(glMath::vec3f(0,1,0),angle);
        // cube.translate(glMath::vec3f(140.0f,0.0,-5.0f));
        // angle += 0.2;
        // -----------------------------
        // change view matrix here
        // -----------------------------
        // std::cout<<"---------------"<<std::endl;
        // std::cout<<cargs.cameraPos<<std::endl;
        terrain.lookAt(cargs.cameraPos, cargs.cameraPos + cargs.cameraFront, cargs.cameraUp);

        // -----------------------------
        // change proj matrix here
        // -----------------------------
        terrain.perspective(pargs.fov, pargs.sw, pargs.sh, pargs.nearZ, pargs.farZ);

        sf::Event event;
        while (window.pollEvent(event))
        {

            // check the type of the event...
            switch (event.type)
            {
            // window closed
            case sf::Event::Closed:
                window.close();
                break;

            // key pressed
            case sf::Event::MouseMoved:
                handleMouseMovement(margs, cargs, window);
                break;

            case sf::Event::KeyPressed:
                if (event.key.code == sf::Keyboard::Escape)
                {
                    window.close();
                }else if (event.key.code == sf::Keyboard::Enter){
                    terrain.generateInitialTerrain(0.1*constants::SCREEN_WIDTH,0.1*constants::SCREEN_HEIGHT,0.8*constants::SCREEN_WIDTH,0.8f*constants::SCREEN_HEIGHT);
                }
                break;
            // case sf::Event::MouseWheelScrolled:
            //     handleMouseScroll(pargs, event.mouseWheel.delta);
            //     std::cout << event.mouseWheelScroll.delta<< std::endl;
            //     break;

            // we don't process other types of events
            default:
                break;
            }
        }

        checkCameraMovement(cargs);

        window.clear();
        terrain.updateVertices();
        // cout<<cargs.cameraPos<<endl;
        terrain.render();
        window.display();
    }
}