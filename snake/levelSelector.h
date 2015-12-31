#ifndef LEVEL_SELECTOR_H
#define LEVEL_SELECTOR_H

#include "../cgvViewport.h"
#include "../cgvScene.h"
#include "../cgvInterfaceSDL.h"
#include "labyrinth.h"


class levelSelector: public cgvScene{

private:
    cgvViewport* gameViewport;
    cgvViewport* minimapViewport;

    labyrinth* currentMap;

    cgvTexture instructionsT;
    cgvTexture levelsT;
    cgvTexture mapsT;
    cgvTexture titleT;
    
    cgvMaterial blankM;

    int level;
    mazeType map;
    bool show;

public:
    levelSelector(cgvViewport* game, cgvViewport* minimap);
    ~levelSelector(){};
    void launchGame();
    virtual void render();

    void upLevel(){ level = (level+1)%10; }
    void downLevel(){ level = (level+9)%10; }

    virtual void keyboardCallback(SDL_Keycode e);

    void launch();

    void upMap(){
        switch(map){
            case MAZE_EMPTY: map=MAZE_ONEBOX; break;
            case MAZE_ONEBOX: map=MAZE_TWOBOXES; break;
            case MAZE_TWOBOXES: map=MAZE_CROSS; break;
            case MAZE_CROSS: map=MAZE_EMPTY; break;
        }
    }

    void downMap(){
        switch(map){
            case MAZE_EMPTY: map=MAZE_CROSS; break;
            case MAZE_ONEBOX: map=MAZE_EMPTY; break;
            case MAZE_TWOBOXES: map=MAZE_ONEBOX; break;
            case MAZE_CROSS: map=MAZE_TWOBOXES; break;
        }
    }

};

#endif
