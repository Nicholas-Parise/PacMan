#ifndef TEXTUREMANAGER_H
#define TEXTUREMANAGER_H
#pragma once
#include "configuration.h"
#include <SFML/Graphics.hpp>

class TextureManager
{
    public:
        TextureManager();
        virtual ~TextureManager();

        sf::Texture berryTextures[8];

        sf::Texture redTextures[8];
        sf::Texture blueTextures[8];
        sf::Texture orangeTextures[8];
        sf::Texture pinkTextures[8];
        sf::Texture scaredTextures[4];
        sf::Texture eyeTextures[4];

        sf::Texture deadTextures[11];
        sf::Texture PacTexture[2];

        sf::Texture YNtextures[4];
        sf::Texture trackTextures[6];
        sf::Texture settingsTextures[2];
        sf::Texture returnTextures[2];
        sf::Texture helpTextures[2];

    protected:
        void loadGhosts();
        void loadBerry();
        void loadPac();
        void loadMenuElements();


    private:
        sf::Image RedSheetimage;
        sf::Image BlueSheetimage;
        sf::Image OrangeSheetimage;
        sf::Image PinkSheetimage;
        sf::Image EyeSheetimage;

        sf::Image DeadSheetimage;

        sf::Image BerrySheetimage;

};

#endif // TEXTUREMANAGER_H
