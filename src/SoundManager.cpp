#include "SoundManager.h"

SoundManager::SoundManager()
{
    // music
    BackG_Pizza.openFromFile("Assets/Audio/Music/Pizza_Theme.wav");

    BackG_Wii.openFromFile("Assets/Audio/Music/Wii_Menu2.wav");

    BackG_Subwooder.openFromFile("Assets/Audio/Music/SubwooferLullaby.ogg");

    BackG_Sweden.openFromFile("Assets/Audio/Music/Sweden.ogg");

    // effects
    // load
    startBuffer.loadFromFile("Assets/Audio/Effect/Mac_Startup.wav");

    teleportBuffer.loadFromFile("Assets/Audio/Effect/XP_Dots.wav");

    dotBuffer.loadFromFile("Assets/Audio/Effect/XP_Teleport.wav");

    gameOverBuffer.loadFromFile("Assets/Audio/Effect/XP_End.wav");

    clickBuffer.loadFromFile("Assets/Audio/Effect/Click_Button.wav");

    hoverBuffer.loadFromFile("Assets/Audio/Effect/Select_Button.wav");

    deadBuffer.loadFromFile("Assets/Audio/Effect/Death.wav");

    powerBuffer.loadFromFile("Assets/Audio/Effect/PowerUp.wav");

    eatBuffer.loadFromFile("Assets/Audio/Effect/XP_Yay.wav");

    berryBuffer.loadFromFile("Assets/Audio/Effect/Fortnite_Clap.wav");

    // set
    start_Game.setBuffer(startBuffer);

    teleport_Game.setBuffer(teleportBuffer);

    Dot_Chomp.setBuffer(dotBuffer);

    gameOver.setBuffer(gameOverBuffer);

    Button_click.setBuffer(clickBuffer);

    Button_select.setBuffer(hoverBuffer);

    Dead.setBuffer(deadBuffer);

    Power_Chomp.setBuffer(powerBuffer);

    Eat_Ghost.setBuffer(eatBuffer);

    Berry_Chomp.setBuffer(berryBuffer);


    BackG_Wii.setLoop(true);
    BackG_Pizza.setLoop(true);
    BackG_Subwooder.setLoop(true);
    BackG_Sweden.setLoop(true);

    BackG_Wii.setVolume(60.f);
    teleport_Game.setVolume(50.f);
    start_Game.setVolume(50.f);
    BackG_Pizza.setVolume(10.f);
    Power_Chomp.setVolume(30.f);
}

SoundManager::~SoundManager()
{
    //dtor
}
