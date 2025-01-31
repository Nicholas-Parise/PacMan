#include "Settings.h"

Settings::Settings(sf::Texture *trackTextures, sf::Texture *YNtextures, sf::Texture *settingsTextures, sf::Texture *returnTextures, sf::Texture *helpTextures)
{
    readInSettings("Assets/Other/Settings.txt");

    this->trackTextures = trackTextures;
    this->YNtextures = YNtextures;
    this->settingsTextures = settingsTextures;
    this->returnTextures = returnTextures;
    this->helpTextures = helpTextures;


    tracks[0].emplace(trackTextures[0]);
    tracks[1].emplace(trackTextures[0]);
    tracks[2].emplace(trackTextures[0]);

    setYN[0].emplace(YNtextures[0]);
    setYN[1].emplace(YNtextures[0]);
    setYN[2].emplace(YNtextures[0]);

    settingBTN.emplace(settingsTextures[0]);
    returnBTN.emplace(returnTextures[0]);
    helpBTN.emplace(helpTextures[0]);

    initSprite();

    aOptions[0] = &Master;
    aOptions[1] = &Music;
    aOptions[2] = &Effect;
}

Settings::~Settings()
{
    //dtor
}

// this sets all the arrays to false to reset the hover texture each frame
void Settings::resetHover(){
    for(int i = 0; i<6; i++){
        hoverOffsets[i] = 0;
    }
    settingOffset = 0;
    returnOffset = 0;
    helpOffset = 0;
}


void Settings::hoverYN(int index){
    hoverOffsets[index] = 1;
}

void Settings::hoverTrack(int index){
 hoverOffsets[index+3] = 1;
}


void Settings::hoverReturn(){
    returnOffset = 1;
}

void Settings::hoverSettings(){
    settingOffset = 1;
}

void Settings::hoverHelp(){
    helpOffset = 1;
}


void Settings::initSprite(){

    for(int i = 0; i<3; i++){
        tracks[i]->setOrigin(sf::Vector2f(65,47));
        tracks[i]->setPosition(sf::Vector2f(((conf::SIZEX*conf::TILESIZE/2)-100) + 100*i,400.f));
        tracks[i]->setScale(sf::Vector2f(0.6f,0.6f));

        setYN[i]->setScale(sf::Vector2f(0.7f,0.7f));
        setYN[i]->setPosition(sf::Vector2f(350,i*90+10));
    }

    settingBTN->setOrigin(sf::Vector2f(312,47));
    settingBTN->setPosition(sf::Vector2f(conf::SIZEX*conf::TILESIZE/2.f,388.f));
    settingBTN->setScale(sf::Vector2f(0.7f,0.7f));

    returnBTN->setOrigin(sf::Vector2f(136,47));
    returnBTN->setPosition(sf::Vector2f(conf::SIZEX*conf::TILESIZE/2.f,500.f));
    returnBTN->setScale(sf::Vector2f(0.6f,0.6f));

    helpBTN->setOrigin(sf::Vector2f(111,47));
    helpBTN->setPosition(sf::Vector2f(conf::SIZEX*conf::TILESIZE/2.f,488.f));
    helpBTN->setScale(sf::Vector2f(0.6f,0.6f));
}


void Settings::textureSwitcher(){

    for(int i = 0; i<3; i++){
        if(Track == i+1){
            tracks[i]->setTexture(trackTextures[i*2+1]);
        }else{
            tracks[i]->setTexture(trackTextures[i*2+hoverOffsets[i+3]]);
        }

        if(*aOptions[i]){
            setYN[i]->setTexture(YNtextures[hoverOffsets[i]]);
        }else{
            setYN[i]->setTexture(YNtextures[2+hoverOffsets[i]]);
        }
    }

    settingBTN->setTexture(settingsTextures[settingOffset]);
    returnBTN->setTexture(returnTextures[returnOffset]);
    helpBTN->setTexture(helpTextures[helpOffset]);
}


void Settings::readInSettings(std::string filename){

    int FileLine = 0;
    std::string editstring;
    char current = '1';
    int interval = 0;

    std::ifstream readFile;
    readFile.open(filename);

    if(readFile.is_open())
    {

        while(!readFile.eof())
        {

            current = '1';
            interval = 0;

            readFile >> editstring;

            while(current != ':')
            {

                current = editstring[interval];
                interval++;
            }


            current = editstring[interval];

            if(FileLine == 0)
            {

                if(current == '1')
                {
                    Master = true;
                }
            }

            if(FileLine == 1)
            {

                if(current == '1')
                {
                    Music = true;
                }
            }
            if(FileLine == 2)
            {

                if(current == '1')
                {
                    Effect = true;
                }
            }
            if(FileLine == 3)
            {
                Track = current - '0';
                break;
            }

            FileLine++;
        }
    }
}


void Settings::saveSettings(std::string filename){

    std::string Setting1, Setting2, Setting3, Setting4;
    std::ofstream writeFile(filename);

    writeFile<<"Master:"<<Master<<"\n";
    writeFile<<"Music:"<<Music<<"\n";
    writeFile<<"SoundEf:"<<Effect<<"\n";
    writeFile<<"Track:"<<Track;
    writeFile.close();
}
