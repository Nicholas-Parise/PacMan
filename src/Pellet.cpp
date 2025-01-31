#include "Pellet.h"

Pellet::Pellet(sf::Texture &texture) : Berry(texture)
{

    sf::RectangleShape tempDot;
    sf::CircleShape tempPowerUp;

    for (int i = 0; i < DOTS; i++){

        tempDot.setFillColor(sf::Color::White);
        tempDot.setSize(sf::Vector2f(5.0, 5.0));
        tempDot.setOrigin(sf::Vector2f(2.5, 2.5));
        Dot.push_back(tempDot);
    }


    for (int i = 0; i < POWERUPS; i++){

        tempPowerUp.setFillColor(sf::Color::White);
        tempPowerUp.setRadius(conf::TILESIZE/2);
        tempPowerUp.setOrigin(sf::Vector2f(conf::TILESIZE/2, conf::TILESIZE/2));
        tempPowerUp.setOutlineColor(sf::Color(250, 150, 100));
        PowerUp.push_back(tempPowerUp);
    }

    Berry.setScale(sf::Vector2f(2.0, 2.0));
    Berry.setPosition(sf::Vector2f(1000,1000));

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
                Dot[dotplace].setPosition(sf::Vector2f(conf::TILESIZE*j+(conf::TILESIZE/2), conf::TILESIZE*i+(conf::TILESIZE/2)));
                dotplace++;

            }
            if(conf::GameMatrix[i][j] == 8){
                PowerUp[PowerUpplace].setPosition(sf::Vector2f(conf::TILESIZE*j+(conf::TILESIZE/2), conf::TILESIZE*i+(conf::TILESIZE/2)));
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
        if(pac.getGlobalBounds().findIntersection(Dot[i].getGlobalBounds())){

            Dot[i].setPosition(sf::Vector2f(Dot[i].getPosition().x+1000,0));

            dotsEaten ++;
            //score +=5;
            return true;
        }
    }
    return false;
}


bool Pellet::powerHit(sf::Sprite pac){

    for (int i = 0; i < POWERUPS; i++){
        if(pac.getGlobalBounds().findIntersection(PowerUp[i].getGlobalBounds())){

            PowerUp[i].setPosition(sf::Vector2f(PowerUp[i].getPosition().x+1000,0));

            PowerUpEaten ++;
            return true;
        }
    }
    return false;
}


bool Pellet::berryHit(sf::Sprite pac){

    if(pac.getGlobalBounds().findIntersection(Berry.getGlobalBounds())){

            Berry.setPosition(sf::Vector2f(1000,1000));
            return true;
    }
    return false;
}



void Pellet::spawnBerry(sf::Texture *berryTextures, int Berrytimer){

    if(Berrytimer == 120){

        int randtemp = rand()%7;

        Berry.setTexture(berryTextures[randtemp]);

        Berry.setPosition(sf::Vector2f(conf::TILESIZE*13+(conf::TILESIZE/2),conf::TILESIZE*23));

    }

}



