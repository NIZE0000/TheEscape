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

	this->grid = 85.333333333; // 6 grid base on 512 equation of 1.0 / 6.0 * 512
	this->wallHeight = 100;

	this->bound[7][7][2]; //  for store all in X and Z axis to ref position  6 grid
	for (int i = 0; i < 7; i++)
	{
		for (int j = 0; j < 7; j++)
		{
			this->bound[i][j][0] = this->grid * (-3 + j);
			this->bound[i][j][1] = this->grid * (3 - i);
			// std::cout << this->bound[i][j][0] << ", " << this->bound[i][j][1] << " ";
		}
		// std::cout << std::endl;
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
	{					 // render ground

		glPushAttrib(GL_TEXTURE_BIT);
		glEnable(GL_TEXTURE_2D);

		glColor3f(0.7, 0.7, 0.7);
		glBegin(GL_TRIANGLE_STRIP);
		glTexCoord2f(0.0, 0.0);
		glTexCoord2f(0.0, 0.0);
		glVertex3f(this->bound[6][6][0], 0.0, this->bound[6][6][1]);
		glTexCoord2f(6.0, 0.0);
		glVertex3f(this->bound[6][0][0], 0.0, this->bound[6][0][1]);
		glTexCoord2f(0.0, 6.0);
		glVertex3f(this->bound[0][6][0], 0.0, this->bound[0][6][1]);
		glTexCoord2f(6.0, 6.0);
		glVertex3f(this->bound[0][0][0], 0.0, this->bound[0][0][1]);

		glEnd();

		glPopAttrib();
	}

	this->wall.Bind(); // binding wall texture
	{				   // render Roof
		glPushAttrib(GL_TEXTURE_BIT);
		glEnable(GL_TEXTURE_2D);

		glColor3f(0.6, 0.6, 0.6);
		glBegin(GL_TRIANGLE_STRIP);
		glVertex3f(this->bound[6][0][0], this->wallHeight, this->bound[6][0][1]);
		glTexCoord2f(6.0, 0.0);
		glVertex3f(this->bound[6][6][0], this->wallHeight, this->bound[6][6][1]);
		glTexCoord2f(0.0, 6.0);
		glVertex3f(this->bound[0][0][0], this->wallHeight, this->bound[0][0][1]);
		glTexCoord2f(6.0, 6.0);
		glVertex3f(this->bound[0][6][0], this->wallHeight, this->bound[0][6][1]);
		glEnd();
		glPopAttrib();
	}

	// render wall
	glColor3f(0.6, 0.6, 0.6);

	glRotatef(180.0, 0.0, 1.0, 0.0);

	for (int i = 0; i < sizeof(this->walls) / 16; i++)
	{
		int index[2][2] = {
			{this->walls[i][0][0], this->walls[i][0][1]}, /// row
			{this->walls[i][1][0], this->walls[i][1][1]}, // colume
		};

		float wall[][2] = {
			{
				this->bound[index[0][0]][index[0][1]][0], // x
				this->bound[index[0][0]][index[0][1]][1], // z
			},
			{
				this->bound[index[1][0]][index[1][1]][0], // x
				this->bound[index[1][0]][index[1][1]][1], // z
			}};

		Map::drawWall(wall);
	}
	glRotatef(-180.0, 0.0, 1.0, 0.0);
}

void Map::drawWall(float point[][2])
{
	float dif = (abs((point[0][0]) - (point[1][0])) + abs((point[0][1]) - (point[1][1]))) / this->grid; // use for repeat texture on correct axis

	glPushAttrib(GL_TEXTURE_BIT);
	glEnable(GL_TEXTURE_2D);

	glBegin(GL_TRIANGLE_STRIP);
	glTexCoord2f(0.0, 0.0);
	glVertex3f(point[0][0], 0, point[0][1]);
	glTexCoord2f(dif, 0.0);
	glVertex3f(point[1][0], 0, point[1][1]);
	glTexCoord2f(0.0, 1);
	glVertex3f(point[0][0], this->wallHeight, point[0][1]);
	glTexCoord2f(dif, 1);
	glVertex3f(point[1][0], this->wallHeight, point[1][1]);
	glEnd();

	glBegin(GL_TRIANGLE_STRIP);
	glTexCoord2f(0.0, 0.0);
	glVertex3f(point[1][0], 0, point[1][1]);
	glTexCoord2f(dif, 0.0);
	glVertex3f(point[0][0], 0, point[0][1]);
	glTexCoord2f(0.0, 1);
	glVertex3f(point[1][0], this->wallHeight, point[1][1]);
	glTexCoord2f(dif, 1);
	glVertex3f(point[0][0], this->wallHeight, point[0][1]);
	glEnd();

	glPopAttrib();
}

bool Map::checkCollision(float *x, float *y, float *z) // AABB - AABB collision
{

	// not done yet
	int space = 5;

	for (int i = 0; i < sizeof(this->walls) / 16; i++)
	{
		int index[2][2] = {
			{this->walls[i][0][0], this->walls[i][0][1]}, /// row
			{this->walls[i][1][0], this->walls[i][1][1]}, // colume
		};

		float wall[][2] = {
			{
				this->bound[index[0][0]][index[0][1]][0], // x
				this->bound[index[0][0]][index[0][1]][1], // z
			},
			{
				this->bound[index[1][0]][index[1][1]][0], // x
				this->bound[index[1][0]][index[1][1]][1], // z
			}};

		bool collisionX = false, collisionZ = false;

		// collision x-axis?
		if ((*x - space <= wall[0][0] &&
			 *x + space >= wall[1][0]) ||
			(*x + space > wall[0][0] &&
			 *x - space < wall[1][0]))
		{
			collisionX = true;
		}

		// collision z-axis?
		if ((*z - space <= wall[0][1] &&
			 *z + space >= wall[1][1]) ||
			(*z + space > wall[0][1] &&
			 *z - space < wall[1][1]))
		{
			collisionZ = true;
		}

		// collision only if on both axes
		if (collisionX && collisionZ)
		{

			return true;
		}

		// -256, 256 -170.667, 256 -85.3333, 256 0, 256 85.3333, 256 170.667, 256 256, 256
		// -256, 170.667 -170.667, 170.667 -85.3333, 170.667 0, 170.667 85.3333, 170.667 170.667, 170.667 256, 170.667
		// -256, 85.3333 -170.667, 85.3333 -85.3333, 85.3333 0, 85.3333 85.3333, 85.3333 170.667, 85.3333 256, 85.3333
		// -256, 0 -170.667, 0 -85.3333, 0 0, 0 85.3333, 0 170.667, 0 256, 0
		// -256, -85.3333 -170.667, -85.3333 -85.3333, -85.3333 0, -85.3333 85.3333, -85.3333 170.667, -85.3333 256, -85.3333
		// -256, -170.667 -170.667, -170.667 -85.3333, -170.667 0, -170.667 85.3333, -170.667 170.667, -170.667 256, -170.667
		// -256, -256 -170.667, -256 -85.3333, -256 0, -256 85.3333, -256 170.667, -256 256, -256
	}

	return false;
}