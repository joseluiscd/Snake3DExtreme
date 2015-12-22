#include "cgvInterfaceSDL.h"
#include "cgvScene.h"

cgvInterfaceSDL::cgvInterfaceSDL(char* w_title, int w, int h, bool fullscreen):
height(h), width(w), renderer(NULL), window(NULL), windowFlags(SDL_WINDOW_OPENGL),
windowTitle(w_title)
{
    if(fullscreen) windowFlags = (SDL_WindowFlags)(windowFlags | SDL_WINDOW_FULLSCREEN);

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

    window = SDL_CreateWindow(windowTitle, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, windowFlags);
    if(window==NULL) {
        fprintf(stderr, "Window could not be created: %s\n", SDL_GetError());
        quitSDL();
    }

    renderer = SDL_CreateRenderer(window, -1, 0);
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

void cgvInterfaceSDL::proccessEvents(){
    SDL_Event event;

    while( SDL_PollEvent( &event ) ) {
        switch( event.type ) {
        case SDL_KEYDOWN:
            // Key was pressed
            break;
        case SDL_QUIT:
            quitSDL(0);
            break;
        }

    }
}

void cgvInterfaceSDL::renderFrame(){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // clear the window and the z-buffer

    //Render all the scenes inside their viewports
    for(int i=0; i<viewports.size(); i++){
        viewports[i].applyViewport(this->width, this->height);
        viewports[i].applyCamera();
        viewports[i].renderScene();
    }

	// refresh the window
	SDL_GL_SwapWindow(window);
}

void cgvInterfaceSDL::renderLoop(){
    while(1){
        proccessEvents();
        renderFrame();
    }
}

void cgvInterfaceSDL::quitSDL(int code){
    SDL_Quit();
    exit(code);
}

void cgvInterfaceSDL::addViewport(cgvViewport &v){
    viewports.push_back(v);
}
