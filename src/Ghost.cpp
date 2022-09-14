#include <Ghost.h>
#include <texture.h>

Ghost::Ghost(/* args */)
{
    this->MovementSpeed = 60;
}

Ghost::~Ghost()
{
    this->ghost.Delete();
}

void Ghost::loadTexture()
{
    this->ghost.ID = 2;
    this->ghost.Image_Format = GL_RGBA;
    this->ghost.Internal_Format = GL_RGBA;
    this->ghost.Generate("assets/textures/ghost.png", 600, 600);
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
    update();

    float width = 0, height = 25, depth = 25;

    this->ghost.Bind(); // binding texture
    {

        glPushAttrib(GL_TEXTURE_BIT);
        glEnable(GL_TEXTURE_2D);

        glColor3f(1.0, 1.0, 1.0);
        glBegin(GL_TRIANGLE_STRIP);
        glTexCoord2f(0.0, 0.0);
        glVertex3f(width, -height, -depth);
        glTexCoord2f(1.0, 0.0);
        glVertex3f(width, -height, depth);
        glTexCoord2f(0.0, 1.0);
        glVertex3f(width, height, -depth);
        glTexCoord2f(1.0, 1.0);
        glVertex3f(width, height, depth);
        glEnd();

        glPopAttrib();
    }
}

void Ghost::chasePlayer(float *x, float *y, float *z)
{
    float deltaTime = this->deltatime;
    float speedRot = 2;
    float space = 10;

    float velocity = MovementSpeed * deltaTime;

    // get player position and chasing
    float d, dx, dz;

    dx = (*x - this->pos[0]);
    dz = (*z - this->pos[2]);
    d = sqrt((dx * dx) + (dz * dz));
    // std::cout << dx / d << ", " << dz / d << std::endl;
    // std::cout << d << std::endl;

    if ((int(this->dir[0]) == int(dx / d) || int(this->dir[2]) == int(dz / d)) && d > space)
    {
        this->pos[0] -= this->dir[0] * velocity;
        this->pos[2] += this->dir[2] * velocity;
    }

    if (this->dir[0] > dx / d && this->dir[2] > dz / d) // >>
    {
        this->rot[1] -= speedRot;
        return;
    }
    if (this->dir[0] > dx / d && this->dir[2] < dz / d) // ><
    {
        this->rot[1] += speedRot;
        return;
    }
    if (this->dir[0]<dx / d &&this->dir[2]> dz / d) //<>
    {
        this->rot[1] += speedRot;
        return;
    }
    if (this->dir[0] < dx / d && this->dir[2] < dz / d) //<<
    {
        this->rot[1] -= speedRot;
        return;
    }
}

void Ghost::update()
{
    // calculate direction
    this->dir[0] = -cos((rot[1] - 90) * DEG_TO_RED); // X
    this->dir[2] = -sin((rot[1] - 90) * DEG_TO_RED); // Z

    // ref to camera position
    // -+ ++
    // -- +-

    glRotatef(180, 0.0, 1.0, 0.0);

    glTranslatef(this->pos[0], this->pos[1], this->pos[2]);
    glRotatef(this->rot[0], 1.0, 0.0, 0.0);
    glRotatef(this->rot[1] - 90, 0.0, 1.0, 0.0);
    glRotatef(this->rot[2] - 180, 0.0, 0.0, 1.0);
}

void Ghost::Debug()
{
    std::cout << " Ghost: " << std::endl;
    // Debug dir pos rot
    std::cout << " dir " << this->dir[0] << ", " << this->dir[1] << ", " << this->dir[2] << std::endl;
    std::cout << " pos " << this->pos[0] << ", " << this->pos[1] << ", " << this->pos[2] << std::endl;
    std::cout << " rot " << this->rot[0] << ", " << this->rot[1] << ", " << this->rot[2] << std::endl;
}
