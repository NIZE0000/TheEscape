#pragma once
#include <pch.h>

#include <Map.h>
#include <MiniMap.h>
#include <Ghost.h>
#include <Scene.h>
#include <fps_camera.h>

class Game
{
private:
    /* data */
    GLFWwindow *wnd;

public:
    Game(GLFWwindow *gl_wnd);
    ~Game();
    ;
    void loadTex();
    void render3D();
    void render2D();
    void processKeys();
    void update();
};

Game::Game(GLFWwindow *gl_wnd)
{
    this->wnd = *gl_wnd;
}

Game::~Game()
{
    map.~Map();
    ghost.~Ghost();
    scene.~Scene();
}

void Game::loadTex()
{
    map.loadTexture();
    ghost.loadTexture();
    scene.loadTexture();
}

void Game::render2D()
{
    minimap.render();
    scene.render();
}

void Game::render3D()
{

    // camera or player
    camera.render();
    // camera.Debug(); // return log from class atrribute

    // render map
    map.render();
    
    ghost.render();
    // ghost.Debug(); // return log from class atrribute
}

void Game::update()
{
}