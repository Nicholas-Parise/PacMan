#ifndef SOUNDMANAGER_H
#define SOUNDMANAGER_H
#include <SFML/Audio.hpp>

class SoundManager
{
    public:
        SoundManager();
        virtual ~SoundManager();

        //music
        sf::Music BackG_Pizza;
        sf::Music BackG_Wii;
        sf::Music BackG_Subwooder;
        sf::Music BackG_Sweden;

        // effects
        sf::Sound start_Game;
        sf::Sound teleport_Game;
        sf::Sound gameOver;
        sf::Sound Button_click;
        sf::Sound Button_select;
        sf::Sound Dead;
        sf::Sound Eat_Ghost;

        sf::Sound Dot_Chomp;
        sf::Sound Power_Chomp;
        sf::Sound Berry_Chomp;


    protected:

    private:
        // effect buffers
        sf::SoundBuffer startBuffer;
        sf::SoundBuffer teleportBuffer;
        sf::SoundBuffer deadBuffer;
        sf::SoundBuffer gameOverBuffer;

        sf::SoundBuffer eatBuffer;
        sf::SoundBuffer powerBuffer;
        sf::SoundBuffer dotBuffer;
        sf::SoundBuffer berryBuffer;

        sf::SoundBuffer clickBuffer;
        sf::SoundBuffer hoverBuffer;
};

#endif // SOUNDMANAGER_H
