/*
 * Map.h
 *
 *  Created on: Sep 3, 2022
 *      Author: Nice
 */

#ifndef SRC_MAP_H_
#define SRC_MAP_H_

#include <texture.h>

class Map
{
public:
	Map();
	virtual ~Map();
	void render();
	void loadTexture();
	bool checkCollision(float *x, float *y, float *z);
	Texture2D ground;
	Texture2D wall;

	int walls[19][2][2] = {
		// refer to index
		{{0, 0}, {6, 0}},
		{{0, 0}, {0, 6}},
		{{6, 0}, {6, 6}},
		{{0, 6}, {6, 6}},

		{{5, 0}, {5, 1}},
		{{5, 1}, {2, 1}},
		{{5, 5}, {6, 5}},
		{{5, 4}, {5, 5}},
		{{5, 5}, {6, 5}},
		{{6, 3}, {4, 3}},
		{{6, 2}, {5, 2}},
		{{4, 2}, {3, 2}},
		{{3, 2}, {3, 5}},
		{{1, 0}, {1, 4}},
		{{2, 1}, {2, 3}},
		{{1, 5}, {3, 5}},
		{{1, 4}, {2, 4}},
		{{5, 4}, {4, 4}},
		{{4, 4}, {4, 5}},

	};

private:
	float grid;
	float wallHeight;
	float bound[7][7][2];

	void drawWall(float point[][2]);
};

#endif /* SRC_MAP_H_ */
