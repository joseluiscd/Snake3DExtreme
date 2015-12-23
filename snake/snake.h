#ifndef SNAKE_H
#define SNAKE_H

#include <list>
#include <pair>
#include "labyrinth.h"

typedef enum{
    SNAKE_B_L; // ←↓
    SNAKE_B_R; // ↓→
    SNAKE_T_L; // ↑→
    SNAKE_T_R; // ←↑
} snakeCellType;

typedef enum{
    SNAKE_UP;
    SNAKE_DOWN;
    SNAKE_LEFT;
    SNAKE_RIGHT;
} snakeDirection;

typedef struct {
    int x, y;
    snakeCellType celltype;
} snakeCell;

//Data structure to represent the snake
class snake{
private:
    list<pair<int, int> > body;

public:
    void advance(const labyrinth& lab, snakeDirection d, bool food=false);
}

#endif
