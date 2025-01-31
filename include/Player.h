#include "Entity.h"
#include <vector>

class Player: public Entity{

    public:
        Player(sf::Texture &texture);
        virtual ~Player();
        void reset();
        void textureSwitcher(sf::Texture *pacTextures, sf::Texture *deadTextures);
        void goDirection(Directions d);
        void updateAniTimer();
        bool killPac();
        void handleInput();
        void stop();
        std::vector<Directions> avaliableDirections();

        int aniTimer;
        int deadAniTimer;

        bool dead;

    protected:

    private:
};
