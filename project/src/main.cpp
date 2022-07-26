#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>

#define log(x) std::cerr<< x << std::endl;
#define SCREEN_HEIGHT 600
#define SCREEN_WIDTH 800

// scaling constants
float sx = 10.0f;
float sy = 10.0f;
float sz = 10.0f;
// translation constants
float tx = 100.0f;
float ty = -200.0f;
float tz = 20.0f;
// rotation constants
float angleXrot = 45.0f;
float angleYrot = 50.0f;
float angleZrot = 30.0f;

struct vec3f
{
    float x, y, z;
};
struct triangle
{
    vec3f v[3];
};
struct mesh
{
    std::vector<triangle> tris;
};
template <class T>
struct Matrix4x4
{
    T m[4][4] = {0.0f};
};
typedef Matrix4x4<float> Matrix44f;
// overloaded debugPrint
void debugPrint(triangle t)
{
    std::cout << "=====Triangle--debug--start=======" << std::endl;
    for (int i = 0; i < 3; i++)
    {
        std::cout << t.v[i].x << " " << t.v[i].y << " " << t.v[i].z << std::endl;
    }
    std::cout << "=====Triangle--debug--end=======" << std::endl;
}


class Engine3d
{
private:
    mesh meshCube;
    sf::RenderWindow &window;
    Matrix44f projMatrix;

public:
    Engine3d(sf::RenderWindow &w) : window(w)
    {
        meshCube.tris = {

            // SOUTH
            {0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f, 0.0f},
            {0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f},

            // EAST
            {1.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f, 1.0f, 1.0f, 1.0f},
            {1.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f},

            // NORTH
            {1.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f, 1.0f},
            {1.0f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f},

            // WEST
            {0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f},
            {0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f},

            // TOP
            {0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f},
            {0.0f, 1.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f},

            // BOTTOM
            {1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f},
            {1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f},

        };

        createProjMatrix();
    }
    void mulvecxMatrix(vec3f &i, vec3f &o, Matrix44f &m)
    {
        o.x = i.x * m.m[0][0] + i.y * m.m[1][0] + i.z * m.m[2][0] + m.m[3][0];
        o.y = i.x * m.m[0][1] + i.y * m.m[1][1] + i.z * m.m[2][1] + m.m[3][1];
        o.z = i.x * m.m[0][2] + i.y * m.m[1][2] + i.z * m.m[2][2] + m.m[3][2];
        float w = i.x * m.m[0][3] + i.y * m.m[1][3] + i.z * m.m[2][3] + m.m[3][3];
        if (w != 0.0f)
        {
            o.x /= w;
            o.y /= w;
            o.z /= w;
        }
    }
    void createProjMatrix()
    {
        float fNear = 0.1f;
        float fFar = 1000.0f;
        float fFov = 40.0f;
        float fAspectRatio = (float)SCREEN_WIDTH / (float)SCREEN_HEIGHT;
        float fFovRad = 1.0f / tanf(fFov * 0.5f / 180.0f * 3.14159f);

        projMatrix.m[0][0] = fAspectRatio * fFovRad;
        projMatrix.m[1][1] = fFovRad;
        projMatrix.m[2][2] = fFar / (fFar - fNear);
        projMatrix.m[3][2] = (-fFar * fNear) / (fFar - fNear);
        projMatrix.m[2][3] = 1.0f;
        projMatrix.m[3][3] = 0.0f;
    }
    void updateScreen()
    {
        window.clear();
        render();
        window.display();
    }

private:
    void render()
    {
        // sf::CircleShape circle(50);
        // circle.setFillColor(sf::Color::Green);
        // circle.setPosition(200, 300);
        // window.draw(circle);
        // sf::ConvexShape triShape;
        // triShape.setPointCount(3);
        double thx = (angleXrot * 3.14) / 180;
        double thy = (angleYrot * 3.14) / 180;
        double thz = (angleZrot * 3.14) / 180;
        angleXrot += 0.05f;
        angleYrot += 0.06f;
        angleZrot += 0.04f;
        Matrix44f rotX = {
            1, 0, 0, 0,
            0, cos(thx), sin(thx), 0,
            0, -sin(thx), cos(thx), 0,
            0, 0, 0, 1};
        Matrix44f rotY = {
            cos(thy), 0, -sin(thy), 0,
            0, 1, 0, 0,
            sin(thy), 0, cos(thy), 0,
            0, 0, 0, 1};
        Matrix44f rotZ = {
            cos(thz), sin(thz), 0, 0,
            -sin(thz), cos(thz), 0, 0,
            0, 0, 1, 0,
            0, 0, 0, 1};
        Matrix44f scaling = {
            sx, 0, 0, 0,
            0, sy, 0, 0,
            0, 0, sz, 0,
            0, 0, 0, 1};
        Matrix44f translation = {
            1, 0, 0, 0,
            0, 1, 0, 0,
            0, 0, 1, 0,
            tx, ty, tz, 1};
        for (auto tri : meshCube.tris)
        {
            triangle triProjected = tri;
            log("1. no projection");
            // debugPrint(triProjected);
            // // scaling
            // mulvecxMatrix(triProjected.v[0], triProjected.v[0], scaling);
            // mulvecxMatrix(triProjected.v[1], triProjected.v[1], scaling);
            // mulvecxMatrix(triProjected.v[2], triProjected.v[2], scaling);

            log("2. after scaling");
            // debugPrint(triProjected);
            // for z axis rotation
            mulvecxMatrix(triProjected.v[0], triProjected.v[0], rotY);
            mulvecxMatrix(triProjected.v[1], triProjected.v[1], rotY);
            mulvecxMatrix(triProjected.v[2], triProjected.v[2], rotY);
            log("3. after rotY ");
            // debugPrint(triProjected);
            // for x axis rotation .
            // mulvecxMatrix(triProjected.v[0], triProjected.v[0], rotX);
            // mulvecxMatrix(triProjected.v[1], triProjected.v[1], rotX);
            // mulvecxMatrix(triProjected.v[2], triProjected.v[2], rotX);
            // log("4. after rotx ");
            // debugPrint(triProjected);
            // for z axis rotation
            // mulvecxMatrix(triProjected.v[0], triProjected.v[0], rotZ);
            // mulvecxMatrix(triProjected.v[1], triProjected.v[1], rotZ);
            // mulvecxMatrix(triProjected.v[2], triProjected.v[2], rotZ);

            // // now translation. ( for now works like a view matrix i.e. camera )
            triProjected.v[0].z += 20.0f;
            triProjected.v[1].z += 20.0f;
            triProjected.v[2].z += 20.0f;
            // by translation matrix

            // mulvecxMatrix(triProjected.v[0], triProjected.v[0], translation);
            // mulvecxMatrix(triProjected.v[1], triProjected.v[1], translation);
            // mulvecxMatrix(triProjected.v[2], triProjected.v[2], translation);
            // log("5. after translation ");
            // debugPrint(triProjected);
            // now projection.
            mulvecxMatrix(triProjected.v[0], triProjected.v[0], projMatrix);
            mulvecxMatrix(triProjected.v[1], triProjected.v[1], projMatrix);
            mulvecxMatrix(triProjected.v[2], triProjected.v[2], projMatrix);
            // log("6. after projection");
            // debugPrint(triProjected);
            // scaling triProjected matrix to the screen from clip coordinates(ndc)
            // we add 1.0f as clip coordinates / ndc given  by projection matrix is in
            // [ -1,1 ] range.
            triProjected.v[0].x += 1.0f;
            triProjected.v[0].y += 1.0f;
            triProjected.v[1].x += 1.0f;
            triProjected.v[1].y += 1.0f;
            triProjected.v[2].x += 1.0f;
            triProjected.v[2].y += 1.0f;

            // log("7. after shifting to [0,2] ");
            // debugPrint(triProjected);
            triProjected.v[0].x *= 0.5f * (float)SCREEN_WIDTH;
            triProjected.v[0].y *= 0.5f * (float)SCREEN_HEIGHT;
            triProjected.v[1].x *= (float)SCREEN_WIDTH / 2.0f;
            triProjected.v[1].y *= (float)SCREEN_HEIGHT / 2.0f;
            triProjected.v[2].x *= (float)SCREEN_WIDTH / 2.0f;
            triProjected.v[2].y *= (float)SCREEN_HEIGHT / 2.0f;

            // log("8. after shifting to screen ");
            // debugPrint(triProjected);
            // alternative way

            // triProjected.v[1].x *= (float)SCREEN_WIDTH;
            // triProjected.v[1].y *= (float)SCREEN_HEIGHT;
            // triProjected.v[2].x *= (float)SCREEN_WIDTH;
            // triProjected.v[2].y *= (float)SCREEN_HEIGHT;
            // log("triprojected 3");
            // debugPrint(triProjected);
            sf::Vertex line[] =
                {
                    sf::Vertex(sf::Vector2f(triProjected.v[0].x, triProjected.v[0].y)),
                    sf::Vertex(sf::Vector2f(triProjected.v[1].x, triProjected.v[1].y))};
            window.draw(line, 2, sf::Lines);
            // VVI : negative sign is given in y as sfml has down positive but my
            // calculation has coordinate system where y in up is positive.

            line[0] = sf::Vertex(sf::Vector2f(triProjected.v[1].x, triProjected.v[1].y)),
            line[1] = sf::Vertex(sf::Vector2f(triProjected.v[2].x, triProjected.v[2].y)),
            window.draw(line, 2, sf::Lines);

            line[0] = sf::Vertex(sf::Vector2f(triProjected.v[2].x, triProjected.v[2].y)),
            line[1] = sf::Vertex(sf::Vector2f(triProjected.v[0].x, triProjected.v[0].y)),
            window.draw(line, 2, sf::Lines);

            // triShape.setPoint(0, sf::Vector2f(triProjected.v[0].x, triProjected.v[0].y));
            // triShape.setPoint(1, sf::Vector2f(triProjected.v[1].x, triProjected.v[1].y));
            // triShape.setPoint(2, sf::Vector2f(triProjected.v[2].x, triProjected.v[2].y));
            // window.draw(triShape);
        }
    }
};
int main()
{
    sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "SFML works!");
    auto desktop = sf::VideoMode::getDesktopMode();
    window.setPosition(sf::Vector2i(desktop.width / 2.0f - window.getSize().x / 2, desktop.height / 2 - window.getSize().y / 2));
    Engine3d engine(window);
    // window.setFramerateLimit(240);
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        sf::VertexArray triangle(sf::Triangles, 3);

        // define the position of the triangle's points
        // triangle[0].position = sf::Vector2f(100.f, 200.f);
        // triangle[1].position = sf::Vector2f(220.f, 250.f);
        // triangle[2].position = sf::Vector2f(150.f, 300.f);
        // window.clear();
        // window.draw(triangle);
        // window.display();
        engine.updateScreen();
    }

    return 0;
}
// #include <SFML/Graphics.hpp>
// #include <iostream>
// #include <cmath>

// #define log(x) std::cout << x << std::endl;
// #define SCREEN_HEIGHT 600
// #define SCREEN_WIDTH 800

// // scaling constants
// float sx = 10.0f;
// float sy = 10.0f;
// float sz = 10.0f;
// // translation constants
// float tx = 100.0f;
// float ty = -200.0f;
// float tz = 20.0f;
// // rotation constants
// float angleXrot = 45.0f;
// float angleYrot = 50.0f;
// float angleZrot = 30.0f;

// struct vec3f
// {
//     float x, y, z;
// };
// struct triangle
// {
//     vec3f v[3];
// };
// struct mesh
// {
//     std::vector<triangle> tris;
// };
// template <class T>
// struct Matrix4x4
// {
//     T m[4][4] = {0.0f};
// };
// typedef Matrix4x4<float> Matrix44f;
// // overloaded debugPrint
// void debugPrint(triangle t)
// {
//     std::cout << "=====Triangle--debug--start=======" << std::endl;
//     for (int i = 0; i < 3; i++)
//     {
//         std::cout << t.v[i].x << " " << t.v[i].y << " " << t.v[i].z << std::endl;
//     }
//     std::cout << "=====Triangle--debug--end=======" << std::endl;
// }
// class Engine3d
// {
// private:
//     mesh meshCube;
//     sf::RenderWindow &window;
//     Matrix44f projMatrix;

// public:
//     Engine3d(sf::RenderWindow &w) : window(w)
//     {
//         meshCube.tris = {

//             // SOUTH
//             {0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f, 0.0f},
//             {0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f},

//             // EAST
//             {1.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f, 1.0f, 1.0f, 1.0f},
//             {1.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f},

//             // NORTH
//             {1.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f, 1.0f},
//             {1.0f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f},

//             // WEST
//             {0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f},
//             {0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f},

//             // TOP
//             {0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f},
//             {0.0f, 1.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f},

//             // BOTTOM
//             {1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f},
//             {1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f},

//         };

//         createProjMatrix();
//     }
//     void mulvecxMatrix(vec3f &i, vec3f &o, Matrix44f &m)
//     {
//         o.x = i.x * m.m[0][0] + i.y * m.m[1][0] + i.z * m.m[2][0] + m.m[3][0];
//         o.y = i.x * m.m[0][1] + i.y * m.m[1][1] + i.z * m.m[2][1] + m.m[3][1];
//         o.z = i.x * m.m[0][2] + i.y * m.m[1][2] + i.z * m.m[2][2] + m.m[3][2];
//         float w = i.x * m.m[0][3] + i.y * m.m[1][3] + i.z * m.m[2][3] + m.m[3][3];
//         if (w != 0.0f)
//         {
//             o.x /= w;
//             o.y /= w;
//             o.z /= w;
//         }
//     }
//     void createProjMatrix()
//     {
//         float fNear = 0.1f;
//         float fFar = 1000.0f;
//         float fFov = 40.0f;
//         float fAspectRatio = (float)SCREEN_WIDTH / (float)SCREEN_HEIGHT;
//         float fFovRad = 1.0f / tanf(fFov * 0.5f / 180.0f * 3.14159f);

//         projMatrix.m[0][0] = fAspectRatio * fFovRad;
//         projMatrix.m[1][1] = fFovRad;
//         projMatrix.m[2][2] = fFar / (fFar - fNear);
//         projMatrix.m[3][2] = (-fFar * fNear) / (fFar - fNear);
//         projMatrix.m[2][3] = 1.0f;
//         projMatrix.m[3][3] = 0.0f;
//     }
//     void updateScreen()
//     {
//         window.clear();
//         render();
//         window.display();
//     }

// private:
//     void render()
//     {
//         // sf::CircleShape circle(50);
//         // circle.setFillColor(sf::Color::Green);
//         // circle.setPosition(200, 300);
//         // window.draw(circle);
//         // sf::ConvexShape triShape;
//         // triShape.setPointCount(3);
//         float thx = (angleXrot * 3.14) / 180;
//         float thy = (angleYrot * 3.14) / 180;
//         float thz = (angleZrot * 3.14) / 180;
//         angleXrot += 0.05f;
//         angleYrot += 0.06f;
//         angleZrot += 0.04f;
//         Matrix44f rotX = {
//             1, 0, 0, 0,
//             0, cos(thx), sin(thx), 0,
//             0, -sin(thx), cos(thx), 0,
//             0, 0, 0, 1};
//         Matrix44f rotY = {
//             cos(thy), 0, -sin(thy), 0,
//             0, 1, 0, 0,
//             sin(thy), 0, cos(thy), 0,
//             0, 0, 0, 1};
//         Matrix44f rotZ = {
//             cos(thz), sin(thz), 0, 0,
//             -sin(thz), cos(thz), 0, 0,
//             0, 0, 1, 0,
//             0, 0, 0, 1};
//         Matrix44f scaling = {
//             sx, 0, 0, 0,
//             0, sy, 0, 0,
//             0, 0, sz, 0,
//             0, 0, 0, 1};
//         Matrix44f translation = {
//             1, 0, 0, 0,
//             0, 1, 0, 0,
//             0, 0, 1, 0,
//             tx, ty, tz, 1};
//         for (auto tri : meshCube.tris)
//         {
//             triangle triProjected = tri;
//             log("1. no projection");
//             debugPrint(triProjected);
//             // // scaling
//             // mulvecxMatrix(triProjected.v[0], triProjected.v[0], scaling);
//             // mulvecxMatrix(triProjected.v[1], triProjected.v[1], scaling);
//             // mulvecxMatrix(triProjected.v[2], triProjected.v[2], scaling);

//             // log("2. after scaling");
//             // debugPrint(triProjected);
//             // for z axis rotation
//             mulvecxMatrix(triProjected.v[0], triProjected.v[0], rotY);
//             mulvecxMatrix(triProjected.v[1], triProjected.v[1], rotY);
//             mulvecxMatrix(triProjected.v[2], triProjected.v[2], rotY);
//             log("3. after rotY ");
//             debugPrint(triProjected);
//             // for x axis rotation .
//             // mulvecxMatrix(triProjected.v[0], triProjected.v[0], rotX);
//             // mulvecxMatrix(triProjected.v[1], triProjected.v[1], rotX);
//             // mulvecxMatrix(triProjected.v[2], triProjected.v[2], rotX);
//             // log("4. after rotx ");
//             // debugPrint(triProjected);
//             // for z axis rotation
//             // mulvecxMatrix(triProjected.v[0], triProjected.v[0], rotZ);
//             // mulvecxMatrix(triProjected.v[1], triProjected.v[1], rotZ);
//             // mulvecxMatrix(triProjected.v[2], triProjected.v[2], rotZ);

//             // // now translation. ( for now works like a view matrix i.e. camera )
//             triProjected.v[0].z += 20.0f;
//             triProjected.v[1].z += 20.0f;
//             triProjected.v[2].z += 20.0f;
//             // by translation matrix

//             // mulvecxMatrix(triProjected.v[0], triProjected.v[0], translation);
//             // mulvecxMatrix(triProjected.v[1], triProjected.v[1], translation);
//             // mulvecxMatrix(triProjected.v[2], triProjected.v[2], translation);
//             // log("5. after translation ");
//             // debugPrint(triProjected);
//             // now projection.
//             mulvecxMatrix(triProjected.v[0], triProjected.v[0], projMatrix);
//             mulvecxMatrix(triProjected.v[1], triProjected.v[1], projMatrix);
//             mulvecxMatrix(triProjected.v[2], triProjected.v[2], projMatrix);
//             log("6. after projection");
//             debugPrint(triProjected);
//             // scaling triProjected matrix to the screen from clip coordinates(ndc)
//             // we add 1.0f as clip coordinates / ndc given  by projection matrix is in
//             // [ -1,1 ] range.
//             triProjected.v[0].x += 1.0f;
//             triProjected.v[0].y += 1.0f;
//             triProjected.v[1].x += 1.0f;
//             triProjected.v[1].y += 1.0f;
//             triProjected.v[2].x += 1.0f;
//             triProjected.v[2].y += 1.0f;

//             log("7. after shifting to [0,2] ");
//             debugPrint(triProjected);
//             triProjected.v[0].x *= 0.5f * (float)SCREEN_WIDTH;
//             triProjected.v[0].y *= 0.5f * (float)SCREEN_HEIGHT;
//             triProjected.v[1].x *= (float)SCREEN_WIDTH / 2.0f;
//             triProjected.v[1].y *= (float)SCREEN_HEIGHT / 2.0f;
//             triProjected.v[2].x *= (float)SCREEN_WIDTH / 2.0f;
//             triProjected.v[2].y *= (float)SCREEN_HEIGHT / 2.0f;

//             log("8. after shifting to screen ");
//             debugPrint(triProjected);
//             // alternative way

//             // triProjected.v[1].x *= (float)SCREEN_WIDTH;
//             // triProjected.v[1].y *= (float)SCREEN_HEIGHT;
//             // triProjected.v[2].x *= (float)SCREEN_WIDTH;
//             // triProjected.v[2].y *= (float)SCREEN_HEIGHT;
//             // log("triprojected 3");
//             // debugPrint(triProjected);
//             sf::Vertex line[] =
//                 {
//                     sf::Vertex(sf::Vector2f(triProjected.v[0].x, triProjected.v[0].y)),
//                     sf::Vertex(sf::Vector2f(triProjected.v[1].x, triProjected.v[1].y))};
//             window.draw(line, 2, sf::Lines);
//             // VVI : negative sign is given in y as sfml has down positive but my
//             // calculation has coordinate system where y in up is positive.

//             line[0] = sf::Vertex(sf::Vector2f(triProjected.v[1].x, triProjected.v[1].y)),
//             line[1] = sf::Vertex(sf::Vector2f(triProjected.v[2].x, triProjected.v[2].y)),
//             window.draw(line, 2, sf::Lines);

//             line[0] = sf::Vertex(sf::Vector2f(triProjected.v[2].x, triProjected.v[2].y)),
//             line[1] = sf::Vertex(sf::Vector2f(triProjected.v[0].x, triProjected.v[0].y)),
//             window.draw(line, 2, sf::Lines);

//             // triShape.setPoint(0, sf::Vector2f(triProjected.v[0].x, triProjected.v[0].y));
//             // triShape.setPoint(1, sf::Vector2f(triProjected.v[1].x, triProjected.v[1].y));
//             // triShape.setPoint(2, sf::Vector2f(triProjected.v[2].x, triProjected.v[2].y));
//             // window.draw(triShape);
//         }
//     }
// };

// int main()
// {
//     sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "SFML works!");
//     auto desktop = sf::VideoMode::getDesktopMode();
//     window.setPosition(sf::Vector2i(desktop.width / 2.0f - window.getSize().x / 2, desktop.height / 2 - window.getSize().y / 2));
//     while (window.isOpen())
//     {
//         sf::Event event;
//         while (window.pollEvent(event))
//         {
//             if (event.type == sf::Event::Closed)
//                 window.close();
//         }
//         sf::VertexArray triangle(sf::Triangles, 3);

//         // define the position of the triangle's points
//         triangle[0].position = sf::Vector2f(100.f, 200.f);
//         triangle[1].position = sf::Vector2f(220.f, 250.f);
//         triangle[2].position = sf::Vector2f(150.f, 300.f);
//         window.clear();
//         window.draw(triangle);
//         window.display();
//     }

//     return 0;
// }