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
    cameraType typeCamera;

public:
    cgvViewport(float _x, float _y, float _w, float _h, cgvScene* _scene, int cameraNum=0, cameraType camT=CGV_PARALLEL);

    void applyViewport(int width, int height); //Width and height of the window
    void applyCamera();
    void renderScene();

    void setScene(cgvScene* _scene){scene=_scene;};
    cgvScene* getScene(){return scene;};


};

#endif
