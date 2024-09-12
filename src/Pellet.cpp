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

    Berry.setScale(2.f, 2.f);
    Berry.setPosition(1000,1000);

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


bool Pellet::dotHit(sf::Sprite pac){

    for (int i = 0; i < DOTS; i++){
        if(pac.getGlobalBounds().intersects(Dot[i].getGlobalBounds())){

            Dot[i].setPosition(Dot[i].getPosition().x+1000,0);

            dotsEaten ++;
            //score +=5;
            return true;
        }
    }
    return false;
}


bool Pellet::powerHit(sf::Sprite pac){

    for (int i = 0; i < POWERUPS; i++){
        if(pac.getGlobalBounds().intersects(PowerUp[i].getGlobalBounds())){

            PowerUp[i].setPosition(PowerUp[i].getPosition().x+1000,0);

            PowerUpEaten ++;
            return true;
        }
    }
    return false;
}


bool Pellet::berryHit(sf::Sprite pac){

    if(pac.getGlobalBounds().intersects(Berry.getGlobalBounds())){

            Berry.setPosition(1000,1000);
            return true;
    }
    return false;
}



void Pellet::spawnBerry(sf::Texture *berryTextures, int Berrytimer){

    if(Berrytimer == 120){

        int randtemp = rand()%7;

        Berry.setTexture(berryTextures[randtemp]);

        Berry.setPosition(522/2,620/2);
    }

}



