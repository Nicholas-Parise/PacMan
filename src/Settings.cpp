#include "Settings.h"

Settings::Settings()
{
    readInSettings("Assets/Other/Settings.txt");
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
}


void Settings::hoverYN(int index){
    hoverOffsets[index] = 1;
}

void Settings::hoverTrack(int index){
 hoverOffsets[index+3] = 1;
}


void Settings::initSprite(){

    for(int i = 0; i<3; i++){
        tracks[i].setOrigin(65,47);
        tracks[i].setPosition(sf::Vector2f(1000,1000));
        tracks[i].setScale(.6f,.6f);

        setYN[i].setScale(.7f,.7f);
        setYN[i].setPosition(1000,1000);
    }

}

void Settings::appear(){

    for(int i = 0; i<3; i++){
        tracks[i].setPosition(sf::Vector2f(150 + 100*i,450.f));
        setYN[i].setPosition(400,i*90+10);
    }
}


void Settings::disappear(){

    for(int i = 0; i<3; i++){
        tracks[i].setPosition(1000,1000);
        setYN[i].setPosition(1000,1000);
    }

}



void Settings::textureSwitcher(sf::Texture *trackTextures, sf::Texture *YNtextures){

    for(int i = 0; i<3; i++){
        if(Track == i+1){
            tracks[i].setTexture(trackTextures[i*2+1]);
        }else{
            tracks[i].setTexture(trackTextures[i*2+hoverOffsets[i+3]]);
        }

        if(*aOptions[i]){
            setYN[i].setTexture(YNtextures[hoverOffsets[i]]);
        }else{
            setYN[i].setTexture(YNtextures[2+hoverOffsets[i]]);
        }

    }
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
