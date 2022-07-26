#pragma once 

#include <SFML/Graphics.hpp>
#include <vector>
#include "glMath/glMath.h"

class Line {
    public:
    std::vector<glMath::vec2i> point1;
    std::vector<glMath::vec2i> point2;
    Line(glMath::vec2i point1, glMath::vec2i point2);
    void draw();
};

Line::Line(glMath::vec2i p1, glMath::vec2i p2) {
    point1.push_back(p1);
    point2.push_back(p2);
}

void Line::draw(){
    sf::Image buffer();
    // sf::Sprite bufferSprite(buffer);
    //line((int)point1[0].x , (int)point1[0].y, (int)point2[0].x , (int)point2[0].y);
}

void drawLine(glMath::vec2i point1, glMath::vec2i point2){
    //line(point1.x, point1.y, point2.x, point2.y);
}