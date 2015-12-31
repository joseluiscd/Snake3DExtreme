#include "labyrinth.h"
#include "../cgvInterfaceSDL.h"

labyrinth::labyrinth(int w, int h, mazeType mt, int level):width(w), height(h), currentSnake(),
cgvScene(NULL),currentDirection(SNAKE_UP), timerId(0), lost(false),
globalLight(GL_LIGHT0, cgvPoint3D(0, 0, 8), cgvColor(1, 1, 1, 1), cgvColor(1, 1, 1, 1), cgvColor(1, 1, 1, 1), 0.7, 0, 0),
wallMaterial(cgvColor(0.3,0.3,0.3), cgvColor(1,0,0), cgvColor(1,1,1,0), 120),
baseMaterial(cgvColor(0.3,0.1,0.1), cgvColor(1,1,1), cgvColor(1,1,1,0), 120),
foodMaterial(cgvColor(0,0.1,0.1), cgvColor(0,1,1), cgvColor(1,1,1,0), 120),
baseTexture("images/bg.png"), wallTexture("images/wall.png")
{
    //GLOBAL CAMERA
    cameras.push_back(cgvCamera(cgvPoint3D(width/2-0.5,height/2-0.5,8),cgvPoint3D(width/2-0.5,height/2-0.5,0),cgvPoint3D(0,1.0,0),
		                                width, height, 0.1, 200));

    //SNAKE TOP CAMERA
    cameras.push_back(cgvCamera(cgvPoint3D(0, 0, 10), cgvPoint3D(0, 3, 0), cgvPoint3D(0,1,0),
		                                width/3, height/3, 0.1, 200));
    lab = new gridType* [width];
    level>0 && level<=10 ? this->timer_interval=(-50*level)+550 : throw cgvException("That level doesn't exist");
    for(int i=0;i<width;i++){
        lab[i] = new gridType[height];
        for(int j=0;j<height;j++) lab[i][j]=GRID_BLANK;
    }

    //DRAW THE LABYRINTH IN THE MATRIX
    switch(mt){
        case MAZE_EMPTY:
        break; //Nothing, the easiest!!

        case MAZE_ONEBOX:
        for(int i=width/4;i<=3*width/4;i++){
            for(int j=height/4;j<=3*height/4;j++){
                lab[i][j]=GRID_WALL;
            }
        }
        break;

        case MAZE_TWOBOXES:
        for(int i=width/4;i<=3*width/4;i++){
            for(int j=height/4;j<=3*height/4;j++){
                if(j<=(3*height/8) || j>5*height/8) lab[i][j]=GRID_WALL;
            }
        }
        break;

        case MAZE_CROSS:
        int min = width<height?width:height;
        for(int i=1;i<min/2-1;i++){
            lab[i][i] = GRID_WALL;
            lab[width-i-1][i] = GRID_WALL;
            lab[width-i-1][height-i-1] = GRID_WALL;
            lab[i][height-i-1] = GRID_WALL;

        }

    }

    //Add the first food
    int fx, fy;
    do{
        fx = rand()%width;
        fy = rand()%height;
    } while(lab[fx][fy]!=GRID_BLANK);
    lab[fx][fy] = GRID_FOOD;
    int w_i,h_i;
}

void labyrinth::render(){
    //TODO Draw boxes around
    globalLight.apply();
    drawWalls();
    if(lost) glTranslatef(0.01*((rand()%10)-5), 0.01*((rand()%10)-5), 0.01*((rand()%10)-5));
    currentSnake.render();

}

//STEP THE SNAKE
void labyrinth::timerCallback(unsigned int delay){
    currentSnake.advance(currentDirection);
    snakePosition p = currentSnake.getPosition();
    int hx = p.head.x;
    int hy = p.head.y;
    int tx = p.tail.x;
    int ty = p.tail.y;

    cameras[1].setCameraParameters(cgvPoint3D(hx, hy-3, 10), cgvPoint3D(hx, hy, 0), cgvPoint3D(0,1,0));

    bool addFood = false;

    if(hx<0 || hy<0 || hx>=width || hy>=height){
        lose();
        printf("OUT\n");
        return;
    }

    switch(lab[hx][hy]){
    case GRID_FOOD:
        lab[hx][hy] = GRID_BLANK;
        addFood=true;
        break;
    case GRID_BLANK:
        currentSnake.removeTail();
        lab[tx][ty] = GRID_BLANK;
        break;
    default: //SNAKE OR WALL
        printf("SNAKE OR WALL\n");
        printf("%d, %d, %d\n", lab[hx][hy], hx, hy);
        lose();
        return;
    }
    //Add the new head
    lab[hx][hy] = GRID_SNAKE;
    //TODO Add food
    if(addFood){
        int fx, fy;
        do{
            fx = rand()%width;
            fy = rand()%height;
        } while(lab[fx][fy]!=GRID_BLANK);
        lab[fx][fy] = GRID_FOOD;
    }
}

void labyrinth::keyboardCallback(SDL_Keycode e){
    switch(e){
        case SDLK_UP:
        if(currentDirection!=SNAKE_DOWN) currentDirection=SNAKE_UP;
        break;

        case SDLK_DOWN:
        if(currentDirection!=SNAKE_UP) currentDirection=SNAKE_DOWN;
        break;

        case SDLK_LEFT:
        if(currentDirection!=SNAKE_RIGHT) currentDirection=SNAKE_LEFT;
        break;

        case SDLK_RIGHT:
        if(currentDirection!=SNAKE_LEFT) currentDirection=SNAKE_RIGHT;
        break;

    }
}
void labyrinth::launch(){
    cgvInterfaceSDL& interface = cgvInterfaceSDL::getInstance();
    timerId = interface.addTimer(this, timer_interval);
    interface.addKeyboardListener(this);
}

void labyrinth::lose(){
    cgvInterfaceSDL& interface = cgvInterfaceSDL::getInstance();
    interface.deleteTimer(timerId);
    currentSnake.removeHead();
    printf("ÑAñaañaaaaa...\n");
    lost=true;
}

void labyrinth::drawFood(int x, int y){
    glPushMatrix();
        glTranslatef(x, y, 0);
        GLUquadricObj *cyl=gluNewQuadric();
        gluQuadricDrawStyle(cyl,GLU_FILL);
            gluSphere(cyl, 0.3, 200, 200);
        gluDeleteQuadric(cyl);
    glPopMatrix();
}

void labyrinth::drawWalls(){
    baseMaterial.apply();
    baseTexture.apply();
    float w = baseTexture.getWidth();
    float h = baseTexture.getHeight();
    glNormal3f(0, 0, 1);
    glBegin(GL_QUADS);
        //THE BASE
        glTexCoord2f(0, h);
        glVertex3f(-0.5, -0.5, -0.5);
        glTexCoord2f(w, h);
        glVertex3f(width-0.5, -0.5, -0.5);
        glTexCoord2f(w, 0);
        glVertex3f(width-0.5, height-0.5, -0.5);
        glTexCoord2f(0, 0);
        glVertex3f(-0.5, height-0.5, -0.5);
    glEnd();
    baseTexture.disable();

    wallMaterial.apply();
    wallTexture.apply();
    glBegin(GL_QUADS);
        //LEFT BORDER
        glNormal3f(1, 0, 0);
        glTexCoord2f(0, h*height);
        glVertex3f(-0.5, -0.5, 0.5);
        glTexCoord2f(w*width, h*height);
        glVertex3f(-0.5, -0.5, -0.5);
        glTexCoord2f(w*width, 0);
        glVertex3f(-0.5, height-0.5, -0.5);
        glTexCoord2f(0, 0);
        glVertex3f(-0.5, height-0.5, 0.5);
        //RIGHT BORDER
        glNormal3f(-1, 0, 0);
        glTexCoord2f(0, h*height);
        glVertex3f(width-0.5, -0.5, 0.5);
        glTexCoord2f(w*width, h*height);
        glVertex3f(width-0.5, height-0.5, 0.5);
        glTexCoord2f(w*width, 0);
        glVertex3f(width-0.5, height-0.5, -0.5);
        glTexCoord2f(0, 0);
        glVertex3f(width-0.5, -0.5, -0.5);

        //TOP BORDER
        glNormal3f(-1, 0, 0);
        glTexCoord2f(0, h*height);
        glVertex3f(-0.5, height-0.5, 0.5);
        glTexCoord2f(w*width, h*height);
        glVertex3f(-0.5, height-0.5, -0.5);
        glTexCoord2f(w*width, 0);
        glVertex3f(width-0.5, height-0.5, -0.5);
        glTexCoord2f(0, 0);
        glVertex3f(width-0.5, height-0.5, 0.5);

        //BOTTOM BORDER
        glNormal3f(1, 0, 0);
        glTexCoord2f(0, h*height);
        glVertex3f(-0.5, -0.5, 0.5);
        glTexCoord2f(w*width, h*height);
        glVertex3f(width-0.5, -0.5, 0.5);
        glTexCoord2f(w*width, 0);
        glVertex3f(width-0.5, -0.5, -0.5);
        glTexCoord2f(0, 0);
        glVertex3f(-0.5, -0.5, -0.5);


    glEnd();

    for(int i=0; i<width; i++){
        for(int j=0; j<height; j++){
            float startX=i-0.5, endX=i+0.5, startY=j-0.5, endY=j+0.5;
            switch(lab[i][j]){
                case GRID_WALL:
                glBegin(GL_QUADS);
                    //FRONT QUAD
                    glNormal3f(0, 0, 1);
                    glTexCoord2f(0, h);
                    glVertex3f(startX, startY, 0.5);
                    glTexCoord2f(w, h);
                    glVertex3f(endX, startY, 0.5);
                    glTexCoord2f(w, 0);
                    glVertex3f(endX, endY, 0.5);
                    glTexCoord2f(0, 0);
                    glVertex3f(startX, endY, 0.5);

                    //TOP QUAD
                    glNormal3f(0, 1, 0);
                    glTexCoord2f(0, h);
                    glVertex3f(startX, endY, 0.5);
                    glTexCoord2f(w, h);
                    glVertex3f(endX, endY, 0.5);
                    glTexCoord2f(w, 0);
                    glVertex3f(endX, endY, -0.5);
                    glTexCoord2f(0, 0);
                    glVertex3f(startX, endY, -0.5);

                    //BOTTOM QUAD
                    glNormal3f(0, -1, 0);
                    glTexCoord2f(0, h);
                    glVertex3f(startX, startY, 0.5);
                    glTexCoord2f(w, h);
                    glVertex3f(startX, startY, -0.5);
                    glTexCoord2f(w, 0);
                    glVertex3f(endX, startY, -0.5);
                    glTexCoord2f(0, 0);
                    glVertex3f(endX, startY, 0.5);

                    //RIGHT QUAD
                    glNormal3f(1, 0, 0);
                    glTexCoord2f(0, h);
                    glVertex3f(endX, startY, 0.5);
                    glTexCoord2f(w, h);
                    glVertex3f(endX, startY, -0.5);
                    glTexCoord2f(w, 0);
                    glVertex3f(endX, endY, -0.5);
                    glTexCoord2f(0, 0);
                    glVertex3f(endX, endY, 0.5);

                    //LEFT QUAD
                    glNormal3f(-1, 0, 0);
                    glTexCoord2f(0, h);
                    glVertex3f(startX, startY, 0.5);
                    glTexCoord2f(w, h);
                    glVertex3f(startX, endY, 0.5);
                    glTexCoord2f(w, 0);
                    glVertex3f(startX, endY, -0.5);
                    glTexCoord2f(0, 0);
                    glVertex3f(startX, startY, -0.5);
                glEnd();
                break;

                case GRID_FOOD:
                foodMaterial.apply();
                drawFood(i, j);
                wallMaterial.apply();
                break;

            }

        }
    }
    wallTexture.disable();
}
