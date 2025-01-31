#include "Entity.h"

Entity::Entity(sf::Texture &texture) : sprite(texture)
{
   //sprite.setTexture(texture);
 //   sf::Sprite sprite(texture);

}

Entity::~Entity()
{
    //dtor
}

void Entity::updateRC(){
    row = sprite.getPosition().y/conf::TILESIZE;
    col = sprite.getPosition().x/conf::TILESIZE;
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

    if(sprite.getPosition().x<conf::TILESIZE + 2 && direction == LEFT){ // less than one tile away from left side
        sprite.setPosition(sf::Vector2f((float)(26*conf::TILESIZE+conf::TILESIZE/2),(float)(14*conf::TILESIZE+conf::TILESIZE/2)));
        return true;
    }

    if(sprite.getPosition().x>26*conf::TILESIZE+conf::TILESIZE/2 && direction == RIGHT){ // less than one tile away from right side
        sprite.setPosition(sf::Vector2f(conf::TILESIZE+conf::TILESIZE/2,14*conf::TILESIZE+conf::TILESIZE/2));
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

