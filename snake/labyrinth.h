#ifndef LABYRINTH_H
#define LABYRINTH_H

#include "snake.h"


class labyrinth{
private:
    int height, width; //Size of the labyrinth
    int** lab;
    snake currentSnake;

public:
    labyrinth(int width=20, int height=20);

};
#endif
