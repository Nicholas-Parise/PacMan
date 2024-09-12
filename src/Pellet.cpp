#include "Pellet.h"

Pellet::Pellet()
{
    sf::RectangleShape tempDot;
    sf::CircleShape tempPowerUp;

    for (int i = 0; i < DOTS; i++){

        tempDot.setFillColor(sf::Color::White);
        tempDot.setSize(sf::Vector2f(5, 5));
        tempDot.setOrigin(2.5,2.5);
        Dot.push_back(tempDot);
    }


    for (int i = 0; i < POWERUPS; i++){

        tempPowerUp.setFillColor(sf::Color::White);
        tempPowerUp.setRadius(10);
        tempPowerUp.setOrigin(10,10);
        tempPowerUp.setOutlineColor(sf::Color(250, 150, 100));
        PowerUp.push_back(tempPowerUp);
    }

    reset();
}

Pellet::~Pellet()
{
    //dtor
}



void Pellet::reset(){

    int dotplace = 0;
    int PowerUpplace = 0;
    for(int i = 0; i<conf::SIZEY; i++){
        for(int j = 0; j<conf::SIZEX; j++){

            if(conf::GameMatrix[i][j] == 0){
                Dot[dotplace].setPosition(sf::Vector2f(18.78571429*j+(18.78571429/2), 18.61290323*i+(18.61290323/2)));
                dotplace++;

            }
            if(conf::GameMatrix[i][j] == 8){
                PowerUp[PowerUpplace].setPosition(sf::Vector2f(18.78571429*j+(18.78571429/2), 18.61290323*i+(18.61290323/2)));
                PowerUpplace++;

            }

        }
    }

     dotsEaten = 0;
     PowerUpEaten = 0;
}


void Pellet::animate(int &glowTimer){

    if(glowTimer%2 == 0){
        for(int i = 0; i<POWERUPS; i++){
            PowerUp[i].setOutlineThickness(-11+(glowTimer/2));
        }
    }

    if (glowTimer > 24)
    {
        glowTimer = 0;
    }
}

