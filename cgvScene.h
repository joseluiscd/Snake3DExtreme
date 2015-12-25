#ifndef CGV_SCENE_H
#define CGV_SCENE_H

#include <vector>
#include <functional>
#include "cgvCamera.h"
#include <SDL2/SDL.h>

using namespace std;
class cgvScene;
typedef function<void(cgvScene*)> renderfunc_t;

class cgvScene{
protected:
    vector<cgvCamera> cameras;
    cameraType tcam;
    renderfunc_t* renderf;
    bool getKeyboardEvents;

public:
    cgvScene(renderfunc_t* _renderf = NULL);
    virtual ~cgvScene();

    virtual void render();
    void applyCamera(int numCamera);
    void addCamera(const cgvCamera& cam);
    virtual void timerCallback(unsigned int delay);
    virtual void keyboardCallback(SDL_Keycode e);
};

#endif
