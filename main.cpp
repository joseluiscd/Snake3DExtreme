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
#include "snake/levelSelector.h"

int main( int argc, char* argv[] )
{
    cgvInterfaceSDL& inter = cgvInterfaceSDL::getInstance("Snake3D Extreme (Ninja Edition!!) (PEGI 18)", 640, 640, false);
    inter.initSDL();
    inter.initOpenGL();

    labyrinth lb(20, 20, MAZE_EMPTY, 5);

    cgvViewport juego(0, 0, 1, 1, &lb, 1, CGV_PERSPECTIVE);
    cgvViewport minimap(0, 0, 0.4, 0.4, &lb, 0);
    levelSelector ls(&juego, &minimap);
    cgvViewport levelSelect(0.1, 0.1, 0.9, 0.9, &ls);

    inter.addViewport(juego);
    inter.addViewport(minimap);
    inter.addViewport(levelSelect);
    ls.launch();
    inter.renderLoop();
    return 0;
}
