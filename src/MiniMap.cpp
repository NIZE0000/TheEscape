#include <pch.h>
#include <MiniMap.h>

MiniMap::MiniMap()
{
}

MiniMap::~MiniMap()
{
}

void MiniMap::render()
{
    drawMiniMap();
    drawPosition();
}

void MiniMap::drawMiniMap()
{
    float grid = 85.333333333 / 3;

    glPushMatrix();

    // bg
    glColor4f(0.5, 0.5, 0.5, 0.7);
    glBegin(GL_TRIANGLE_STRIP);
    glVertex3f(0.0, 0.0, 0.0);
    glVertex3f(grid * 6, 0.0, 0.0);
    glVertex3f(0.0, grid * 6, 0.0);
    glVertex3f(grid * 6, grid * 6, 0.0);
    glEnd();

    // boarder
    glColor4f(1.0, 1.0, 1.0, 1.0);
    glBegin(GL_LINES);
    glVertex3f(0.0, 0.0, 0.0);
    glVertex3f(512.0 / 3.0, 0.0, 0.0);

    glVertex3f(0.0, 512.0 / 3.0, 0.0);
    glVertex3f(512.0 / 3.0, 512.0 / 3.0, 0.0);

    glVertex3f(0.0, 0.0, 0.0);
    glVertex3f(0.0, 512.0 / 3.0, 0.0);

    glVertex3f(512.0 / 3.0, 512.0 / 3.0, 0.0);
    glVertex3f(512.0 / 3.0, 0.0, 0.0);
    glEnd();

    float walls[][2][2] = {
        {{-3, 3}, {3, 3}},
        {{-3, 3}, {-3, 2}},
        {{-3, 2}, {-1, 2}},
        {{0, 2}, {1, 2}},
        {{2, 2}, {3, 2}},
        {{-1, 2}, {-1, 0}},
        {{0, 2}, {0, 0}},
        {{1, 2}, {1, 0}},
        {{2, 2}, {2, -2}},
        {{3, 3}, {3, 2}},
        {{-3, 0}, {-1, 0}},
        {{0, 0}, {1, 0}},
        {{-3, 0}, {-1, 0}},
        {{-3, 0}, {-3, -1}},
        {{-3, -1}, {1, -1}},
        {{-3, 0}, {-3, -1}},
        {{1, -1}, {1, -3}},
        {{1, -3}, {3, -3}},
        {{3, -2}, {3, -3}},
        {{2, -2}, {3, -2}},

    };
    glTranslatef(grid * 3.0, grid * 3.0, 0.0);
    glRotatef(-90.0, 0.0, 0.0, 1.0);
    glScalef(1.0, -1.0, 0.0);
    for (int i = 0; i < sizeof(walls) / 16; i++)
    {
        float wall[][2] = {
            {walls[i][0][0], walls[i][0][1]}, {walls[i][1][0], walls[i][1][1]}};
        glColor4f(1.0, 1.0, 1.0, 1.0);
        glBegin(GL_LINES);
        glVertex3f(grid * walls[i][0][0], grid * walls[i][0][1], 0.0);
        glVertex3f(grid * walls[i][1][0], grid * walls[i][1][1], 0.0);
        glEnd();
    }
    glPopMatrix();
}

void MiniMap::drawPosition()
{

    for (Location locate : this->locations)
    {
        glPushMatrix();
        if (locate.Color == R)
        {
            glColor4f(1.0, 0.0, 0.0, 1.0);
        }
        if (locate.Color == G)
        {
            glColor4f(0.0, 1.0, 0.0, 1.0);
        }
        if (locate.Color == B)
        {
            glColor4f(0.0, 0.0, 1.0, 1.0);
        }

        // Location Point
        glTranslatef(85.0, 85.0, 0.0);
        glBegin(GL_POINTS);
        glPointSize(5.0);
        glVertex3f(locate.pos[0], locate.pos[2], 0.0);
        // glVertex3f(0.0, 100.0, 0.0);

        glEnd();
        glPopMatrix();

        this->locations.pop_back();
    }
        // std::cout<<sizeof(this->locations)<<std::endl;
}

void MiniMap::updatePosition(float *x, float *y, float *z, enum Color color)
{
    Location point;
    point.pos[0] = *x;
    point.pos[1] = *y;
    point.pos[2] = *z;

    point.Color = color;

    this->locations.push_back(point);
}