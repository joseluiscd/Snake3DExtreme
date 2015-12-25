#include <SDL2/SDL.h>
#include <GL/gl.h>
#include <GL/glu.h>

#include <stdio.h>
#include <stdlib.h>

#include "cgvScene.h"
#include "cgvViewport.h"
#include "cgvInterfaceSDL.h"

#include "snake/snake.h"
#include "snake/labyrinth.h"

int main( int argc, char* argv[] )
{
    cgvInterfaceSDL& inter = cgvInterfaceSDL::getInstance("CrappySnake 3D", 500, 500, false);
    inter.initSDL();
    inter.initOpenGL();

    labyrinth lb(8, 8);
    lb.addCamera(cgvCamera(cgvPoint3D(4,4,10), cgvPoint3D(4,4,0), cgvPoint3D(0,1,0), 8, 8, .02, 20));
    lb.launch();

    cgvViewport juego(0, 0, 1, 1, &lb, 1);

    inter.addViewport(juego);

    inter.renderLoop();
    return 0;
}
