#include "cgvScene.h"
#include "cgvLight.h"
#include "cgvMaterial.h"
#include "cgvColor.h"

cgvScene::cgvScene():cameras(), tcam(CGV_PARALLEL){
    cameras.push_back(cgvCamera(cgvPoint3D(6.0,4.0,8),cgvPoint3D(0,0,0),cgvPoint3D(0,1.0,0),
		                                3, 3, 0.1, 200));
}

void cgvScene::render(){
    cgvLight light(GL_LIGHT0, cgvPoint3D(5, 5, 0), cgvColor(0, 0, 0, 1), cgvColor(1, 1, 1, 1), cgvColor(1, 1, 1, 1), 1, 0, 0);
    light.switchOn();
    light.apply();
    cgvMaterial(cgvColor(0,0,0), cgvColor(1,0,0), cgvColor(1,1,1), 120).apply();

    GLUquadricObj *cyl=gluNewQuadric();
    gluQuadricDrawStyle(cyl,GLU_FILL);
        gluSphere(cyl, 1, 20, 20);
    gluDeleteQuadric(cyl);
}

void cgvScene::addCamera(cgvCamera &cam){
    cameras.push_back(cam);
}

void cgvScene::applyCamera(int numCamera){
    cameras.at(numCamera).apply(tcam);
}
