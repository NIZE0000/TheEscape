/*
 * Map.h
 *
 *  Created on: Sep 3, 2022
 *      Author: Nice
 */

#ifndef SRC_MAP_H_
#define SRC_MAP_H_

#include <texture.h>

class Map {
public:
	Map();
	virtual ~Map();
	void render();
	void loadTexture();
	bool checkBoundary(float position[3]);
	Texture2D ground;
	Texture2D wall;

private:
	float grid;
	float wallHeight;
	float bound[7][7][2];
	void drawWall(float point[][2]);
	void drawGround(float point[][2]);

};

#endif /* SRC_MAP_H_ */
