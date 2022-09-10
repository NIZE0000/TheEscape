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

	std::vector<Location> locations;

public:
	// Constructors
	MiniMap();
	~MiniMap();

	// Methods
	void updatePosition(float *x, float *y, float *z, enum Color color);
	void render();
};

#endif