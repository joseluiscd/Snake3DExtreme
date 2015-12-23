#ifndef CGV_VIEWPORT_H
#define CGV_VIEWPORT_H

#include <vector>
#include "cgvScene.h"
#include "cgvColor.h"

class cgvViewport{
private:
    float x, y, w, h;
    cgvScene* scene;
    int numCamera;

public:
    cgvViewport(float _x, float _y, float _w, float _h, cgvScene* _scene, int cameraNum=0);

    void applyViewport(int width, int height); //Width and height of the window
    void applyCamera();
    void renderScene();


};

#endif
