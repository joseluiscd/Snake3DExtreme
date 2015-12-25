#include "cgvScene.h"
#include "cgvLight.h"
#include "cgvMaterial.h"
#include "cgvColor.h"

cgvScene::cgvScene(renderfunc_t* _renderf):cameras(), tcam(CGV_PERSPECTIVE), renderf(_renderf), getKeyboardEvents(false){

}

cgvScene::~cgvScene(){

}
void cgvScene::render(){
    if(!renderf){
        cgvLight light(GL_LIGHT0, cgvPoint3D(5, 5, 0), cgvColor(1, 0, 0, 1), cgvColor(1, 1, 1, 1), cgvColor(1, 1, 1, 1), 1, 0, 0);
        light.switchOn();
        light.apply();
        cgvMaterial(cgvColor(0.1,0,0), cgvColor(1,0,0), cgvColor(1,1,1), 120).apply();

        GLUquadricObj *cyl=gluNewQuadric();
        gluQuadricDrawStyle(cyl,GLU_FILL);
            gluSphere(cyl, 1, 200, 200);
        gluDeleteQuadric(cyl);
    } else {
        (*renderf)(this);
    }

}

void cgvScene::addCamera(const cgvCamera &cam){
    cameras.push_back(cam);
}

void cgvScene::applyCamera(int numCamera){
    cameras.at(numCamera).apply(tcam);
}

void cgvScene::timerCallback(unsigned int delay){

}

void cgvScene::keyboardCallback(SDL_Keycode e){
    
}
