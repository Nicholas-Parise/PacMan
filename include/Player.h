#include "Entity.h"

class Player: public Entity{

    public:
        Player(sf::Texture &texture);
        virtual ~Player();
        void reset();
        void textureSwitcher(sf::Texture *pacTextures, sf::Texture *deadTextures);
        void goDirection(Directions d);
        void updateAniTimer();
        bool killPac();

        int aniTimer;
        int deadAniTimer;

        bool dead;

    protected:

    private:
};
