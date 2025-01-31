#include "Ghost.h"
#include "configuration.h"


Ghost::Ghost(sf::Texture *ghostTextures, sf::Texture *scaredTextures, sf::Texture *eyeTextures) : Entity(ghostTextures[0]){

    sprite.setOrigin(sf::Vector2f(14.0f,14.0f));

    this->ghostTextures = ghostTextures;
    this->scaredTextures = scaredTextures;
    this->eyeTextures = eyeTextures;

    reset();
}


void Ghost::reset()
{

    xSpeed = 0;
    ySpeed = 0;
    oldRow = -1;
    oldCol = -1;
    direction = NONE;

    row = conf::GhostHomeRow+3;
    col = conf::GhostHomeCol;
    state = SCATTER;

    sprite.setPosition(sf::Vector2f(conf::TILESIZE*col+(conf::TILESIZE/2),conf::TILESIZE*row+(conf::TILESIZE/2)));
}

void Ghost::setScatter(int r, int c)
{
    this->scatterRow = r;
    this->scatterCol = c;
}



void Ghost::changeState(States s)
{

    if(state != DEAD)
    {
        state = s;
        //direction = NONE;
    }
}


bool Ghost::isOppositeDirection(Directions a, Directions b)
{

    if(a == b)
    {
        return false;
    }

    if(a == UP && b == DOWN || a == DOWN && b == UP)
    {
        return true;
    }

    if(a == LEFT && b == RIGHT|| a == RIGHT && b == LEFT)
    {
        return true;
    }

    return false;
}


sf::Vector2f matrixToScreen(int row, int col)
{
    // Add half the tile size to both coordinates for centering
    return sf::Vector2f(col * conf::TILESIZE + conf::TILESIZE / 2.0f, row * conf::TILESIZE + conf::TILESIZE / 2.0f);
}

void Ghost::moveSprite(float deltaTime)
{
    float speed = conf::GhostSpeed;

    if(state == DEAD){
        speed = conf::DeadSpeed;
    }


    // if there are no nodes
    if(path.size()<2) return;

    // Get current and target positions in screen coordinates (centered)
    sf::Vector2f currentPos = sprite.getPosition();
    sf::Vector2f targetPos = matrixToScreen(path[1].row, path[1].col);

    // Compute direction and distance
    sf::Vector2f direction = targetPos - currentPos;
    float distance = std::sqrt(direction.x * direction.x + direction.y * direction.y);


    if(abs(direction.x) > abs(direction.y)){

        if(direction.x >0){
            this->direction = RIGHT;
            //std::cout<<"right"<<std::endl;
        }
        else{
            this->direction = LEFT;
                 //   std::cout<<"left"<<std::endl;
        }
    }else{

        if(direction.y > 0)
        {
            this->direction = DOWN;
             //   std::cout<<"down"<<std::endl;
        }
        else
        {
            this->direction = UP;
              //  std::cout<<"up"<<std::endl;
        }

    }


    // Check if we're close enough to the target node
    if (distance > 1.0f)
    {
        // Move toward the target node
        sf::Vector2f normalizedDir = (direction * speed / distance) ; //* deltaTime
        sprite.move(normalizedDir);
    }
    else
    {
        // Snap to target node and move to the next one
        sprite.setPosition(targetPos);
    }
}



void Ghost::scaredStop(int powerUpTimer)
{

    if(this->state == SCARED)
    {
        if(powerUpTimer > 600)
        {
            this->state = CHASE;
        }
    }
}


void Ghost::outOfSpawn(){

    if(row == conf::GhostHomeRow+3 && col == conf::GhostHomeCol && state == DEAD)
    {
        state = SCATTER;
        direction = NONE;
    }
}



void Ghost::textureSwitcher(int FeetTimer, int powerUpTimer)
{

    int offset = 0;
    sf::Texture *textures;
    sf::Texture *tex;

    switch(state)
    {
    case SCARED:
        textures = scaredTextures;
        offset = 1;
        break;
    case DEAD:
        textures = eyeTextures;
        offset = 0;
        break;
    default:
    case CHASE:
    case SCATTER:
        textures = ghostTextures;
        offset = 4;
        break;
    };

    if(FeetTimer<10)
    {
        offset = 0;
    }


    if(this->state != SCARED)
    {
        switch(direction)
        {

        case NONE:
        case LEFT:
            tex = &(textures[0+offset]);
            break;
        case UP:
            tex = &(textures[1+offset]);
            break;
        case RIGHT:
            tex = &(textures[2+offset]);
            break;
        case DOWN:
            tex = &(textures[3+offset]);
            break;
        };

    }
    else
    {
        if(powerUpTimer <480 || (powerUpTimer > 510 && powerUpTimer < 540) || powerUpTimer >570)
        {

            tex = &textures[0+offset];

        }
        else if((powerUpTimer > 480 && powerUpTimer < 510) || (powerUpTimer > 540&& powerUpTimer < 570))
        {

            tex = &textures[2+offset];
        }
    }

    sprite.setTexture(*tex);
}




Ghost::~Ghost()
{
    //dtor
}
