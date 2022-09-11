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

private:
	float grid;
	float wallHeight;
	float bound[7][7][2];
	int walls[20][2][2] = { //refer to index
		// {{0, 0}, {6, 0}},
		// {{0, 0}, {0, 6}},
		// {{6, 0}, {6, 6}},
		// {{0, 6}, {6, 6}},
		
		{{1, 1}, {1, 6}},

		// {{1, 5}, {1, 6}},
		// {{1, 5}, {4, 5}},



		// {{-3, 2}, {-1, 2}},
		// {{0, 2}, {1, 2}},
		// {{2, 2}, {3, 2}},
		// {{-1, 2}, {-1, 0}},
		// {{0, 2}, {0, 0}},
		// {{1, 2}, {1, 0}},
		// {{2, 2}, {2, -2}},
		// {{3, 3}, {3, 2}},
		// {{-3, 0}, {-1, 0}},
		// {{0, 0}, {1, 0}},
		// {{-3, 0}, {-1, 0}},
		// {{-3, 0}, {-3, -1}},
		// {{-3, -1}, {1, -1}},
		// {{-3, 0}, {-3, -1}},
		// {{1, -1}, {1, -3}},
		// {{1, -3}, {3, -3}},
		// {{3, -2}, {3, -3}},
		// {{2, -2}, {3, -2}},
	};
	void drawWall(float point[][2]);
};

#endif /* SRC_MAP_H_ */
