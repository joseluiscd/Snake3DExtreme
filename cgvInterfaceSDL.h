#ifndef CGV_INTERFACE_SDL_H
#define CGV_INTERFACE_SDL_H

#include <SDL2/SDL.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <vector>
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
    // void something(T* value);
    template<typename T= void* >
    int addTimer(function<void(T*)>& callback, unsigned int interval = 10, T* param=NULL){
        function<unsigned int(unsigned int, void*)> new_callback = [&](unsigned int interval, T* param)->unsigned int{
            callback(param);
            return interval;
        };
        int ret = SDL_AddTimer(interval, new_callback.operator(), param);
        return ret!=0?ret:throw cgvException("The timer could not be added.");
    }

    void deleteTimer(int timer){
        SDL_RemoveTimer(timer) ? true : throw cgvException("The timer wasn't removed");
    }

    static cgvInterfaceSDL& getInstance(char* w_title = "", int w=640, int h=480, bool fullscreen=false);
};

#endif
