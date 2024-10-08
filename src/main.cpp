#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <cstring>
#include <fstream>
#include <cmath>
#include <vector>
#include <algorithm>
#include <sstream>
#include <queue>

#include <thread>
#include <chrono>

#include "ghost.h"
#include "Player.h"
#include "Settings.h"
#include "GameStateManager.h"
#include "Node.h"
#include "configuration.h"
#include "Pathing.h"
#include "Pellet.h"
#include "SoundManager.h"
#include "TextureManager.h"

using namespace std;


// Note to self use Delta Time for movement don't use set frame limit

//https://www.codesdope.com/blog/article/backtracking-to-solve-a-rat-in-a-maze-c-java-pytho/
//https://www.youtube.com/watch?v=ataGotQ7ir8



sf::View getLetterboxView(sf::View view, int windowWidth, int windowHeight)
{

    // Compares the aspect ratio of the window to the aspect ratio of the view,
    // and sets the view's viewport accordingly in order to archieve a letterbox effect.
    // A new view (with a new viewport set) is returned.

    float windowRatio = windowWidth / (float) windowHeight;
    float viewRatio = view.getSize().x / (float) view.getSize().y;
    float sizeX = 1;
    float sizeY = 1;
    float posX = 0;
    float posY = 0;

    bool horizontalSpacing = true;
    if (windowRatio < viewRatio)
        horizontalSpacing = false;

    // If horizontalSpacing is true, the black bars will appear on the left and right side.
    // Otherwise, the black bars will appear on the top and bottom.

    if (horizontalSpacing)
    {
        sizeX = viewRatio / windowRatio;
        posX = (1 - sizeX) / 2.f;
    }

    else
    {
        sizeY = windowRatio / viewRatio;
        posY = (1 - sizeY) / 2.f;
    }

    view.setViewport( sf::FloatRect(posX, posY, sizeX, sizeY) );

    return view;
}


bool isSpriteHover(sf::FloatRect Button, sf::Vector2f mp)
{

    if (Button.contains(mp))
    {
        return true;
    }

    return false;
}


vector<int> ClossestTile(float PositionX, float PositionY, std::vector<sf::RectangleShape> Tiles)
{

    int FinalPlace = -1;
    int row = 1;
    int col = 1;

    for(int i = 0; i<28*31; i++)
    {

        if ((Tiles[i].getGlobalBounds()).contains(sf::Vector2f(PositionX, PositionY)))
        {

            FinalPlace = i;
            break;
        }
    }
    if(FinalPlace != -1)
    {
        col = FinalPlace/28;
        row = FinalPlace%28;
    }

    vector<int> RowColArray = {row,col};

    return RowColArray;
}

vector<Directions> WallTest(int Row, int Col, Directions currentDur, bool &Stop)
{

    std::vector<Directions> AvallibleDir;

    //1 is a wall

    if(Col >0)
    {
        //Above
        if(conf::GameMatrix[Col-1][Row] == 1)
        {

            if(currentDur == UP)
            {
                Stop = true;
            }
        }
        else
        {
            AvallibleDir.push_back(UP);
        }
    }

    //below
    if(conf::GameMatrix[Col+1][Row] == 1)
    {

        if(currentDur == DOWN)
        {
            Stop = true;
        }
    }
    else
    {
        AvallibleDir.push_back(DOWN);
    }


    //Left
    if(conf::GameMatrix[Col][Row-1] == 1)
    {

        if(currentDur == LEFT)
        {
            Stop = true;
        }
    }
    else
    {
        AvallibleDir.push_back(LEFT);
    }


    //Right
    if(conf::GameMatrix[Col][Row+1] == 1)
    {

        if(currentDur == RIGHT)
        {
            Stop = true;
        }
    }
    else
    {
        AvallibleDir.push_back(RIGHT);
    }


    //cout<<"Available dir: "<<AvallibleDir.size()<<endl;

    return AvallibleDir;

}


bool CenterOfTile(int Row, int Col, string currentDur, sf::Sprite GameSprite, bool Stop)
{

    bool inCenter = false;

    bool HorizCenter = false;
    bool VertCenter = false;

    float SpriteX = GameSprite.getPosition().x;
    float SpriteY = GameSprite.getPosition().y;

    float TileX = 18.78571429*Row;
    float TileY = 18.61290323*Col;
    float TileXCenter = (18.78571429*Row)+(18.78571429/2);
    float TileYCenter =(18.61290323*Col)+(18.61290323/2);


    if((SpriteX > (TileXCenter-5)) && (SpriteX < (TileXCenter+5)))
    {

        HorizCenter = true;

        // cout<<"a"<<endl;
    }

    //Note to self change -10 // +10 to something smaller than 8

    if((SpriteY > (TileYCenter-5)) && (SpriteY < (TileYCenter+5)))
    {

        VertCenter = true;
        //    cout<<"b"<<endl;
    }


    if((currentDur == "Left" || currentDur == "Right") && VertCenter == true)
    {
        inCenter = true;
    }



    if((currentDur == "Up" || currentDur == "Down") && HorizCenter == true)
    {
        inCenter = true;
    }


    if(VertCenter && HorizCenter == true)
    {
        inCenter = true;
    }


    return inCenter;
}



void scoreUpdate(sf::Text &HsDis, sf::Text &scoreDis, int score, int highscore, string &scoreShow, string &HSString)
{
    stringstream ss;
    ss<<score;
    ss>>scoreShow;

    scoreDis.setString("Score: "+scoreShow);

    stringstream ss2;
    ss2<<highscore;
    ss2>>HSString;

    HsDis.setString("HS: "+HSString);
}


void SaveHS(int &highscore, int score, sf::Text &NewHS)
{
    ifstream readFile;
    readFile.open("Assets/Other/High_Score.txt");

    if(readFile.is_open())
    {
        readFile >> highscore;
    }
    readFile.close();

    ofstream writeFile("Assets/Other/High_Score.txt");
    if(writeFile.is_open())
    {

        if(score>highscore)
        {
            highscore = score;
            NewHS.setPosition(522/2, 400);
        }

        writeFile<< highscore;

    }
    writeFile.close();
}




void PlaceLives(std::vector<sf::Sprite> &PacLife)
{
    for(int i = 0; i<PacLife.size(); i++)
    {
        PacLife[i].setOrigin(15,15);
        PacLife[i].setPosition(400 + i*50,600);
    }
}

int main()
{

    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;
    sf::RenderWindow window(sf::VideoMode(522, 620), "PacMan", sf::Style::Default,settings);
    window.setFramerateLimit(60);
    sf::View view(sf::FloatRect(0.f, 0.f, window.getSize().x, window.getSize().y));

    sf::Font font;
    font.loadFromFile("Assets/Other/Arial.ttf");


    sf::Text GameDone("Loading...", font);
    GameDone.setCharacterSize(30);
    GameDone.setStyle(sf::Text::Bold);
    GameDone.setFillColor(sf::Color::Red);
    GameDone.setPosition(182, 387);

    window.draw(GameDone);
    window.display();

    srand (time(NULL));


    Player pacman;
    int PacLives = 3;
    bool stopPacMan;


    Ghost rGhost;
    rGhost.setScatter(23,1);

    Ghost bGhost;
    bGhost.setScatter(24,29);

    Ghost oGhost;
    oGhost.setScatter(3,29);
    int OrangePacDistance;

    Ghost pGhost;
    pGhost.setScatter(2,1);


    Settings setting;

    GameStateManager gsManager;

    Pathing pathing;

    Pellet pellet;

    SoundManager soundManager;

    TextureManager textureManager;

    Ghost *ghosts[4];
    ghosts[0] = &rGhost;
    ghosts[1] = &bGhost;
    ghosts[2] = &oGhost;
    ghosts[3] = &pGhost;

    int solutionRow = 14;
    int solutionCol = 17;

    int score = 0;
    int highscore = 0;

    int Level = 0;
    bool freeLife = true;

    int place = 0;

    int feetTimer = 0;


    const string Help_Text = "\t\t\t\t\t\t\t\t HELP \n \n \nMove is Arrow keys \nIf you eat all the dots on the board more will spawn. \nIf a ghost hits you and is not Blue, YOU. WILL. DIE! \nTo make a ghost blue you must eat a power pellet,\nthere are 4 accros the map.\nYou Have 3 lives,\nif you beat the High score You get a free life.\n\n\t\tBy. Nicholas Parise";
    const string Settings_Text = "Master Audio: \n\n\n Music: \n\n\n Sound Effects: \n\n\n\n Music Track:";
    string scoreShow;
    string HSString;

    vector <int> TempRowCol;


    std::vector<Directions> PacManAvallibleDir = {LEFT,RIGHT};


    std::vector<sf::RectangleShape> Tiles(868);

    for(int i = 0; i<31; i++)
    {
        for(int j = 0; j<28; j++)
        {

            Tiles[place].setOrigin(0,0);
            Tiles[place].setSize(sf::Vector2f(18.78571429, 18.61290323));
            Tiles[place].setPosition(sf::Vector2f(18.78571429*j,18.61290323*i));

            if(conf::GameMatrix[i][j] == 0)
            {
                Tiles[place].setFillColor(sf::Color(0,255,255,128));
                Tiles[place].setFillColor(sf::Color(0,255,255,0));
            }

            if(conf::GameMatrix[i][j] == 8)
            {
                Tiles[place].setFillColor(sf::Color(0,255,255,128));
                Tiles[place].setFillColor(sf::Color(0,255,255,0));
            }

            if(conf::GameMatrix[i][j] == 1)
            {
                Tiles[place].setFillColor(sf::Color(255,0,255,100));
                // Tiles[place].setFillColor(sf::Color(255,0,255,0));
            }

            if(conf::GameMatrix[i][j] == 6)
            {
                Tiles[place].setFillColor(sf::Color(255,255,0,0));
            }
            place++;
        }
    }

    sf::Image image;
    image.loadFromFile("Assets/Sprite/PacMan_background.png");

    sf::Texture MapTexture;
    MapTexture.loadFromImage(image);

    sf::Sprite Background;
    Background.setTexture(MapTexture);
    Background.setPosition(sf::Vector2f(0, 0));

    sf::Texture PauseTexture;
    PauseTexture.loadFromFile("Assets/Sprite/pause.png");

    sf::Texture texture9;
    texture9.loadFromFile("Assets/Other/PacMan-Start.png");

    // -----

    sf::Sprite Paused;
    Paused.setTexture(PauseTexture);
    Paused.setPosition(sf::Vector2f(0, 0));
    Paused.setOrigin(25,31);
    Paused.setScale(1.f,1.f);
    Paused.setPosition(261,288);


    sf::Sprite TitlePacMan;
    TitlePacMan.setTexture(textureManager.PacTexture[0]);
    TitlePacMan.setOrigin(15,15);
    TitlePacMan.setRotation(-90);


    sf::Sprite StartImage;
    StartImage.setTexture(texture9);
    StartImage.setPosition(sf::Vector2f(266, 150));
    StartImage.setOrigin(225,51);


    std::vector<sf::Sprite> PacLife(3, sf::Sprite(textureManager.PacTexture[0]));
    PlaceLives(PacLife);


    //----------------Text----------------

    sf::Text NewHS("NEW HIGHSCORE!!", font);
    NewHS.setCharacterSize(30);
    NewHS.setStyle(sf::Text::Bold);
    NewHS.setFillColor(sf::Color::Red);
    NewHS.setOrigin(150,15);
    NewHS.setPosition(1000, 1000);


    sf::Text scoreDis("0", font);
    scoreDis.setCharacterSize(30);
    scoreDis.setStyle(sf::Text::Bold);
    scoreDis.setFillColor(sf::Color::White);
    scoreDis.setOrigin(15,15);
    scoreDis.setPosition(30,590);

    sf::Text HsDis("0", font);
    HsDis.setCharacterSize(30);
    HsDis.setStyle(sf::Text::Bold);
    HsDis.setFillColor(sf::Color::White);
    HsDis.setOrigin(15,15);
    HsDis.setPosition(250, 590);

    sf::Text PreStart("Push Space To Start", font);
    PreStart.setCharacterSize(30);
    PreStart.setStyle(sf::Text::Bold);
    PreStart.setFillColor(sf::Color::White);
    PreStart.setOrigin(142,15);
    PreStart.setPosition(522/2, 620/2);


    GameDone.setOrigin(95,15);
    GameDone.setPosition(522/2, 322);
    GameDone.setString("GAME OVER");



    sf::Text Help_text_sprite(Help_Text, font);
    Help_text_sprite.setCharacterSize(20);
    Help_text_sprite.setStyle(sf::Text::Bold);
    Help_text_sprite.setFillColor(sf::Color::White);
    Help_text_sprite.setPosition(0, 100);


    sf::Text Settings_text_sprite(Settings_Text, font);
    Settings_text_sprite.setCharacterSize(30);
    Settings_text_sprite.setStyle(sf::Text::Bold);
    Settings_text_sprite.setFillColor(sf::Color::White);
    Settings_text_sprite.setPosition(100, 10);


    sf::Vector2i pixelPos;
    sf::Vector2f worldPos;

    // done loading, play music
    if(setting.Music)
    {
        soundManager.BackG_Wii.play();
    }

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {

                SaveHS(highscore,score,NewHS);
                window.close();

                return 0;
            }

            if (event.type == sf::Event::Resized)
            {
                view = getLetterboxView( view, event.size.width, event.size.height );
            }

            pixelPos = sf::Mouse::getPosition(window);
            worldPos = window.mapPixelToCoords(pixelPos);

            if(event.type == sf::Event::MouseButtonReleased &&  event.mouseButton.button == sf::Mouse::Left)
            {
                //  cout<<worldPos.x<<" "<<worldPos.y<<endl;
                TempRowCol = ClossestTile(worldPos.x,worldPos.y, Tiles);
                //  cout<<endl;
                //  cout<<TempRowCol[0]<<" "<<TempRowCol[1]<<endl;
                //  return 0;
            }


            TitlePacMan.setPosition(worldPos.x,worldPos.y);

            ///////

            setting.resetHover();


            if(isSpriteHover(setting.settingBTN.getGlobalBounds(), sf::Vector2f(worldPos.x, worldPos.y)) && gsManager.gState == GameStates::MENU)
            {

                setting.hoverSettings();

                if(setting.Effect)
                {
                    soundManager.Button_select.play();
                }


                if(event.type == sf::Event::MouseButtonReleased &&  event.mouseButton.button == sf::Mouse::Left)
                {

                    gsManager.changeState(GameStates::SETTINGS);

                    if(setting.Effect)
                    {
                        soundManager.Button_click.play();
                    }
                }
            }


            if(isSpriteHover(setting.returnBTN.getGlobalBounds(), sf::Vector2f(worldPos.x, worldPos.y)) && (gsManager.gState == GameStates::SETTINGS || gsManager.gState == GameStates::HELP))
            {

                setting.hoverReturn();

                if(setting.Effect)
                {
                    soundManager.Button_select.play();
                }

                if(event.type == sf::Event::MouseButtonReleased &&  event.mouseButton.button == sf::Mouse::Left)
                {

                    gsManager.changeState(GameStates::MENU);

                    if(setting.Effect)
                    {
                        soundManager.Button_click.play();
                    }

                    setting.saveSettings("Assets/Other/Settings.txt");
                }
            }


            if(isSpriteHover(setting.helpBTN.getGlobalBounds(), sf::Vector2f(worldPos.x, worldPos.y)) && gsManager.gState == GameStates::MENU){

                 setting.hoverHelp();

                if(setting.Effect)
                {
                    soundManager.Button_select.play();
                }

                if(event.type == sf::Event::MouseButtonReleased &&  event.mouseButton.button == sf::Mouse::Left)
                {

                    gsManager.changeState(GameStates::HELP);

                    if(setting.Effect)
                    {
                        soundManager.Button_click.play();
                    }
                }
            }

            // ---------------



            for(int i = 0; i<3; i++)
            {

                if(isSpriteHover(setting.setYN[i].getGlobalBounds(), sf::Vector2f(worldPos.x, worldPos.y)))
                {

                    setting.hoverYN(i);

                    if(setting.Effect)
                    {
                        soundManager.Button_select.play();
                    }

                    if(event.type == sf::Event::MouseButtonReleased &&  event.mouseButton.button == sf::Mouse::Left)
                    {

                        if(setting.Effect)
                        {
                            soundManager.Button_click.play();
                        }

                        if(*setting.aOptions[i])
                        {
                            *setting.aOptions[i] = false;
                            if(i == 0)
                            {
                                *setting.aOptions[1] = false;
                                *setting.aOptions[2] = false;
                                soundManager.BackG_Wii.stop();
                            }
                        }
                        else
                        {
                            if(i == 0 || i > 0 && *setting.aOptions[0])
                            {
                                *setting.aOptions[i] = true;
                            }
                        }
                    }
                }

                //

                if(isSpriteHover(setting.tracks[i].getGlobalBounds(), sf::Vector2f(worldPos.x, worldPos.y)))
                {

                    setting.hoverTrack(i);

                    if(setting.Effect)
                    {
                        soundManager.Button_select.play();
                    }

                    if(event.type == sf::Event::MouseButtonReleased &&  event.mouseButton.button == sf::Mouse::Left)
                    {

                        if(setting.Effect)
                        {
                            soundManager.Button_click.play();
                        }

                        setting.Track = i+1;
                    }
                }
            }

            setting.textureSwitcher(textureManager.trackTextures, textureManager.YNtextures,textureManager.settingsTextures, textureManager.returnTextures, textureManager.helpTextures);
        }



        //////Path Finding


        TempRowCol = ClossestTile(pacman.sprite.getPosition().x,pacman.sprite.getPosition().y, Tiles);
        pacman.row = TempRowCol[0];
        pacman.col = TempRowCol[1];

        TempRowCol = ClossestTile(rGhost.sprite.getPosition().x,rGhost.sprite.getPosition().y, Tiles);
        rGhost.row = TempRowCol[0];
        rGhost.col = TempRowCol[1];

        TempRowCol = ClossestTile(oGhost.sprite.getPosition().x,oGhost.sprite.getPosition().y, Tiles);
        oGhost.row = TempRowCol[0];
        oGhost.col = TempRowCol[1];

        TempRowCol = ClossestTile(bGhost.sprite.getPosition().x,bGhost.sprite.getPosition().y, Tiles);
        bGhost.row = TempRowCol[0];
        bGhost.col = TempRowCol[1];

        TempRowCol = ClossestTile(pGhost.sprite.getPosition().x,pGhost.sprite.getPosition().y, Tiles);
        pGhost.row = TempRowCol[0];
        pGhost.col = TempRowCol[1];


        // update all ghosts pathing
        for(int i = 0; i<4; i++)
        {

            // red
            solutionRow = pacman.row;
            solutionCol = pacman.col;

            switch(i)
            {
                case 1:
                {
                    // blue
                    if(pacman.direction == UP)
                    {
                        solutionCol-=2;
                    }
                    if(pacman.direction == DOWN)
                    {
                        solutionCol+=2;
                    }
                    if(pacman.direction == LEFT)
                    {
                        solutionRow-=2;
                    }
                    if(pacman.direction == RIGHT)
                    {
                        solutionRow+=2;
                    }


                    ///TODO proper destination needed

                    int tempSolutionRow = solutionRow - rGhost.row;
                    int tempSolutionCol = solutionCol - rGhost.col;

                    solutionRow = solutionRow + (tempSolutionRow*-1);
                    solutionCol = solutionCol + (tempSolutionCol*-1);
                    break;
                }
                case 2:
                {
                    //orange
                    OrangePacDistance = pow(pacman.row-oGhost.row,2) + pow(pacman.col-oGhost.col,2);
                    if(OrangePacDistance<80)
                    {
                        solutionRow =  oGhost.scatterRow;
                        solutionCol = oGhost.scatterCol;
                    } // else pacman
                    break;
                }
                case 3:
                    //pink
                {
                    if(pacman.direction == UP)
                    {
                        solutionCol-=4;
                    }
                    if(pacman.direction == DOWN)
                    {
                        solutionCol+=4;
                    }
                    if(pacman.direction == LEFT)
                    {
                        solutionRow-=4;
                    }
                    if(pacman.direction == RIGHT)
                    {
                        solutionRow+=4;
                    }
                }
            }

            if(pacman.changedPosition()|| ghosts[i]->changedPosition())
            {
                ghosts[i]->updateOldRC();

                Node start(ghosts[i]->col,ghosts[i]->row,ghosts[i]->direction);

                switch(ghosts[i]->state)
                {

                case CHASE:
                {
                    Node finish(solutionCol,solutionRow);
                    ghosts[i]->path = pathing.shortestPath(start,finish);
                }
                break;
                case SCATTER:
                {
                    Node finish(ghosts[i]->scatterCol,ghosts[i]->scatterRow);
                    ghosts[i]->path = pathing.shortestPath(start,finish);
                }
                break;
                case SCARED:
                {
                    ghosts[i]->path = pathing.scaredSolver(start);
                }
                break;
                case DEAD:
                {
                    Node finish(conf::GhostHomeCol+3,conf::GhostHomeRow);
                    ghosts[i]->path = pathing.shortestPath(start,finish);
                }
                break;
                }
            }
        }

        pacman.updateOldRC();




        //////////////



        PacManAvallibleDir = WallTest(pacman.row, pacman.col, pacman.direction, stopPacMan);



        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
        {

            if(gsManager.gState != GameStates::PAUSE && gsManager.gState != GameStates::MENU && gsManager.pauseTimer >10)
            {

                gsManager.pauseTimer = 10;
                gsManager.changeState(GameStates::PAUSE);

                soundManager.BackG_Pizza.pause();
                soundManager.BackG_Subwooder.pause();
                soundManager.BackG_Sweden.pause();
            }

            else if(gsManager.gState == GameStates::PAUSE && gsManager.pauseTimer > 30)
            {

                gsManager.changeState(GameStates::GAME);
                gsManager.pauseTimer = 0;

                if(setting.Music)
                {
                    switch(setting.Track)
                    {
                    case 1:
                        soundManager.BackG_Pizza.play();
                        break;
                    case 2:
                        soundManager.BackG_Subwooder.play();
                        break;
                    case 3:
                        soundManager.BackG_Sweden.play();
                        break;
                    }
                }
            }
        }


        if(!pacman.dead)
        {
            for(int i = 0; i<PacManAvallibleDir.size(); i++)
            {

                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && PacManAvallibleDir[i] == LEFT)
                {

                    pacman.goDirection(LEFT);

                }
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)&& PacManAvallibleDir[i] == RIGHT)
                {

                    pacman.goDirection(RIGHT);
                }

                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)&& PacManAvallibleDir[i] == UP)
                {

                    pacman.goDirection(UP);

                }
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)&& PacManAvallibleDir[i] == DOWN)
                {

                    pacman.goDirection(DOWN);
                }
            }
        }


        if((pacman.teleporter() | rGhost.teleporter() | oGhost.teleporter() | bGhost.teleporter() | pGhost.teleporter())&& setting.Effect)
        {
            soundManager.teleport_Game.play();
        }


        if(stopPacMan)
        {
            stopPacMan = false;
            pacman.setSpeed(0,0);
        }


        // update all ghosts
        for(int i = 0; i<4; i++)
        {
            ghosts[i]->outOfSpawn();
            ghosts[i]->followPath();
            ghosts[i]->scaredStop(gsManager.powerUpTimer);
        }


        // --Dot Hit Test--
        if(pellet.dotHit(pacman.sprite))
        {
            score +=5;
            if(setting.Effect)
            {
                soundManager.Dot_Chomp.play();
            }
        }

        // --Powerup Hit Test--
        if(pellet.powerHit(pacman.sprite))
        {

            pellet.PowerUpEaten ++;

            if(setting.Effect)
            {
                soundManager.Power_Chomp.play();
            }

            gsManager.GhostScared = true;
            gsManager.powerUpTimer = 0;

            score +=25;

            rGhost.changeState(SCARED);
            oGhost.changeState(SCARED);
            bGhost.changeState(SCARED);
            pGhost.changeState(SCARED);
        }

        // -- Berry Hite Test --
        if(pellet.berryHit(pacman.sprite))
        {
            score +=10;
            if(setting.Effect)
            {
                soundManager.Berry_Chomp.play();
            }
        }


        if(rGhost.state != SCARED || oGhost.state != SCARED || pGhost.state != SCARED || bGhost.state != SCARED)
        {
            gsManager.GhostScared = false;
        }


        // ghost pacman hittest
        if(!pacman.dead && conf::DEBUG == false)
        {

            for(int i = 0; i<4; i++)
            {

                if(pacman.sprite.getGlobalBounds().intersects((ghosts[i])->sprite.getGlobalBounds()))
                {

                    if(ghosts[i]->state == SCARED)
                    {
                        score +=10;

                        if(setting.Effect)
                        {
                            soundManager.Eat_Ghost.play();
                        }

                        ghosts[i]->changeState(DEAD);


                    }
                    else if(ghosts[i]->state != DEAD)
                    {

                        soundManager.BackG_Pizza.pause();
                        soundManager.BackG_Subwooder.pause();
                        soundManager.BackG_Sweden.pause();

                        if(setting.Effect)
                        {
                            soundManager.Dead.play();
                        }

                        pacman.dead = true;
                    }
                }
            }
        }


        if(gsManager.ghostState  == 60*5 ||  gsManager.ghostState  == 60*30||  gsManager.ghostState  == 60*55||  gsManager.ghostState  == 60*80)
        {
            cout<<"Chase"<<endl;

            rGhost.changeState(CHASE);
            oGhost.changeState(CHASE);
            bGhost.changeState(CHASE);
            pGhost.changeState(CHASE);

        }
        else if(gsManager.ghostState == 60*25||  gsManager.ghostState  == 60*50||  gsManager.ghostState  == 60*75)
        {
            cout<<"Scatter"<<endl;

            rGhost.changeState(SCATTER);
            oGhost.changeState(SCATTER);
            bGhost.changeState(SCATTER);
            pGhost.changeState(SCATTER);
        }



        if(freeLife && score>highscore)
        {
            freeLife = false;
            PacLives++;
        }



        /// ------ start game -------
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && gsManager.gState == GameStates::MENU)
        {

            cout<<"play"<<endl;

            gsManager.changeState(GameStates::GAME);
            gsManager.reset();

            freeLife = true;
            PacLives = 3;
            Level = 0;

            score = 0;

            pacman.reset();

            rGhost.reset();
            oGhost.reset();
            pGhost.reset();
            bGhost.reset();

            PlaceLives(PacLife);

            pellet.reset();

            soundManager.BackG_Wii.stop();
            if(setting.Effect)
            {
                soundManager.Button_click.play();
                soundManager.start_Game.play();
            }

            if(setting.Music)
            {
                switch(setting.Track)
                {
                case 1:
                    soundManager.BackG_Pizza.play();
                    break;
                case 2:
                    soundManager.BackG_Subwooder.play();
                    break;
                case 3:
                    soundManager.BackG_Sweden.play();
                    break;
                }
            }
        }

        /// ------ go to next level -------
        if(pellet.dotsEaten >= pellet.DOTS && pellet.PowerUpEaten >= pellet.POWERUPS)
        {

            if(setting.Effect)
            {
                soundManager.start_Game.play();
            }

            Level++;

            gsManager.berryTimer = 0;
            gsManager.ghostState = -1;

            pacman.reset();

            rGhost.reset();
            oGhost.reset();
            pGhost.reset();
            bGhost.reset();

            pellet.reset();
        }

        /// ------ pac man dead ------
        if(pacman.killPac() && conf::DEBUG == false)
        {

            cout<<"reset"<<endl;

            pacman.dead = false;

            PacLives --;
            PacLife[PacLives].setPosition(1000,1000);

            gsManager.reset();

            pacman.reset();

            rGhost.reset();
            oGhost.reset();
            pGhost.reset();
            bGhost.reset();

            if(setting.Music)
            {
                switch(setting.Track)
                {
                case 1:
                    soundManager.BackG_Pizza.play();
                    break;
                case 2:
                    soundManager.BackG_Subwooder.play();
                    break;
                case 3:
                    soundManager.BackG_Sweden.play();
                    break;
                }
            }
        }

        /// ------ Game Over ------
        if(PacLives == 0 && gsManager.gState == GameStates::GAME && conf::DEBUG == false)
        {

            PacLives--;

            if(setting.Effect)
            {
                soundManager.gameOver.play();
            }

            SaveHS(highscore,score,NewHS);

            soundManager.BackG_Pizza.stop();
            soundManager.BackG_Subwooder.stop();
            soundManager.BackG_Sweden.stop();

            gsManager.changeState(GameStates::GAMEOVER);
        }
        /// ------

        scoreUpdate(HsDis, scoreDis, score, highscore, scoreShow, HSString);

        pellet.animate(gsManager.glowTimer);

        pellet.spawnBerry(textureManager.berryTextures,gsManager.berryTimer);


        if(gsManager.TitlePacTimer < 10)
        {
            TitlePacMan.setTexture(textureManager.PacTexture[1]);
        }
        else
        {
            TitlePacMan.setTexture(textureManager.PacTexture[0]);
            gsManager.TitlePacTimer = 0;
        }


        if(gsManager.endGame() && setting.Music)
        {
            soundManager.BackG_Wii.play();
        }


        // set the textures of the ghosts
        if(feetTimer >= 20)
        {
            feetTimer = 0;
        }
        else
        {
            feetTimer+=2;
        }

        pacman.updateAniTimer();

        pacman.textureSwitcher(textureManager.PacTexture, textureManager.deadTextures);

        rGhost.textureSwitcher(textureManager.redTextures, textureManager.scaredTextures, textureManager.eyeTextures, feetTimer, gsManager.powerUpTimer);

        oGhost.textureSwitcher(textureManager.orangeTextures, textureManager.scaredTextures, textureManager.eyeTextures, feetTimer, gsManager.powerUpTimer);

        pGhost.textureSwitcher(textureManager.pinkTextures, textureManager.scaredTextures, textureManager.eyeTextures, feetTimer, gsManager.powerUpTimer);

        bGhost.textureSwitcher(textureManager.blueTextures, textureManager.scaredTextures, textureManager.eyeTextures, feetTimer, gsManager.powerUpTimer);

        gsManager.increment();

        if(gsManager.gState == GameStates::GAME && !pacman.dead)
        {

            pacman.sprite.move(pacman.xSpeed,pacman.ySpeed);
            rGhost.sprite.move(rGhost.xSpeed, rGhost.ySpeed);
            oGhost.sprite.move(oGhost.xSpeed, oGhost.ySpeed);
            bGhost.sprite.move(bGhost.xSpeed, bGhost.ySpeed);
            pGhost.sprite.move(pGhost.xSpeed, pGhost.ySpeed);
        }

        /// ---- debug graphics ----


         if(conf::DEBUG == true){

            place = 0;
            for(int i = 0; i<31; i++)
            {
                for(int j = 0; j<28; j++)
                {

                    if(conf::GameMatrix[i][j] == 0)
                    {
                        Tiles[place].setFillColor(sf::Color(0,255,255,128));
                    }
                    if(conf::GameMatrix[i][j] == 8)
                    {
                        Tiles[place].setFillColor(sf::Color(0,255,255,128));
                    }
                    if(conf::GameMatrix[i][j] == 6)
                    {
                        Tiles[place].setFillColor(sf::Color(255,255,0,128));
                    }
                    if(j == conf::GhostHomeRow && i == conf::GhostHomeCol)
                    {
                        Tiles[place].setFillColor(sf::Color(255,0,255,128));
                    }

                    if(j == conf::GhostHomeRow && i == conf::GhostHomeCol+3)
                    {
                        Tiles[place].setFillColor(sf::Color(255,50,255,128));
                    }

                    place++;
                }
            }


            for(int i = 0; i< pGhost.path.size(); i++)
            {
                Tiles[pGhost.path[i].row*28+pGhost.path[i].col].setFillColor(sf::Color(255,105,180,128));
            }

            for(int i = 0; i< oGhost.path.size(); i++)
            {
                Tiles[oGhost.path[i].row*28+oGhost.path[i].col].setFillColor(sf::Color(255,140,0,128));
            }


            for(int i = 0; i< bGhost.path.size(); i++)
            {
                Tiles[bGhost.path[i].row*28+bGhost.path[i].col].setFillColor(sf::Color(0,0,255,128));
            }


            for(int i = 0; i< rGhost.path.size(); i++)
            {
                Tiles[rGhost.path[i].row*28+rGhost.path[i].col].setFillColor(sf::Color(255,0,0,128));
            }
        }

        /// -------------------------------------------


        window.clear();
        window.setView(view);

        switch(gsManager.gState)
        {

        case GameStates::MENU:
            window.draw(setting.settingBTN);
            window.draw(setting.helpBTN);
            window.draw(StartImage);
            window.draw(PreStart);
            window.draw(TitlePacMan);
            break;

        case GameStates::SETTINGS:
            for(int i = 0; i<3; i++)
            {
                window.draw(setting.tracks[i]);
                window.draw(setting.setYN[i]);
            }
            window.draw(Settings_text_sprite);
            window.draw(setting.returnBTN);
            break;

        case GameStates::HELP:
            window.draw(Help_text_sprite);
            window.draw(setting.returnBTN);
            break;

        case GameStates::PAUSE:
            window.draw(Paused);
        case GameStates::GAME:

            window.draw(Background);

            if(conf::DEBUG)
            {
                int temp = 0;
                for(int i = 0; i<31; i++)
                {
                    for(int j = 0; j<28; j++)
                    {
                        //if(conf::GameMatrix[i][j] != 1){
                        window.draw(Tiles[temp]);
                        // }
                        temp++;
                    }
                }
            }

            for(int i = 0; i< pellet.DOTS; i++)
            {
                window.draw(pellet.Dot[i]);
            }

            for(int i = 0; i< pellet.POWERUPS; i++)
            {
                window.draw(pellet.PowerUp[i]);
            }

            window.draw(rGhost.sprite);
            window.draw(oGhost.sprite);
            window.draw(bGhost.sprite);
            window.draw(pGhost.sprite);

            window.draw(pacman.sprite);

            window.draw(scoreDis);
            window.draw(pellet.Berry);

            for(int i = 0; i<PacLife.size(); i++)
            {
                window.draw(PacLife[i]);
            }
            break;

        case GameStates::GAMEOVER:
            window.draw(NewHS);
            window.draw(GameDone);
            break;

        };

        sf::View view = window.getView();
        window.display();
    }

    return 0;
}
