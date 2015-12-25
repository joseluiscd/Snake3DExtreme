#ifndef LABYRINTH_H
#define LABYRINTH_H

#include "snake.h"
#include "../cgvScene.h"
#include "../cgvLight.h"

typedef enum{
    GRID_BLANK,
    GRID_WALL,
    GRID_SNAKE,
    GRID_FOOD
} gridType;

class labyrinth: public cgvScene{
private:
    int height, width; //Size of the labyrinth
    gridType** lab;
    snake currentSnake;
    snakeDirection currentDirection;
    cgvLight globalLight;

    int timer;
    void drawWalls();


public:
    labyrinth(int width=20, int height=20);
    virtual void render();
    virtual void timerCallback(unsigned int delay);
    virtual void keyboardCallback(SDL_Keycode e);
    void launch();

};
#endif
