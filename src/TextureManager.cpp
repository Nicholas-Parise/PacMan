#include "TextureManager.h"

TextureManager::TextureManager(){

    loadBerry();
    loadGhosts();
    loadPac();
    loadMenuElements();
}

TextureManager::~TextureManager()
{
    //dtor
}

void TextureManager::loadBerry(){

    BerrySheetimage.loadFromFile("Assets/Sprite/Berry_Sprite_Sheet.png");
    berryTextures[0].loadFromImage(BerrySheetimage, false, sf::IntRect(Bry_Cherry));
    berryTextures[1].loadFromImage(BerrySheetimage, false, sf::IntRect(Bry_Strawberry));
    berryTextures[2].loadFromImage(BerrySheetimage, false, sf::IntRect(Bry_Peach));
    berryTextures[3].loadFromImage(BerrySheetimage, false, sf::IntRect(Bry_Apple));
    berryTextures[4].loadFromImage(BerrySheetimage, false, sf::IntRect(Bry_Lime));
    berryTextures[5].loadFromImage(BerrySheetimage, false, sf::IntRect(Bry_Spear));
    berryTextures[6].loadFromImage(BerrySheetimage, false, sf::IntRect(Bry_Bell));
    berryTextures[7].loadFromImage(BerrySheetimage, false, sf::IntRect(Bry_Key));
}


void TextureManager::loadGhosts(){

    RedSheetimage.loadFromFile("Assets/Sprite/RedGhostSpriteSheet.png");
    redTextures[0].loadFromImage(RedSheetimage, false, sf::IntRect(GhostLeft1));
    redTextures[1].loadFromImage(RedSheetimage, false, sf::IntRect(GhostUp1));
    redTextures[2].loadFromImage(RedSheetimage, false, sf::IntRect(GhostRight1));
    redTextures[3].loadFromImage(RedSheetimage, false, sf::IntRect(GhostDown1));
    redTextures[4].loadFromImage(RedSheetimage, false, sf::IntRect(GhostLeft2));
    redTextures[5].loadFromImage(RedSheetimage, false, sf::IntRect(GhostUp2));
    redTextures[6].loadFromImage(RedSheetimage, false, sf::IntRect(GhostRight2));
    redTextures[7].loadFromImage(RedSheetimage, false, sf::IntRect(GhostDown2));

    //

    BlueSheetimage.loadFromFile("Assets/Sprite/BlueGhostSpriteSheet.png");
    blueTextures[0].loadFromImage(BlueSheetimage, false, sf::IntRect(GhostLeft1));
    blueTextures[1].loadFromImage(BlueSheetimage, false, sf::IntRect(GhostUp1));
    blueTextures[2].loadFromImage(BlueSheetimage, false, sf::IntRect(GhostRight1));
    blueTextures[3].loadFromImage(BlueSheetimage, false, sf::IntRect(GhostDown1));
    blueTextures[4].loadFromImage(BlueSheetimage, false, sf::IntRect(GhostLeft2));
    blueTextures[5].loadFromImage(BlueSheetimage, false, sf::IntRect(GhostUp2));
    blueTextures[6].loadFromImage(BlueSheetimage, false, sf::IntRect(GhostRight2));
    blueTextures[7].loadFromImage(BlueSheetimage, false, sf::IntRect(GhostDown2));

    //

    OrangeSheetimage.loadFromFile("Assets/Sprite/OrangeGhostSpriteSheet.png");
    orangeTextures[0].loadFromImage(OrangeSheetimage, false, sf::IntRect(GhostLeft1));
    orangeTextures[1].loadFromImage(OrangeSheetimage, false, sf::IntRect(GhostUp1));
    orangeTextures[2].loadFromImage(OrangeSheetimage, false, sf::IntRect(GhostRight1));
    orangeTextures[3].loadFromImage(OrangeSheetimage, false, sf::IntRect(GhostDown1));
    orangeTextures[4].loadFromImage(OrangeSheetimage, false, sf::IntRect(GhostLeft2));
    orangeTextures[5].loadFromImage(OrangeSheetimage, false, sf::IntRect(GhostUp2));
    orangeTextures[6].loadFromImage(OrangeSheetimage, false, sf::IntRect(GhostRight2));
    orangeTextures[7].loadFromImage(OrangeSheetimage, false, sf::IntRect(GhostDown2));

    ////////

    PinkSheetimage.loadFromFile("Assets/Sprite/PinkGhostSpriteSheet.png");
    pinkTextures[0].loadFromImage(PinkSheetimage, false, sf::IntRect(GhostLeft1));
    pinkTextures[1].loadFromImage(PinkSheetimage, false, sf::IntRect(GhostUp1));
    pinkTextures[2].loadFromImage(PinkSheetimage, false, sf::IntRect(GhostRight1));
    pinkTextures[3].loadFromImage(PinkSheetimage, false, sf::IntRect(GhostDown1));
    pinkTextures[4].loadFromImage(PinkSheetimage, false, sf::IntRect(GhostLeft2));
    pinkTextures[5].loadFromImage(PinkSheetimage, false, sf::IntRect(GhostUp2));
    pinkTextures[6].loadFromImage(PinkSheetimage, false, sf::IntRect(GhostRight2));
    pinkTextures[7].loadFromImage(PinkSheetimage, false, sf::IntRect(GhostDown2));

    //

    scaredTextures[0].loadFromFile("Assets/Sprite/ScaredGhost1.png");
    scaredTextures[1].loadFromFile("Assets/Sprite/ScaredGhost2.png");
    scaredTextures[2].loadFromFile("Assets/Sprite/ScaredGhostWhite1.png");
    scaredTextures[3].loadFromFile("Assets/Sprite/ScaredGhostWhite2.png");

    //////

    EyeSheetimage.loadFromFile("Assets/Sprite/EyeSpriteSheet.png");
    eyeTextures[0].loadFromImage(EyeSheetimage, false, sf::IntRect(GhostLeft1));
    eyeTextures[1].loadFromImage(EyeSheetimage, false, sf::IntRect(GhostUp1));
    eyeTextures[2].loadFromImage(EyeSheetimage, false, sf::IntRect(GhostRight1));
    eyeTextures[3].loadFromImage(EyeSheetimage, false, sf::IntRect(GhostDown1));
}

void TextureManager::loadPac(){

    DeadSheetimage.loadFromFile("Assets/Sprite/Pac-Death-SpriteSheet.png");
    deadTextures[0].loadFromImage(DeadSheetimage, false, sf::IntRect(Pac_wack1));
    deadTextures[1].loadFromImage(DeadSheetimage, false, sf::IntRect(Pac_wack2));
    deadTextures[2].loadFromImage(DeadSheetimage, false, sf::IntRect(Pac_wack3));
    deadTextures[3].loadFromImage(DeadSheetimage, false, sf::IntRect(Pac_wack4));
    deadTextures[4].loadFromImage(DeadSheetimage, false, sf::IntRect(Pac_wack5));
    deadTextures[5].loadFromImage(DeadSheetimage, false, sf::IntRect(Pac_wack6));
    deadTextures[6].loadFromImage(DeadSheetimage, false, sf::IntRect(Pac_wack7));
    deadTextures[7].loadFromImage(DeadSheetimage, false, sf::IntRect(Pac_wack8));
    deadTextures[8].loadFromImage(DeadSheetimage, false, sf::IntRect(Pac_wack9));
    deadTextures[9].loadFromImage(DeadSheetimage, false, sf::IntRect(Pac_wack10));
    deadTextures[10].loadFromImage(DeadSheetimage, false, sf::IntRect(Pac_wack11));

    PacTexture[0].loadFromFile("Assets/Sprite/PacMan_open.png");
    PacTexture[1].loadFromFile("Assets/Sprite/PacMan_closed.png");

}


void TextureManager::loadMenuElements(){

    YNtextures[0].loadFromFile("Assets/Buttons/Yes_1.png");
    YNtextures[1].loadFromFile("Assets/Buttons/Yes_2.png");
    YNtextures[2].loadFromFile("Assets/Buttons/No_1.png");
    YNtextures[3].loadFromFile("Assets/Buttons/No_2.png");

    trackTextures[0].loadFromFile("Assets/Buttons/1_1.png");
    trackTextures[1].loadFromFile("Assets/Buttons/1_2.png");
    trackTextures[2].loadFromFile("Assets/Buttons/2_1.png");
    trackTextures[3].loadFromFile("Assets/Buttons/2_2.png");
    trackTextures[4].loadFromFile("Assets/Buttons/3_1.png");
    trackTextures[5].loadFromFile("Assets/Buttons/3_2.png");

    settingsTextures[0].loadFromFile("Assets/Buttons/Settings_1.png");
    settingsTextures[1].loadFromFile("Assets/Buttons/Settings_2.png");

    returnTextures[0].loadFromFile("Assets/Buttons/Return_1.png");
    returnTextures[1].loadFromFile("Assets/Buttons/Return_2.png");

    helpTextures[0].loadFromFile("Assets/Buttons/Help_1.png");
    helpTextures[1].loadFromFile("Assets/Buttons/Help_2.png");
}

