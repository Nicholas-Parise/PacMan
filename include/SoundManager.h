#ifndef SOUNDMANAGER_H
#define SOUNDMANAGER_H
#include <SFML/Audio.hpp>
#include <iostream>

class SoundManager
{
    public:
        SoundManager();
        virtual ~SoundManager();

        void playMusic();
        void pauseMusic();
        void stopMusic();

        //music
        sf::Music BackG_Pizza;
        sf::Music BackG_Wii;
        sf::Music BackG_Subwooder;
        sf::Music BackG_Sweden;

        // effects

        std::optional<sf::Sound> start_Game;
        std::optional<sf::Sound> teleport_Game;
        std::optional<sf::Sound> gameOver;
        std::optional<sf::Sound> Button_click;
        std::optional<sf::Sound> Button_select;
        std::optional<sf::Sound> Dead;
        std::optional<sf::Sound> Eat_Ghost;

        std::optional<sf::Sound> Dot_Chomp;
        std::optional<sf::Sound> Power_Chomp;
        std::optional<sf::Sound> Berry_Chomp;


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

        void loadMusic();
        void loadEffects();
};

#endif // SOUNDMANAGER_H
