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

enum States{
    CHASE,
    SCATTER,
    SCARED,
    DEAD
};

class Ghost
{
    public:
        Ghost();
        virtual ~Ghost();
        void reset();
        void setScatter(int r, int c);
        void setSpeed(int x, int y);
        void followPath(int PathRow, int PathCol, float speed, float deadSpeed);
        bool changedPosition();
        void updateOldRC();
        std::string dirToString();
        void scaredStop(int powerUpTimer);
        sf::Texture &textureSwitcher(sf::Texture *ghostTextures, sf::Texture *scaredTextures, sf::Texture *eyeTextures, int FeetTimer, int powerUpTimer);
        bool isOppositeDirection(Directions a, Directions b);

        float xSpeed;
        float ySpeed;
        int row;
        int col;
        int oldRow;
        int oldCol;
        int pathIndex;

        int scatterRow;
        int scatterCol;

       // vector<vector<int>> solution(870);
       // vector<int> PathCol;
       // vector<int> PathRow;

        Directions direction;
        States state;


    protected:

    private:
};

