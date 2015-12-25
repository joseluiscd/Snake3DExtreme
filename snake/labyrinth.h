#ifndef LABYRINTH_H
#define LABYRINTH_H

#include "snake.h"
#include "../cgvScene.h"
#include "../cgvLight.h"

class labyrinth: public cgvScene{
private:
    int height, width; //Size of the labyrinth
    int** lab;
    snake currentSnake;
    snakeDirection currentDirection;
    cgvLight globalLight;

public:
    labyrinth(int width=20, int height=20);
    virtual void render();
    virtual void timerCallback(unsigned int delay);
    virtual void keyboardCallback(SDL_Keycode e);
    void launch();

};
#endif
