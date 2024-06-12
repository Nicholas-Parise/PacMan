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

    row = 14;
    col = 17;

    sprite.setPosition(sf::Vector2f(18.78571429*row+(18.78571429/2), 18.61290323*col+(18.61290323/2)));
}

/*
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && PacManAvallibleDir[i] == "Left"){

                PacMan.setRotation(-180);
                goDirection(LEFT);

            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)&& PacManAvallibleDir[i] == "Right"){

                PacMan.setRotation(0);

                goDirection(RIGHT);
            }

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)&& PacManAvallibleDir[i] == "Up"){

                PacMan.setRotation(-90);
                goDirection(UP);

            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)&& PacManAvallibleDir[i] == "Down"){

                PacMan.setRotation(90);
                goDirection(DOWN);

            }
*/



void Player::textureSwitcher(sf::Texture &pacTextures,sf::Texture &pacTextures2){

    sf::Texture *tex;
    int offset = 1;

    sprite.setTexture(pacTextures2);

    if(aniTimer<10) {
        offset = 0;
        sprite.setTexture(pacTextures);
    }


/*
    switch(direction){

        case LEFT:
            sprite.setRotation(-180);
            break;
        case UP:
            sprite.setRotation(-90);
            break;
        case RIGHT:
            sprite.setRotation(0);
            break;
        case DOWN:
            sprite.setRotation(90);
            break;
    };
*/

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

    if(xSpeed !=0 || ySpeed !=0){

        aniTimer++;

        if(aniTimer > 20){
            aniTimer = 0;
        }
    }
}






