#ifndef CGV_INTERFACE_SDL_H
#define CGV_INTERFACE_SDL_H

#include <SDL2/SDL.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <vector>

#include "cgvScene.h"
#include "cgvViewport.h"


using namespace std;

class cgvInterfaceSDL {
private:
    SDL_Window* window;
    SDL_Renderer* renderer;

    int width;
    int height;
    char* windowTitle;
    SDL_WindowFlags windowFlags;

    vector<cgvViewport> viewports;

public:
    cgvInterfaceSDL(char* title, int w=640, int h=480, bool fullscreen=false);
    void initSDL();
    void initOpenGL();
    void quitSDL(int code=0);

    void proccessEvents();
    void renderFrame();
    void renderLoop();

    void addViewport(cgvViewport& v);
};

#endif
