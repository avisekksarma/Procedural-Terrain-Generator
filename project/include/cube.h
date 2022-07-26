#pragma once

#include <sstream>
#include <vector>
#include "glMath/glMath.h"
#include "line.h"
#include <iostream>

class Cube {
    
public:
    Cube();

	std::stringstream VertexBuffer;
	std::stringstream indexBuffer;

    std::vector<glMath::vec3f> vertices;
    std::vector<glMath::vec2i> indices;


    void draw();
};
Cube::Cube() {

	VertexBuffer << "0 0 0 0 100 0 100 100 0 100 0 0 0 0 100 0 100 100 100 100 100 100 0 100";
	indexBuffer << "1 4 3 2 1 2 6 5 5 6 7 8 3 4 8 7 1 5 8 4 2 3 7 6";
	vertices.push_back(glMath::vec3f(0, 0, 0));
	vertices.push_back(glMath::vec3f(0, 100, 0));
	vertices.push_back(glMath::vec3f(100, 100, 0));
	vertices.push_back(glMath::vec3f(100, 0, 0));
	vertices.push_back(glMath::vec3f(0, 0, 100));
	vertices.push_back(glMath::vec3f(0, 100, 100));
	vertices.push_back(glMath::vec3f(100, 100, 100));
	vertices.push_back(glMath::vec3f(100, 0, 100));

	indices.push_back(glMath::vec2i(1, 4));
	indices.push_back(glMath::vec2i(3, 2));
	indices.push_back(glMath::vec2i(1, 2));
	indices.push_back(glMath::vec2i(6, 5));

	indices.push_back(glMath::vec2i(5, 6));
	indices.push_back(glMath::vec2i(7, 8));
	indices.push_back(glMath::vec2i(3, 4));
	indices.push_back(glMath::vec2i(8, 7));

	indices.push_back(glMath::vec2i(1, 5));
	indices.push_back(glMath::vec2i(8, 4));
	indices.push_back(glMath::vec2i(2, 3));
	indices.push_back(glMath::vec2i(7, 6));
	

}

void Cube::draw() {
	glMath::mat4f model(1.0f);
	model = glMath::translate(model, glMath::vec3f(100, 100, 0));
	glMath::mat4f view(1.0f);
	// view = glMath::perspective(glMath::radians(45.f), 720.f/1080.f, 0.1f, 100.f);
	std::cout << model;
	// model = view * model;


	for (auto &i : vertices) {
		glMath::vec3f v(i.x, i.y, i.z);
		v =  model * v;
		std::cout << v << std::endl;
		i =  glMath::vec3f(v.x, v.y, v.z);
	}
	for (auto &i : indices) {

		Line l(glMath::vec2i(vertices[i.x].x, vertices[i.x].y),glMath::vec2i(vertices[i.y].x, vertices[i.y].y));
		l.draw();
	}
}

