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
}

void MiniMap::drawMiniMap()
{
    float grid = 85.333333333 / 3;

    glPushMatrix();

    // bg
    glColor4f(0.0, 0.0, 0.0, 1.0);
    glBegin(GL_TRIANGLE_STRIP);
    glVertex3f(0.0, 0.0, 0.0);
    glVertex3f(grid * 6, 0.0, 0.0);
    glVertex3f(0.0, grid * 6, 0.0);
    glVertex3f(grid * 6, grid * 6, 0.0);
    glEnd();

    //boarder
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
    glTranslatef(grid * 3.0,grid * 3.0,0.0);
    glRotatef(-90.0,0.0,0.0,1.0);
    glScalef(1.0,-1.0,0.0);
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