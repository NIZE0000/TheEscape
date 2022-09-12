#include <Ghost.h>

Ghost::Ghost(/* args */)
{
    this->MovementSpeed = 2.5;
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

void Ghost::setDegree(float x, float y, float z)
{
    this->rot[0] = x;
    this->rot[1] = y;
    this->rot[2] = z;
}

void Ghost::render()
{

    // *make it ref to camera position
    // -+ ++
    // -- +-
    // glRotatef(180, 0.0, 1.0, 0.0);

    glTranslatef(this->pos[0], this->pos[1],this->pos[2]);
    glRotatef(this->rot[0], 1.0, 0.0, 0.0);
    glRotatef(this->rot[1], 0.0, 1.0, 0.0);
    glColor3f(1.0, 0.0, 0.0);

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

void Ghost::move(Movement direction, float deltaTime)
{
    if (direction == FORWARD || direction == BACKWARD)
    {
        this->dir[0] = sin(rot[1] * DEG_TO_RED);  // X
        this->dir[2] = -cos(rot[1] * DEG_TO_RED); // Z
    }
    if (direction == LEFT || direction == RIGHT)
    {
        this->dir[0] = cos(rot[1] * DEG_TO_RED);  // X
        this->dir[2] = -sin(rot[1] * DEG_TO_RED); // Z
    }

    float velocity = this->MovementSpeed * deltaTime;

    if (direction == FORWARD)
    {
        this->pos[0] -= this->dir[0] * velocity;
        this->pos[2] -= this->dir[2] * velocity;
    }

    if (direction == BACKWARD)
    {
        this->pos[0] += this->dir[0] * velocity;
        this->pos[2] += this->dir[2] * velocity;
    }
    if (direction == LEFT)
    {
        this->pos[0] += this->dir[0] * velocity;
        this->pos[2] -= this->dir[2] * velocity;
    }
    if (direction == RIGHT)
    {
        this->pos[0] += -this->dir[0] * velocity;
        this->pos[2] += this->dir[2] * velocity;
    }
}