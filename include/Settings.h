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
        void textureSwitcher(sf::Texture *trackTextures, sf::Texture *YNtextures, sf::Texture *settingsTextures, sf::Texture *returnTextures, sf::Texture *helpTextures);
        void resetHover();
        void hoverYN(int index);
        void hoverTrack(int index);
        void hoverReturn();
        void hoverSettings();
        void hoverHelp();

        int Track = 1;
        bool Master = false;
        bool Music = false;
        bool Effect = false;
        bool *aOptions[3];  // pointer to all the options

        int hoverOffsets[6];
        int settingOffset;
        int returnOffset;
        int helpOffset;

        sf::Sprite tracks[3];
        sf::Sprite setYN[3];

        sf::Sprite settingBTN;
        sf::Sprite returnBTN;
        sf::Sprite helpBTN;

    protected:

    private:
        void initSprite();

};


