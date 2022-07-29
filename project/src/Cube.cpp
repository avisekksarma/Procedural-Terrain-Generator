#include "../include/cube.h"
#include "../include/glMath.h"

Cube::Cube(sf::RenderWindow& w): window(&w),model(glMath::mat4f(1.0f)),view(1.0f),proj(1.0f) {

	local.tris = {
		// SOUTH
		{ glMath::vec3f(-0.5f, 0.5f, 0.5f),    glMath::vec3f(-0.5f, 0.5f, 0.5f),    glMath::vec3f(0.5f, 0.5f, 0.5f) },
		{ glMath::vec3f(-0.5f, 0.5f, 0.5f),    glMath::vec3f(0.5f, 0.5f, 0.5f),    glMath::vec3f(0.5f, -0.5f, 0.5f) },

		// EAST                                                      
		{ glMath::vec3f(-0.5f, -0.5f, 0.5f),    glMath::vec3f(-0.5f, 0.5f, 0.5f),    glMath::vec3f(-0.5f, 0.5f, -0.5f) },
		{ glMath::vec3f(-0.5f, -0.5f, 0.5f),    glMath::vec3f(-0.5f, 0.5f, -0.5f),    glMath::vec3f(-0.5f, -0.5f, -0.5f) },

		// NORTH                                                     
		{ glMath::vec3f(-0.5f, 0.5f, -0.5f),    glMath::vec3f(0.5f, 0.5f, -0.5f),    glMath::vec3f(-0.5f, -0.5f, -0.5f) },
		{ glMath::vec3f(-0.5f, -0.5f, -0.5f),    glMath::vec3f(0.5f, 0.5f, -0.5f),    glMath::vec3f(0.5f, -0.5f, -0.5f) },

		// WEST                                                      
		{ glMath::vec3f(0.5f, -0.5f, 0.5f),    glMath::vec3f(0.5f, 0.5f, 0.5f),    glMath::vec3f(0.5f, 0.5f, -0.5f) },
		{ glMath::vec3f(0.5f, -0.5f, 0.5f),    glMath::vec3f(0.5f, 0.5f, -0.5f),    glMath::vec3f(0.5f, -0.5f, -0.5f) },

		// TOP                                                       
		{ glMath::vec3f(-0.5f, 0.5f, 0.5f),    glMath::vec3f(-0.5f, 0.5f, -0.5f),    glMath::vec3f(0.5f, 0.5f, -0.5f) },
		{ glMath::vec3f(-0.5f, 0.5f, 0.5f),    glMath::vec3f(0.5f, 0.5f, -0.5f),    glMath::vec3f(0.5f, 0.5f, 0.5f) },

		// BOTTOM                                                    
		{ glMath::vec3f(-0.5f, -0.5f, 0.5f),    glMath::vec3f(-0.5f, -0.5f, -0.5f),    glMath::vec3f(0.5f, -0.5f, -0.5f) },
		{ glMath::vec3f(-0.5f, -0.5f, 0.5f),    glMath::vec3f(0.5f, -0.5f, -0.5f),    glMath::vec3f(0.5f, -0.5f, 0.5f) },

	};
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
	model = glMath::rotate<float>(model, glMath::degToRadians(angle) ,p);
}

void Cube::perspective(float fov,float sw,float sh,float nearZ,float farZ){
	proj = glMath::perspective<float>(view, fov,sw,sh,nearZ,farZ);
}


// fills the meshcube upto to be rendered part i.e. upto projection done
void Cube::updateVertices()
{
	meshCube.tris.clear();
	for (auto i : local.tris) {
		glMath::trianglef t;
		int count = 0;
		for (auto j : i.p)
		{
			glMath::vec4f v (j.x, j.y, j.z,1);
			// glMath::vec3f v ((j.x + 1)*540, (j.y-1)*(-360), j.z);
			v =  proj * v;
			if(v.w!=1 and v.w!=0){
				v.x /= v.w;
				v.y /= v.w;
				v.z /= v.w;
				v.w = 1;
			}
			t.p[count++] = glMath::vec3f(v.x, v.y, v.z);
		}
		meshCube.tris.push_back(t);
	}
	toWindowCoord();
}

void Cube::toWindowCoord()
{
	for (auto &i : meshCube.tris) {
		for (auto &j : i.p)
		{
			glMath::vec3f v(j.x, j.y, j.z);
			j = glMath::vec3f((v.x + 1)*540, (v.y-1)*(-360), v.z);
		}
	}
	
}
void Cube::scale(glMath::vec3f p)
{
	model = glMath::scale(model, p);
}