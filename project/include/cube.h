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
	// copy
	mesh meshCube;
	// actual
	mesh local;
	// std::vector<sf::Vertex> vertices;
	glMath::mat4f toWindow;
	glMath::mat4f model;
	glMath::mat4f view;
	glMath::mat4f proj;
	bool first;

public:
	void drawTriangle(glMath::vec3f p1, glMath::vec3f p2, glMath::vec3f p3, int color);
	void fillTriangle(glMath::vec3f p1, glMath::vec3f p2, glMath::vec3f p3, int color);
	void render();
	// void setVertex();
	void translate(glMath::vec3f p);
	void rotate(glMath::vec3f p, float angle);
	void scale(glMath::vec3f p);
	void perspective(float fov, float sw, float sh, float nearZ, float farZ);
	void lookAt(glMath::vec3f from, glMath::vec3f to, glMath::vec3f temp);
	// void scale();
	void updateVertices();
	void toWindowCoord();
	void fillTriangle(sf::Vector2f vt1, sf::Vector2f vt2, sf::Vector2f vt3);

private:
	void putpixel(float x, float y, int color);
	void BLA(int x0, int y0, int xl, int yl, int color);
	void fillBottomFlatTriangle(sf::Vector2f v1, sf::Vector2f v2, sf::Vector2f v3);
	void fillTopFlatTriangle(sf::Vector2f v1, sf::Vector2f v2, sf::Vector2f v3);
	void scanLine(int x0, int x1, int y0, int y1);
};
