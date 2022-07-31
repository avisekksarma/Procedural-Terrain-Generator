#pragma once

#include <SFML/Graphics.hpp>
#include <sstream>
#include <vector>
#include "../include/glMath.h"
#include <iostream>
#include <math.h>
#include "./zbuffer.h"
#include "./zBufferTemp.h"

#include <list>

struct mesh
{
	std::vector<glMath::trianglef> tris;
};

class Cube
{

public:
	Cube(sf::RenderWindow &w);
	sf::RenderWindow *window;
	mesh meshCube; // copy
	mesh local;	   // actual

	glMath::mat4f model;
	glMath::mat4f view;
	glMath::mat4f proj;
	ZBuffer zbuffer;
	std::list<glMath::trianglef> listTriangles;

	bool first;

public:
	void drawTriangle(glMath::vec3f p1, glMath::vec3f p2, glMath::vec3f p3, sf::Color color);
	void fillTriangle(glMath::vec3f vt1, glMath::vec3f vt2, glMath::vec3f vt3, sf::Color color);
	// void fillTriangle(sf::Vector2f vt1, sf::Vector2f vt2, sf::Vector2f vt3,
	//  sf::Color color);
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
	void clipAgainstPlanes();

private:
	void putpixel(float x, float y, sf::Color color);

	void BLA(int x0, int y0, int xl, int yl, sf::Color color);

	void fillBottomFlatTriangle(glMath::vec3f v1, glMath::vec3f v2, glMath::vec3f v3, sf::Color color);
	// void fillBottomFlatTriangle(sf::Vector2f v1, sf::Vector2f v2, sf::Vector2f 
	// v3, sf::Color color);
	void fillTopFlatTriangle(glMath::vec3f v1, glMath::vec3f v2, glMath::vec3f v3, sf::Color color);
	// void scanLine(int x0, int x1, int y0, int y1m, float z, sf::Color color);
	void scanLine(int x0, int x1, int y0, int y1m, sf::Color color);
};
