#include <Ghost.h>
#include <pch.h>

Ghost::Ghost(/* args */)
{
}

Ghost::~Ghost()
{
}

void Ghost::render()
{
    // glLoadIdentity();
	glPushMatrix();

	// glRotatef(180.0, 0.0, 1.0, 0.0);
    glColor3f(0.0,0.0,1.0);
    glTranslatef(200.0,+50,220.0);

    float width=10, height= 10, depth=10;

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

    glPopMatrix();
}