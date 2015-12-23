#include "cgvScene.h"
#include "cgvViewport.h"
#include "cgvException.h"

#include <GL/gl.h>
cgvViewport::cgvViewport(float _x, float _y, float _w, float _h, cgvScene* _scene, int cameraNum) {
    scene = _scene;
    numCamera = cameraNum;
    _x >=0 && _x <=1 ? x = _x : throw cgvException("x must be between 0 and 1");
    _y >=0 && _y <=1 ? y = _y : throw cgvException("y must be between 0 and 1");
    _w >=0 && _w <=1 ? w = _w : throw cgvException("w must be between 0 and 1");
    _h >=0 && _h <=1 ? h = _h : throw cgvException("h must be between 0 and 1");

}

void cgvViewport::applyViewport(int width, int height){
     glViewport(x*width, y*height, w*width, h*height);
 }

void cgvViewport::applyCamera(){
    scene->applyCamera(numCamera);
}

void cgvViewport::renderScene(){
    scene->render();
}
