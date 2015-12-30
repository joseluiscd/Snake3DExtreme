#ifndef CGV_INTERFACE_SDL_H
#define CGV_INTERFACE_SDL_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <vector>
#include <set>
#include <functional>

#include "cgvScene.h"
#include "cgvViewport.h"
#include "cgvException.h"

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
    set<cgvScene*> scenes_keyboard;
    cgvInterfaceSDL(char* title, int w=640, int h=480, bool fullscreen=false);
    cgvInterfaceSDL(cgvInterfaceSDL& inter);
    cgvInterfaceSDL& operator=(const cgvInterfaceSDL& inter);
public:
    void initSDL();
    void initOpenGL();
    void quitSDL(int code=0);

    void proccessEvents();
    void renderFrame();
    void renderLoop();

    void addViewport(cgvViewport& v);

    //Adds a timer with a callback function
    // void something();
    int addTimer(cgvScene* scene, unsigned int interval = 10);
    void addKeyboardListener(cgvScene* scene);

    void deleteTimer(int timer){
        SDL_RemoveTimer(timer) ? true : throw cgvException("The timer wasn't removed");
    }

    SDL_Texture* getSDLImage(const char* path, int& w, int& h);
    void drawImage(SDL_Texture*, int x, int y, int width, int height);
    
    static unsigned int timerCallback(unsigned int delay, void* callback);
    static cgvInterfaceSDL& getInstance(char* w_title = "", int w=640, int h=480, bool fullscreen=false);
};

#endif
