#include "cgvScene.h"

cgvScene::cgvScene():cameras(){
    cameras.push_back(cgvCamera(cgvPoint3D(6.0,4.0,8),cgvPoint3D(0,0,0),cgvPoint3D(0,1.0,0),
		                                3, 3, 0.1, 200));
}

void cgvScene::render(){
    GLUquadricObj *cyl=gluNewQuadric();
    gluQuadricDrawStyle(cyl,GLU_FILL);
        gluCylinder(cyl,1,1,1,20,20);
    gluDeleteQuadric(cyl);
}

void cgvScene::addCamera(cgvCamera &cam){
    cameras.push_back(cam);
}

void cgvScene::applyCamera(int numCamera){
    cameras.at(numCamera).apply();
}
