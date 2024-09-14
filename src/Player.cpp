#include "Player.h"

Player::Player()
{
    sprite.setOrigin(15,15);
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

    row = 14;
    col = 17;

    sprite.setPosition(sf::Vector2f(18.78571429*row+(18.78571429/2), 18.61290323*col+(18.61290323/2)));
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
            sprite.setRotation(-180);
            xSpeed = -2;
            ySpeed = 0;
            break;
        case UP:
            sprite.setRotation(-90);
            xSpeed = 0;
            ySpeed = -2;
            break;
        case RIGHT:
            sprite.setRotation(0);
            xSpeed = 2;
            ySpeed = 0;
            break;
        case DOWN:
            sprite.setRotation(90);
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






