#pragma once
#include <pch.h>
#include <texture.h>

class MenuScene
{
private:
    /* data */
    GLFWwindow *wnd;

    void GameOver();
    void Survive();
    void MainMenu();
    Texture2D GAMEOVER;
    Texture2D SURVIVE;

    // for home menu
    Texture2D GameTilte;
    Texture2D Start;
    Texture2D Exit;

    // mouse position
    float mouseX, mousey;

public:
    bool gamestart = false;
    bool gameover;
    bool survive;

    MenuScene(/* args */);
    ~MenuScene();
    void loadTexture();
    void render();
    void updateLogic(float *cx, float *cz,
                     float *gx, float *gz,
                     float *dx, float *dz);
    void updateMouse(float mx, float my);
    void setWindow(GLFWwindow *window);
};

MenuScene::MenuScene(/* args */)
{
}

MenuScene::~MenuScene()
{
    this->GAMEOVER.Delete();
    this->SURVIVE.Delete();
}

void MenuScene::loadTexture()
{
    this->GameTilte.ID = rand();
    this->GameTilte.Image_Format = GL_RGBA;
    this->GameTilte.Internal_Format = GL_RGBA;
    this->GameTilte.Generate("../assets/textures/menu/home/GameTitle.png", 1024, 1024);

    this->Start.ID = rand();
    this->Start.Image_Format = GL_RGBA;
    this->Start.Internal_Format = GL_RGBA;
    this->Start.Generate("../assets/textures/menu/home/Start.png", 192, 64);

    this->Exit.ID = rand();
    this->Exit.Image_Format = GL_RGBA;
    this->Exit.Internal_Format = GL_RGBA;
    this->Exit.Generate("../assets/textures/menu/home/Exit.png", 131, 65);

    this->GAMEOVER.ID = rand();
    this->GAMEOVER.Image_Format = GL_RGBA;
    this->GAMEOVER.Internal_Format = GL_RGBA;
    this->GAMEOVER.Generate("../assets/textures/menu/end/GameOver.png", 1024, 1024);

    this->SURVIVE.ID = rand();
    this->SURVIVE.Image_Format = GL_RGBA;
    this->SURVIVE.Internal_Format = GL_RGBA;
    this->SURVIVE.Generate("../assets/textures/menu/end/Survive.png", 1024, 1024);
}

void MenuScene::render()
{
    glTranslatef(+256.0, +256.0, 0.0);
    glRotatef(90, 0.0, 0.0, 1.0);
    glTranslatef(-256.0, -256.0, 0.0);

    if (!this->gamestart)
    {
        MainMenu();
        return;
    }
    if (this->gameover)
    {
        GameOver();
        return;
    }
    if (this->survive)
    {
        Survive();
        return;
    }
}

void MenuScene::GameOver()
{
    this->GAMEOVER.Bind();

    glPushAttrib(GL_TEXTURE_BIT);
    glEnable(GL_TEXTURE_2D);

    glColor3f(1.0, 1.0, 1.0);
    glBegin(GL_TRIANGLE_STRIP);
    glTexCoord2f(1.0, 1.0);
    glVertex2f(0.0, 0.0);
    glTexCoord2f(1.0, 0.0);
    glVertex2f(512.0, 0.0);
    glTexCoord2f(0.0, 1.0);
    glVertex2f(0.0, 512.0);
    glTexCoord2f(0.0, 0.0);
    glVertex2f(512.0, 512.0);
    glEnd();

    glPopAttrib();
}

void MenuScene::Survive()
{
    this->SURVIVE.Bind();

    glPushAttrib(GL_TEXTURE_BIT);
    glEnable(GL_TEXTURE_2D);

    glColor3f(1.0, 1.0, 1.0);
    glBegin(GL_TRIANGLE_STRIP);
    glTexCoord2f(1.0, 1.0);
    glVertex2f(0.0, 0.0);
    glTexCoord2f(1.0, 0.0);
    glVertex2f(512.0, 0.0);
    glTexCoord2f(0.0, 1.0);
    glVertex2f(0.0, 512.0);
    glTexCoord2f(0.0, 0.0);
    glVertex2f(512.0, 512.0);
    glEnd();

    glPopAttrib();
}

void MenuScene::updateLogic(float *cx, float *cz,
                            float *gx, float *gz,
                            float *dx, float *dz)
{

    float disDoor = (pow(*cx - *dx, 2) + pow(*cz - *dz, 2)) / 10;
    float disGhost = (pow(*cx - *gx, 2) + pow(*cz - *gz, 2)) / 10;

    if (disDoor < 10 && !this->gameover) // player position == door
    {
        this->survive = true;
        return;
    }
    // else
    // {
    //     this->survive = false;
    // }
    if (disGhost < 10 && !this->survive) // player position == ghost posiition
    {
        this->gameover = true;
        return;
    }
    // else
    // {
    //     this->gameover = false;
    // }
}

void MenuScene::MainMenu()
{

    this->GameTilte.Bind();
    glPushAttrib(GL_TEXTURE_BIT);
    glEnable(GL_TEXTURE_2D);
    glColor3f(1.0, 1.0, 1.0);
    glBegin(GL_TRIANGLE_STRIP);
    glTexCoord2f(1.0, 1.0);
    glVertex2f(0.0, 0.0);
    glTexCoord2f(1.0, 0.0);
    glVertex2f(512.0, 0.0);
    glTexCoord2f(0.0, 1.0);
    glVertex2f(0.0, 512.0);
    glTexCoord2f(0.0, 0.0);
    glVertex2f(512.0, 512.0);
    glEnd();
    glPopAttrib();

    // glfwGet

    this->Start.Bind();

    glPushAttrib(GL_TEXTURE_BIT);
    glEnable(GL_TEXTURE_2D);

    glColor3f(1.0, 1.0, 1.0);

    // if (this->x )
    {
        glColor3f(1.0, 0.0, 0.0);
    }
    
    glTranslatef(-64/2,-192/2,0);

    glTranslatef(200,512/2,0);

    glBegin(GL_TRIANGLE_STRIP);
    glTexCoord2f(1.0, 1.0);
    glVertex2f(0.0, 0.0);
    glTexCoord2f(1.0, 0.0);
    glVertex2f(64.0, 0.0);
    glTexCoord2f(0.0, 1.0);
    glVertex2f(0.0, 192.0);
    glTexCoord2f(0.0, 0.0);
    glVertex2f(64.0, 192.0);
    glEnd();

    glPopAttrib();

    // this->Exit.Bind();

    // glPushAttrib(GL_TEXTURE_BIT);
    // glEnable(GL_TEXTURE_2D);

    // glColor3f(1.0, 1.0, 1.0);
    // glBegin(GL_TRIANGLE_STRIP);
    // glTexCoord2f(1.0, 1.0);
    // glVertex2f(0.0, 0.0);
    // glTexCoord2f(1.0, 0.0);
    // glVertex2f(512.0, 0.0);
    // glTexCoord2f(0.0, 1.0);
    // glVertex2f(0.0, 512.0);
    // glTexCoord2f(0.0, 0.0);
    // glVertex2f(512.0, 512.0);
    // glEnd();

    // glPopAttrib();
}

void MenuScene::updateMouse(float mx, float my)
{
    this->mouseX = mx;
    this->mousey = my;
}

void MenuScene::setWindow(GLFWwindow *window){
    this->wnd = window;
}
