#ifndef SNAKE_H
#define SNAKE_H

#include <list>
#include <GL/gl.h>
#include <GL/glu.h>
#include <SDL2/SDL.h>
#include "../cgvMaterial.h"
using namespace std;

class snake;

typedef enum{
    SNAKE_B_L, // ←↓
    SNAKE_B_R, // ↓→
    SNAKE_T_L, // ↑→
    SNAKE_T_R, // ←↑
    SNAKE_HORIZ, // --
    SNAKE_VERTIC, // |
    SNAKE_HEAD,
    SNAKE_TAIL
} snakeCellType;

typedef enum{
    SNAKE_UP,
    SNAKE_DOWN,
    SNAKE_LEFT,
    SNAKE_RIGHT
} snakeDirection;

typedef struct {
    int x, y;
    snakeCellType celltype;
} snakeCell;

typedef list<snakeCell>::iterator cellIterator;

//Data structure to represent the snake
class snake{
private:
    list<snakeCell> body;
    SDL_mutex* body_mutex; //STL is awful for synchronization
    cgvMaterial snakeMaterial;
public:
    snake();
    virtual ~snake();
    void advance(snakeDirection d, bool food=false);
    inline void updateCoordinates(snakeDirection d, int& newX, int& newY);

    void render();
    static void drawCell(snakeCellType t, int x, int y);
};

#endif
