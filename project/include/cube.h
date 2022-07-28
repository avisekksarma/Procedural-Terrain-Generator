#pragma once

#include <SFML/Graphics.hpp>
#include <sstream>
#include <vector>
#include "../include/glMath.h"
#include <iostream>
#include <math.h>

struct mesh
{
	std::vector<glMath::trianglef> tris;
};

class Cube
{

public:
	Cube(sf::RenderWindow &w);
	sf::RenderWindow *window;
	mesh meshCube;
	mesh ndc;
	// std::vector<sf::Vertex> vertices;
	glMath::mat4f toWindow;
	// std::vector<sf::Vertex> vertices;
	glMath::mat4f model;
	glMath::mat4f view;
	glMath::mat4f proj;

public:
	void drawTriangle(glMath::vec3f p1, glMath::vec3f p2, glMath::vec3f p3, int color);
	void render();
	// void setVertex();
	void translate(glMath::vec3f p);
	void rotate(glMath::vec3f p, float angle);
	void scale(glMath::vec3f p);
	void perspective(float fov, float sw, float sh, float nearZ, float farZ);
	void scale();
	void updateVertices();
	void toWindowCoord();

private:
	void putpixel(float x, float y, int color);
	void BLA(int x0, int y0, int xl, int yl, int color);
};
