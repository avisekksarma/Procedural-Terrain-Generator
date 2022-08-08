#include "../include/terrain.h"
#include "../include/glMath.h"
#include "../include/constants.h"
#include <list>
#include <iostream>
#include "../include/PerlinNoise.hpp"
#include "../include/perlin.h"
#include "../include/random.hpp"

using namespace std;
using Random = effolkronium::random_static;

Terrain::Terrain(sf::RenderWindow &w,Context & c) :window(&w),context(c),model(glMath::mat4f(1.0f)), view(1.0f), proj(1.0f), zbuffer(constants::SCREEN_WIDTH, constants::SCREEN_HEIGHT)
{

}

void Terrain::drawTriangle(glMath::vec3f p1, glMath::vec3f p2, glMath::vec3f p3, sf::Color color)
{

    BLA(p1.x, p1.y, p2.x, p2.y, color);
    BLA(p2.x, p2.y, p3.x, p3.y, color);
    BLA(p3.x, p3.y, p1.x, p1.y, color);
}

void Terrain::BLA(int x0, int y0, int xl, int yl, sf::Color color)
{
    int delx = std::fabs(xl - x0);
    int dely = std::fabs(yl - y0);
    int a = 0, b = 0;
    int p = 0;
    a = ((xl - x0) > 0) ? 1 : -1;
    b = ((yl - y0) > 0) ? 1 : -1;
    if (delx > dely)
    {
        p = 2 * dely - delx;
        for (int i = 0; i <= delx; i++)
        {

            putpixel(x0, y0, color);
            x0 += a;
            if (p <= 0)
                p += 2 * dely;
            else
            {
                p += 2 * dely - 2 * delx;
                y0 += b;
            }
        }
    }
    else
    {
        p = 2 * delx - dely;
        for (int i = 0; i <= dely; i++)
        {
            putpixel(x0, y0, color);
            y0 += b;
            if (p <= 0)
                p += 2 * delx;
            else
            {
                p += 2 * delx - 2 * dely;
                x0 += a;
            }
        }
    }
}

void Terrain::putpixel(float x, float y, sf::Color color)
{

    sf::Vertex vertex(sf::Vector2f(x, y), color);
    window->draw(&vertex, 1, sf::Points);
}

void Terrain::render()
{
    sf::Color colors[12] = {
        // red
        sf::Color(255, 0, 0),
        sf::Color(255, 0, 0),
        // green
        sf::Color(0, 255, 0),
        sf::Color(0, 255, 0),
        // blue
        sf::Color(0, 0, 255),
        sf::Color(0, 0, 255),

        sf::Color(255, 255, 0),
        sf::Color(255, 255, 0),

        sf::Color(0, 255, 255),
        sf::Color(0, 255, 255),

        sf::Color(255, 0, 255),
        sf::Color(255, 0, 255),
    };
    int count = 0;
    for (auto &i : listTriangles)
    {

        // drawTriangle(i.p[0], i.p[1], i.p[2], sf::Color(0, 0, 0));
        // fillTriangle(i.p[0], i.p[1], i.p[2], colors[count++]);
        // fillTriangle(i.p[0], i.p[1], i.p[2], sf::Color(255,255,255));
        fillTriangle(i.p[0], i.p[1], i.p[2], sf::Color(i.red, i.green, i.blue));
        // if (count == 12)
        // {
        //     count = 0;
        // }
    }
}

void Terrain::translate(glMath::vec3f p)
{
    p.x = (float)(2 * p.x) / constants::SCREEN_WIDTH;
    p.y = (float)(2 * p.y) / constants::SCREEN_HEIGHT;

    model = glMath::translate<float>(model, p);
}

void Terrain::rotate(glMath::vec3f p, float angle)
{
    model = glMath::rotate<float>(model, glMath::degToRadians(angle), p);
}

void Terrain::scale(glMath::vec3f p)
{
    model = glMath::scale<float>(model, p);
}

void Terrain::perspective(float fov, float sw, float sh, float nearZ, float farZ)
{
    proj = glMath::perspective<float>(fov, sw, sh, nearZ, farZ);
}

void Terrain::lookAt(glMath::vec3f from, glMath::vec3f to, glMath::vec3f temp)
{
    view = glMath::lookAt<float>(from, to, temp);
}

// fills the meshTerrain upto to be rendered part i.e. upto projection done
void Terrain::updateVertices()
{
    meshTerrain.tris.clear();
    listTriangles.clear();
    zbuffer.Clear();

    for (auto i : local.tris)
    {
        glMath::trianglef triafterView;

        int k = 0;


        for (auto j : i.p)
        {
            glMath::vec4f v(j.x, j.y, j.z, 1);
            v = view * model * v;
            triafterView.p[k] = glMath::vec3f(v.x, v.y, v.z);
            k++;
        }

        // ------------------------------
        // Backface Detection
        // ------------------------------

        // glMath::vec3f line2 = triafterView.p[2]-triafterView.p[0];
        // glMath::vec3f line1 = triafterView.p[1]-triafterView.p[0];
        // glMath::vec3f normal =glMath::cross<float>(line2,line1);
        // normal = glMath::normalize(normal);
        // // glMath::vec3f camDir = -context.cargs.cameraFront;
		// glMath::vec3f camDir = context.cargs.cameraPos + context.cargs.cameraFront;
        // camDir = glMath::normalize(camDir);
        // if(glMath::dot(normal,camDir)>0.1){
        //     // std::cout<<"gayo"<<std::endl;
        //     continue;
        // }

        int nClippedTriangles = 0;
        glMath::trianglef clipped[2];
        // the w component is 1 until it is projected by pers. matrix
        // TODO: for now i put 1.0f in plane too.
        // camera and clipping works version
        // nClippedTriangles = glMath::triangleNumClippedInPlane<float>({0.0f, 0.0f, -1.5f}, {0.0f, 0.0f, -1.0f}, triafterView, clipped[0], clipped[1]);
        nClippedTriangles = glMath::triangleNumClippedInPlane<float>({0.0f, 0.0f, -1.5f}, {0.0f, 0.0f, -1.0f}, triafterView, clipped[0], clipped[1]);
        // say looping in two triangles.
        for (int m = 0; m < nClippedTriangles; m++)
        {
            glMath::trianglef t;
            int count = 0;
            // looping in each vertex of a  triangle
            for (auto &j : clipped[m].p)
            {
                glMath::vec4f v(j.x, j.y, j.z, 1);
                // glMath::vec3f v ((j.x + 1)*540, (j.y-1)*(-360), j.z);
                // v =  proj*view*model * v;
                v = proj * v;
                // perspective division
                if (v.w != 1 and v.w != 0)
                {
                    v.x /= v.w;
                    v.y /= v.w;
                    v.z /= v.w;
                    // v.w = 1;
                }
                t.p[count++] = glMath::vec3f(v.x, v.y, v.z);
            }


            t.p[0].x = (int)(((t.p[0].x + 1) * 540) + 0.5);
            t.p[0].y = (int)(((t.p[0].y - 1) * -360) + 0.5);
            t.p[1].x = (int)(((t.p[1].x + 1) * 540) + 0.5);
            t.p[1].y = (int)(((t.p[1].y - 1) * -360) + 0.5);
            t.p[2].x = (int)(((t.p[2].x + 1) * 540) + 0.5);
            t.p[2].y = (int)(((t.p[2].y - 1) * -360) + 0.5);

            t.red = i.red;
            t.green = i.green;
            t.blue = i.blue;
            meshTerrain.tris.push_back(t);
        }
    }
    // cout << "SIZEOF MESH before clipping:" << meshTerrain.tris.size() << endl;
    clipAgainstPlanes();
    // cout << "SIZEOF MESH after clipping:" << meshTerrain.tris.size() << endl;
}

void Terrain::clipAgainstPlanes()
{
    int countOfTriangles = 0;
    for (auto &triToRaster : meshTerrain.tris)
    {
        // Clip triangles against all four screen edges, this could yield
        // a bunch of triangles, so create a queue that we traverse to
        //  ensure we only test new triangles generated against planes
        glMath::trianglef clipped[2];
        // listTriangles;
        std::list<glMath::trianglef> tempListTriangles;

        // Add initial triangle
        tempListTriangles.push_back(triToRaster);
        int nNewTriangles = 1;

        for (int p = 0; p < 4; p++)
        {
            int nTrisToAdd = 0;
            while (nNewTriangles > 0)
            {
                // Take triangle from front of queue
                glMath::trianglef test = tempListTriangles.front();
                tempListTriangles.pop_front();
                nNewTriangles--;

                // Clip it against a plane. We only need to test each
                // subsequent plane, against subsequent new triangles
                // as all triangles after a plane clip are guaranteed
                // to lie on the inside of the plane. I like how this
                // comment is almost completely and utterly justified
                switch (p)
                {
                case 0:
                    nTrisToAdd = glMath::triangleNumClippedInPlane({0.0f, 0.0f, 0.0f}, {0.0f, 50.0f, 0.0f}, test, clipped[0], clipped[1]);
                    break;
                case 1:
                    nTrisToAdd = glMath::triangleNumClippedInPlane({0.0f, (float)(constants::SCREEN_HEIGHT)-1, 0.0f}, {0.0f, -1.0f, 0.0f}, test, clipped[0], clipped[1]);
                    break;
                case 2:
                    nTrisToAdd = glMath::triangleNumClippedInPlane({0.0f, 0.0f, 0.0f}, {1.0f, 0.0f, 0.0f}, test, clipped[0], clipped[1]);
                    break;
                case 3:
                    nTrisToAdd = glMath::triangleNumClippedInPlane({(float)(constants::SCREEN_WIDTH)-1, 0.0f, 0.0f}, {-1.0f, 0.0f, 0.0f}, test, clipped[0], clipped[1]);
                    break;
                }

                // Clipping may yield a variable number of triangles, so
                // add these new ones to the back of the queue for subsequent
                // clipping against next planes
                for (int w = 0; w < nTrisToAdd; w++)
                {
                    tempListTriangles.push_back(clipped[w]);
                }
            }
            nNewTriangles = tempListTriangles.size();
        }
        countOfTriangles += tempListTriangles.size();
        for (auto &i : tempListTriangles)
        {
            i.red = triToRaster.red;
            i.green = triToRaster.green;
            i.blue = triToRaster.blue;
            listTriangles.push_back(i);
        }
    }
    // cout << "SIZEOF MESH after the screen clipping:" << countOfTriangles << endl;
}
void Terrain::toWindowCoord()
{
    for (auto &i : meshTerrain.tris)
    {
        for (auto &j : i.p)
        {
            glMath::vec3f v(j.x, j.y, j.z);
            // std::cout<<window->getSize().x<<" "<<window->getSize().y<<std::endl;
            j = glMath::vec3f((v.x + 1) * (window->getSize().x / 2.0f), -(v.y - 1) * (window->getSize().y / 2.0f), v.z);
        }
    }
}

void Terrain::fillBottomFlatTriangle(glMath::vec3f v1, glMath::vec3f v2, glMath::vec3f v3, sf::Color color)
{
    float invslope1 = (float)(v2.x - v1.x) / (v2.y - v1.y);
    float invslope2 = (float)(v3.x - v1.x) / (v3.y - v1.y);

    // float avgZ = (v1.z+v2.z+v3.z)/3.f;

    float curx1 = v1.x;
    float curx2 = v1.x;

    for (int scanlineY = v1.y; scanlineY <= v2.y; scanlineY++)
    {
        // BLA((int)curx1, scanlineY, (int)curx2, scanlineY, 1);
        // scanLine((int)curx1, scanlineY, (int)curx2, scanlineY, avgZ, color);
        scanLine((int)curx1, scanlineY, (int)curx2, scanlineY, color);
        curx1 += invslope1;
        curx2 += invslope2;
    }
}

void Terrain::fillTopFlatTriangle(glMath::vec3f v1, glMath::vec3f v2, glMath::vec3f v3, sf::Color color)
{
    float invslope1 = (v3.x - v1.x) / (v3.y - v1.y);
    float invslope2 = (v3.x - v2.x) / (v3.y - v2.y);

    float curx1 = v3.x;
    float curx2 = v3.x;

    for (int scanlineY = v3.y; scanlineY > v1.y; scanlineY--)
    {
        scanLine((int)curx1, scanlineY, (int)curx2, scanlineY, color);
        curx1 -= invslope1;
        curx2 -= invslope2;
    }
}

void Terrain::scanLine(int x0, int y0, int x1, int y1, sf::Color color)
{
    int delx = std::fabs(x1 - x0);
    int a = 0;
    a = ((x1 - x0) > 0) ? 1 : -1;
    float z;
    int tempX = x0;
    for (int i = 0; i <= delx; i++)
    {
        z = zbuffer.returnZ(x0, y0);
        if (zbuffer.TestAndSet(x0, y0, z))
        {
            if ( x0 == tempX || x0 == x1 )
            {
                if (color.r != 255 && color.g != 255 && color.b != 255)
                {
                    putpixel(x0, y0, sf::Color::Black);
                }
                else
                {
                    putpixel(x0, y0, color);
                }
            }
            else 
            {
                putpixel(x0, y0, color);
            }

            // putpixel(x0, y0, color);
        }
        // z = z - (zbuffer.plane.A / zbuffer.plane.C);
        x0 += a;
    }
}

void Terrain::fillTriangle(glMath::vec3f vt1, glMath::vec3f vt2, glMath::vec3f vt3, sf::Color color)
{
    zbuffer.makePlaneEquation(vt1, vt2, vt3);
    std::vector<glMath::vec3f> v;
    v.push_back(vt1);
    v.push_back(vt2);
    v.push_back(vt3);

    for (unsigned int i = 0; i < v.size(); i++)
    {
        for (auto itj = v.begin(); itj != v.end() - 1; itj = std::next(itj))
        {
            if ((*itj).y > (*std::next(itj)).y)
            {
                std::swap(*itj, *std::next(itj));
            }
        }
    }

    vt1 = v.at(0);
    vt2 = v.at(1);
    vt3 = v.at(2);
    /* here we know that v1.y <= v2.y <= v3.y */
    /* check for trivial case of bottom-flat triangle */
    if (vt2.y == vt3.y)
    {
        fillBottomFlatTriangle(vt1, vt2, vt3, color);
    }
    /* check for trivial case of top-flat triangle */
    else if (vt1.y == vt2.y)
    {
        fillTopFlatTriangle(vt1, vt2, vt3, color);
    }
    else
    {
        /* general case - split the triangle in a topflat and bottom-flat one */
        glMath::vec3f v4 = glMath::vec3f(
            (int)(vt1.x + ((float)(vt2.y - vt1.y) / (float)(vt3.y - vt1.y)) * (vt3.x - vt1.x)), vt2.y, 0.0f);
        fillBottomFlatTriangle(vt1, vt2, v4, color);
        fillTopFlatTriangle(vt2, v4, vt3, color);
    }
}

void Terrain::generateInitialTerrain(int _x, int _z, int _w, int _l)
{
    local.tris.clear();
    colorMap.clear();
    consts.create(_x, _z, _w, _l);
    int row = consts.lengthZ / consts.ztrilen;
    int col = consts.widthX / consts.xtrilen;
    glMath::trianglef up;
    glMath::trianglef down;
    int x = consts.XTopLeft;
    int z = consts.ZTopLeft;

    float incX = (float)(2 * consts.xtrilen) / constants::SCREEN_WIDTH;
    float incZ = (float)(2 * consts.ztrilen) / constants::SCREEN_HEIGHT;

    int val = Random::get(1000,6000);
    Perlin perlin(4, 1.2f, 1.1f, val);

    double perlinNoise[6] = {0.0f};
    for (int i = 0; i < row; i++)
    {
        x = consts.XTopLeft;
        for (int j = 0; j < col; j++)
        {
            glMath::vec3f lC;
            lC = glMath::returnLocalCoords<float>(glMath::vec3f(x, z, 0.0f));

            up.p[1] = glMath::vec3f(lC.x, fabs(perlin.Get(lC.x, lC.y)), lC.y);
            up.p[2] = glMath::vec3f(lC.x + incX, fabs(perlin.Get(lC.x + incX, lC.y)), lC.y);
            up.p[0] = glMath::vec3f(lC.x, fabs(perlin.Get(lC.x, lC.y+incZ)), lC.y + incZ);

            down.p[0] = glMath::vec3f(lC.x, fabs(perlin.Get(lC.x, lC.y + incZ)), lC.y + incZ);
            down.p[1] = glMath::vec3f(lC.x + incX, fabs(perlin.Get(lC.x + incX, lC.y)), lC.y);
            down.p[2] = glMath::vec3f(lC.x + incX, fabs(perlin.Get(lC.x + incX, lC.y + incZ)), lC.y + incZ);

            float upAvg = (up.p[0].y + up.p[1].y + up.p[2].y)/3.f;
            float downAvg = (down.p[0].y + down.p[1].y + down.p[2].y)/3.f;

            if (up.p[1].y >= 0.5 )
            {
                // colorMap.push_back(sf::Color::Green);
                up.red = 255;
                up.green = 255;
                up.blue = 255;
            }
            else if (up.p[1].y >= 0.25)
            {
                up.red = 0;
                up.green = 140;
                up.blue = 19;
            }
            else if (up.p[1].y >= 0.1)
            {
                up.red = 0;
                up.green = 102;
                up.blue = 14;
            }
            else 
            {
                up.red = 15;
                up.green = 54;
                up.blue = 123;
            }

            if (down.p[1].y >= 0.5 )
            {
                // colorMap.push_back(sf::Color::Green);
                down.red = 255;
                down.green = 255;
                down.blue = 255;
            }
            else if (down.p[1].y >= 0.3)
            {
                down.red = 0;
                down.green = 140;
                down.blue = 19;
            }
            else if (down.p[1].y >= 0.1)
            {
                down.red = 0;
                down.green = 102;
                down.blue = 14;
            }
            else 
            {
                down.red = 15;
                down.green = 54;
                down.blue = 123;
            }



            x += consts.xtrilen;
            local.tris.push_back(up);
            local.tris.push_back(down);
        }
        z += consts.ztrilen;
    }
}

int xSize = 20;
int zSize = 20;

void Terrain::initTerrain()
{
    Perlin perlin(4, 2.f, 2.f, 1234);
    auto vertices = new glMath::vec3f[(xSize + 1) * (zSize + 1)];
    for (int i=0, z=0; z <= zSize; z ++)
    {
        for ( int x=0; x <= xSize; x ++)
        {
            float y = perlin.Get(x * 0.3f, y * 0.3f);
            vertices[i] = glMath::vec3f(consts.XTopLeft + x, y, consts.ZTopLeft + z);
            i++;
        }
    }

}
