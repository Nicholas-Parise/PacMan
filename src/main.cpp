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

    view.setViewport( sf::FloatRect({posX, posY}, {sizeX, sizeY}) );

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


sf::Vector2u ClossestTile(float PositionX, float PositionY)
{
    int row = PositionY/conf::TILESIZE;
    int col = PositionX/conf::TILESIZE;

    return sf::Vector2u(row, col);
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
            NewHS.setPosition(sf::Vector2f(522/2, 400));
        }

        writeFile<< highscore;

    }
    writeFile.close();
}


void PlaceLives(std::vector<sf::Sprite> &PacLife)
{
    for(int i = 0; i<PacLife.size(); i++)
    {
        PacLife[i].setOrigin(sf::Vector2f(15,15));
        PacLife[i].setPosition(sf::Vector2f(((conf::SIZEX*conf::TILESIZE)-(2*40+15)) + i*40,(conf::SIZEY+1)*conf::TILESIZE));
    }
}

int main()
{

    sf::ContextSettings settings;
    settings.antiAliasingLevel = 8;
    sf::RenderWindow window(sf::VideoMode({conf::SIZEX*conf::TILESIZE, (conf::SIZEY+3)*conf::TILESIZE}), "PacMan", sf::Style::Default,sf::State::Windowed ,settings);
    window.setFramerateLimit(60);
    sf::View view(sf::FloatRect({0.f, 0.f}, {window.getSize().x, window.getSize().y}));

    const sf::Font font("Assets/Other/Arial.ttf");

    sf::Text GameDone(font, "Loading...", 30);
    GameDone.setStyle(sf::Text::Bold);
    GameDone.setFillColor(sf::Color::Red);
    GameDone.setPosition(sf::Vector2f((conf::SIZEX*conf::TILESIZE/2)-60, conf::SIZEY*conf::TILESIZE/2));

    window.draw(GameDone);
    window.display();

    srand (time(NULL));

    TextureManager textureManager;

    Player pacman(textureManager.PacTexture[0]);
    int PacLives = 3;

    Ghost rGhost(textureManager.redTextures, textureManager.scaredTextures, textureManager.eyeTextures);
    rGhost.setScatter(1,23);

    Ghost bGhost(textureManager.blueTextures, textureManager.scaredTextures, textureManager.eyeTextures);
    bGhost.setScatter(29,24);

    Ghost oGhost(textureManager.orangeTextures, textureManager.scaredTextures, textureManager.eyeTextures);
    oGhost.setScatter(29,3);
    int OrangePacDistance;

    Ghost pGhost(textureManager.pinkTextures, textureManager.scaredTextures, textureManager.eyeTextures);
    pGhost.setScatter(1,2);

    Settings setting(textureManager.trackTextures, textureManager.YNtextures, textureManager.settingsTextures, textureManager.returnTextures, textureManager.helpTextures);

    GameStateManager gsManager;

    Pathing pathing;

    Pellet pellet(textureManager.berryTextures[0]);

    SoundManager soundManager;


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


    const string Help_Text = "\t\t\t\t\t\t\t HELP \n \n \nControls: Arrow keys to move\nEat all the dots to respawn more. \nA ghost must be scared to be eaten! \nEat a power pellet to make the ghosts scared.\nYou die if a normal ghost touches you\nGameover when you have no lives\nbeat the High score to earn a bonus life!\n\n\t\tBy. Nicholas Parise";



    const string Settings_Text = "Master Audio: \n\n\n Music: \n\n\n Sound Effects: \n\n\n Music Track:";
    string scoreShow;
    string HSString;

    sf::Vector2u TempRowCol;


    std::vector<Directions> PacManAvallibleDir = {LEFT,RIGHT};


    std::vector<sf::RectangleShape> Tiles(868);

    for(int i = 0; i<conf::SIZEY; i++)
    {
        for(int j = 0; j<conf::SIZEX; j++)
        {

            Tiles[place].setOrigin(sf::Vector2f(0,0));
            Tiles[place].setSize(sf::Vector2f(conf::TILESIZE, conf::TILESIZE));
            Tiles[place].setPosition(sf::Vector2f(conf::TILESIZE*j,conf::TILESIZE*i));

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

    sf::Sprite Background(MapTexture);
    Background.setPosition(sf::Vector2f(0, 0));

    sf::Texture PauseTexture;
    PauseTexture.loadFromFile("Assets/Sprite/pause.png");

    sf::Texture texture9;
    texture9.loadFromFile("Assets/Other/PacMan-Start.png");

    // -----

    sf::Sprite Paused(PauseTexture);
    Paused.setPosition(sf::Vector2f(0, 0));
    Paused.setOrigin(sf::Vector2f(25,31));
    Paused.setScale(sf::Vector2f(1.f,1.f));
    Paused.setPosition(sf::Vector2f(261,288));


    sf::Sprite TitlePacMan(textureManager.PacTexture[0]);
    TitlePacMan.setOrigin(sf::Vector2f(15,15));
    TitlePacMan.setRotation(sf::degrees(-90.0f));


    sf::Sprite StartImage(texture9);
    StartImage.setPosition(sf::Vector2f(conf::SIZEX*conf::TILESIZE/2, 150));
    StartImage.setOrigin(sf::Vector2f(225,51));


    std::vector<sf::Sprite> PacLife(3, sf::Sprite(textureManager.PacTexture[0]));
    PlaceLives(PacLife);


    //----------------Text----------------

    sf::Text NewHS(font,"NEW HIGHSCORE!!", 30);
    NewHS.setStyle(sf::Text::Bold);
    NewHS.setFillColor(sf::Color::Red);
    NewHS.setOrigin(sf::Vector2f(150,15));
    NewHS.setPosition(sf::Vector2f(1000, 1000));


    sf::Text scoreDis(font,"0", 30);
    scoreDis.setStyle(sf::Text::Bold);
    scoreDis.setFillColor(sf::Color::White);
    scoreDis.setOrigin(sf::Vector2f(15,15));
    scoreDis.setPosition(sf::Vector2f(30,(conf::SIZEY+1)*conf::TILESIZE));



    sf::Text HsDis(font, "0", 30);
    HsDis.setStyle(sf::Text::Bold);
    HsDis.setFillColor(sf::Color::White);
    HsDis.setOrigin(sf::Vector2f(15, 15));
    HsDis.setPosition(sf::Vector2f(250, 590));

    sf::Text PreStart(font,"Push Space To Start",30);
    PreStart.setStyle(sf::Text::Bold);
    PreStart.setFillColor(sf::Color::White);
    PreStart.setOrigin(sf::Vector2f(142,15));
    PreStart.setPosition(sf::Vector2f(conf::SIZEX*conf::TILESIZE/2, conf::SIZEY*conf::TILESIZE/2));


    GameDone.setOrigin(sf::Vector2f(95,15));
    GameDone.setPosition(sf::Vector2f(conf::SIZEX*conf::TILESIZE/2, conf::SIZEY*conf::TILESIZE/2));
    GameDone.setString("GAME OVER");



    sf::Text Help_text_sprite(font, Help_Text, 20);
    Help_text_sprite.setStyle(sf::Text::Bold);
    Help_text_sprite.setFillColor(sf::Color::White);
    Help_text_sprite.setPosition(sf::Vector2f(0,100));


    sf::Text Settings_text_sprite(font, Settings_Text, 30);
    Settings_text_sprite.setStyle(sf::Text::Bold);
    Settings_text_sprite.setFillColor(sf::Color::White);
    Settings_text_sprite.setPosition(sf::Vector2f(100,10));


    sf::Vector2i pixelPos;
    sf::Vector2f worldPos;

    // done loading, play music
    if(setting.Music)
    {
        soundManager.BackG_Wii.play();
    }

    while (window.isOpen())
    {

        while (const std::optional event = window.pollEvent()){

            if (event->is<sf::Event::Closed>())
            {

                SaveHS(highscore,score,NewHS);
                window.close();

                return 0;
            }

            if (const auto* resized = event->getIf<sf::Event::Resized>())
            {
                view = getLetterboxView( view, resized->size.x, resized->size.y );
            }

            pixelPos = sf::Mouse::getPosition(window);
            worldPos = window.mapPixelToCoords(pixelPos);

            if(event->is<sf::Event::MouseButtonReleased>() )
            {
                cout<<" r"<<worldPos.y/conf::TILESIZE<<" c"<<worldPos.x/conf::TILESIZE<<endl;
            }


            TitlePacMan.setPosition(sf::Vector2f(worldPos.x,worldPos.y));

            ///////

            setting.resetHover();


            if(isSpriteHover(setting.settingBTN->getGlobalBounds(), sf::Vector2f(worldPos.x, worldPos.y)) && gsManager.gState == GameStates::MENU)
            {

                setting.hoverSettings();

                if(setting.Effect)
                {
                    soundManager.Button_select->play();
                }


                if(event->is<sf::Event::MouseButtonReleased>())
                {

                    gsManager.changeState(GameStates::SETTINGS);

                    if(setting.Effect)
                    {
                        soundManager.Button_click->play();
                    }
                }
            }else if(isSpriteHover(setting.returnBTN->getGlobalBounds(), sf::Vector2f(worldPos.x, worldPos.y)) && (gsManager.gState == GameStates::SETTINGS || gsManager.gState == GameStates::HELP)){

                setting.hoverReturn();

                if(setting.Effect)
                {
                    soundManager.Button_select->play();
                }

                if(event->is<sf::Event::MouseButtonReleased>())
                {

                    gsManager.changeState(GameStates::MENU);

                    if(setting.Effect)
                    {
                        soundManager.Button_click->play();
                    }

                    setting.saveSettings("Assets/Other/Settings.txt");
                }
            }else if(isSpriteHover(setting.helpBTN->getGlobalBounds(), sf::Vector2f(worldPos.x, worldPos.y)) && gsManager.gState == GameStates::MENU){

                 setting.hoverHelp();

                if(setting.Effect)
                {
                    soundManager.Button_select->play();
                }

                if(event->is<sf::Event::MouseButtonReleased>())
                {

                    gsManager.changeState(GameStates::HELP);

                    if(setting.Effect)
                    {
                        soundManager.Button_click->play();
                    }
                }
            }

            // ---------------



            for(int i = 0; i<3; i++)
            {

                if(isSpriteHover(setting.setYN[i]->getGlobalBounds(), sf::Vector2f(worldPos.x, worldPos.y)))
                {

                    setting.hoverYN(i);

                    if(setting.Effect)
                    {
                        soundManager.Button_select->play();
                    }

                    if(event->is<sf::Event::MouseButtonReleased>())
                    {

                        if(setting.Effect)
                        {
                            soundManager.Button_click->play();
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

                if(isSpriteHover(setting.tracks[i]->getGlobalBounds(), sf::Vector2f(worldPos.x, worldPos.y)))
                {

                    setting.hoverTrack(i);

                    if(setting.Effect)
                    {
                        soundManager.Button_select->play();
                    }

                    if(event->is<sf::Event::MouseButtonReleased>())
                    {

                        if(setting.Effect)
                        {
                            soundManager.Button_click->play();
                        }

                        setting.Track = i+1;
                    }
                }
            }

            setting.textureSwitcher();
        }


        /// Path Finding

        // update row and col with the tile size
        pacman.updateRC();
        rGhost.updateRC();
        oGhost.updateRC();
        bGhost.updateRC();
        pGhost.updateRC();

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
                        solutionRow-=2;
                    }
                    if(pacman.direction == DOWN)
                    {
                        solutionRow+=2;
                    }
                    if(pacman.direction == LEFT)
                    {
                        solutionCol-=2;
                    }
                    if(pacman.direction == RIGHT)
                    {
                        solutionCol+=2;
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
                        solutionRow = oGhost.scatterRow;
                        solutionCol = oGhost.scatterCol;
                    } // else pacman
                    break;
                }
                case 3:
                    //pink
                {
                    if(pacman.direction == UP)
                    {
                        solutionRow-=4;
                    }
                    if(pacman.direction == DOWN)
                    {
                        solutionRow+=4;
                    }
                    if(pacman.direction == LEFT)
                    {
                        solutionCol-=4;
                    }
                    if(pacman.direction == RIGHT)
                    {
                        solutionCol+=4;
                    }
                }
            }

            if(pacman.changedPosition()|| ghosts[i]->changedPosition()){
                ghosts[i]->updateOldRC();

                Node start(ghosts[i]->row,ghosts[i]->col,ghosts[i]->direction);

                switch(ghosts[i]->state)
                {

                case CHASE:
                {
                    Node finish(solutionRow, solutionCol);
                    ghosts[i]->path = pathing.shortestPath(start,finish);
                }
                break;
                case SCATTER:
                {
                    Node finish(ghosts[i]->scatterRow, ghosts[i]->scatterCol);
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
                    Node finish(conf::GhostHomeRow+3,conf::GhostHomeCol);
                    ghosts[i]->path = pathing.shortestPath(start,finish);
                }
                break;
                }
            }
        }

        pacman.updateOldRC();




        //////////////


        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape))
        {

            if(gsManager.gState != GameStates::PAUSE && gsManager.gState != GameStates::MENU && gsManager.pauseTimer >10)
            {

                gsManager.pauseTimer = 10;
                gsManager.changeState(GameStates::PAUSE);

                soundManager.pauseMusic();
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


        pacman.handleInput();


        if((pacman.teleporter() | rGhost.teleporter() | oGhost.teleporter() | bGhost.teleporter() | pGhost.teleporter())&& setting.Effect)
        {
            soundManager.teleport_Game->play();
        }


        // update all ghosts
        for(int i = 0; i<4; i++)
        {
            ghosts[i]->outOfSpawn();
            ghosts[i]->moveSprite(1.0);
            ghosts[i]->scaredStop(gsManager.powerUpTimer);
        }


        // --Dot Hit Test--
        if(pellet.dotHit(pacman.sprite))
        {
            score +=5;
            if(setting.Effect)
            {
                soundManager.Dot_Chomp->play();
            }
        }

        // --Powerup Hit Test--
        if(pellet.powerHit(pacman.sprite))
        {

            pellet.PowerUpEaten ++;

            if(setting.Effect)
            {
                soundManager.Power_Chomp->play();
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
                soundManager.Berry_Chomp->play();
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

                if(pacman.sprite.getGlobalBounds().findIntersection((ghosts[i])->sprite.getGlobalBounds()))
                {

                    if(ghosts[i]->state == SCARED)
                    {
                        score +=10;

                        if(setting.Effect)
                        {
                            soundManager.Eat_Ghost->play();
                        }

                        ghosts[i]->changeState(DEAD);

                    }
                    else if(ghosts[i]->state != DEAD)
                    {

                        soundManager.pauseMusic();

                        if(setting.Effect)
                        {
                            soundManager.Dead->play();
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
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space) && gsManager.gState == GameStates::MENU)
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
                soundManager.Button_click->play();
                soundManager.start_Game->play();
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
                soundManager.start_Game->play();
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
            PacLife[PacLives].setPosition({1000,1000});

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
                soundManager.gameOver->play();
            }

            SaveHS(highscore,score,NewHS);

            soundManager.stopMusic();

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

        rGhost.textureSwitcher(feetTimer, gsManager.powerUpTimer);

        oGhost.textureSwitcher(feetTimer, gsManager.powerUpTimer);

        pGhost.textureSwitcher(feetTimer, gsManager.powerUpTimer);

        bGhost.textureSwitcher(feetTimer, gsManager.powerUpTimer);

        gsManager.increment();

        if(gsManager.gState == GameStates::GAME && !pacman.dead)
        {

            pacman.sprite.move(sf::Vector2f(pacman.xSpeed, pacman.ySpeed));
            rGhost.sprite.move(sf::Vector2f(rGhost.xSpeed, rGhost.ySpeed));
            oGhost.sprite.move(sf::Vector2f(oGhost.xSpeed, oGhost.ySpeed));
            bGhost.sprite.move(sf::Vector2f(bGhost.xSpeed, bGhost.ySpeed));
            pGhost.sprite.move(sf::Vector2f(pGhost.xSpeed, pGhost.ySpeed));
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
            window.draw(*setting.settingBTN);
            window.draw(*setting.helpBTN);
            window.draw(StartImage);
            window.draw(PreStart);
            window.draw(TitlePacMan);
            break;

        case GameStates::SETTINGS:
            for(int i = 0; i<3; i++)
            {
                window.draw(*setting.tracks[i]);
                window.draw(*setting.setYN[i]);
            }
            window.draw(Settings_text_sprite);
            window.draw(*setting.returnBTN);
            break;

        case GameStates::HELP:
            window.draw(Help_text_sprite);
            window.draw(*setting.returnBTN);
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
