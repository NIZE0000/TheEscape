#pragma once

#include <pch.h>

class Ghost
{
private:
    float pos[3];
    float rot[3];
    float dir[3];

public:
    Ghost(/* args */);
    ~Ghost();
    void setPosition(float x, float y, float z);
    void getPosition(float *x, float *y, float *z);
    void render();
};