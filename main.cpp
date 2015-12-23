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

    cgvScene escena;
    escena.addCamera(cgvCamera(cgvPoint3D(2,0,0), cgvPoint3D(0,0,0), cgvPoint3D(0,1,0), 2, 2, .02, 20));
    cgvViewport vp(0, 0, 1, 1, &escena);
    cgvViewport vp2(0, 0, 0.2, 0.2, &escena, 1);

    snake sn;
    labyrinth lb;
    renderfunc_t snake_render([&](cgvScene* escena){
        sn.render();
    });
    function<void(void*)> function_advance = [&](void*){ sn.advance(SNAKE_LEFT); };
    inter.addTimer(function_advance, 100);

    cgvScene serpiente(&snake_render);
    serpiente.addCamera(cgvCamera(cgvPoint3D(2,0,0), cgvPoint3D(0,0,0), cgvPoint3D(0,1,0), 10, 10, .02, 20));

    cgvViewport juego(0, 0, 1, 1, &serpiente);

    inter.addViewport(vp);
    inter.addViewport(vp2);
    inter.addViewport(juego);

    inter.renderLoop();
    return 0;
}
