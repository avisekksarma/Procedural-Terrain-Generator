#pragma once
#include <SFML/Graphics.hpp>
#include <sstream>
#include <vector>
#include "../include/glMath.h"
#include <iostream>
#include <math.h>

#include "./zBufferTemp.h"

#include <list>
namespace TerrainGen
{
    struct mesh
    {
        std::vector<glMath::trianglef> tris;
    };
} // namespace  Terrain

struct TerrainConstants
{
    int XTopLeft;
    int ZTopLeft;
    int widthX;
    int lengthZ;
    int xtrilen = 54.f;
    int ztrilen = 36.f;
    TerrainConstants() {}
    void create(int x, int z, int w, int l)
    {
        XTopLeft = x;
        ZTopLeft = z;
        widthX = w;
        lengthZ = l;
    }
};
class Terrain
{

public:
    Terrain(sf::RenderWindow &w);
    sf::RenderWindow *window;
    TerrainGen::mesh meshTerrain; // copy
    TerrainGen::mesh local;       // actual
    TerrainConstants consts;
    glMath::mat4f model;
    glMath::mat4f view;
    glMath::mat4f proj;
    ZBuffer zbuffer;
    std::list<glMath::trianglef> listTriangles;
    // bool first;

public:
    void drawTriangle(glMath::vec3f p1, glMath::vec3f p2, glMath::vec3f p3, sf::Color color);
    void fillTriangle(glMath::vec3f vt1, glMath::vec3f vt2, glMath::vec3f vt3, sf::Color color);
    void render();
    void translate(glMath::vec3f p);
    void rotate(glMath::vec3f p, float angle);
    void scale(glMath::vec3f p);
    void perspective(float fov, float sw, float sh, float nearZ, float farZ);
    void lookAt(glMath::vec3f from, glMath::vec3f to, glMath::vec3f temp);
    void updateVertices();
    void toWindowCoord();
    void clipAgainstPlanes();

    // Terrain Parts
    void generateInitialTerrain(int x, int z, int w, int l);

private:
    void putpixel(float x, float y, sf::Color color);
    void BLA(int x0, int y0, int xl, int yl, sf::Color color);
    void fillBottomFlatTriangle(glMath::vec3f v1, glMath::vec3f v2, glMath::vec3f v3, sf::Color color);
    void fillTopFlatTriangle(glMath::vec3f v1, glMath::vec3f v2, glMath::vec3f v3, sf::Color color);
    void scanLine(int x0, int x1, int y0, int y1m, sf::Color color);
};
