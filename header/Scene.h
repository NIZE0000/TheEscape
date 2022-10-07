#pragma once
#include <pch.h>
#include <texture.h>

class Scene
{
private:
    /* data */
    

    void GameOver();
    void Survive();
    Texture2D GAMEOVER;
    Texture2D SURVIVE;

public:
    bool gameover;
    bool survive;

    Scene(/* args */);
    ~Scene();
    void loadTexture();
    void render();
    void updateLogic(float *cx, float *cz,
                     float *gx, float *gz,
                     float *dx, float *dz);
};

Scene::Scene(/* args */)
{
}

Scene::~Scene()
{
    this->GAMEOVER.Delete();
    this->SURVIVE.Delete();
}

void Scene::loadTexture()
{
    this->GAMEOVER.Image_Format = GL_RGBA;
    this->GAMEOVER.Internal_Format = GL_RGBA;
    this->GAMEOVER.Generate("../assets/textures/GameOver.png", 1024, 1024);

    this->SURVIVE.Image_Format = GL_RGBA;
    this->SURVIVE.Internal_Format = GL_RGBA;
    this->SURVIVE.Generate("../assets/textures/Survive.png", 1024, 1024);
}

void Scene::render()
{
    glTranslatef(+256.0, +256.0, 0.0);
    glRotatef(90, 0.0, 0.0, 1.0);
    glTranslatef(-256.0, -256.0, 0.0);

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

void Scene::GameOver()
{
    this->GAMEOVER.Bind();

    glPushAttrib(GL_TEXTURE_BIT);
    glEnable(GL_TEXTURE_2D);

    glColor3f(1.0, 0.0, 0.0);
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

void Scene::Survive()
{
    this->SURVIVE.Bind();

    glPushAttrib(GL_TEXTURE_BIT);
    glEnable(GL_TEXTURE_2D);

    glColor3f(0.0, 1.0, 0.0);
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

void Scene::updateLogic(float *cx, float *cz,
                        float *gx, float *gz,
                        float *dx, float *dz)
{

    float disDoor = (pow(*cx - *dx, 2) + pow(*cz - *dz, 2))/10;
    float disGhost = (pow(*cx - *gx, 2) + pow(*cz - *gz, 2))/10;

    if (disDoor < 10 && !this->gameover) // player position == door
    {
        this->survive = true;
        return;
    }

    if (disGhost < 10 && !this->survive) // player position == ghost posiition +- space
    {
        this->gameover = true;
        return;
    }

}