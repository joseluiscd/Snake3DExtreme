#include "levelSelector.h"

levelSelector::levelSelector(cgvViewport* game, cgvViewport* minimap): cgvScene(), show(true),
gameViewport(game), minimapViewport(minimap), instructionsT("images/instructions.png"),
blankM(cgvColor(1,1,1), cgvColor(0,0,0), cgvColor(0,0,0), 0),
titleT("images/title.png"), levelsT("images/levels.png"), mapsT("images/maps.png"), level(4)
{
    this->addCamera(cgvCamera(cgvPoint3D(50, 50, 1), cgvPoint3D(50, 50, 0), cgvPoint3D(0,1,0), 50, 50, 0.1, 2));
}

void levelSelector::launchGame(){
    this->show= false;
    currentMap = new labyrinth(20, 20, map, level+1);
    printf("Antigua: %d\n", minimapViewport->getScene());
    minimapViewport->setScene(currentMap);
    printf("Nueva: %d\n", minimapViewport->getScene());
    gameViewport->setScene(currentMap);
    currentMap->launch();
}

void levelSelector::render(){
    if(show){
        blankM.apply();
        titleT.apply();
        glBegin(GL_QUADS);
            glTexCoord2f(0, titleT.getHeight());
            glVertex2f(0, 66);
            glTexCoord2f(titleT.getWidth(), titleT.getHeight());
            glVertex2f(100, 66);
            glTexCoord2f(titleT.getWidth(), 0);
            glVertex2f(100, 100);
            glTexCoord2f(0,0);
            glVertex2f(0, 100);
        glEnd();
        titleT.disable();

        instructionsT.apply();
        glBegin(GL_QUADS);
            glTexCoord2f(0, instructionsT.getHeight());
            glVertex2f(0, 33);
            glTexCoord2f(instructionsT.getWidth(), instructionsT.getHeight());
            glVertex2f(33, 33);
            glTexCoord2f(instructionsT.getWidth(), 0);
            glVertex2f(33, 66);
            glTexCoord2f(0,0);
            glVertex2f(0, 66);
        glEnd();
        instructionsT.disable();

        levelsT.apply();
        glBegin(GL_QUADS);
            glTexCoord2f(0,(levelsT.getHeight()/10)*(level+1));

            glVertex2f(56, 40);
            glTexCoord2f(levelsT.getWidth(), (levelsT.getHeight()/10)*(level+1));

            glVertex2f(76, 40);
            glTexCoord2f(levelsT.getWidth(),(levelsT.getHeight()/10)*level  );

            glVertex2f(76, 60);
            glTexCoord2f(0, (levelsT.getHeight()/10)*level );

            glVertex2f(56, 60);
        glEnd();
        levelsT.disable();

        mapsT.apply();
        glBegin(GL_QUADS);
            glTexCoord2f(0,(mapsT.getHeight()/4)*((int)map+1));

            glVertex2f(46, 26);
            glTexCoord2f(mapsT.getWidth(), (mapsT.getHeight()/4)*((int)map+1));

            glVertex2f(86, 26);
            glTexCoord2f(mapsT.getWidth(),(mapsT.getHeight()/4)*(int)map  );

            glVertex2f(86, 36);
            glTexCoord2f(0, (mapsT.getHeight()/4)*(int)map );

            glVertex2f(46, 36);
        glEnd();
        mapsT.disable();

    }
}

void levelSelector::keyboardCallback(SDL_Keycode e){
    switch(e){
        case SDLK_RIGHT: upLevel(); break;
        case SDLK_LEFT: downLevel(); break;
        case SDLK_UP: upMap(); break;
        case SDLK_DOWN: downMap(); break;
        case SDLK_SPACE:
        case SDLK_RETURN:
            this->launchGame();

    }
}

void levelSelector::launch(){
    cgvInterfaceSDL& inter = cgvInterfaceSDL::getInstance();
    inter.addKeyboardListener(this);
}
