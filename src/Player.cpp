#include "Player.h"

Player::Player(sf::Texture &texture) : Entity(texture)
{
    sprite.setOrigin(sf::Vector2f(15,15));
    reset();
}

Player::~Player()
{
    //dtor
}


void Player::reset(){
    xSpeed = 0;
    ySpeed = 0;
    oldRow = -1;
    oldCol = -1;
    direction = NONE;

    dead = false;

    row = 17;
    col = 14;

    sprite.setPosition(sf::Vector2f(conf::TILESIZE*col+(conf::TILESIZE/2),conf::TILESIZE*row+(conf::TILESIZE/2)));
}


bool Player::killPac(){
    if(dead && deadAniTimer >= 98){
        return true;
    }
    return false;
}



void Player::textureSwitcher(sf::Texture *pacTextures, sf::Texture *deadTextures){

    sf::Texture *tex;

    if(dead){

        sprite.setTexture(deadTextures[deadAniTimer/9]);
        //tex = &(textures[1+offset]);
        //    sprite.setTexture(*tex);

    }else{
        //int offset = 1;
        sprite.setTexture(pacTextures[1]);
        if(aniTimer<10) {
            //offset = 0;
            sprite.setTexture(pacTextures[0]);
        }
    }
}


void Player::goDirection(Directions d){

    this->direction = d;

    switch(direction){

        case LEFT:
            sprite.setRotation(sf::degrees(-180.0f));
            xSpeed = -2;
            ySpeed = 0;
            break;
        case UP:
            sprite.setRotation(sf::degrees(-90.0f));
            xSpeed = 0;
            ySpeed = -2;
            break;
        case RIGHT:
            sprite.setRotation(sf::degrees(0.0f));
            xSpeed = 2;
            ySpeed = 0;
            break;
        case DOWN:
            sprite.setRotation(sf::degrees(90.0f));
            xSpeed = 0;
            ySpeed = 2;
            break;
    };
}


void Player::updateAniTimer(){

    if(dead){
        if(deadAniTimer < 98){
            deadAniTimer++;
        }else{
         deadAniTimer = 0;
        }
    }else{
        deadAniTimer = 0;
        if(xSpeed !=0 || ySpeed !=0){
            aniTimer++;
            if(aniTimer > 20){
                aniTimer = 0;
            }
        }
    }
}






