#pragma once
#include <string>
#include <SFML/Graphics.hpp>
#include <iostream>

   enum Directions{
    UP,
    DOWN,
    LEFT,
    RIGHT,
    NONE
    };

class Entity
{
    public:
        Entity();
        virtual ~Entity();
        void setSpeed(int x, int y);
        bool changedPosition();
        void updateOldRC();
        bool teleporter();
        std::string dirToString();

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
