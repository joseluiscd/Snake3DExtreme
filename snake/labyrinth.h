#ifndef LABYRINTH_H
#define LABYRINTH_H

#include "snake.h"
#include "../cgvScene.h"
#include "../cgvLight.h"
#include "../cgvTexture.h"

typedef enum{
    GRID_BLANK,
    GRID_WALL,
    GRID_SNAKE,
    GRID_FOOD
} gridType;

typedef enum{
    MAZE_EMPTY,
    MAZE_ONEBOX,
    MAZE_TWOBOXES,
    MAZE_CROSS,
    MAZE_EXTREME
} mazeType;

class labyrinth: public cgvScene{
private:
    int height, width; //Size of the labyrinth
    gridType** lab;
    snake currentSnake;
    snakeDirection currentDirection;
    cgvLight globalLight;

    cgvMaterial wallMaterial;
    cgvMaterial baseMaterial;
    cgvMaterial foodMaterial;

    cgvTexture baseTexture;
    cgvTexture wallTexture;
    int timerId;
    bool lost;
    void drawWalls();
    void drawFood(int x, int y);


public:
    labyrinth(int width=20, int height=20, mazeType mt=MAZE_EMPTY);
    virtual void render();
    virtual void timerCallback(unsigned int delay);
    virtual void keyboardCallback(SDL_Keycode e);
    void launch();
    void lose();

};
#endif
