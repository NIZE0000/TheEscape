/*
 * Map.cpp
 *
 *  Created on: Sep 3, 2022
 *      Author: Nice
 */

#include <Map.h>
#include <pch.h>

Map::Map()
{
	// TODO Auto-generated constructor stub

	this->grid = 85.333333333; // 1/6 grid base on 512 equation of 1.0 / 6.0 * 512
	this->wallHeight = 100;

	this->bound[7][7][2] ; // for store all in X and Z axis to ref position in 1/6 grid

	for (int i = 0; i < 7; i++)
	{
		for (int j = 0; j < 7; j++)
		{
			this->bound[i][j][0] = this->grid * (-3 + j);
			this->bound[i][j][1] = this->grid * (-3 + i);
			std::cout << this->bound[i][j][0] << ", " << this->bound[i][j][1] <<" ";
		}
		std::cout<<std::endl;
	}
}

void Map::loadTexture()
{
	this->ground.ID = 0;
	this->ground.Generate("/home/Nice/GL/The Escape/assets/textures/ground.jpg", 512, 512);
	this->wall.ID = 1;
	this->wall.Generate("/home/Nice/GL/The Escape/assets/textures/wall.jpg", 500, 500);
}

Map::~Map()
{
	// TODO Auto-generated destructor stub
	this->ground.Delete();
	this->wall.Delete();
}

void Map::render()
{
	this->ground.Bind(); // binding ground texture

	// render ground
	glPushMatrix();

	glPushAttrib(GL_TEXTURE_BIT);
	glEnable(GL_TEXTURE_2D);

	glColor3f(0.7, 0.7, 0.7);
	glBegin(GL_TRIANGLE_STRIP);
	glTexCoord2f(0.0, 0.0);
	glVertex3f(-256.0, 0.0, 256.0);
	glTexCoord2f(6.0, 0.0);
	glVertex3f(256.0, 0.0, 256.0);
	glTexCoord2f(0.0, 6.0);
	glVertex3f(-256.0, 0.0, -256.0);
	glTexCoord2f(6.0, 6.0);
	glVertex3f(256.0, 0.0, -256.0);
	glEnd();

	glPopAttrib();

	this->wall.Bind(); // binding wall texture

	glPushAttrib(GL_TEXTURE_BIT);
	glEnable(GL_TEXTURE_2D);

	// render Roof
	glColor3f(0.6, 0.6, 0.6);
	glBegin(GL_TRIANGLE_STRIP);
	glTexCoord2f(0.0, 0.0);
	glVertex3f(256.0, this->wallHeight, 256.0);
	glTexCoord2f(6.0, 0.0);
	glVertex3f(-256.0, this->wallHeight, 256.0);
	glTexCoord2f(0.0, 6.0);
	glVertex3f(256.0, this->wallHeight, -256.0);
	glTexCoord2f(6.0, 6.0);
	glVertex3f(-256.0, this->wallHeight, -256.0);
	glEnd();
	glPopAttrib();

	// render wall
	glColor3f(0.6, 0.6, 0.6);

	float walls[][2][2] = {
		{{-3, 3}, {3, 3}},
		{{-3, 3}, {-3, 2}},
		{{-3, 2}, {-1, 2}},
		{{0, 2}, {1, 2}},
		{{2, 2}, {3, 2}},
		{{-1, 2}, {-1, 0}},
		{{0, 2}, {0, 0}},
		{{1, 2}, {1, 0}},
		{{2, 2}, {2, -2}},
		{{3, 3}, {3, 2}},
		{{-3, 0}, {-1, 0}},
		{{0, 0}, {1, 0}},
		{{-3, 0}, {-1, 0}},
		{{-3, 0}, {-3, -1}},
		{{-3, -1}, {1, -1}},
		{{-3, 0}, {-3, -1}},
		{{1, -1}, {1, -3}},
		{{1, -3}, {3, -3}},
		{{3, -2}, {3, -3}},
		{{2, -2}, {3, -2}},

	};
	for (int i = 0; i < sizeof(walls) / 16; i++)
	{
		float wall[][2] = {
			{walls[i][0][0], walls[i][0][1]}, {walls[i][1][0], walls[i][1][1]}};
		Map::drawWall(wall);
	}

	glPopMatrix();
}

void Map::drawWall(float point[][2])
{
	float dif = (abs((point[0][0]) - (point[1][0]))) + (abs((point[0][1]) - (point[1][1])));
	// std::cout<<dif<<" "<< " "<< (point[0][0])<<std::endl; // debug

	glPushAttrib(GL_TEXTURE_BIT);
	glEnable(GL_TEXTURE_2D);

	glBegin(GL_TRIANGLE_STRIP);
	glTexCoord2f(0.0, 0.0);
	glVertex3f(point[0][0] * this->grid, 0, point[0][1] * this->grid);
	glTexCoord2f(dif, 0.0);
	glVertex3f(point[1][0] * this->grid, 0, point[1][1] * this->grid);
	glTexCoord2f(0.0, 1);
	glVertex3f(point[0][0] * this->grid, this->wallHeight, point[0][1] * this->grid);
	glTexCoord2f(dif, 1);
	glVertex3f(point[1][0] * this->grid, this->wallHeight, point[1][1] * this->grid);
	glEnd();

	glBegin(GL_TRIANGLE_STRIP);
	glTexCoord2f(0.0, 0.0);
	glVertex3f(point[1][0] * this->grid, 0, point[1][1] * this->grid);
	glTexCoord2f(dif, 0.0);
	glVertex3f(point[0][0] * this->grid, 0, point[0][1] * this->grid);
	glTexCoord2f(0.0, 1);
	glVertex3f(point[1][0] * this->grid, this->wallHeight, point[1][1] * this->grid);
	glTexCoord2f(dif, 1);
	glVertex3f(point[0][0] * this->grid, this->wallHeight, point[0][1] * this->grid);
	glEnd();

	glPopAttrib();
}

void Map::drawGround(float point[][2])
{
	glBegin(GL_TRIANGLE_STRIP);
	glVertex3f(point[0][0] * this->grid, 0, point[0][1] * this->grid);
	glVertex3f(point[1][0] * this->grid, 0, point[1][1] * this->grid);
	glVertex3f(point[2][0] * this->grid, 0, point[2][1] * this->grid);
	glVertex3f(point[3][0] * this->grid, 0, point[3][1] * this->grid);
	glEnd();
}

bool Map::checkBoundary(float position[3])
{
	// if (this->position[0] this->position[1] this->position[2])
	// {
	// 	/* code */
	// }

	// return true;
}