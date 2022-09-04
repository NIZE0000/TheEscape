/*
 * Map.cpp
 *
 *  Created on: Sep 3, 2022
 *      Author: Nice
 */

#include "Map.h"
#include "texture.h"
#include <glm/vec3.hpp>
#include <pch.h>

// vector<Texture2D> grounds, walls;
// Texture2D ground;

Map::Map()
{
	// TODO Auto-generated constructor stub

	this->grid = 85.333333333; // 1/6 grid base on 512 equation of 1.0 / 6.0 * 512
	this->wallHeight = 50;
}

Map::~Map()
{
	// TODO Auto-generated destructor stub
}

void Map::render()
{
	glPushMatrix();

	Texture2D ground;

	ground.Generate("ground.jpg", this->grid, this->grid);


	// ground render
	glColor3f(0.5, 0.4, 0.3);
	glBegin(GL_TRIANGLE_STRIP);
	glTexCoord3f(0*1/6, 0.0, 6*1/6);
	glVertex3f(-256.0, 0.0, 256.0);
	
	glTexCoord3f(6*1/6, 0.0, 6*1/6);
	glVertex3f(256.0, 0.0, 256.0);

	glTexCoord3f(0*1/6, 0.0, 0*1/6);
	glVertex3f(-256.0, 0.0, -256.0);
	
	glTexCoord3f(6*1/6, 0.0, 0*1/6);
	glVertex3f(256.0, 0.0, -256.0);
	glEnd();

	

	// wall
	glColor3f(0.5, 0.2, 0.1);

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
	glBegin(GL_TRIANGLE_STRIP);
	glVertex3f(point[0][0] * this->grid, 0, point[0][1] * this->grid);
	glVertex3f(point[1][0] * this->grid, 0, point[1][1] * this->grid);
	glVertex3f(point[0][0] * this->grid, this->wallHeight, point[0][1] * this->grid);
	glVertex3f(point[1][0] * this->grid, this->wallHeight, point[1][1] * this->grid);
	glEnd();

	glBegin(GL_TRIANGLE_STRIP);
	glVertex3f(point[1][0] * this->grid, 0, point[1][1] * this->grid);
	glVertex3f(point[0][0] * this->grid, 0, point[0][1] * this->grid);
	glVertex3f(point[1][0] * this->grid, this->wallHeight, point[1][1] * this->grid);
	glVertex3f(point[0][0] * this->grid, this->wallHeight, point[0][1] * this->grid);
	glEnd();
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