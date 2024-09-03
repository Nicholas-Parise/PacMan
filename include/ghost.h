#pragma once
#include "Entity.h"
#include "Node.h"
#include <vector>

enum States{
    CHASE,
    SCATTER,
    SCARED,
    DEAD
};

class Ghost: public Entity{
    public:
        Ghost();
        virtual ~Ghost();
        void reset();

        void setScatter(int r, int c);

        void changeState(States s);
        void followPath(int PathRow, int PathCol);
        void scaredStop(int powerUpTimer);
        bool isOppositeDirection(Directions a, Directions b);
        //sf::Texture &textureSwitcher(sf::Texture *ghostTextures, sf::Texture *scaredTextures, sf::Texture *eyeTextures, int FeetTimer, int powerUpTimer);
        void textureSwitcher(sf::Texture *ghostTextures, sf::Texture *scaredTextures, sf::Texture *eyeTextures, int FeetTimer, int powerUpTimer);


        int scatterRow;
        int scatterCol;

        std::vector<Node> path;

       // vector<vector<int>> solution(870);
       // vector<int> PathCol;
       // vector<int> PathRow;

        States state;

    protected:

    private:
};

