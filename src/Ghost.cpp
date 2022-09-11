#include <Ghost.h>

Ghost::Ghost(/* args */)
{
}

Ghost::~Ghost()
{
}

void Ghost::setPosition(float x, float y, float z)
{
    this->pos[0] = x;
    this->pos[1] = y;
    this->pos[2] = z;
}

void Ghost::getPosition(float *x, float *y, float *z)
{
    *x = this->pos[0];
    *y = this->pos[1];
    *z = this->pos[2];
}

void Ghost::render()
{

    // glRotatef(180.0, 0.0, 1.0, 0.0);
    glColor3f(1.0, 0.0, 0.0);
    glTranslatef(200.0, +50, 220.0);

    float width = 10, height = 10, depth = 10;

    glBegin(GL_QUADS);
    // glTexCoord2f(1, 0);
    glVertex3f(width, -height, -depth);
    // glTexCoord2f(1, 1);
    glVertex3f(width, height, -depth);
    // glTexCoord2f(0, 1);
    glVertex3f(width, height, depth);
    // glTexCoord2f(0, 0);
    glVertex3f(width, -height, depth);
    glEnd();
}