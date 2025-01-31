#include <SFML/Graphics.hpp>
#include <string>
#include <fstream>
#include <iostream>
#include "configuration.h"

class Settings
{
    public:
        Settings(sf::Texture *trackTextures, sf::Texture *YNtextures, sf::Texture *settingsTextures, sf::Texture *returnTextures, sf::Texture *helpTextures);
        virtual ~Settings();
        void readInSettings(std::string filename);
        void saveSettings(std::string filename);
        void textureSwitcher();
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

        std::optional<sf::Sprite> tracks[3];
        std::optional<sf::Sprite> setYN[3];

        std::optional<sf::Sprite> settingBTN;
        std::optional<sf::Sprite> returnBTN;
        std::optional<sf::Sprite> helpBTN;

    protected:

    private:
        void initSprite();
        const std::string Settings_Text = "Master Audio: \n\n\n Music: \n\n\n Sound Effects: \n\n\n Music Track:";
        sf::Texture *trackTextures;
        sf::Texture *YNtextures;
        sf::Texture *settingsTextures;
        sf::Texture *returnTextures;
        sf::Texture *helpTextures;

};


