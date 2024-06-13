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


void Settings::hoverYN(int index){

}

void Settings::hoverTrack(int index){

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
            tracks[i].setTexture(trackTextures[i*2]);
        }

        if(*aOptions[i]){
        setYN[i].setTexture(YNtextures[0]);
        }else{
        setYN[i].setTexture(YNtextures[2]);
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

                if(current == 't')
                {

                    Master = true;
                }
            }

            if(FileLine == 1)
            {

                if(current == 't')
                {
                    Music = true;
                }
            }
            if(FileLine == 2)
            {

                if(current == 't')
                {
                    Effect = true;
                }
            }
            if(FileLine == 3)
            {
                Track = current - '0';
            }

            if(FileLine == 3)
            {
                break;
            }


            FileLine++;
        }
    }
}


void Settings::saveSettings(std::string filename){

    std::string Setting1, Setting2, Setting3, Setting4;
    std::ofstream writeFile(filename);

    if(Master){
        Setting1 =  "Master:t\n";
    }else{
        Setting1 = "Master:f\n";
    }

    if(Music){
        Setting2 =  "Music:t\n";
    }else{
        Setting2 =  "Music:f\n";
    }

    if(Effect){
        Setting3 =  "SoundEf:t\n";
    }else{
        Setting3 =  "SoundEf:f\n";
    }

    Setting4 = "Track:"+Track;

    writeFile<<Setting1;
    writeFile<<Setting2;
    writeFile<<Setting3;
    writeFile<<Setting4;
    writeFile.close();
}
