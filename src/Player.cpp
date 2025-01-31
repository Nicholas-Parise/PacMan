#include "Player.h"

Player::Player(sf::Texture &texture) : Entity(texture)
{
    sprite.setOrigin(sf::Vector2f(15,15));
    reset();
}

Player::~Player()
{
    //dtor
}


void Player::reset(){
    xSpeed = 0;
    ySpeed = 0;
    oldRow = -1;
    oldCol = -1;
    direction = NONE;

    dead = false;

    row = 17;
    col = 14;

    sprite.setPosition(sf::Vector2f(conf::TILESIZE*col+(conf::TILESIZE/2),conf::TILESIZE*row+(conf::TILESIZE/2)));
}


bool Player::killPac(){
    if(dead && deadAniTimer >= 98){
        return true;
    }
    return false;
}



void Player::textureSwitcher(sf::Texture *pacTextures, sf::Texture *deadTextures){

    sf::Texture *tex;

    if(dead){

        sprite.setTexture(deadTextures[deadAniTimer/9]);
        //tex = &(textures[1+offset]);
        //    sprite.setTexture(*tex);

    }else{
        //int offset = 1;
        sprite.setTexture(pacTextures[1]);
        if(aniTimer<10) {
            //offset = 0;
            sprite.setTexture(pacTextures[0]);
        }
    }
}

void Player::handleInput(){

    std::vector<Directions> PacManAvallibleDir = avaliableDirections();

    if(!dead){
            for(int i = 0; i<PacManAvallibleDir.size(); i++)
            {
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left) && PacManAvallibleDir[i] == LEFT)
                {
                    goDirection(LEFT);
                }
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right) && PacManAvallibleDir[i] == RIGHT)
                {
                    goDirection(RIGHT);
                }

                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up) && PacManAvallibleDir[i] == UP)
                {
                    goDirection(UP);
                }

                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down) && PacManAvallibleDir[i] == DOWN)
                {
                    goDirection(DOWN);
                }
            }
        }

}


/*
std::vector<Directions> Player::avaliableDirections()
{

    std::vector<Directions> AvallibleDir;


    if(conf::GameMatrix[row-1][col] != 1 && direction != DOWN){
        AvallibleDir.push_back(UP);
    }else{
        stop();
    }

    if(conf::GameMatrix[row+1][col] != 1 && direction != UP){
        AvallibleDir.push_back(DOWN);
    }else{
        stop();
    }


    if(conf::GameMatrix[row][col+1] != 1 && direction != LEFT){
        AvallibleDir.push_back(RIGHT);
    }else{
        stop();
    }

    if(conf::GameMatrix[row][col-1] != 1 && direction != RIGHT){
        AvallibleDir.push_back(LEFT);
    }else{
        stop();
    }

    return AvallibleDir;
}
*/


std::vector<Directions> Player::avaliableDirections()
{

    std::vector<Directions> AvallibleDir;

    //1 is a wall

/*
    if(conf::GameMatrix[row-1][col] != 1 && direction != DOWN){
        AvallibleDir.push_back(UP);
    }else{
        stop();
    }
*/

        //Above
        if(conf::GameMatrix[row-1][col] == 1)
        {

            if(direction == UP)
            {

                stop();
            }
        }
        else
        {
            AvallibleDir.push_back(UP);
        }

    //below
    if(conf::GameMatrix[row+1][col] == 1)
    {

        if(direction == DOWN)
        {
                         stop();
        }
    }
    else
    {
        AvallibleDir.push_back(DOWN);
    }


    //Left
    if(conf::GameMatrix[row][col-1] == 1)
    {

        if(direction == LEFT)
        {
                            stop();
        }
    }
    else
    {
        AvallibleDir.push_back(LEFT);
    }


    //Right
    if(conf::GameMatrix[row][col+1] == 1)
    {

        if(direction == RIGHT)
        {
                          stop();
        }
    }
    else
    {
        AvallibleDir.push_back(RIGHT);
    }


    //cout<<"Available dir: "<<AvallibleDir.size()<<endl;

    return AvallibleDir;

}






 void Player::stop(){
    this->setSpeed(0,0);
}



void Player::goDirection(Directions d){

    this->direction = d;

    switch(direction){

        case LEFT:
            sprite.setRotation(sf::degrees(-180.0f));
            xSpeed = -2;
            ySpeed = 0;
            break;
        case UP:
            sprite.setRotation(sf::degrees(-90.0f));
            xSpeed = 0;
            ySpeed = -2;
            break;
        case RIGHT:
            sprite.setRotation(sf::degrees(0.0f));
            xSpeed = 2;
            ySpeed = 0;
            break;
        case DOWN:
            sprite.setRotation(sf::degrees(90.0f));
            xSpeed = 0;
            ySpeed = 2;
            break;
    };
}


void Player::updateAniTimer(){

    if(dead){
        if(deadAniTimer < 98){
            deadAniTimer++;
        }else{
         deadAniTimer = 0;
        }
    }else{
        deadAniTimer = 0;
        if(xSpeed !=0 || ySpeed !=0){
            aniTimer++;
            if(aniTimer > 20){
                aniTimer = 0;
            }
        }
    }
}






