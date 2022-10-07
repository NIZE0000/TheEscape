#pragma once

#include <pch.h>

#include <Camera.h>
#include <Map.h>
#include <Ghost.h>
#include <MiniMap.h>
#include <Scene.h>

class Game
{
private:
    /* data */
    GLFWwindow *wnd;
    Camera camera;
    Scene scene;
    Map map;
    MiniMap minimap;
    Ghost ghost;

    float deltatime;
    float mx, my;

public:
    Game();
    ~Game();
    void loadTex();
    void render3D();
    void render2D();
    void processKeys();
    void update();
    void setDeltatime(float Deltatime);
    void setMousePosition(float x, float y);
    void ProcessMouseMovement(float xoffset, float yoffset, GLboolean constrainPitch = true);
    void setWindow(GLFWwindow *gl_wnd);
};

Game::Game()
{
    srand(time(NULL));

    // set position
    this->map.setDoorPos(-255.0, 0.0, 210.0);
    this->map.setDoorRot(180.0);

    this->camera.setPosition(-230.0, 0.0, -220.0);
    this->camera.setDegree(0.0, -90, 0.0);
    // this->camera.setDegree(0.0, rand() % 360, 0.0);

    this->ghost.setPosition(rand() % 250 - (rand() % 250), -20.0, rand() % 250 - (rand() % 250));
    this->ghost.setDegree(0.0, 0.0, 0.0);
}

Game::~Game()
{
    this->map.~Map();
    this->ghost.~Ghost();
    this->scene.~Scene();
}

void Game::loadTex()
{
    this->map.loadTexture();
    this->ghost.loadTexture();
    this->scene.loadTexture();
}

void Game::render2D()
{
    if (!this->scene.gameover && !this->scene.survive)
    {
        this->minimap.render();
    }
    else
    {
        this->scene.render();
    }
}

void Game::render3D()
{

    if (!this->scene.gameover && !this->scene.survive)
    {
        this->camera.render();
        // camera.Debug(); // return log from class attribute

        this->map.render();
        this->ghost.render();
        // ghost.Debug(); // return log from class attribute
    }
    
}

void Game::update()
{
    this->camera.updateDeltatime(this->deltatime);
    this->ghost.updateDeltatime(this->deltatime);


    // Process keyboard
    this->camera.ProcessKeyboard(this->wnd);

    // get player position to draw
    float cx, cy, cz;
    this->camera.getPosition(&cx, &cy, &cz);

    bool check = map.checkCollision(&cx, &cy, &cz);
    this->camera.updateCollision(check);

    this->minimap.updatePosition(&cx, &cy, &cz, G);

    this->ghost.chasePlayer(&cx, &cy, &cz);

    // get ghost position to draw
    float gx, gy, gz;
    this->ghost.getPosition(&gx, &gy, &gz);
    this->minimap.updatePosition(&gx, &gy, &gz, R);

    // get door position
    float dx, dy, dz;
    this->map.getDoorPos(&dx, &dy, &dz);

    // scene check logic to set gameover or survive
    this->scene.updateLogic(&cx, &cz,
                                &gx, &gz,
                                &dx, &dz);
}

void Game::setDeltatime(float Deltatime)
{
    this->deltatime = Deltatime;
}

void Game::setMousePosition(float x, float y)
{
    this->mx = x;
    this->my = y;
}

void Game::ProcessMouseMovement(float xoffset, float yoffset, GLboolean constrainPitch)
{
    this->camera.ProcessMouseMovement(xoffset, yoffset, constrainPitch);
}

void Game::setWindow(GLFWwindow *gl_wnd)
{
    this->wnd = gl_wnd;
}