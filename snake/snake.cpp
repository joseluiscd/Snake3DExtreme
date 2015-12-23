#include "snake.h"
#include <list>
#include <cstdio>

snake::snake(): body(){
    body.push_back(snakeCell {0, 3, SNAKE_HEAD});
    body.push_back(snakeCell {0, 2, SNAKE_VERTIC});
    body.push_back(snakeCell {0, 1, SNAKE_VERTIC});
    body.push_back(snakeCell {0, 0, SNAKE_TAIL});
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
        newX--;
        break;
    }
}
void snake::advance(snakeDirection d, bool food){
    cellIterator head = body.begin();
    cellIterator tail = --body.end();
    
    int newX=head->x, newY=head->y;
    updateCoordinates(d, newX, newY);
    body.push_front(snakeCell {newX, newY, SNAKE_HEAD});

    if(!food){
        tail = --body.erase(tail);
        tail->celltype = SNAKE_TAIL;
    }

}

void snake::render(){
    for(cellIterator it=body.begin(); it!=body.end(); it++){
        drawCell(it->celltype, it->x, it->y);
    }
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
