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
    escena.addCamera(cgvCamera(cgvPoint3D(2,0,0), cgvPoint3D(0,0,0), cgvPoint3D(0,1,0), 2, 2, .02, 20));
    cgvViewport vp(0, 0, 1, 1, &escena);
    cgvViewport vp2(0, 0, 0.2, 0.2, &escena, 1);


    inter.addViewport(vp);
    inter.addViewport(vp2);
    inter.renderLoop();
    return 0;
}
