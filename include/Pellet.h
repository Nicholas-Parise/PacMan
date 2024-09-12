#ifndef PELLET_H
#define PELLET_H
#include "configuration.h"
#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>

class Pellet
{
    public:
        Pellet();
        virtual ~Pellet();
        void reset();
        void animate(int &glowTimer);

        int dotsEaten;
        int PowerUpEaten;

        std::vector<sf::RectangleShape> Dot;
        std::vector<sf::CircleShape> PowerUp;

        const int DOTS = 244;
        const int POWERUPS = 4;

    protected:

    private:
};

#endif // PELLET_H
