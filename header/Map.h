/*
 * Map.h
 *
 *  Created on: Sep 3, 2022
 *      Author: Nice
 */

#ifndef SRC_MAP_H_
#define SRC_MAP_H_


class Map {
public:
	Map();
	virtual ~Map();
	void render();
private:
	float grid;
	float wallHeight;
	void drawWall(float point[][2]);
	void drawGround(float point[][2]);

};

#endif /* SRC_MAP_H_ */
