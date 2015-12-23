#include "labyrinth.h"
labyrinth::labyrinth(int w, int h):width(w), height(h), currentSnake(){
    lab = new int* [width];
    for(int i=0;i<width;i++){
        lab[i] = new int[height];
        for(int j=0;j<height;j++) lab[i][j]=0;
    }
}
