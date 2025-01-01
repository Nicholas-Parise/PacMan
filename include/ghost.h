#pragma once
#include "Entity.h"
#include "Node.h"
#include <vector>
#include <cmath>


enum States
{
    CHASE,
    SCATTER,
    SCARED,
    DEAD
};

class Ghost: public Entity
{
public:
    Ghost(sf::Texture &texture);
    virtual ~Ghost();
    void reset();

    void setScatter(int r, int c);

    void changeState(States s);
    void followPath();
    void scaredStop(int powerUpTimer);
    void outOfSpawn();
    bool isOppositeDirection(Directions a, Directions b);
    //sf::Texture &textureSwitcher(sf::Texture *ghostTextures, sf::Texture *scaredTextures, sf::Texture *eyeTextures, int FeetTimer, int powerUpTimer);
    void textureSwitcher(sf::Texture *ghostTextures, sf::Texture *scaredTextures, sf::Texture *eyeTextures, int FeetTimer, int powerUpTimer);
    void moveSprite(float deltaTime);

    int scatterRow;
    int scatterCol;

    std::vector<Node> path;

    States state;

protected:

private:
};

