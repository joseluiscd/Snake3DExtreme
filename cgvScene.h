#ifndef CGV_SCENE_H
#define CGV_SCENE_H

#include <vector>
#include "cgvCamera.h"

using namespace std;

class cgvScene{
private:
    vector<cgvCamera> cameras;
    cameraType tcam;

public:
    cgvScene();

    void render();
    void applyCamera(int numCamera);
    void addCamera(cgvCamera& cam);
};

#endif
