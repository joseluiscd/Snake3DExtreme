#include "labyrinth.h"
#include "../cgvInterfaceSDL.h"

labyrinth::labyrinth(int w, int h):width(w), height(h), currentSnake(),
cgvScene(NULL),currentDirection(SNAKE_UP),
globalLight(GL_LIGHT0, cgvPoint3D(5, 5, 0), cgvColor(1, 0, 0, 1), cgvColor(1, 1, 1, 1), cgvColor(1, 1, 1, 1), 1, 0, 0)
{
    cameras.push_back(cgvCamera(cgvPoint3D(6.0,4.0,8),cgvPoint3D(0,0,0),cgvPoint3D(0,1.0,0),
		                                3, 3, 0.1, 200));
    lab = new int* [width];

    for(int i=0;i<width;i++){
        lab[i] = new int[height];
        for(int j=0;j<height;j++) lab[i][j]=0;
    }

}

void labyrinth::render(){
    //TODO Draw boxes around
    globalLight.apply();
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
