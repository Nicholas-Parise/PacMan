#include "GameStateManager.h"

GameStateManager::GameStateManager(){

    gState = GameStates::MENU;
    GhostScared = false;
    PacDead = true;
}

GameStateManager::~GameStateManager(){
    //dtor
}


void GameStateManager::toString(GameStates s){

  switch(s){

        case GameStates::GAME:
                std::cout<<"game"<<std::endl;
            break;

        case GameStates::GAMEOVER:
    std::cout<<"game over"<<std::endl;
            break;

        case GameStates::MENU:
    std::cout<<"menu"<<std::endl;
        break;
        case GameStates::SETTINGS:
    std::cout<<"settings"<<std::endl;
    break;
        case GameStates::HELP:
    std::cout<<"help"<<std::endl;
             break;
        case GameStates::PAUSE:
                std::cout<<"pause"<<std::endl;
            break;
 };

}



void GameStateManager::changeState(GameStates s){
    gState = s;
    reset();
}

bool GameStateManager::endGame(){
    if(gState == GameStates::GAMEOVER){
        if(gameoverTimer > 80){
            std::cout<<"game over"<<std::endl;
            changeState(GameStates::MENU);
            return true;
        }
    }
    return false;
}


void GameStateManager::increment(){

    switch(gState){

        case GameStates::GAME:
             berryTimer++;
            glowTimer++;
            if(!GhostScared && powerUpTimer>600){
                ghostState++;
            }
            break;

        case GameStates::GAMEOVER:
            gameoverTimer++;
            break;

        case GameStates::MENU:
        case GameStates::SETTINGS:
        case GameStates::HELP:
             TitlePacTimer++;
             break;
        case GameStates::PAUSE:
            break;
 };

    pauseTimer++;
    powerUpTimer++;

}


 void GameStateManager::reset(){

    pauseTimer = 0;
    glowTimer = 0;
    powerUpTimer = 0;
    berryTimer = 0;
    ghostState = -1;
    gameoverTimer = 0;
    TitlePacTimer = 0;

    GhostScared = false;
 }

