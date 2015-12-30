#include "cgvInterfaceSDL.h"
#include "cgvScene.h"

cgvInterfaceSDL::cgvInterfaceSDL(char* w_title, int w, int h, bool fullscreen):
height(h), width(w), renderer(NULL), window(NULL), windowFlags(SDL_WINDOW_OPENGL),
windowTitle(w_title), scenes_keyboard()
{
    if(fullscreen) windowFlags = (SDL_WindowFlags)(windowFlags | SDL_WINDOW_FULLSCREEN);

}

cgvInterfaceSDL& cgvInterfaceSDL::getInstance(char* w_title, int w, int h, bool fullscreen){
    //This class is used as a Singleton
    static cgvInterfaceSDL interface(w_title, w, h, fullscreen); //Lazy initialization
    return interface;
}

void cgvInterfaceSDL::initSDL(){
    if( SDL_Init( SDL_INIT_VIDEO | SDL_INIT_TIMER ) < 0 ) {
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

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    SDL_GL_CreateContext(window);
    if(renderer==NULL){
        fprintf(stderr, "Renderer could not be created: %s\n", SDL_GetError());
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

    glEnable(GL_LIGHTING); // enable the lighting of the scene
    glEnable(GL_NORMALIZE); // normalize the normal vectors required by the lighting computation.
	glEnable(GL_TEXTURE_2D); // enable the use of 2D textures

}

void cgvInterfaceSDL::proccessEvents(){
    SDL_Event event;

    while( SDL_PollEvent( &event ) ) {
        switch( event.type ) {
        case SDL_KEYDOWN:
            // Key was pressed
            if(event.key.keysym.sym == SDLK_ESCAPE){
                quitSDL(0);
            } else {
                for(set<cgvScene*>::iterator it=scenes_keyboard.begin();it!=scenes_keyboard.end(); it++){
                    (*it)->keyboardCallback(event.key.keysym.sym);
                }
            }
            break;
        case SDL_QUIT:
            quitSDL(0);
            break;
        }

    }
}

void cgvInterfaceSDL::renderFrame(){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // clear the window and the z-buffer
    SDL_RenderClear(renderer);
    //Render all the scenes inside their viewports
    for(int i=0; i<viewports.size(); i++){
        viewports[i].applyViewport(this->width, this->height);
        viewports[i].applyCamera();
        viewports[i].renderScene();
    }

	// refresh the window
    SDL_RenderDrawLine(renderer, 0, 0, 500, 500);
    SDL_RenderPresent(renderer);
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

int cgvInterfaceSDL::addTimer(cgvScene* scene, unsigned int interval){
    int ret = SDL_AddTimer(interval, timerCallback, (void*)scene);
    return ret!=0?ret:throw cgvException("The timer could not be added.");
}

void cgvInterfaceSDL::addKeyboardListener(cgvScene *scene){
    scenes_keyboard.insert(scene);
}

unsigned int cgvInterfaceSDL::timerCallback(unsigned int delay, void *scene){
    ((cgvScene*)scene)->timerCallback(delay);
    return delay;
}

SDL_Texture* cgvInterfaceSDL::getSDLImage(const char *path, int& w, int&h){
    SDL_Texture* toRet = IMG_LoadTexture(renderer, path);
    toRet == NULL ? throw cgvException("Could not load the image."): 0;
    //SDL_QueryTexture(toRet, NULL, NULL, &w, &h);
    SDL_SetTextureBlendMode(toRet, SDL_BLENDMODE_BLEND);
    printf("W: %d, H: %d\n", w, h);
    return toRet;
}

void cgvInterfaceSDL::drawImage(SDL_Texture *tex, int x, int y, int width, int height){
    SDL_Rect texr; texr.x = x; texr.y = y; texr.w = width; texr.h = height;
    SDL_RenderCopy(renderer, tex, NULL, &texr)==0?0: throw cgvException("Could not draw the texture.");
}
