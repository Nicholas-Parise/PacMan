#pragma once
#include <string>
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Directions.h"
#include "configuration.h"

class Entity
{
    public:
        Entity(sf::Texture &texture);
        virtual ~Entity();
        void setSpeed(int x, int y);
        bool changedPosition();
        void updateOldRC();
        bool teleporter();
        std::string dirToString();
        void reset();
        void updateRC();

        float xSpeed;
        float ySpeed;
        int row;
        int col;
        int oldRow;
        int oldCol;

        Directions direction;

        sf::Sprite sprite;

    protected:

    private:
};
