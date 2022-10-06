#ifndef MINIMAP_H
#define MINIMAP_H

enum Color
{
	R,
	G,
	B
};
struct Location
{
	float pos[3],
		Color;
};

class MiniMap
{
private:
	// Variables
	// float area[] = 0 ;
	void drawMiniMap();
	void drawPosition();
	float grid;
	float mapRotation;
	float bound[7][7][2];
	std::vector<Location> locations;
	int walls[19][2][2] = {
		// refer to index
		{{0, 0}, {6, 0}},
		{{0, 0}, {0, 6}},
		{{6, 0}, {6, 6}},
		{{0, 6}, {6, 6}},
		{{5, 0}, {5, 1}},
		{{5, 1}, {2, 1}},
		{{5, 5}, {6, 5}},
		{{5, 4}, {5, 5}},
		{{5, 5}, {6, 5}},
		{{6, 3}, {4, 3}},
		{{6, 2}, {5, 2}},
		{{4, 2}, {3, 2}},
		{{3, 2}, {3, 5}},
		{{1, 0}, {1, 4}},
		{{2, 1}, {2, 3}},
		{{1, 5}, {3, 5}},
		{{1, 4}, {2, 4}},
		{{5, 4}, {4, 4}},
		{{4, 4}, {4, 5}},

	};

public:
	// Constructors
	MiniMap();
	~MiniMap();

	// Methods
	void updatePosition(float *x, float *y, float *z, enum Color color);
	void render();
};

MiniMap::MiniMap()
{
    this->grid = 85.333333333 / 3;
    this->mapRotation = 90;

    this->bound[7][7][2]; // for store all in X and Z axis to ref position  6 grid
    for (int i = 0; i < 7; i++)
    {
        for (int j = 0; j < 7; j++)
        {
            this->bound[i][j][0] = this->grid * (-3 + j);
            this->bound[i][j][1] = this->grid * (3 - i);
        }
    }
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

    glPushMatrix();

    // bg
    glColor4f(0.5, 0.5, 0.5, 0.7);
    glBegin(GL_TRIANGLE_STRIP);
    glVertex3f(0.0, 0.0, 0.0);
    glVertex3f(this->grid * 6, 0.0, 0.0);
    glVertex3f(0.0, this->grid * 6, 0.0);
    glVertex3f(this->grid * 6, this->grid * 6, 0.0);
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

    // draw lines
    glTranslatef(grid * 3.0, grid * 3.0, 0.0);
    glRotatef(this->mapRotation, 0.0, 0.0, 1.0);
    glScalef(1.0, -1.0, 0.0);
    for (int i = 0; i < sizeof(this->walls) / 16; i++)
    {
        int index[2][2] = {
            {this->walls[i][0][0], this->walls[i][0][1]}, /// row
            {this->walls[i][1][0], this->walls[i][1][1]}, // colume
        };

        float wall[][2] = {
            {
                this->bound[index[0][0]][index[0][1]][0], // x
                this->bound[index[0][0]][index[0][1]][1], // z
            },
            {
                this->bound[index[1][0]][index[1][1]][0], // x
                this->bound[index[1][0]][index[1][1]][1], // z
            }};

        glColor4f(1.0, 1.0, 1.0, 1.0);
        glBegin(GL_LINES);
        glVertex3f(wall[0][0], wall[0][1], 0.0);
        glVertex3f(wall[1][0], wall[1][1], 0.0);
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

        glTranslatef(this->grid * 3, this->grid * 3, 0.0);
        glRotatef(this->mapRotation, 0.0, 0.0, 1.0);
        glScalef(1.0, -1.0, 0.0);
        glBegin(GL_POINTS);
        glVertex3f(locate.pos[0] / 3, locate.pos[2] / 3, 0.0);
        glEnd();

        glPopMatrix();

        this->locations.pop_back();
    }
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

#endif