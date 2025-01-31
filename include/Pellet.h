#ifndef PELLET_H
#define PELLET_H
#include "configuration.h"
#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>

class Pellet
{
    public:
        Pellet(sf::Texture &texture);
        virtual ~Pellet();
        void reset();
        void animate(int &glowTimer);

        bool dotHit(sf::Sprite pac);
        bool powerHit(sf::Sprite pac);
        bool berryHit(sf::Sprite pac);

        void spawnBerry(sf::Texture *berryTextures, int Berrytimer);

        int dotsEaten;
        int PowerUpEaten;

        std::vector<sf::RectangleShape> Dot;
        std::vector<sf::CircleShape> PowerUp;

        sf::Sprite Berry;

        const int DOTS = 244;
        const int POWERUPS = 4;

    protected:

    private:
};

#endif // PELLET_H
