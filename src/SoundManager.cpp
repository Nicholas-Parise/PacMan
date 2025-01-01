#include "SoundManager.h"

SoundManager::SoundManager(){

    loadMusic();

    loadEffects();

    BackG_Wii.setLooping(true);
    BackG_Pizza.setLooping(true);
    BackG_Subwooder.setLooping(true);
    BackG_Sweden.setLooping(true);

    BackG_Wii.setVolume(60.0f);
    teleport_Game->setVolume(50.0f);
    start_Game->setVolume(50.0f);
    BackG_Pizza.setVolume(10.0f);
    Power_Chomp->setVolume(30.0f);
}

SoundManager::~SoundManager()
{
    //dtor
}

void SoundManager::loadMusic(){
    BackG_Pizza.openFromFile("Assets/Audio/Music/Pizza_Theme.wav");
    BackG_Wii.openFromFile("Assets/Audio/Music/Wii_Menu2.wav");
    BackG_Subwooder.openFromFile("Assets/Audio/Music/SubwooferLullaby.ogg");
    BackG_Sweden.openFromFile("Assets/Audio/Music/Sweden.ogg");
}


void SoundManager::loadEffects(){

 // load
    startBuffer.loadFromFile("Assets/Audio/Effect/Mac_Startup.wav");

    teleportBuffer.loadFromFile("Assets/Audio/Effect/XP_Teleport.wav");

    dotBuffer.loadFromFile("Assets/Audio/Effect/XP_Dots.wav");

    gameOverBuffer.loadFromFile("Assets/Audio/Effect/XP_End.wav");

    clickBuffer.loadFromFile("Assets/Audio/Effect/Click_Button.wav");

    hoverBuffer.loadFromFile("Assets/Audio/Effect/Select_Button.wav");

    deadBuffer.loadFromFile("Assets/Audio/Effect/Death.wav");

    powerBuffer.loadFromFile("Assets/Audio/Effect/PowerUp.wav");

    eatBuffer.loadFromFile("Assets/Audio/Effect/XP_Yay.wav");

    berryBuffer.loadFromFile("Assets/Audio/Effect/Fortnite_Clap.wav");

    // set
    start_Game.emplace(startBuffer);

    teleport_Game.emplace(teleportBuffer);

    Dot_Chomp.emplace(dotBuffer);

    gameOver.emplace(gameOverBuffer);

    Button_click.emplace(clickBuffer);

    Button_select.emplace(hoverBuffer);

    Dead.emplace(deadBuffer);

    Power_Chomp.emplace(powerBuffer);

    Eat_Ghost.emplace(eatBuffer);

    Berry_Chomp.emplace(berryBuffer);


}
