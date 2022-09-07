#pragma once
#define MY_DEG_TO_RAD 0.01745329251994329576923690768489
#define MY_RAD_TO_DEG 57.295779513082320876798154814105

class MyCamera
{
public:
    MyCamera();
	virtual ~MyCamera();

    void render();
    void setPos(float x, float y, float z);
    void getPos(float * x, float * y, float * z);
    void getRot(float * x, float * y, float * z);

    void moveFw();
    void moveBw();
    void slideLeft();
    void slideRight();
    void turnLeft();
    void turnRight();

private:
    float pos[3];
    float dir[3];
    float rot[3];
    float moveSpeed[3];
    float rotSpeed[3];
};