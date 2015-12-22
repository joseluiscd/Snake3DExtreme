#include <SDL2/SDL.h>
#include <GL/gl.h>
#include <GL/glu.h>

#include <stdio.h>
#include <stdlib.h>

#include "cgvScene.h"
#include "cgvViewport.h"
#include "cgvInterfaceSDL.h"

int main( int argc, char* argv[] )
{
    cgvInterfaceSDL inter("Juego guay", 500, 500, false);
    inter.initSDL();
    inter.initOpenGL();

    cgvScene escena;
    cgvViewport vp(0, 0, 1, 1, &escena);

    inter.addViewport(vp);
    inter.renderLoop();
    return 0;
}
