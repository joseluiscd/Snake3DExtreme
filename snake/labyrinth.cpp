#include "labyrinth.h"
#include "../cgvInterfaceSDL.h"

labyrinth::labyrinth(int w, int h):width(w), height(h), currentSnake(),
cgvScene(NULL),currentDirection(SNAKE_UP), timer(0),
globalLight(GL_LIGHT0, cgvPoint3D(5, 5, 0), cgvColor(1, 0, 0, 1), cgvColor(1, 1, 1, 1), cgvColor(1, 1, 1, 1), 1, 0, 0)
{
    cameras.push_back(cgvCamera(cgvPoint3D(6.0,4.0,8),cgvPoint3D(0,0,0),cgvPoint3D(0,1.0,0),
		                                3, 3, 0.1, 200));
    lab = new gridType* [width];

    for(int i=0;i<width;i++){
        lab[i] = new gridType[height];
        for(int j=0;j<height;j++) lab[i][j]=GRID_BLANK;
    }

    for(int i=0;i<10;i++){
        lab[rand()%width][rand()%height] = GRID_WALL;
    }

}

void labyrinth::render(){
    //TODO Draw boxes around
    globalLight.apply();
    drawWalls();
    currentSnake.render();
}

void labyrinth::timerCallback(unsigned int delay){
    currentSnake.advance(currentDirection);
}

void labyrinth::keyboardCallback(SDL_Keycode e){
    switch(e){
        case SDLK_UP:
        if(currentDirection!=SNAKE_DOWN) currentDirection=SNAKE_UP;
        break;

        case SDLK_DOWN:
        if(currentDirection!=SNAKE_UP) currentDirection=SNAKE_DOWN;
        break;

        case SDLK_LEFT:
        if(currentDirection!=SNAKE_RIGHT) currentDirection=SNAKE_LEFT;
        break;

        case SDLK_RIGHT:
        if(currentDirection!=SNAKE_LEFT) currentDirection=SNAKE_RIGHT;
        break;

    }
}
void labyrinth::launch(){
    cgvInterfaceSDL& interface = cgvInterfaceSDL::getInstance();
    interface.addTimer(this, 200);
    interface.addKeyboardListener(this);
}

void labyrinth::drawWalls(){

    glBegin(GL_QUADS);
        //LEFT BORDER
        glVertex3f(-0.5, -0.5, 0.5);
        glVertex3f(-0.5, -0.5, -0.5);
        glVertex3f(-0.5, height+0.5, -0.5);
        glVertex3f(-0.5, height+0.5, 0.5);
        //RIGHT BORDER
        glVertex3f(width+0.5, -0.5, 0.5);
        glVertex3f(width+0.5, height+0.5, 0.5);
        glVertex3f(width+0.5, height+0.5, -0.5);
        glVertex3f(width+0.5, -0.5, -0.5);

        //TOP BORDER
        glVertex3f(-0.5, height+0.5, 0.5);
        glVertex3f(-0.5, height+0.5, -0.5);
        glVertex3f(width+0.5, height+0.5, -0.5);
        glVertex3f(width+0.5, height+0.5, 0.5);

        //BOTTOM BORDER
        glVertex3f(-0.5, -0.5, 0.5);
        glVertex3f(width+0.5, -0.5, 0.5);
        glVertex3f(width+0.5, -0.5, -0.5);
        glVertex3f(-0.5, -0.5, -0.5);

    glEnd();

    for(int i=0; i<width; i++){
        for(int j=0; j<height; j++){
            float startX=i-0.5, endX=i+0.5, startY=j-0.5, endY=j+0.5;
            switch(lab[i][j]){
                case GRID_WALL:
                glBegin(GL_QUADS);
                    //FRONT QUAD
                    glVertex3f(startX, startY, 0.5);
                    glVertex3f(endX, startY, 0.5);
                    glVertex3f(endX, endY, 0.5);
                    glVertex3f(startX, endY, 0.5);

                    //TOP QUAD
                    glVertex3f(startX, endY, 0.5);
                    glVertex3f(endX, endY, 0.5);
                    glVertex3f(endX, endY, -0.5);
                    glVertex3f(startX, endY, -0.5);

                    //BOTTOM QUAD
                    glVertex3f(startX, startY, 0.5);
                    glVertex3f(startX, startY, -0.5);
                    glVertex3f(endX, startY, -0.5);
                    glVertex3f(endX, startY, 0.5);

                    //RIGHT QUAD
                    glVertex3f(endX, startY, 0.5);
                    glVertex3f(endX, startY, -0.5);
                    glVertex3f(endX, endY, -0.5);
                    glVertex3f(endX, endY, 0.5);

                    //LEFT QUAD
                    glVertex3f(startX, startY, 0.5);
                    glVertex3f(startX, endY, 0.5);
                    glVertex3f(startX, endY, -0.5);
                    glVertex3f(startX, startY, -0.5);
                glEnd();
                break;
            }
        }
    }
}
