#include <pch.h>
#include <camera.h>

MyCamera::MyCamera()
{
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

MyCamera::~MyCamera()
{

}

void MyCamera::render()
{

}

void MyCamera::setPos(float x, float y, float z)
{
    this->pos[0] = x;
    this->pos[1] = y;
    this->pos[2] = z;
}

void MyCamera::getPos(float * x, float * y, float * z)
{
    (*x) = this->pos[0];
    (*y) = this->pos[1];
    (*z) = this->pos[2];
}

void MyCamera::getRot(float *x, float * y, float * z)
{
    (*x) = this->rot[0];
    (*y) = this->rot[1];
    (*z) = this->rot[2];
}

void MyCamera::moveFw()
{
    this->pos[0] += this->moveSpeed[0] * this->dir[0];
    this->pos[1] += this->moveSpeed[1] * this->dir[1];
    this->pos[2] += this->moveSpeed[2] * this->dir[2];
}

void MyCamera::moveBw()
{
    this->pos[0] -= this->moveSpeed[0] * this->dir[0];
    this->pos[1] -= this->moveSpeed[1] * this->dir[1];
    this->pos[2] -= this->moveSpeed[2] * this->dir[2];
}

void MyCamera::slideLeft()
{
}

void MyCamera::slideRight()
{
}

void MyCamera::turnLeft()
{
    this->rot[1] -= this->rotSpeed[1];

    this->dir[0] = cos(this->rot[1] * MY_DEG_TO_RAD);
    this->dir[2] = sin(this->rot[1] * MY_DEG_TO_RAD);
}

void MyCamera::turnRight()
{
    this->rot[1] += this->rotSpeed[1];

    this->dir[0] = cos(this->rot[1] * MY_DEG_TO_RAD);
    this->dir[2] = sin(this->rot[1] * MY_DEG_TO_RAD);
}