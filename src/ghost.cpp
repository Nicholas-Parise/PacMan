#include "Ghost.h"
#include "configuration.h"


Ghost::Ghost(){

    sprite.setOrigin(15,15);

    reset();

    // vector<vector<int>> solution(870);
    // vector<int> PathCol;
    // vector<int> PathRow;
}


void Ghost::reset(){

    xSpeed = 0;
    ySpeed = 0;
    oldRow = -1;
    oldCol = -1;
    direction = NONE;

    row = 13;
    col = 15;
    state = SCATTER;

    sprite.setPosition(sf::Vector2f(18.78571429*row+(18.78571429/2), 18.61290323*col+(18.61290323/2)));
}

void Ghost::setScatter(int r, int c){
    this->scatterRow = r;
    this->scatterCol = c;
}



void Ghost::changeState(States s){

    if(state != DEAD){
        state = s;
        direction = NONE;
    }
}


 bool Ghost::isOppositeDirection(Directions a, Directions b){

    if(a == b){
        return false;
    }

    if(a == UP && b == DOWN || a == DOWN && b == UP){
        return true;
    }

    if(a == LEFT && b == RIGHT|| a == RIGHT && b == LEFT){
        return true;
    }

    return false;
}


void Ghost::followPath(int PathRow, int PathCol){

    Directions tempDir = direction;

    int rowMulti = PathRow - this->row;
    int colMulti = PathCol - this->col;

    if(rowMulti == 0){
        if(colMulti>0){
            tempDir = DOWN;
        }else{
            tempDir = UP;
        }
    }

    if(colMulti == 0){
        if(rowMulti>0){
            tempDir = RIGHT;
        }else{
            tempDir = LEFT;
        }
    }

    if(isOppositeDirection(this->direction,tempDir)){
        return;
    }else{
        this->direction = tempDir;
    }


    if(this->state == DEAD){
        this->xSpeed = conf::DeadSpeed * rowMulti;
        this->ySpeed = conf::DeadSpeed * colMulti;
    }else{
        this->xSpeed = conf::GhostSpeed * rowMulti;
        this->ySpeed = conf::GhostSpeed * colMulti;
    }

}


void Ghost::scaredStop(int powerUpTimer) {

    if(this->state == SCARED){
        if(powerUpTimer > 600) {
            this->state = CHASE;
        }
    }
}


void Ghost::textureSwitcher(sf::Texture *ghostTextures, sf::Texture *scaredTextures, sf::Texture *eyeTextures, int FeetTimer, int powerUpTimer){

    int offset = 0;
    sf::Texture *textures;
    sf::Texture *tex;

    switch(state){
        case SCARED:
            textures = scaredTextures;
            offset = 1;
            break;
        case DEAD:
            textures = eyeTextures;
            offset = 0;
            break;
        default:
        case CHASE:
        case SCATTER:
            textures = ghostTextures;
            offset = 4;
            break;
    };

    if(FeetTimer<10) {
        offset = 0;
    }


    if(this->state != SCARED){
        switch(direction){

            case LEFT:
                tex = &(textures[0+offset]);
                break;
            case UP:
                tex = &(textures[1+offset]);
                break;
            case RIGHT:
                tex = &(textures[2+offset]);
                break;
            case DOWN:
                tex = &(textures[3+offset]);
                break;
        };

    }else{
        if(powerUpTimer <480 || (powerUpTimer > 510 && powerUpTimer < 540) || powerUpTimer >570) {

            tex = &textures[0+offset];

        } else if((powerUpTimer > 480 && powerUpTimer < 510) || (powerUpTimer > 540&& powerUpTimer < 570)) {

            tex = &textures[2+offset];
        }
    }

    sprite.setTexture(*tex);
}




Ghost::~Ghost()
{
    //dtor
}
