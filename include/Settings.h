#include <SFML/Graphics.hpp>
#include <string>
#include <fstream>
#include <iostream>

class Settings
{
    public:
        Settings();
        virtual ~Settings();
        void readInSettings(std::string filename);
        void saveSettings(std::string filename);
        void textureSwitcher(sf::Texture *trackTextures, sf::Texture *YNtextures);
        void appear();
        void disappear();
        void resetHover();
        void hoverYN(int index);
        void hoverTrack(int index);

        int Track = 1;
        bool Master = false;
        bool Music = false;
        bool Effect = false;
        bool *aOptions[3];  // pointer to all the options

        int hoverOffsets[6];


        sf::Sprite tracks[3];
        sf::Sprite setYN[3];
        sf::Sprite retrn;


    protected:

    private:
        void initSprite();

};


