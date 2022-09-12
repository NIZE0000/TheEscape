#pragma once

#include <pch.h>

class Ghost
{
private:
    float pos[3];
    float rot[3];
    float dir[3];
    float MovementSpeed;
    const float DEG_TO_RED = 0.017453293;
    enum Movement
    {
        FORWARD,
        BACKWARD,
        LEFT,
        RIGHT
    };

public:
    Ghost(/* args */);
    ~Ghost();
    void setPosition(float x, float y, float z);
    void getPosition(float *x, float *y, float *z);
    void setDegree(float x, float y, float z);
    void move(Movement direction, float deltaTime);
    void render();
};