/*
 * Player.cpp
 *
 *  Created on: Sep 2, 2022
 *      Author: Nice
 */

#include <Player.h>

Player::Player()
{
	// TODO Auto-generated constructor stub
	this->pos[0] = 0.0;
	this->pos[1] = 0.0;
	this->pos[2] = 0.0;

	this->dir[0] = 0.0;
	this->dir[1] = 0.0;
	this->dir[2] = -1.0;

	this->rot[0] = 0.0;
	this->rot[1] = 0.0;
	this->rot[2] = 0.0;

	this->moveSpeed[0] = 1.0;
	this->moveSpeed[1] = 1.0;
	this->moveSpeed[2] = 1.0;

	this->rotSpeed[0] = 1.0;
	this->rotSpeed[1] = 1.0;
	this->rotSpeed[2] = 1.0;
}

Player::~Player()
{
	// TODO Auto-generated destructor stub
}

// void Player::setPos(float x, float y, float z)
// {
// 	this->pos[0] = x;
// 	this->pos[1] = y;
// 	this->pos[2] = z;
// }
// void Player::getPos(float *x, float *y, float *z)
// {
// 	(*x) = this->pos[0];
// 	(*y) = this->pos[1];
// 	(*z) = this->pos[2];
// }

// void Player::moveForward()
// {
// 	this->pos[0] += this->moveSpeed[0] * this->dir[0];
// 	// this->pos[1] += this->moveSpeed[1] * this->dir[1];
// 	this->pos[2] += this->moveSpeed[2] * this->dir[2];
// }
// void Player::moveBackward()
// {
// 	this->pos[0] -= this->moveSpeed[0] * this->dir[0];
// 	// this->pos[1] -= this->moveSpeed[1] * this->dir[1];
// 	this->pos[2] -= this->moveSpeed[2] * this->dir[2];
// }
// void Player::moveRight()
// {
// 	this->pos[0] -= this->moveSpeed[0] * this->dir[0];
// }
// void Player::moveLeft()
// {
// 	this->pos[0] += this->moveSpeed[0] * this->dir[0];
// 	// this->pos[1] += this->moveSpeed[1] * this->dir[1];
// 	// this->pos[2] += this->moveSpeed[2] * this->dir[2];
// }

// void Player::turnLeft()
// {
// 	this->rot[1] += this->rotSpeed[1];
// }
// void Player::turnRigth()
// {
// 	this->rot[1] -= this->rotSpeed[1];
// }
