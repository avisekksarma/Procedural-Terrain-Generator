#include "../include/cube.h"
#include "../include/glMath.h"

Cube::Cube(sf::RenderWindow &w) : window(&w), model(glMath::mat4f(1.0f)),view(1.0f),proj(1.0f)
{

	meshCube.tris = {
		// SOUTH
		{glMath::vec3f(0.0f, 0.0f, 0.0f), glMath::vec3f(0.0f, 1.0f, 0.0f), glMath::vec3f(1.0f, 1.0f, 0.0f)},
		{glMath::vec3f(0.0f, 0.0f, 0.0f), glMath::vec3f(1.0f, 1.0f, 0.0f), glMath::vec3f(1.0f, 0.0f, 0.0f)},

		// EAST
		{glMath::vec3f(1.0f, 0.0f, 0.0f), glMath::vec3f(1.0f, 1.0f, 0.0f), glMath::vec3f(1.0f, 1.0f, 1.0f)},
		{glMath::vec3f(1.0f, 0.0f, 0.0f), glMath::vec3f(1.0f, 1.0f, 1.0f), glMath::vec3f(1.0f, 0.0f, 1.0f)},

		// NORTH
		{glMath::vec3f(1.0f, 0.0f, 1.0f), glMath::vec3f(1.0f, 1.0f, 1.0f), glMath::vec3f(0.0f, 1.0f, 1.0f)},
		{glMath::vec3f(1.0f, 0.0f, 1.0f), glMath::vec3f(0.0f, 1.0f, 1.0f), glMath::vec3f(0.0f, 0.0f, 1.0f)},

		// WEST
		{glMath::vec3f(0.0f, 0.0f, 1.0f), glMath::vec3f(0.0f, 1.0f, 1.0f), glMath::vec3f(0.0f, 1.0f, 0.0f)},
		{glMath::vec3f(0.0f, 0.0f, 1.0f), glMath::vec3f(0.0f, 1.0f, 0.0f), glMath::vec3f(0.0f, 0.0f, 0.0f)},

		// TOP
		{glMath::vec3f(0.0f, 1.0f, 0.0f), glMath::vec3f(0.0f, 1.0f, 1.0f), glMath::vec3f(1.0f, 1.0f, 1.0f)},
		{glMath::vec3f(0.0f, 1.0f, 0.0f), glMath::vec3f(1.0f, 1.0f, 1.0f), glMath::vec3f(1.0f, 1.0f, 0.0f)},

		// BOTTOM
		{glMath::vec3f(1.0f, 0.0f, 1.0f), glMath::vec3f(0.0f, 0.0f, 1.0f), glMath::vec3f(0.0f, 0.0f, 0.0f)},
		{glMath::vec3f(1.0f, 0.0f, 1.0f), glMath::vec3f(0.0f, 0.0f, 0.0f), glMath::vec3f(1.0f, 0.0f, 0.0f)},

	};

	// meshCube.tris = {
	// 	{ glMath::vec3f(0.0f, 0.0f, 0.0f),    glMath::vec3f(0.0f, 100.0f, 0.0f),    glMath::vec3f(100.0f, 100.0f, 0.0f) }
	// };
}

void Cube::drawTriangle(glMath::vec3f p1, glMath::vec3f p2, glMath::vec3f p3, int color = 1)
{
	BLA(p1.x, p1.y, p2.x, p2.y, color);
	BLA(p2.x, p2.y, p3.x, p3.y, color);
	BLA(p3.x, p3.y, p1.x, p1.y, color);
}

void Cube::BLA(int x0, int y0, int xl, int yl, int color)
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

void Cube::putpixel(float x, float y, int color)
{
	sf::Vertex vertex(sf::Vector2f(x, y), sf::Color::White);
	window->draw(&vertex, 1, sf::Points);
}

void Cube::render()
{
	for (auto &i : meshCube.tris)
	{
		drawTriangle(i.p[0], i.p[1], i.p[2]);
	}
}
  
void Cube::translate(glMath::vec3f p)
{
	model = glMath::translate<float>(model, p);
}

void Cube::rotate(glMath::vec3f p, float angle)
{
	model = glMath::rotate<float>(model, (float)(PIE / 180) * (angle), p);
}

void Cube::perspective(float fov,float sw,float sh,float nearZ,float farZ){
	model = glMath::perspective<float>(model, fov,sw,sh,nearZ,farZ);
}

void Cube::updateVertices()
{
	for (auto &i : meshCube.tris)
	{
		for (auto &j : i.p)
		{
			glMath::vec3f v(j.x, j.y, j.z);
			v = proj * view * model * v;
			j = glMath::vec3f(v.x, v.y, v.z);
		}
	}
}
void Cube::scale(glMath::vec3f p)
{
	model = glMath::scale(model, p);
}