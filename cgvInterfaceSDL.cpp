
#include "cgvInterfaceSDL.h"

cgvInterfaceSDL::cgvInterfaceSDL(char* w_title, int w, int h, bool fullscreen):
height(h), width(w), renderer(NULL), window(NULL), windowFlags(SDL_WINDOW_OPENGL),
windowTitle(w_title)
{
    if(fullscreen) windowFlags |= SDL_WINDOW_FULLSCREEN;

}

void cgvInterfaceSDL::initSDL(){
    if( SDL_Init( SDL_INIT_VIDEO ) < 0 ) {
        fprintf(stderr, "Video initialization failed: %s\n", SDL_GetError());
        quitSDL();
    }

    // 24 bit color
    SDL_GL_SetAttribute( SDL_GL_RED_SIZE, 8 );
    SDL_GL_SetAttribute( SDL_GL_GREEN_SIZE, 8 );
    SDL_GL_SetAttribute( SDL_GL_BLUE_SIZE, 8 );

    // The depth buffer
    SDL_GL_SetAttribute( SDL_GL_DEPTH_SIZE, 16 );

    // Double buffer for rendering
    SDL_GL_SetAttribute( SDL_GL_DOUBLEBUFFER, 1 );

    window = SDL_CreateWindow(windowTitle, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, flags);
    if(window==NULL) {
        fprintf(stderr, "Window could not be created: %s\n", SDL_GetError());
        quitSDL();
    }

    renderer = SDL_CreateRenderer(w, -1, 0);
    if(renderer==NULL){
        fprintf(stderr, "Renderer could not be created: %s\n",SDL_GetError( ) );
        quitSDL();
    }
}

void cgvInterfaceSDL::initOpenGL(){
    glShadeModel( GL_SMOOTH );

    glCullFace( GL_BACK );
    glFrontFace( GL_CCW );
    glEnable( GL_CULL_FACE );

    glEnable(GL_DEPTH_TEST);
    glClearColor(0, 0, 0, 0);
}

void cgvInterfaceSDL::quitSDL(){
    SDL_Quit();
    exit(0);
}
