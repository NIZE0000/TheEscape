#include <pch.h>

class Menu
{
private:
    /* data */
    GLFWwindow wnd;

public:
    Menu(GLFWwindow *window);
    ~Menu();
    void render();
    void update();
};

Menu::Menu(GLFWwindow *window)
{
    this->wnd = *window;
}

Menu::~Menu()
{
}

void Menu::render()
{
}

void Menu::update()
{
}
