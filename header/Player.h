/*
 * Player.h
 *
 *  Created on: Sep 2, 2022
 *      Author: Nice
 */

#ifndef SRC_PLAYER_H_
#define SRC_PLAYER_H_

class Player {
public:
	Player();
	virtual ~Player();

	void checkMoveable();

//	void render();
	void setPos(float x, float y, float z);
	void getPos(float *x, float *y, float *z);

	void move();

	void turnLeft();
	void turnRigth();
	void turnUp();
	void turnDown();



private:
	float pos[3];
	float dir[3];
	float rot[3];
	float moveSpeed[3];
	float rotSpeed[3];
};

#endif /* SRC_PLAYER_H_ */
