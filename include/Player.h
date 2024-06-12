#include "Entity.h"

class Player: public Entity{

    public:
        Player();
        virtual ~Player();
        void reset();
        void textureSwitcher(sf::Texture &pacTextures,sf::Texture &pacTextures2);
        void goDirection(Directions d);
        void updateAniTimer();

        int aniTimer;


    protected:

    private:
};
