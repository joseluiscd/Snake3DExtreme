#include "snake.h"
#include <list>
#include <cstdio>
#include "../cgvException.h"

snake::snake(): body(),
snakeMaterial(cgvColor(0.1,0,0), cgvColor(1,0,0), cgvColor(1,1,1), 120){
    body_mutex = SDL_CreateMutex();
    body.push_back(snakeCell {0, 3, SNAKE_HEAD});
    body.push_back(snakeCell {0, 2, SNAKE_VERTIC});
    body.push_back(snakeCell {0, 1, SNAKE_VERTIC});
    body.push_back(snakeCell {0, 0, SNAKE_TAIL});
}

snake::~snake(){
    SDL_DestroyMutex(body_mutex);
}

void snake::updateCoordinates(snakeDirection d, int& newX, int& newY){
    switch(d){
        case SNAKE_UP:
        newY++;
        break;

        case SNAKE_DOWN:
        newY--;
        break;

        case SNAKE_LEFT:
        newX--;
        break;

        case SNAKE_RIGHT:
        newX++;
        break;
    }
}
void snake::advance(snakeDirection d, bool food){
    if(SDL_LockMutex(body_mutex) == 0){
        cellIterator head = body.begin();
        cellIterator tail = --body.end();

        int newX=head->x, newY=head->y;
        updateCoordinates(d, newX, newY);
        body.push_front(snakeCell {newX, newY, SNAKE_HEAD});

        if(!food){
            body.erase(tail);
            tail = --body.end();
            tail->celltype = SNAKE_TAIL;
        }

    } else {
        throw cgvException("Could not lock the snake's mutex.");
    }

    SDL_UnlockMutex(body_mutex);
}

void snake::render(){
    if(SDL_LockMutex(body_mutex) == 0){
        snakeMaterial.apply();
        for(cellIterator it=body.begin(); it!=body.end(); it++){
            drawCell(it->celltype, it->x, it->y);
        }
    } else {
        throw cgvException("Could not lock the snake's mutex while rendering.");
    }
    SDL_UnlockMutex(body_mutex);
}

void snake::drawCell(snakeCellType t, int x, int y){
    glPushMatrix();
        glTranslatef(x, y, 0);
        GLUquadricObj *cyl=gluNewQuadric();
        gluQuadricDrawStyle(cyl,GLU_FILL);
            gluSphere(cyl, 1, 200, 200);
        gluDeleteQuadric(cyl);
    glPopMatrix();
}
