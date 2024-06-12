#include "Entity.h"

Entity::Entity()
{
    //ctor
}

Entity::~Entity()
{
    //dtor
}

void Entity::setSpeed(int x, int y){
    this->xSpeed = x;
    this->ySpeed = y;
}

bool Entity::changedPosition(){

    if(this->row != this->oldRow){
        return true;
    }
    if(this->col != this->oldCol){
        return true;
    }

    return false;
}

void Entity::updateOldRC(){
    this->oldRow = this->row;
    this->oldCol = this->col;
}


bool Entity::teleporter(){

    if(sprite.getPosition().x<20 && direction == LEFT){
        sprite.setPosition(522,269.887096835);
        return true;
    }

    if(sprite.getPosition().x>512 && direction == RIGHT){
        sprite.setPosition(10,269.887096835);
        return true;
    }

    return false;
}


std::string Entity::dirToString(){
    if(direction == UP)
        return "Up";
    if(direction == RIGHT)
        return "Right";
    if(direction == UP)
        return "Up";
    if(direction == LEFT)
        return "Left";
}



void Entity::reset(){
    xSpeed = 0;
    ySpeed = 0;
    oldRow = -1;
    oldCol = -1;
    direction = NONE;
}

