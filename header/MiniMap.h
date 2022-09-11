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

#endif