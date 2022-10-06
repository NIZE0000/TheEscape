#include <pch.h>
#include <texture.h>

class Button
{
private:
    /* data */
    float pos[3];
    float width, height;
public:
    Button(/* args */);
    ~Button();
    void loadTex(char file);
    void render();
    void update(float mx, float my);
};

Button::Button(/* args */)
{
}

Button::~Button()
{
}

void Button::render(){

}

void Button::update(){

}
