#ifndef CGV_INTERFACE_SDL_H
#define CGV_INTERFACE_SDL_H

#include <SDL2/SDL.h>
#include <GL/gl.h>
#include <GL/glu.h>

class cgvInterfaceSDL {
private:
    SDL_Window* window;
    SDL_Renderer* renderer;

    int width;
    int height;

    char* windowTitle;

    SDL_WindowFlags windowFlags;

public:
    cgvInterfaceSDL(int w=640, int h=480, bool fullscreen=false);
    void initSDL();
    void initOpenGL();
    void quitSDL();
}

#endif
