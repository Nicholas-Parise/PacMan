#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <ctime>
#include <Images.h>

using namespace std;

bool PacManCheck(sf::Sprite PacMan, sf::Image image, bool &LeftWallPos, bool &RigthWallPos, bool &UpWallPos, bool &DownWallPos) {


    const sf::Color wallcolor(33, 33, 255);

    int tempx = 0, tempy = 0, tempxx = 0, tempyy = 0,tempxxx = 0, tempyyy = 0,tempxxxx = 0, tempyyyy = 0;

    bool onceTrue = false;

    for (int a = 14; a > 0; a--) {
        for (int b = 14; b > 0; b--) {

            tempx = PacMan.getPosition().x+a;
            tempy = PacMan.getPosition().y+b;

            tempxx = PacMan.getPosition().x-a;
            tempyy = PacMan.getPosition().y-b;

            tempxxx = PacMan.getPosition().x+a;
            tempyyy = PacMan.getPosition().y-b;

            tempxxxx = PacMan.getPosition().x-a;
            tempyyyy = PacMan.getPosition().y+b;


            if (image.getPixel(tempx, tempy) == wallcolor) {


                if (image.getPixel(PacMan.getPosition().x+7, tempy) == wallcolor) {

                    DownWallPos = true;
                    UpWallPos = false;
                } else {

                    DownWallPos = false;

                }


                if (image.getPixel(tempx, PacMan.getPosition().y+7) == wallcolor) {

                    RigthWallPos = true;
                    LeftWallPos = false;
                } else {

                    RigthWallPos = false;

                }

                onceTrue = true;
            }

            if (image.getPixel(tempxx, tempyy) == wallcolor) {


                if (image.getPixel(PacMan.getPosition().x-7, tempyy) == wallcolor) {

                    UpWallPos = true;
                    DownWallPos = false;

                } else {
                    UpWallPos = false;
                }

                if (image.getPixel(tempxx, PacMan.getPosition().y-7) == wallcolor) {

                    LeftWallPos = true;
                    RigthWallPos = false;
                } else {
                    LeftWallPos = false;
                }

                onceTrue = true;

            }

            if (image.getPixel(tempxxx, tempyyy) == wallcolor) {

                if (image.getPixel(PacMan.getPosition().x+7, tempyyy) == wallcolor) {

                    UpWallPos = true;
                    DownWallPos = false;
                } else {
                    UpWallPos = false;
                }

                if (image.getPixel(tempxxx, PacMan.getPosition().y-7) == wallcolor) {

                    RigthWallPos = true;
                    LeftWallPos = false;

                } else {
                    RigthWallPos = false;
                }

                onceTrue = true;
            }


            if (image.getPixel(tempxxxx, tempyyyy) == wallcolor) {


                if (image.getPixel(PacMan.getPosition().x-7, tempyyyy) == wallcolor) {

                    DownWallPos = true;
                    UpWallPos = false;
                } else {
                    DownWallPos = false;
                }

                if (image.getPixel(tempxxxx, PacMan.getPosition().y+7) == wallcolor) {

                    LeftWallPos = true;
                    RigthWallPos = false;
                } else {
                    LeftWallPos = false;
                }

                onceTrue = true;
            }


            if(onceTrue == true) {

                return true;
            }

////////////
            /*
            //up
            if(image.getPixel(PacMan.getPosition().x+b, PacMan.getPosition().y-6) == wallcolor){

            UpWallPos = true;
            DownWallPos = false;
            onceTrue = true;
            }
            //down
            if(image.getPixel(PacMan.getPosition().x+b, PacMan.getPosition().y+6) == wallcolor){

            DownWallPos = true;
            UpWallPos = false;
             onceTrue = true;
            }
            //Left
            if(image.getPixel(PacMan.getPosition().x-6,PacMan.getPosition().y+b) == wallcolor){

            LeftWallPos = true;
            RigthWallPos = false;
            onceTrue = true;
            }
            //Right
            if(image.getPixel(PacMan.getPosition().x+6,PacMan.getPosition().y+b) == wallcolor){

            RigthWallPos = true;
            LeftWallPos = false;
             onceTrue = true;
            }

            if(onceTrue == true) {

                return true;
            }

            */
////////////
        }
    }

    return false;

}


bool OrangeAlienCheck(sf::Sprite OrangeGhost, sf::Image image, bool &OrangeLeftWallPos, bool &OrangeRigthWallPos, bool &OrangeUpWallPos, bool &OrangeDownWallPos) {


    const sf::Color wallcolor(33, 33, 255);

    int tempx = 0, tempy = 0, tempxx = 0, tempyy = 0,tempxxx = 0, tempyyy = 0,tempxxxx = 0, tempyyyy = 0;

    bool onceTrue = false;

    for (int a = 14; a > 0; a--) {
        for (int b = 14; b > 0; b--) {

            tempx = OrangeGhost.getPosition().x+a;
            tempy = OrangeGhost.getPosition().y+b;

            tempxx = OrangeGhost.getPosition().x-a;
            tempyy = OrangeGhost.getPosition().y-b;

            tempxxx = OrangeGhost.getPosition().x+a;
            tempyyy = OrangeGhost.getPosition().y-b;

            tempxxxx = OrangeGhost.getPosition().x-a;
            tempyyyy = OrangeGhost.getPosition().y+b;


            if (image.getPixel(tempx, tempy) == wallcolor) {


                if (image.getPixel(OrangeGhost.getPosition().x+7, tempy) == wallcolor) {

                    OrangeDownWallPos = true;
                    OrangeUpWallPos = false;
                } else {

                    OrangeDownWallPos = false;

                }


                if (image.getPixel(tempx, OrangeGhost.getPosition().y+7) == wallcolor) {

                    OrangeRigthWallPos = true;
                    OrangeLeftWallPos = false;
                } else {

                    OrangeRigthWallPos = false;

                }

                onceTrue = true;
            }

            if (image.getPixel(tempxx, tempyy) == wallcolor) {


                if (image.getPixel(OrangeGhost.getPosition().x-7, tempyy) == wallcolor) {

                    OrangeUpWallPos = true;
                    OrangeDownWallPos = false;

                } else {
                    OrangeUpWallPos = false;
                }

                if (image.getPixel(tempxx, OrangeGhost.getPosition().y-7) == wallcolor) {

                    OrangeLeftWallPos = true;
                    OrangeRigthWallPos = false;
                } else {
                    OrangeLeftWallPos = false;
                }

                onceTrue = true;

            }

            if (image.getPixel(tempxxx, tempyyy) == wallcolor) {

                if (image.getPixel(OrangeGhost.getPosition().x+7, tempyyy) == wallcolor) {

                    OrangeUpWallPos = true;
                    OrangeDownWallPos = false;
                } else {
                    OrangeUpWallPos = false;
                }

                if (image.getPixel(tempxxx, OrangeGhost.getPosition().y-7) == wallcolor) {

                    OrangeRigthWallPos = true;
                    OrangeLeftWallPos = false;

                } else {
                    OrangeRigthWallPos = false;
                }

                onceTrue = true;
            }


            if (image.getPixel(tempxxxx, tempyyyy) == wallcolor) {


                if (image.getPixel(OrangeGhost.getPosition().x-7, tempyyyy) == wallcolor) {

                    OrangeDownWallPos = true;
                    OrangeUpWallPos = false;
                } else {
                    OrangeDownWallPos = false;
                }

                if (image.getPixel(tempxxxx, OrangeGhost.getPosition().y+7) == wallcolor) {

                    OrangeLeftWallPos = true;
                    OrangeRigthWallPos = false;
                } else {
                    OrangeLeftWallPos = false;
                }

                onceTrue = true;
            }


            if(onceTrue == true) {

                return true;
            }

        }
    }

    return false;

}


bool RedAlienCheck(sf::Sprite RedGhost, sf::Image image, bool &RedLeftWallPos, bool &RedRigthWallPos, bool &RedUpWallPos, bool &RedDownWallPos, sf::Sprite PacMan) {


    const sf::Color wallcolor(33, 33, 255);

    int tempx = 0, tempy = 0, tempxx = 0, tempyy = 0,tempxxx = 0, tempyyy = 0,tempxxxx = 0, tempyyyy = 0;

    bool onceTrue = false;

    for (int a = 14; a > 0; a--) {
        for (int b = 14; b > 0; b--) {

            tempx = RedGhost.getPosition().x+a;
            tempy = RedGhost.getPosition().y+b;

            tempxx = RedGhost.getPosition().x-a;
            tempyy = RedGhost.getPosition().y-b;

            tempxxx = RedGhost.getPosition().x+a;
            tempyyy = RedGhost.getPosition().y-b;

            tempxxxx = RedGhost.getPosition().x-a;
            tempyyyy = RedGhost.getPosition().y+b;


            if (image.getPixel(tempx, tempy) == wallcolor) {


                if (image.getPixel(RedGhost.getPosition().x+7, tempy) == wallcolor) {

                    RedDownWallPos = true;
                    RedUpWallPos = false;
                } else {

                    RedDownWallPos = false;

                }


                if (image.getPixel(tempx, RedGhost.getPosition().y+7) == wallcolor) {

                    RedRigthWallPos = true;
                    RedLeftWallPos = false;
                } else {

                    RedRigthWallPos = false;

                }

                onceTrue = true;
            }

            if (image.getPixel(tempxx, tempyy) == wallcolor) {


                if (image.getPixel(RedGhost.getPosition().x-7, tempyy) == wallcolor) {

                    RedUpWallPos = true;
                    RedDownWallPos = false;

                } else {
                    RedUpWallPos = false;
                }

                if (image.getPixel(tempxx, RedGhost.getPosition().y-7) == wallcolor) {

                    RedLeftWallPos = true;
                    RedRigthWallPos = false;
                } else {
                    RedLeftWallPos = false;
                }

                onceTrue = true;

            }

            if (image.getPixel(tempxxx, tempyyy) == wallcolor) {

                if (image.getPixel(RedGhost.getPosition().x+7, tempyyy) == wallcolor) {

                    RedUpWallPos = true;
                    RedDownWallPos = false;
                } else {
                    RedUpWallPos = false;
                }

                if (image.getPixel(tempxxx, RedGhost.getPosition().y-7) == wallcolor) {

                    RedRigthWallPos = true;
                    RedLeftWallPos = false;

                } else {
                    RedRigthWallPos = false;
                }

                onceTrue = true;
            }


            if (image.getPixel(tempxxxx, tempyyyy) == wallcolor) {


                if (image.getPixel(RedGhost.getPosition().x-7, tempyyyy) == wallcolor) {

                    RedDownWallPos = true;
                    RedUpWallPos = false;
                } else {
                    RedDownWallPos = false;
                }

                if (image.getPixel(tempxxxx, RedGhost.getPosition().y+7) == wallcolor) {

                    RedLeftWallPos = true;
                    RedRigthWallPos = false;
                } else {
                    RedLeftWallPos = false;
                }

                onceTrue = true;
            }
/////////



//////////

            if(onceTrue == true) {

                return true;
            }

        }
    }

    return false;

}


int findSmallestElement(std::vector< int > &testArr,std::vector< int > &testArr2,int &PacClose) {

    int temp = testArr[0];
    int temp2 = testArr2[0];

    for(int i=0; i<testArr.size(); i++) {
        if(temp>testArr[i]) {
            temp=testArr[i];
        }

        if(temp2>testArr2[i]) {
            temp2=testArr2[i];

        }
    }

    for(int i=0; i<testArr.size(); i++) {

        if(temp == testArr[i] &&temp2 == testArr2[i] ) {

            PacClose = i;

        }

    }

    cout<<"Pac is close to Node: "<<PacClose<<endl;


    testArr.clear();
    testArr2.clear();
    return temp;
}


void paths(int &PacClose,sf::Sprite PacMan,std::vector<sf::RectangleShape> &Node,std::vector<sf::RectangleShape> &lineArr,sf::Sprite RedGhost) {

//start at a Node
//get end Node
//calculate shortest distance using nodes

//start == PacClose
//end == Node[0];



//start
    Node[PacClose].getPosition().x;
    Node[PacClose].getPosition().y;

//end
    Node[0].getPosition().x;
    Node[0].getPosition().y;


//lineArr[1].setPosition(PacMan.getPosition().x,PacMan.getPosition().y);

lineArr[0].setPosition(sf::Vector2f(PacMan.getPosition().x, PacMan.getPosition().y));

    int temp , temp2;

    int xline, yline;

    vector<int> path;


xline = Node[PacClose].getPosition().x-PacMan.getPosition().x;
yline = Node[PacClose].getPosition().y-PacMan.getPosition().y;

if(yline > 0)
lineArr[0].setSize(sf::Vector2f(xline+2, yline+2));


if(yline <0)
lineArr[0].setSize(sf::Vector2f(xline-2, yline-2));

if(Node[PacClose+1].getPosition().x < Node[0].getPosition().x){

cout<<"this worked"<<endl;

if(Node[PacClose-1].getPosition().x < Node[0].getPosition().x){

cout<<"go to node "<<PacClose-1<<endl;
}else{
cout<<"go to node "<<PacClose+1<<endl;

}


}

/*
     for(int i=0; i<Node.size(); i++) {
    for(int j=0; j<Node.size(); j++) {

   path.push_back(Node[i].getPosition().x + Node[j].getPosition().x - Node[PacClose].getPosition().x);
     }
    }
*/


}



int main() {
    int x = 0,y = 0;
    int timer = 0;

    int testTimer = 0;
    int stopTimer = 0;

    int temp = 0;
    int temp1 = 0,temp2 = 0;

    int PacClose = 32;

    srand (time(NULL));


    int OrangeX = 0, Orangey = 0;
    int RedX = 0, RedY = 0;


    int tempCheck = 0, tempCheck2 = 0, tempCheck3 = 0, tempCheck4 = 0;


    std::vector < int > testArr;
    std::vector < int > testArr2;


    bool Left = false;
    bool Right = false;
    bool Up = false;
    bool Down = false;

    bool LeftWallPos = false;
    bool RigthWallPos = false;
    bool UpWallPos = false;
    bool DownWallPos = false;



    bool OrangeLeft = false;
    bool OrangeRight = false;
    bool OrangeUp = false;
    bool OrangeDown = false;

    bool OrangeLeftWallPos = false;
    bool OrangeRigthWallPos = false;
    bool OrangeUpWallPos = false;
    bool OrangeDownWallPos = false;

    bool OrangeUpOnce = false,OrangeDownOnce = false, OrangeLeftOnce = false, OrangeRightOnce = false;




    bool RedLeft = false;
    bool RedRight = false;
    bool RedUp = false;
    bool RedDown = false;

    bool RedLeftWallPos = false;
    bool RedRigthWallPos = false;
    bool RedUpWallPos = false;
    bool RedDownWallPos = false;

    bool RedUpOnce = false,RedDownOnce = false, RedLeftOnce = false, RedRightOnce = false;




    int score = 0;

    sf::RenderWindow window(sf::VideoMode(522, 677), "Pac Man!");
    window.setFramerateLimit(60);



    sf::Image image;
    if (!image.loadFromFile("Assets/PacMan_background.png"))
        return 0;

    sf::Texture texture;

    if (!texture.loadFromImage(image))
        return 0;


    sf::Sprite Background;
    Background.setTexture(texture);
    Background.setPosition(sf::Vector2f(0, 0));


    sf::Texture texture2;
    if (!texture2.loadFromFile("Assets/PacMan_open.png"))
        return -1;

    sf::Texture texture3;
    if (!texture3.loadFromFile("Assets/PacMan_closed.png"))
        return -1;

    sf::Texture texture4;
    if (!texture4.loadFromFile("Assets/OrangeGhostRight.png"))
        return -1;

    sf::Texture texture5;
    if (!texture5.loadFromFile("Assets/RedGhostRight.png"))
        return -1;





    sf::Sprite PacMan;
    PacMan.setTexture(texture2);
    PacMan.setPosition(sf::Vector2f(266, 326));
    PacMan.setOrigin(15,15);

    sf::Sprite OrangeGhost;
    OrangeGhost.setTexture(texture4);
    OrangeGhost.setPosition(sf::Vector2f(256, 256));
    OrangeGhost.setOrigin(15,15);


    sf::Sprite RedGhost;
    RedGhost.setTexture(texture5);
    RedGhost.setPosition(sf::Vector2f(246, 256));
    RedGhost.setOrigin(15,15);



    std::vector<sf::RectangleShape> Dot(340);

    for (int i = 0; i < Dot.size(); i++) {
        Dot[i].setFillColor(sf::Color::White);
        Dot[i].setSize(sf::Vector2f(5, 5));
        Dot[i].setOrigin(2.5,2.5);
    }

      std::vector<sf::RectangleShape> lineArr (70);

 for (int i = 0; i < lineArr.size(); i++) {
        lineArr[i].setFillColor(sf::Color::White);
        }


    int tempx = 30;
    int tempy = 30;

    const sf::Color wallcolor(33, 33, 255);
    const sf::Color wallcolor2(1,0,0);

    for (int i = 0; i < Dot.size(); i++) {


        if (image.getPixel(tempx, tempy) != wallcolor &&image.getPixel(tempx, tempy) != wallcolor2 ) {

            Dot[i].setPosition(tempx,tempy);

        }

        tempx +=30;

        if(tempx == 270) {
            tempx = 263;
        }

        if(tempx == 383) {

            tempx =375;
        }


        if(tempx > 500) {

            tempy +=25;
            tempx = 30;

            if(tempy == 205) {
                tempy = 215;
            }

            if(tempy == 315) {

                tempy = 320;
            }

            if(tempy == 370) {

                tempy = 375;
            }
            if(tempy == 425) {

                tempy = 432;
            }

            if(tempy == 482) {

                tempy = 490;
            }

            if(tempy == 540) {

                tempy = 550;
            }
        }
    }


    std::vector<sf::RectangleShape> Node(66);

    for (int i = 0; i < Node.size(); i++) {
        Node[i].setFillColor(sf::Color::Black);
        Node[i].setSize(sf::Vector2f(15, 15));
        Node[i].setOrigin(7.5,7.5);
    }


    Node[0].setPosition(30,30);
    Node[1].setPosition(120,30);
    Node[2].setPosition(240,30);
    Node[3].setPosition(290,30);
    Node[4].setPosition(400,30);
    Node[5].setPosition(490,30);

    Node[6].setPosition(30,100);
    Node[7].setPosition(120,100);
    Node[8].setPosition(180,100);
    Node[9].setPosition(240,100);
    Node[10].setPosition(290,100);
    Node[11].setPosition(350,100);
    Node[12].setPosition(400,100);
    Node[13].setPosition(490,100);

    Node[14].setPosition(30,160);
    Node[15].setPosition(120,160);
    Node[16].setPosition(180,160);
    Node[17].setPosition(240,160);
    Node[18].setPosition(290,160);
    Node[19].setPosition(350,160);
    Node[20].setPosition(400,160);
    Node[21].setPosition(490,160);

    Node[22].setPosition(180,215);
    Node[23].setPosition(240,215);
    Node[24].setPosition(290,215);
    Node[25].setPosition(350,215);

    Node[26].setPosition(30,270);
    Node[27].setPosition(120,270);
    Node[28].setPosition(180,270);
    Node[29].setPosition(350,270);
    Node[30].setPosition(400,270);
    Node[31].setPosition(490,270);

    Node[32].setPosition(180,330);
    Node[33].setPosition(350,330);

    Node[34].setPosition(30,380);
    Node[35].setPosition(120,380);
    Node[36].setPosition(180,380);
    Node[37].setPosition(240,380);
    Node[38].setPosition(290,380);
    Node[39].setPosition(350,380);
    Node[40].setPosition(400,380);
    Node[41].setPosition(490,380);

    Node[42].setPosition(30,440);
    Node[43].setPosition(70,440);
    Node[44].setPosition(120,440);
    Node[45].setPosition(180,440);
    Node[46].setPosition(240,440);
    Node[47].setPosition(290,440);
    Node[48].setPosition(350,440);
    Node[49].setPosition(400,440);
    Node[50].setPosition(460,440);
    Node[51].setPosition(490,440);

    Node[52].setPosition(30,490);
    Node[53].setPosition(70,490);
    Node[54].setPosition(120,490);
    Node[55].setPosition(180,490);
    Node[56].setPosition(240,490);
    Node[57].setPosition(290,490);
    Node[58].setPosition(350,490);
    Node[59].setPosition(400,490);
    Node[60].setPosition(460,490);
    Node[61].setPosition(490,490);

    Node[62].setPosition(30,550);
    Node[63].setPosition(240,550);
    Node[64].setPosition(290,550);
    Node[65].setPosition(490,550);



    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();

            if(event.type == sf::Event::MouseButtonReleased &&  event.mouseButton.button == sf::Mouse::Left) {

                cout<<"mouse X = "<<sf::Mouse::getPosition(window).x<<" Mouse Y = "<<sf::Mouse::getPosition(window).y<<endl;

            }
        }

        PacManCheck(PacMan,image, LeftWallPos, RigthWallPos, UpWallPos, DownWallPos);

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {

            if(LeftWallPos == false) {
                PacMan.setRotation(-180);
                x = -2;
                y=0;

            } else {
                x = 0;

            }

            //  Left = true;
            //        Right = false;
            //      Up = false;
            //    Down = false;

        } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {

            if(RigthWallPos == false) {
                PacMan.setRotation(0);
                x = 2;
                y=0;

            } else {
                x = 0;

            }

            // Left = false;
            //   Right = true;
            //   Up = false;
            //   Down = false;
        } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {

            if(UpWallPos == false) {
                PacMan.setRotation(-90);
                y= -2;
                x=0;


            } else {

                y = 0;
            }
            //  Left = false;
            //  Right = false;
            //  Up = true;
            //  Down = false;

        } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {



            if(DownWallPos == false) {
                PacMan.setRotation(90);
                y = 2;
                x=0;

            } else {

                y = 0;
            }

            //  Left = false;
            //  Right = false;
            //   Up = false;
            //   Down = true;

        } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {

            x = 0;
            y = 0;
        }

        Left = false;
        Right = false;
        Up = false;
        Down = false;


        if(x == -2) {
            Left = true;

        }
        if(x == 2) {

            Right = true;
        }
        if(y == -2) {
            Up = true;

        }
        if(y == 2) {

            Down = true;
        }


        if(timer == 10) {

            PacMan.setTexture(texture3);

        }

        if(timer == 20) {

            PacMan.setTexture(texture2);
            timer = 0;

        }

        if(timer != 10 || timer !=20) {

            timer++;
        }



        if(PacManCheck(PacMan,image, LeftWallPos, RigthWallPos, UpWallPos, DownWallPos)) {



            if(UpWallPos == true && Up == true) {

                y = 0;
            }

            if (DownWallPos == true && Down == true) {

                y = 0;
            }

            if(LeftWallPos == true && Left == true) {

                x = 0;

            }

            if(RigthWallPos == true && Right == true) {
                x = 0;
            }

        } else {

            LeftWallPos = false;
            RigthWallPos = false;
            UpWallPos = false;
            DownWallPos = false;

        }


        if(UpWallPos == true) {
            cout<<"Wall is up"<<endl;
        }

        if(DownWallPos == true) {
            cout<<"Wall is down"<<endl;
        }

        if(RigthWallPos == true) {
            cout<<"Wall is Right"<<endl;
        }
        if(LeftWallPos == true) {
            cout<<"Wall is left"<<endl;
        }

///////////
//Orange alien stuff

        OrangeAlienCheck(OrangeGhost,image, OrangeLeftWallPos, OrangeRigthWallPos, OrangeUpWallPos, OrangeDownWallPos);

//basic
        if(PacMan.getPosition().y >OrangeGhost.getPosition().y && OrangeDownWallPos == false) {

            OrangeDown = true;
            OrangeUp = false;
        }


        if(PacMan.getPosition().y <OrangeGhost.getPosition().y && OrangeUpWallPos == false) {

            OrangeUp = true;
            OrangeDown = false;

        }

        if(PacMan.getPosition().x >OrangeGhost.getPosition().x && OrangeRigthWallPos == false) {

            OrangeRight = true;
            OrangeLeft = false;

        }

        if(PacMan.getPosition().x <OrangeGhost.getPosition().x && OrangeLeftWallPos == false) {

            OrangeLeft = true;
            OrangeRight = false;

        }

//navigation


        if(PacMan.getPosition().y >OrangeGhost.getPosition().y && OrangeDownWallPos == true && OrangeDown == true) {

            OrangeUpOnce = true;
        }


        if(PacMan.getPosition().y <OrangeGhost.getPosition().y && OrangeUpWallPos == true && OrangeUp == true) {

            OrangeDownOnce = true;
        }

        if(PacMan.getPosition().x >OrangeGhost.getPosition().x && OrangeRigthWallPos == true && OrangeRight == true) {

            OrangeLeftOnce = true;
        }

        if(PacMan.getPosition().x <OrangeGhost.getPosition().x && OrangeLeftWallPos == true && OrangeLeft == true) {

            OrangeRightOnce = true;

        }



        if(OrangeUpOnce == true) {


            OrangeUp = true;
            OrangeDown = false;
        }

        if(OrangeDownOnce == true) {
            OrangeUp = false;
            OrangeDown = true;

        }

        if(OrangeLeftOnce == true) {
            OrangeRight = false;
            OrangeLeft = true;

        }

        if(OrangeRightOnce == true) {
            OrangeLeft = false;
            OrangeRight = true;

        }




        if(OrangeUp == true) {

            Orangey = -1;
        } else {

            Orangey = 1;
        }

        if(OrangeLeft == true) {
            OrangeX = -1;
        } else {
            OrangeX = 1;
        }



        if(OrangeAlienCheck(OrangeGhost,image, OrangeLeftWallPos, OrangeRigthWallPos, OrangeUpWallPos, OrangeDownWallPos)) {


            if(OrangeUpWallPos == true && OrangeUp == true) {

                Orangey = 0;
                OrangeUpOnce = false;
            }

            if (OrangeDownWallPos == true && OrangeDown == true) {

                Orangey = 0;
                OrangeDownOnce = false;
            }

            if(OrangeLeftWallPos == true && OrangeLeft == true) {

                OrangeX = 0;
                OrangeLeftOnce = false;
            }

            if(OrangeRigthWallPos == true && OrangeRight == true) {

                OrangeX = 0;
                OrangeRightOnce = false;
            }




        } else {
            OrangeLeftWallPos = false;
            OrangeRigthWallPos = false;
            OrangeUpWallPos = false;
            OrangeDownWallPos = false;

        }

///////////////////////////////////////////////////////////////////////////////////////////

        for(int i = 0; i > Node.size(); i++) {

            if(PacMan.getPosition().x > Node[i].getPosition().x) {


            }
        }


///////////
//RED alien stuff

        RedAlienCheck(RedGhost,image, RedLeftWallPos, RedRigthWallPos, RedUpWallPos, RedDownWallPos,PacMan);

//basic
/*
  int distanceRight=1000, distanceLeft=1000,distanceUp =1000,distanceDown = 1000, minimum=1000;

int targetY = PacMan.getPosition().y, targetX = PacMan.getPosition().x;

    //If tile is not the one we came from, and is not a wall...
    if ((RedLeftWallPos == false) ) {
      distanceRight= (RedGhost.getPosition().y/8-targetY)*(RedGhost.getPosition().y/8-targetY) + (RedGhost.getPosition().x/8+1-targetX)*(RedGhost.getPosition().x/8+1-targetX);
      if (distanceRight<minimum)
        minimum=distanceRight;
    }
    if ((RedRigthWallPos == false)) {
      distanceLeft= (RedGhost.getPosition().y/8-targetY)*(RedGhost.getPosition().y/8-targetY) + (RedGhost.getPosition().x/8-1-targetX)*(RedGhost.getPosition().x/8-1-targetX);
      if (distanceLeft<minimum)
        minimum=distanceLeft;
    }
    if ((RedDownWallPos == false)) {
      distanceUp= (RedGhost.getPosition().y/8-1-targetY)*(RedGhost.getPosition().y/8-1-targetY) + (RedGhost.getPosition().x/8-targetX)*(RedGhost.getPosition().x/8-targetX);
      if (distanceUp<minimum)
        minimum=distanceUp;
    }
    if ((RedUpWallPos == false)) {
      distanceDown= (RedGhost.getPosition().y/8+1-targetY)*(RedGhost.getPosition().y/8+1-targetY) + (RedGhost.getPosition().x/8-targetX)*(RedGhost.getPosition().x/8-targetX);
      if (distanceDown<minimum)
        minimum=distanceDown;
    }

    if (distanceUp==minimum) RedUp = true;
    else if (distanceRight==minimum) RedRight = true;
    else if (distanceDown==minimum) RedDown = true;
    else if (distanceLeft==minimum) RedLeft = true;


*/


        if(PacMan.getPosition().y >RedGhost.getPosition().y && RedDownWallPos == false) {

            RedDown = true;
            RedUp = false;
        }


        if(PacMan.getPosition().y <RedGhost.getPosition().y && RedUpWallPos == false) {

            RedUp = true;
            RedDown = false;

        }

        if(PacMan.getPosition().x >RedGhost.getPosition().x && RedRigthWallPos == false) {

            RedRight = true;
            RedLeft = false;

        }

        if(PacMan.getPosition().x <RedGhost.getPosition().x && RedLeftWallPos == false) {

            RedLeft = true;
            RedRight = false;

        }

//navigation
        if(RedUpWallPos == true && RedUp == true) {


            RedDownOnce = true;


        }

        if(RedRigthWallPos == true && RedRight == true) {


            RedLeftOnce = true;
        }

        if(RedDownWallPos == true && RedDown == true) {

            RedUpOnce = true;


        }

        if(RedLeftWallPos == true && RedLeft == true) {

            RedRightOnce = true;

        }






        //use temp var wait 5 frame if pacman is in same position ->
        //use .get pixel to see if 5 pixels in any direction are clear the go that way if clear



        if(testTimer == 0) {

            temp1 = RedGhost.getPosition().x;
            temp2 = RedGhost.getPosition().y;


        }
        if(testTimer == 20) {

            if(temp1 == RedGhost.getPosition().x && temp2 == RedGhost.getPosition().y) {

                cout<<"THIUHASDJBKLFNIHUfdeshiou;gfdas;kbljevgfwdakulnahwedfbtgpiouaedshfnbvgaosduifgbynhasodiufgy haospdifhgbn[poaisdhfgopbiahsdnb[poigfu"<<endl;

            }

            testTimer = 0;
        } else {
            testTimer ++;
        }





        if(RedUpOnce == true) {

            RedUp = true;
            RedDown = false;
        }

        if(RedDownOnce == true) {
            RedUp = false;
            RedDown = true;

        }

        if(RedLeftOnce == true) {
            RedRight = false;
            RedLeft = true;

        }

        if(RedRightOnce == true) {
            RedLeft = false;
            RedRight = true;

        }




        if(RedUp == true) {
            RedY = -1;
        }
        if(RedDown == true) {
            RedY = 1;
        }
        if(RedLeft == true) {
            RedX = -1;
        }
        if(RedRight == true) {
            RedX = 1;
        }



        if(RedAlienCheck(RedGhost,image, RedLeftWallPos, RedRigthWallPos, RedUpWallPos, RedDownWallPos,PacMan)) {


            if(RedUpWallPos == true && RedUp == true) {

                RedY = 0;
                RedUpOnce = false;
            }

            if (RedDownWallPos == true && RedDown == true) {

                RedY = 0;
                RedDownOnce = false;
            }

            if(RedLeftWallPos == true && RedLeft == true) {

                RedX = 0;
                RedLeftOnce = false;
            }

            if(RedRigthWallPos == true && RedRight == true) {

                RedX = 0;
                RedRightOnce = false;
            }




        } else {
            RedLeftWallPos = false;
            RedRigthWallPos = false;
            RedUpWallPos = false;
            RedDownWallPos = false;

        }


//////////////////////////////////////


///////////





        if(PacMan.getPosition().x >510) {

            PacMan.setPosition(0,270);
        }

        if(PacMan.getPosition().x<0) {

            PacMan.setPosition(510,270);
        }


        if(OrangeGhost.getPosition().x >510) {

            OrangeGhost.setPosition(0,270);
        }

        if(OrangeGhost.getPosition().x<0) {

            OrangeGhost.setPosition(510,270);
        }


        if(RedGhost.getPosition().x >510) {

            RedGhost.setPosition(0,270);
        }

        if(RedGhost.getPosition().x<0) {

            RedGhost.setPosition(510,270);
        }




        for (int i = 0; i < Dot.size(); i++) {
            if(PacMan.getGlobalBounds().intersects(Dot[i].getGlobalBounds())) {

                Dot[i].setPosition(1000,1000);
                score ++;

            }
        }


        /////////////////

        for(int i = 0; i<Node.size(); i++) {

            if(PacMan.getPosition().x - Node[i].getPosition().x > 0) {

                testArr.push_back(PacMan.getPosition().x - Node[i].getPosition().x);

            } else {

                testArr.push_back(Node[i].getPosition().x- PacMan.getPosition().x);

            }

        }


        for(int i = 0; i<Node.size(); i++) {

            if(PacMan.getPosition().y - Node[i].getPosition().y > 0) {

                testArr2.push_back(PacMan.getPosition().y - Node[i].getPosition().y);

            } else {

                testArr2.push_back(Node[i].getPosition().y- PacMan.getPosition().y);

            }
        }

        cout<<"X = "<<findSmallestElement(testArr, testArr2,PacClose)<<endl;


        paths(PacClose,PacMan,Node,lineArr, RedGhost);


        // cout<<score<<endl;


        PacMan.move(x,y);
        OrangeGhost.move(OrangeX,Orangey);
        RedGhost.move(RedX,RedY);


        window.clear();
        window.draw(Background);

        for (int i = 0; i < Node.size(); i++) {

            window.draw(Node[i]);

        }

        for (int i = 0; i < Dot.size(); i++) {

            window.draw(Dot[i]);
        }

        for(int i = 0; i <lineArr.size();i++){

            window.draw(lineArr[i]);
        }



        window.draw(PacMan);
        window.draw(OrangeGhost);
        window.draw(RedGhost);


        // window.draw(map);
        window.display();
    }

    return 0;
}
