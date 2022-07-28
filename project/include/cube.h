#pragma once

#include <SFML/Graphics.hpp>
#include <sstream>
#include <vector>
#include "../include/glMath.h"
#include <iostream>
#include <math.h>

struct triangle {
	glMath::vec3f p[3];
};

struct mesh {
	std::vector<triangle> tris;
};

class Cube {
    
public:
    Cube(sf::RenderWindow& w);
	sf::RenderWindow* window;
	mesh meshCube;
	std::vector<sf::Vertex> vertices;
	glMath::mat4f model;
	void putpixel(float x, float y, int color);
	void BLA(int x0, int y0, int xl, int yl, int color);
	void drawTriangle(glMath::vec3f p1,glMath::vec3f p2, glMath::vec3f p3, int color);
    void render();
	void setVertex();
	void translate(glMath::vec3f p);
	void rotate(glMath::vec3f p, float angle);
	void updateVertices();
};
