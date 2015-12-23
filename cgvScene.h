#ifndef CGV_SCENE_H
#define CGV_SCENE_H

#include <vector>
#include <functional>
#include "cgvCamera.h"

using namespace std;
class cgvScene;
typedef function<void(cgvScene*)> renderfunc_t;

class cgvScene{
private:
    vector<cgvCamera> cameras;
    cameraType tcam;
    renderfunc_t* renderf;

public:
    cgvScene(renderfunc_t* _renderf = NULL);

    void render();
    void applyCamera(int numCamera);
    void addCamera(const cgvCamera& cam);
};

#endif
