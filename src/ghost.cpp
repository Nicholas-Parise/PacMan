#include "Ghost.h"

Ghost::Ghost(){
    reset();
    // vector<vector<int>> solution(870);
    // vector<int> PathCol;
    // vector<int> PathRow;
}


void Ghost::reset(){
    xSpeed = 0;
    ySpeed = 0;
    row = 13;
    col = 15;
    oldRow = -1;
    oldCol = -1;
    pathIndex = 1;

    direction = NONE;
    state = SCATTER;
}

void Ghost::setScatter(int r, int c){
    this->scatterRow = r;
    this->scatterCol = c;
}

void Ghost::setSpeed(int x, int y){
    this->xSpeed = x;
    this->ySpeed = y;
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



void Ghost::followPath(int PathRow, int PathCol, float speed, float deadSpeed){

    Directions tempDir = NONE;

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
        this->xSpeed = deadSpeed * rowMulti;
        this->ySpeed = deadSpeed * colMulti;
    }else{
        this->xSpeed = speed * rowMulti;
        this->ySpeed = speed * colMulti;
    }

}

bool Ghost::changedPosition(){

    if(this->row != this->oldRow){
        return true;
    }
    if(this->col != this->oldCol){
        return true;
    }

    return false;
}

void Ghost::updateOldRC(){
    this->oldRow = this->row;
    this->oldCol = this->col;
}


std::string Ghost::dirToString(){
    if(direction == UP)
        return "Up";
    if(direction == RIGHT)
        return "Right";
    if(direction == UP)
        return "Up";
    if(direction == LEFT)
        return "Left";
}


void Ghost::scaredStop(int powerUpTimer) {

    if(this->state == SCARED){
        if(powerUpTimer > 600) {
            this->state = CHASE;
        }
    }
}


sf::Texture &Ghost::textureSwitcher(sf::Texture *ghostTextures, sf::Texture *scaredTextures, sf::Texture *eyeTextures, int FeetTimer, int powerUpTimer){

    sf::Texture *textures;
    int offset = 0;

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
                return textures[0+offset];
            case UP:
                return textures[1+offset];
            case RIGHT:
                return textures[2+offset];
            case DOWN:
                return textures[3+offset];
        };

    }else{
        if(powerUpTimer <480 || (powerUpTimer > 510 && powerUpTimer < 540) || powerUpTimer >570) {

            return textures[0+offset];

        } else if((powerUpTimer > 480 && powerUpTimer < 510) || (powerUpTimer > 540&& powerUpTimer < 570)) {

            return textures[2+offset];
        }
    }

    // so it's not null
    return ghostTextures[0];
}







Ghost::~Ghost()
{
    //dtor
}
