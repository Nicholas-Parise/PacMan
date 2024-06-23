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

#include "ghost.h"
#include "Player.h"
#include "Settings.h"
#include "GameStateManager.h"


using namespace std;

const bool DEBUG = false;

const int SIZEX = 28;
const int SIZEY = 31;

const int GhostHomeRow = 13;
const int GhostHomeCol = 11;

const int DeadSpeed = 4.5;      // Must be less than 18
const double GhostSpeed = 1.5;  // Must be less than 18

 const vector<vector<int>> GameMatrix = {
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 0, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 0, 1},
        {1, 8, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 8, 1},
        {1, 0, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 0, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 0, 1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 0, 1},
        {1, 0, 1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 0, 1},
        {1, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 1},
        {1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1},
        {1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 6, 1, 1, 6, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1},
        {1, 1, 1, 1, 1, 1, 0, 1, 1, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 1, 1, 0, 1, 1, 1, 1, 1, 1},
        {1, 1, 1, 1, 1, 1, 0, 1, 1, 6, 1, 1, 1, 1, 1, 1, 1, 1, 6, 1, 1, 0, 1, 1, 1, 1, 1, 1},
        {1, 1, 1, 1, 1, 1, 0, 1, 1, 6, 1, 1, 1, 6, 1, 1, 1, 1, 6, 1, 1, 0, 1, 1, 1, 1, 1, 1},
        {6, 6, 6, 6, 6, 6, 0, 6, 6, 6, 1, 6, 6, 6, 6, 6, 6, 1, 6, 6, 6, 0, 6, 6, 6, 6, 6, 6},
        {1, 1, 1, 1, 1, 1, 0, 1, 1, 6, 1, 1, 1, 6, 1, 1, 1, 1, 6, 1, 1, 0, 1, 1, 1, 1, 1, 1},
        {1, 1, 1, 1, 1, 1, 0, 1, 1, 6, 1, 1, 1, 1, 1, 1, 1, 1, 6, 1, 1, 0, 1, 1, 1, 1, 1, 1},
        {1, 1, 1, 1, 1, 1, 0, 1, 1, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 1, 1, 0, 1, 1, 1, 1, 1, 1},
        {1, 1, 1, 1, 1, 1, 0, 1, 1, 6, 1, 1, 1, 1, 1, 1, 1, 1, 6, 1, 1, 0, 1, 1, 1, 1, 1, 1},
        {1, 1, 1, 1, 1, 1, 0, 1, 1, 6, 1, 1, 1, 1, 1, 1, 1, 1, 6, 1, 1, 0, 1, 1, 1, 1, 1, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 0, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 0, 1},
        {1, 8, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 8, 1},
        {1, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 1},
        {1, 1, 1, 0, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 0, 1, 1, 1},
        {1, 1, 1, 0, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 0, 1, 1, 1},
        {1, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 1},
        {1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1},
        {1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}

        //GameMatrix[31 Y][28 X];

        // 0 is a dot
        //1 is a wall
        //6 is a blank spaces
        // 8 is a big dot
    };

//startx,starty,boxsizex,boxsizex
#define Bry_Cherry 0,0,12,12
#define Bry_Strawberry 16,0,11,12
#define Bry_Peach 32,0,12,12
#define Bry_Apple 48,0,13,13
#define Bry_Lime 65,0,11,12
#define Bry_Spear 80,1,11,11
#define Bry_Bell 96,0,12,13
#define Bry_Key 114,0,7,13

#define Pac_wack1 0,0,30,30
#define Pac_wack2 34,0,30,30
#define Pac_wack3 70,0,30,30
#define Pac_wack4 107,0,30,30
#define Pac_wack5 144,0,30,30
#define Pac_wack6 180,0,30,30
#define Pac_wack7 220,0,30,30
#define Pac_wack8 257,0,30,30
#define Pac_wack9 295,0,30,30
#define Pac_wack10 332,0,30,30
#define Pac_wack11 370,0,30,30

#define GhostRight1 0,0,28,28
#define GhostRight2 32,0,28,28
#define GhostLeft1 64,0,28,28
#define GhostLeft2 96,0,28,28
#define GhostUp1 128,0,28,28
#define GhostUp2 160,0,28,28
#define GhostDown1 192,0,28,28
#define GhostDown2 224,0,28,28

// Note to self use Delta Time for movement don't use set frame limit

//https://www.codesdope.com/blog/article/backtracking-to-solve-a-rat-in-a-maze-c-java-pytho/
//https://www.youtube.com/watch?v=ataGotQ7ir8



void printsolution(int solutionRow,int solutionCol,int StartRow,int StartCol,vector<vector<int>> &solution,vector<vector<int>> maze)
{
//function to print the solution matrix
    cout<<endl;
    int i,j;
    for(i=0; i<SIZEY; i++)
    {
        for(j=0; j<SIZEX; j++)
        {

            if(solutionCol == i && solutionRow == j)
            {
                cout<<"@ ";
            }
            else if(StartCol == i && StartRow == j)
            {
                cout<<"$ ";
            }
            else if(maze[i][j]== 1)
            {
                cout<<"||";
            }
            else
            {
                cout<<" "<<solution[i][j];
            }

        }
        cout<<endl;
    }
}


int SmallestDistance(int Start, int Solution)
{

    int Number;

    if(Start>Solution)
    {
        Number = Start - Solution;
    }
    else
    {

        Number = Solution - Start;
    }

    return Number;
}



int solvemaze(int r, int c, int solutionCol, int solutionRow, Directions CurrentDirection, vector<vector<int>> &solution, vector<int> &PathCol, vector<int> &PathRow, vector<vector<int>> maze)
{

    //if destination is reached, maze is solved
    //destination is the last cell(maze[SIZE-1][SIZE-1])
    if((r==solutionRow) && (c==solutionCol))
    {
        solution[r][c] = 1;
        PathCol.push_back(c);
        PathRow.push_back(r);
        return 1;
    }
    //checking if we can visit in this cell or not
    //the indices of the cell must be in (0,SIZE-1)
    //and solution[r][c] == 0 is making sure that the cell is not already visited
    //maze[r][c] == 0 is making sure that the cell is not blocked
    if(r>=0 && c>=0 && r<SIZEY && c<SIZEX && solution[r][c] == 0 && maze[r][c] != 1)
    {
        //  if(r>=0 && c>=0 && r<SIZEY && c<SIZEX) {

        //if safe to visit then visit the cell
        solution[r][c] = 1;

        PathCol.push_back(c);
        PathRow.push_back(r);

        //cout<<endl;
        // cout<<"---------------"<<endl;

        int BaseRow = SmallestDistance(r, solutionRow);
        int BaseCol = SmallestDistance(c, solutionCol);
        int BaseScore = (BaseRow*BaseRow)+(BaseCol*BaseCol);


        int RigthCol = SmallestDistance(c+1, solutionCol);
        int RigthScore = (BaseRow*BaseRow)+(RigthCol*RigthCol);

        int LeftCol = SmallestDistance(c-1, solutionCol);
        int LeftScore = (BaseRow*BaseRow)+(LeftCol*LeftCol);

        int UpRow = SmallestDistance(r-1, solutionRow);
        int UpScore = (UpRow*UpRow)+(BaseCol*BaseCol);

        int DownRow = SmallestDistance(r+1, solutionRow);
        int DownScore = (DownRow*DownRow)+(BaseCol*BaseCol);


        vector<int> AllScores = {UpScore,LeftScore,DownScore,RigthScore};

        vector<int> AllScoresTemp = AllScores;

        std::sort(AllScoresTemp.begin(), AllScoresTemp.end());

        int lowest = AllScoresTemp[0];
        int SecondLowest = AllScoresTemp[1];
        int ThridLowest = AllScoresTemp[2];
        int Highest = AllScoresTemp[3];

        bool CanGoDown = false;
        bool CanGoUp = false;
        bool CanGoLeft = false;
        bool CanGoRight = false;

        for(int i = 0; i<4; i++)
        {

            if(AllScores[i] == lowest)
            {
                lowest = i;
                break;
            }
        }

        for(int i = 0; i<4; i++)
        {

            if(AllScores[i] == SecondLowest )
            {

                if(i!= lowest)
                {
                    SecondLowest = i;
                    break;
                }
            }
        }

        for(int i = 0; i<4; i++)
        {

            if(AllScores[i] == ThridLowest)
            {
                if(i !=SecondLowest)
                {
                    ThridLowest = i;
                    break;
                }
            }
        }

        for(int i = 0; i<4; i++)
        {

            if(AllScores[i] == Highest)
            {
                if( i !=ThridLowest)
                {
                    Highest = i;
                    break;
                }
            }
        }



//cout<<"Can Go: ";
        if(solution[r-1][c] == 0 && maze[r-1][c] != 1&& CurrentDirection != DOWN)
        {
            CanGoUp = true;
//cout<<"Up ";
        }

        if(solution[r][c-1] == 0 && maze[r][c-1] != 1&& CurrentDirection != RIGHT)
        {
            CanGoLeft = true;
//cout<<"Left ";
        }

        if(solution[r+1][c] == 0 && maze[r+1][c] != 1 && CurrentDirection != UP)
        {
            CanGoDown = true;
//cout<<"Down ";
        }

        if(solution[r][c+1] == 0 && maze[r][c+1] != 1 && CurrentDirection != LEFT)
        {
            CanGoRight = true;
//cout<<"Right ";
        }

//cout<<endl;




//cout<<"Did Go: ";
//        if(CanGoUp == true && lowest == 2) {

        if(CanGoUp == true && lowest == 0)
        {
//cout<<"Up ";
            if(solvemaze((r-1), c, solutionCol, solutionRow,UP,solution,PathCol,PathRow,maze))
                return 1;

        }
        else if(CanGoLeft == true && lowest == 1)
        {
//cout<<"Left ";
            if(solvemaze(r, (c-1), solutionCol, solutionRow,LEFT,solution,PathCol,PathRow,maze))
                return 1;

//        } else if(CanGoDown == true && lowest == 3) {
        }
        else if(CanGoDown == true && lowest == 2)
        {

//cout<<"Down ";
            if(solvemaze((r+1), c, solutionCol, solutionRow,DOWN,solution,PathCol,PathRow,maze))
                return 1;

            //  } else if(CanGoRight == true && lowest == 0) {
        }
        else if(CanGoRight == true && lowest == 3)
        {
//cout<<"Right ";
            if(solvemaze(r, (c+1), solutionCol, solutionRow,RIGHT,solution,PathCol,PathRow,maze))
                return 1;

        }
        else
        {



            //  if(CanGoUp == true && SecondLowest == 2) {
            if(CanGoUp == true && SecondLowest == 0)
            {
//cout<<"Up ";
                if(solvemaze((r-1), c, solutionCol, solutionRow,UP,solution,PathCol,PathRow,maze))
                    return 1;

            }
            else if(CanGoLeft == true && SecondLowest == 1)
            {

//cout<<"Left "<<c-1;
                if(solvemaze(r, (c-1), solutionCol, solutionRow,LEFT,solution,PathCol,PathRow,maze))
                    return 1;

                //} else if(CanGoDown == true && SecondLowest == 3) {

            }
            else if(CanGoDown == true && SecondLowest == 2)
            {
//cout<<"Down ";
                if(solvemaze((r+1), c, solutionCol, solutionRow,DOWN,solution,PathCol,PathRow,maze))
                    return 1;

                // } else if(CanGoRight == true && SecondLowest == 0) {

            }
            else if(CanGoRight == true && SecondLowest == 3)
            {

//cout<<"Right "<<c+1;
                if(solvemaze(r, (c+1), solutionCol, solutionRow,RIGHT,solution,PathCol,PathRow,maze))
                    return 1;

            }
            else
            {



//                if(CanGoUp == true && ThridLowest == 2) {

                if(CanGoUp == true && ThridLowest == 0)
                {

//cout<<"Up ";
                    if(solvemaze((r-1), c, solutionCol, solutionRow,UP,solution,PathCol,PathRow,maze))
                        return 1;

                }
                else if(CanGoLeft == true && ThridLowest == 1)
                {
//cout<<"Left "<<c-1;
                    if(solvemaze(r, (c-1), solutionCol, solutionRow,LEFT,solution,PathCol,PathRow,maze))
                        return 1;

                    //  } else if(CanGoDown == true && ThridLowest == 3) {

                }
                else if(CanGoDown == true && ThridLowest == 2)
                {

//cout<<"Down ";
                    if(solvemaze((r+1), c, solutionCol, solutionRow,DOWN,solution,PathCol,PathRow,maze))
                        return 1;

//               } else if(CanGoRight == true && ThridLowest == 0) {

                }
                else if(CanGoRight == true && ThridLowest == 3)
                {
//cout<<"Right "<<c+1;
                    if(solvemaze(r, (c+1), solutionCol, solutionRow,RIGHT,solution,PathCol,PathRow,maze))
                        return 1;
                }
                else
                {



                    //if(CanGoUp == true && Highest == 2) {
                    if(CanGoUp == true && Highest == 0)
                    {
//cout<<"Up ";
                        if(solvemaze((r-1), c, solutionCol, solutionRow,UP,solution,PathCol,PathRow,maze))
                            return 1;

                    }
                    else if(CanGoLeft == true && Highest == 1)
                    {
//cout<<"Left ";
                        if(solvemaze(r, (c-1), solutionCol, solutionRow,LEFT,solution,PathCol,PathRow,maze))
                            return 1;

                        // } else if(CanGoDown == true && Highest == 3) {
                    }
                    else if(CanGoDown == true && Highest == 2)
                    {

//cout<<"Down ";
                        if(solvemaze((r+1), c, solutionCol, solutionRow,DOWN,solution,PathCol,PathRow,maze))
                            return 1;

                        //  } else if(CanGoRight == true && Highest == 0) {

                    }
                    else if(CanGoRight == true && Highest == 3)
                    {
//cout<<"Right ";
                        if(solvemaze(r, (c+1), solutionCol, solutionRow,RIGHT,solution,PathCol,PathRow,maze))
                            return 1;

                    }
                    else
                    {



                        if(CanGoDown == false && CanGoUp == false && CanGoLeft == false && CanGoRight == true)
                        {

                            //cout<<"Right ";
                            if(solvemaze(r, c+1, solutionCol, solutionRow,RIGHT,solution,PathCol,PathRow,maze))
                                return 1;
                        }

                        if(CanGoDown == false && CanGoUp == false && CanGoLeft == true && CanGoRight == false)
                        {

                            //cout<<"Left ";
                            if(solvemaze(r, c-1, solutionCol, solutionRow,LEFT,solution,PathCol,PathRow,maze))
                                return 1;
                        }

                        if(CanGoDown == false && CanGoUp == true && CanGoLeft == false && CanGoRight == false)
                        {

                            //cout<<"Up ";
                            if(solvemaze(r-1, c, solutionCol, solutionRow,UP,solution,PathCol,PathRow,maze))
                                return 1;
                        }

                        if(CanGoDown == true && CanGoUp == false && CanGoLeft == false && CanGoRight == false)
                        {

                            //cout<<"Down ";
                            if(solvemaze(r+1, c, solutionCol, solutionRow,DOWN,solution,PathCol,PathRow,maze))
                                return 1;
                        }
                    }
                }
            }
        }

        //cout<<"It fucked up!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!"<<endl;


        return 1;

        // This is a last resort if the algorithm seriously messes up this may help to solve the maze


        //going up
        if(solution[r-1][c] == 0 && maze[r-1][c] != 1&& CurrentDirection !=DOWN)
        {
            //cout<<"Up ";
            if(solvemaze(r-1, c, solutionCol, solutionRow,UP,solution,PathCol,PathRow,maze))
                return 1;
        }
        //going left
        if(solution[r][c-1] == 0 && maze[r][c-1] != 1&& CurrentDirection !=RIGHT)
        {
            //cout<<"Left ";
            if(solvemaze(r, c-1, solutionCol, solutionRow,LEFT,solution,PathCol,PathRow,maze))
                return 1;
        }

        //going down
        if(solution[r+1][c] == 0 && maze[r+1][c] != 1 && CurrentDirection !=UP)
        {
            //cout<<"Down ";
            if(solvemaze(r+1, c, solutionCol, solutionRow,DOWN,solution,PathCol,PathRow,maze))
                return 1;
        }

        //going right
        if(solution[r][c+1] == 0 && maze[r][c+1] != 1 && CurrentDirection !=LEFT)
        {
            //cout<<"Right ";
            if(solvemaze(r, c+1, solutionCol, solutionRow,RIGHT,solution,PathCol,PathRow,maze))
                return 1;
        }




        //backtracking
        //  solution[r][c] = 0;
        return 0;
    }
    return 0;

}




void ScaredSolver(int r, int c, Directions CurrentDirection,vector<vector<int>> &solution,vector<int> &PathCol, vector<int> &PathRow,vector<vector<int>> maze){

    solution[r][c] = 1;
    PathCol.push_back(c);
    PathRow.push_back(r);

    float prob = 0.50;

    while(true){

        prob -= 0.05;

        if(solution[r-1][c] == 0 && maze[r-1][c] != 1 && CurrentDirection !=DOWN){
            //up
            if(rand() >= prob){
                solution[r-1][c] = 1;
                PathCol.push_back(c);
                PathRow.push_back(r-1);
                return;
            }
        }

        if(solution[r][c-1] == 0 && maze[r][c-1] != 1&& CurrentDirection !=RIGHT)
        {
            //left
            if(rand() >= prob){
                solution[r][c-1] = 1;
                PathCol.push_back(c-1);
                PathRow.push_back(r);
                return;
            }
        }

        if(solution[r+1][c] == 0 && maze[r+1][c] != 1 && CurrentDirection !=UP)
        {
            //down
            if(rand() >= prob){
                solution[r+1][c] = 1;
                PathCol.push_back(c);
                PathRow.push_back(r+1);
                return;
            }
        }

        if(solution[r][c+1] == 0 && maze[r][c+1] != 1 && CurrentDirection !=LEFT)
        {
            //right
            if(rand() >= prob){
                solution[r][c+1] = 1;
                PathCol.push_back(c+1);
                PathRow.push_back(r);
                return;
            }
        }
    }

    return;
}




sf::View getLetterboxView(sf::View view, int windowWidth, int windowHeight){

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
    if(FinalPlace != -1){
    col = FinalPlace/28;
    row = FinalPlace%28;
    }

    vector<int> RowColArray = {row,col};

    return RowColArray;
}

vector<string> WallTest(vector<vector<int>> GameMatrix, int Row, int Col, Directions currentDur, bool &Stop){

    std::vector<string> AvallibleDir;

    //1 is a wall

    if(Col >0)
    {
        //Above
        if(GameMatrix[Col-1][Row] == 1){

            if(currentDur == UP){
                Stop = true;
            }
        }
        else
        {
            AvallibleDir.push_back("Up");
        }
    }

    //below
    if(GameMatrix[Col+1][Row] == 1){

        if(currentDur == DOWN){
            Stop = true;
        }
    }
    else
    {
        AvallibleDir.push_back("Down");
    }


    //Left
    if(GameMatrix[Col][Row-1] == 1)
    {

        if(currentDur == LEFT)
        {
            Stop = true;
        }
    }
    else
    {
        AvallibleDir.push_back("Left");
    }


    //Right
    if(GameMatrix[Col][Row+1] == 1)
    {

        if(currentDur == RIGHT)
        {
            Stop = true;
        }
    }
    else
    {
        AvallibleDir.push_back("Right");
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



bool OutOfTheCloset(int GhostRow, int GhostCol, vector<int> &PathCol, vector<int> &PathRow, int HouseRow, int HouseCol, bool GhostDead){

    //Makes it go down
    if(GhostCol == HouseCol && GhostRow == HouseRow && GhostDead == true)
    {

        PathCol[1] = HouseRow;
        PathRow[1] = HouseCol+1;


    }


    if(GhostCol == HouseCol+1 && GhostRow == HouseRow && GhostDead == true)
    {

        PathCol[1] = HouseRow;
        PathRow[1] = HouseCol+2;


    }


    if(GhostCol == HouseCol+2 && GhostRow == HouseRow && GhostDead == true)
    {

        PathCol[1] = HouseRow;
        PathRow[1] = HouseCol+3;


    }


    //Makes it go Up
    if(GhostCol == HouseCol+3 && GhostRow == HouseRow)
    {

        PathCol[1] = HouseRow;
        PathRow[1] = HouseCol+2;



        return true;
    }


    if(GhostCol == HouseCol+2 && GhostRow == HouseRow && GhostDead == false)
    {

        PathCol[1] = HouseRow;
        PathRow[1] = HouseCol+1;


    }

    if(GhostCol == HouseCol+1 && GhostRow == HouseRow && GhostDead == false)
    {

        PathCol[1] = HouseRow;
        PathRow[1] = HouseCol;


    }

    return false;
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


void SaveHS(int &highscore, int &score,string &HSString,sf::Text &NewHS)
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

        stringstream ss3;
        ss3<<highscore;
        ss3>>HSString;

        if(score>highscore)
        {

            highscore = score;

            NewHS.setPosition(522/2, 400);
        }

        writeFile<< highscore;

    }
    writeFile.close();

}


void PowerPelletAni(std::vector<sf::CircleShape> &PowerUp, int &glowTimer)
{

    if(glowTimer%2 == 0)
    {
        for(int i = 0; i<PowerUp.size(); i++){
            PowerUp[i].setOutlineThickness(-11+(glowTimer/2));
        }
    }

    if (glowTimer > 24)
    {
        glowTimer = 0;
    }
}



void BerryPlace(sf::Sprite &Berry, int Berrytimer){

    if(Berrytimer == 1200)
    {

        int randtemp = rand()%7;

        if(randtemp == 0)
            Berry.setTextureRect(sf::IntRect(Bry_Cherry));

        if(randtemp == 1)
            Berry.setTextureRect(sf::IntRect(Bry_Strawberry));

        if(randtemp == 2)
            Berry.setTextureRect(sf::IntRect(Bry_Peach));

        if(randtemp == 3)
            Berry.setTextureRect(sf::IntRect(Bry_Apple));

        if(randtemp == 4)
            Berry.setTextureRect(sf::IntRect(Bry_Lime));

        if(randtemp == 5)
            Berry.setTextureRect(sf::IntRect(Bry_Spear));

        if(randtemp == 6)
            Berry.setTextureRect(sf::IntRect(Bry_Bell));

        if(randtemp == 7)
            Berry.setTextureRect(sf::IntRect(Bry_Key));

        Berry.setScale(2.f, 2.f);
        Berry.setPosition(522/2,620/2);
    }

}


void PlaceLives(std::vector<sf::Sprite> &PacLife){
    for(int i = 0; i<PacLife.size(); i++){
        PacLife[i].setOrigin(15,15);
        PacLife[i].setPosition(400 + i*50,600);
    }
}


void resetDots( std::vector<sf::RectangleShape> &Dot, std::vector<sf::CircleShape> &PowerUp){

    int dotplace = 0;
    int PowerUpplace = 0;
    for(int i = 0; i<31; i++){
        for(int j = 0; j<28; j++){

            if(GameMatrix[i][j] == 0){
                Dot[dotplace].setPosition(sf::Vector2f(18.78571429*j+(18.78571429/2), 18.61290323*i+(18.61290323/2)));
                dotplace++;
            }
            if(GameMatrix[i][j] == 8){
                PowerUp[PowerUpplace].setPosition(sf::Vector2f(18.78571429*j+(18.78571429/2), 18.61290323*i+(18.61290323/2)));
                PowerUpplace++;
            }
        }
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
    vector<vector<int>> Red_solution(870);
    vector<int> Red_PathCol;
    vector<int> Red_PathRow;


    Ghost bGhost;
    bGhost.setScatter(29,24);
    vector<vector<int>> Blue_solution(870);
    vector<int> Blue_PathCol;
    vector<int> Blue_PathRow;


    Ghost oGhost;
    oGhost.setScatter(3,29);
    int OrangePacDistance;
    vector<vector<int>> Orange_solution(870);
    vector<int> Orange_PathCol;
    vector<int> Orange_PathRow;


    Ghost pGhost;
    pGhost.setScatter(2,1);
    vector<vector<int>> Pink_solution(870);
    vector<int> Pink_PathCol;
    vector<int> Pink_PathRow;


    Settings setting;

    GameStateManager gsManager;


    Ghost *ghosts[4];
    ghosts[0] = &rGhost;
    ghosts[1] = &bGhost;
    ghosts[2] = &oGhost;
    ghosts[3] = &pGhost;

    int solutionRow = 14;
    int solutionCol = 17;

    int dotsEaten = 0;
    int PowerUpEaten = 0;
    int score = 0;
    int highscore = 0;

    int Level = 0;
    bool freeLife = true;

    int place = 0;

    int feetTimer = 0;


    string Help_Text = "\t\t\t\t\t\t\t\t HELP \n \n \nMove is Arrow keys \nIf you eat all the dots on the board more will spawn. \nIf a ghost hits you and is not Blue, YOU. WILL. DIE! \nTo make a ghost blue you must eat a power pellet,\nthere are 4 accros the map.\nYou Have 3 lives,\nif you beat the High score You get a free life.\n\n\t\tBy. Nicholas Parise";
    string Settings_Text = "Master Audio: \n\n\n Music: \n\n\n Sound Effects: \n\n\n\n Music Track:";
    string scoreShow;
    string HSString;

    vector <int> TempRowCol;


    std::vector<string> PacManAvallibleDir = {"Left","Right"};





    for(int i = 0; i<SIZEX; i++)
    {
        for(int j = 0; j<SIZEY; j++)
        {

            Red_solution[i,j].push_back(0);

            Orange_solution[i,j].push_back(0);

            Blue_solution[i,j].push_back(0);

            Pink_solution[i,j].push_back(0);
        }
    }


    std::vector<sf::RectangleShape> Dot(245);

    for (int i = 0; i < Dot.size(); i++)
    {

        Dot[i].setFillColor(sf::Color::White);
        Dot[i].setSize(sf::Vector2f(5, 5));
        Dot[i].setOrigin(2.5,2.5);
    }


    std::vector<sf::CircleShape> PowerUp(4);

    for (int i = 0; i < PowerUp.size(); i++)
    {

        PowerUp[i].setFillColor(sf::Color::White);
        PowerUp[i].setRadius(10);
        PowerUp[i].setOrigin(10,10);
        PowerUp[i].setOutlineColor(sf::Color(250, 150, 100));
    }


    resetDots(Dot, PowerUp);


    std::vector<sf::RectangleShape> Tiles(868);

    for(int i = 0; i<31; i++){
        for(int j = 0; j<28; j++){

            Tiles[place].setOrigin(0,0);
            Tiles[place].setSize(sf::Vector2f(18.78571429, 18.61290323));
            Tiles[place].setPosition(sf::Vector2f(18.78571429*j,18.61290323*i));

            if(GameMatrix[i][j] == 0){
                Tiles[place].setFillColor(sf::Color(0,255,255,128));
                Tiles[place].setFillColor(sf::Color(0,255,255,0));
            }

            if(GameMatrix[i][j] == 8){
                Tiles[place].setFillColor(sf::Color(0,255,255,128));
                Tiles[place].setFillColor(sf::Color(0,255,255,0));
            }

            if(GameMatrix[i][j] == 1){
                Tiles[place].setFillColor(sf::Color(255,0,255,128));
                Tiles[place].setFillColor(sf::Color(255,0,255,0));
            }

            if(GameMatrix[i][j] == 6){
                Tiles[place].setFillColor(sf::Color(255,255,0,0));
            }
            place++;
        }
    }


    cout<<"done"<<endl;

    sf::Image image;
    image.loadFromFile("Assets/Sprite/PacMan_background.png");

    sf::Texture MapTexture;
    MapTexture.loadFromImage(image);

    sf::Sprite Background;
    Background.setTexture(MapTexture);
    Background.setPosition(sf::Vector2f(0, 0));


    sf::Texture PacTexture1;
    PacTexture1.loadFromFile("Assets/Sprite/PacMan_open.png");

    sf::Texture PacTexture2;
    PacTexture2.loadFromFile("Assets/Sprite/PacMan_closed.png");


    sf::Texture PauseTexture;
    PauseTexture.loadFromFile("Assets/Sprite/pause.png");


    sf::Texture texture9;
    texture9.loadFromFile("Assets/Other/PacMan-Start.png");

    sf::Texture texture10;
    texture10.loadFromFile("Assets/Sprite/Berry_Sprite_Sheet.png");


    ////

    sf::Texture scaredTextures[4];
    scaredTextures[0].loadFromFile("Assets/Sprite/ScaredGhost1.png");
    scaredTextures[1].loadFromFile("Assets/Sprite/ScaredGhost2.png");
    scaredTextures[2].loadFromFile("Assets/Sprite/ScaredGhostWhite1.png");
    scaredTextures[3].loadFromFile("Assets/Sprite/ScaredGhostWhite2.png");

    ////

    sf::Image RedSheetimage;
    RedSheetimage.loadFromFile("Assets/Sprite/RedGhostSpriteSheet.png");

    sf::Texture redTextures[8];
    redTextures[0].loadFromImage(RedSheetimage, sf::IntRect(GhostLeft1));
    redTextures[1].loadFromImage(RedSheetimage, sf::IntRect(GhostUp1));
    redTextures[2].loadFromImage(RedSheetimage, sf::IntRect(GhostRight1));
    redTextures[3].loadFromImage(RedSheetimage, sf::IntRect(GhostDown1));
    redTextures[4].loadFromImage(RedSheetimage, sf::IntRect(GhostLeft2));
    redTextures[5].loadFromImage(RedSheetimage, sf::IntRect(GhostUp2));
    redTextures[6].loadFromImage(RedSheetimage, sf::IntRect(GhostRight2));
    redTextures[7].loadFromImage(RedSheetimage, sf::IntRect(GhostDown2));

    ///////

    sf::Image OrangeSheetimage;
    OrangeSheetimage.loadFromFile("Assets/Sprite/OrangeGhostSpriteSheet.png");

    sf::Texture orangeTextures[8];
    orangeTextures[0].loadFromImage(OrangeSheetimage, sf::IntRect(GhostLeft1));
    orangeTextures[1].loadFromImage(OrangeSheetimage, sf::IntRect(GhostUp1));
    orangeTextures[2].loadFromImage(OrangeSheetimage, sf::IntRect(GhostRight1));
    orangeTextures[3].loadFromImage(OrangeSheetimage, sf::IntRect(GhostDown1));
    orangeTextures[4].loadFromImage(OrangeSheetimage, sf::IntRect(GhostLeft2));
    orangeTextures[5].loadFromImage(OrangeSheetimage, sf::IntRect(GhostUp2));
    orangeTextures[6].loadFromImage(OrangeSheetimage, sf::IntRect(GhostRight2));
    orangeTextures[7].loadFromImage(OrangeSheetimage, sf::IntRect(GhostDown2));


    ////////

    sf::Image BlueSheetimage;
    BlueSheetimage.loadFromFile("Assets/Sprite/BlueGhostSpriteSheet.png");

    sf::Texture blueTextures[8];
    blueTextures[0].loadFromImage(BlueSheetimage, sf::IntRect(GhostLeft1));
    blueTextures[1].loadFromImage(BlueSheetimage, sf::IntRect(GhostUp1));
    blueTextures[2].loadFromImage(BlueSheetimage, sf::IntRect(GhostRight1));
    blueTextures[3].loadFromImage(BlueSheetimage, sf::IntRect(GhostDown1));
    blueTextures[4].loadFromImage(BlueSheetimage, sf::IntRect(GhostLeft2));
    blueTextures[5].loadFromImage(BlueSheetimage, sf::IntRect(GhostUp2));
    blueTextures[6].loadFromImage(BlueSheetimage, sf::IntRect(GhostRight2));
    blueTextures[7].loadFromImage(BlueSheetimage, sf::IntRect(GhostDown2));


    /////
    sf::Image PinkSheetimage;
    PinkSheetimage.loadFromFile("Assets/Sprite/PinkGhostSpriteSheet.png");

    sf::Texture pinkTextures[8];
    pinkTextures[0].loadFromImage(PinkSheetimage, sf::IntRect(GhostLeft1));
    pinkTextures[1].loadFromImage(PinkSheetimage, sf::IntRect(GhostUp1));
    pinkTextures[2].loadFromImage(PinkSheetimage, sf::IntRect(GhostRight1));
    pinkTextures[3].loadFromImage(PinkSheetimage, sf::IntRect(GhostDown1));
    pinkTextures[4].loadFromImage(PinkSheetimage, sf::IntRect(GhostLeft2));
    pinkTextures[5].loadFromImage(PinkSheetimage, sf::IntRect(GhostUp2));
    pinkTextures[6].loadFromImage(PinkSheetimage, sf::IntRect(GhostRight2));
    pinkTextures[7].loadFromImage(PinkSheetimage, sf::IntRect(GhostDown2));

    //////

    sf::Image EyeSheetimage;
    EyeSheetimage.loadFromFile("Assets/Sprite/EyeSpriteSheet.png");

    sf::Texture eyeTextures[4];
    eyeTextures[0].loadFromImage(EyeSheetimage, sf::IntRect(GhostLeft1));
    eyeTextures[1].loadFromImage(EyeSheetimage, sf::IntRect(GhostUp1));
    eyeTextures[2].loadFromImage(EyeSheetimage, sf::IntRect(GhostRight1));
    eyeTextures[3].loadFromImage(EyeSheetimage, sf::IntRect(GhostDown1));

    //////////

    sf::Image DeadSheetimage;
    DeadSheetimage.loadFromFile("Assets/Sprite/Pac-Death-SpriteSheet.png");

    sf::Texture deadTextures[11];
    deadTextures[0].loadFromImage(DeadSheetimage, sf::IntRect(Pac_wack1));
    deadTextures[1].loadFromImage(DeadSheetimage, sf::IntRect(Pac_wack2));
    deadTextures[2].loadFromImage(DeadSheetimage, sf::IntRect(Pac_wack3));
    deadTextures[3].loadFromImage(DeadSheetimage, sf::IntRect(Pac_wack4));
    deadTextures[4].loadFromImage(DeadSheetimage, sf::IntRect(Pac_wack5));
    deadTextures[5].loadFromImage(DeadSheetimage, sf::IntRect(Pac_wack6));
    deadTextures[6].loadFromImage(DeadSheetimage, sf::IntRect(Pac_wack7));
    deadTextures[7].loadFromImage(DeadSheetimage, sf::IntRect(Pac_wack8));
    deadTextures[8].loadFromImage(DeadSheetimage, sf::IntRect(Pac_wack9));
    deadTextures[9].loadFromImage(DeadSheetimage, sf::IntRect(Pac_wack10));
    deadTextures[10].loadFromImage(DeadSheetimage, sf::IntRect(Pac_wack11));


    sf::Texture texture11;
    texture11.loadFromFile("Assets/Other/Solid_black.png");

    sf::Texture texture14;
    texture14.loadFromFile("Assets/Sprite/pause.png");

    sf::Texture texture15;
    texture15.loadFromFile("Assets/Buttons/Settings_1.png");

    sf::Texture texture16;
    texture16.loadFromFile("Assets/Buttons/Settings_2.png");

    sf::Texture texture17;
    texture17.loadFromFile("Assets/Buttons/Return_1.png");

    sf::Texture texture18;
    texture18.loadFromFile("Assets/Buttons/Return_2.png");

    sf::Texture texture19;
    texture19.loadFromFile("Assets/Buttons/Help_1.png");

    sf::Texture texture20;
    texture20.loadFromFile("Assets/Buttons/Help_2.png");


    sf::Texture YNtextures[4];
    YNtextures[0].loadFromFile("Assets/Buttons/Yes_1.png");
    YNtextures[1].loadFromFile("Assets/Buttons/Yes_2.png");
    YNtextures[2].loadFromFile("Assets/Buttons/No_1.png");
    YNtextures[3].loadFromFile("Assets/Buttons/No_2.png");


    sf::Texture trackTextures[6];
    trackTextures[0].loadFromFile("Assets/Buttons/1_1.png");
    trackTextures[1].loadFromFile("Assets/Buttons/1_2.png");
    trackTextures[2].loadFromFile("Assets/Buttons/2_1.png");
    trackTextures[3].loadFromFile("Assets/Buttons/2_2.png");
    trackTextures[4].loadFromFile("Assets/Buttons/3_1.png");
    trackTextures[5].loadFromFile("Assets/Buttons/3_2.png");


    cout<<"done1"<<endl;

    sf::SoundBuffer sound3;
    sound3.loadFromFile("Assets/Audio/Effect/Mac_Startup.wav");

    sf::SoundBuffer sound4;
    sound4.loadFromFile("Assets/Audio/Effect/XP_Dots.wav");

    sf::SoundBuffer sound5;
    sound5.loadFromFile("Assets/Audio/Effect/XP_Start.wav");

    sf::SoundBuffer sound6;
    sound6.loadFromFile("Assets/Audio/Effect/XP_Teleport.wav");

    sf::SoundBuffer sound7;
    sound7.loadFromFile("Assets/Audio/Effect/XP_End.wav");

    sf::SoundBuffer sound8;
    sound8.loadFromFile("Assets/Audio/Effect/Click_Button.wav");

    sf::SoundBuffer sound9;
    sound9.loadFromFile("Assets/Audio/Effect/Select_Button.wav");

    sf::SoundBuffer sound10;
    sound10.loadFromFile("Assets/Audio/Effect/Death.wav");

    sf::SoundBuffer sound11;
    sound11.loadFromFile("Assets/Audio/Effect/PowerUp.wav");

    sf::SoundBuffer sound12;
    sound12.loadFromFile("Assets/Audio/Effect/XP_Yay.wav");

    sf::SoundBuffer sound15;
    sound15.loadFromFile("Assets/Audio/Effect/Fortnite_Clap.wav");

    cout<<"done2"<<endl;
/////

    sf::SoundBuffer sound1;
    sound1.loadFromFile("Assets/Audio/Music/Pizza_Theme.wav");

    sf::SoundBuffer sound2;
    sound2.loadFromFile("Assets/Audio/Music/Wii_Menu2.wav");

    sf::SoundBuffer sound13;
    sound13.loadFromFile("Assets/Audio/Music/SubwooferLullaby.ogg");

    sf::SoundBuffer sound14;
    sound14.loadFromFile("Assets/Audio/Music/Sweden.ogg");



    cout<<"done3"<<endl;
//music
    sf::Sound BackG_Pizza;
    BackG_Pizza.setBuffer(sound1);

    sf::Sound BackG_Subwooder;
    BackG_Subwooder.setBuffer(sound13);

    sf::Sound BackG_Sweden;
    BackG_Sweden.setBuffer(sound14);

//sfx
    sf::Sound BackG_Wii;
    BackG_Wii.setBuffer(sound2);

    sf::Sound Mac_start;
    Mac_start.setBuffer(sound3);

    sf::Sound XP_Tele;
    XP_Tele.setBuffer(sound4);

    sf::Sound XP_start;
    XP_start.setBuffer(sound5);

    sf::Sound Dot_Chomp;
    Dot_Chomp.setBuffer(sound6);

    sf::Sound XP_End;
    XP_End.setBuffer(sound7);

    sf::Sound Button_click;
    Button_click.setBuffer(sound8);

    sf::Sound Button_select;
    Button_select.setBuffer(sound9);

    sf::Sound Dead;
    Dead.setBuffer(sound10);

    sf::Sound PowerSound;
    PowerSound.setBuffer(sound11);

    sf::Sound Yay;
    Yay.setBuffer(sound12);

    sf::Sound Fortnite_Clap;
    Fortnite_Clap.setBuffer(sound15);

    if(setting.Music)
    {
        BackG_Wii.play();
    }

    BackG_Wii.setLoop(true);
    BackG_Pizza.setLoop(true);
    BackG_Subwooder.setLoop(true);
    BackG_Sweden.setLoop(true);

    BackG_Wii.setVolume(60.f);
    XP_Tele.setVolume(50.f);
    Mac_start.setVolume(50.f);
    BackG_Pizza.setVolume(10.f);
    PowerSound.setVolume(30.f);


    ////


    sf::Sprite Paused;
    Paused.setTexture(PauseTexture);
    Paused.setPosition(sf::Vector2f(0, 0));
    Paused.setOrigin(25,31);
    Paused.setScale(1.f,1.f);
    Paused.setPosition(261,288);

    sf::IntRect rectSourceSprite(Bry_Apple);
    sf::Sprite Berry(texture10,rectSourceSprite);
    Berry.setScale(2.f, 2.f);
    Berry.setPosition(1000,1000);


    sf::Sprite TitlePacMan;
    TitlePacMan.setTexture(PacTexture1);
    TitlePacMan.setOrigin(15,15);
    TitlePacMan.setRotation(-90);



    sf::Sprite StartImage;
    StartImage.setTexture(texture9);
    StartImage.setPosition(sf::Vector2f(266, 150));
    StartImage.setOrigin(225,51);

    sf::Sprite Menu;
    Menu.setTexture(texture11);
    Menu.setPosition(sf::Vector2f(0, 0));
    Menu.setOrigin(0,0);
    Menu.setScale(10.f, 10.f);

    sf::Sprite Setting;
    Setting.setTexture(texture15);
    Setting.setOrigin(312,47);
    Setting.setPosition(sf::Vector2f(522/2.f,388.f));
    Setting.setScale(.7f,.7f);

    sf::Sprite Return;
    Return.setTexture(texture17);
    Return.setOrigin(136,47);
    Return.setPosition(sf::Vector2f(522/2.f,550.f));
    Return.setScale(.6f,.6f);

    sf::Sprite Help;
    Help.setTexture(texture19);
    Help.setOrigin(111,47);
    Help.setPosition(sf::Vector2f(522/2.f,488.f));
    Help.setScale(.6f,.6f);

    std::vector<sf::Sprite> PacLife(3, sf::Sprite(PacTexture1));
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



    SaveHS(highscore,score,HSString,NewHS);


    sf::Text HsDis(HSString, font);
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



    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {

                SaveHS(highscore,score,HSString,NewHS);
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


            if(isSpriteHover(Setting.getGlobalBounds(), sf::Vector2f(worldPos.x, worldPos.y)) && gsManager.gState == GameStates::MENU){

                Setting.setTexture(texture16);

                if(setting.Effect){
                    Button_select.play();
                }

                if(event.type == sf::Event::MouseButtonReleased &&  event.mouseButton.button == sf::Mouse::Left){

                    gsManager.changeState(GameStates::SETTINGS);

                    if(setting.Effect){
                        Button_click.play();
                    }

                    setting.appear();
                }
            }else{

                Setting.setTexture(texture15);
            }


            if(isSpriteHover(Return.getGlobalBounds(), sf::Vector2f(worldPos.x, worldPos.y)) && (gsManager.gState == GameStates::SETTINGS || gsManager.gState == GameStates::HELP)){

                Return.setTexture(texture18);

                if(setting.Effect){
                    Button_select.play();
                }

                if(event.type == sf::Event::MouseButtonReleased &&  event.mouseButton.button == sf::Mouse::Left)
                {

                    gsManager.changeState(GameStates::MENU);

                    if(setting.Effect){
                        Button_click.play();
                    }

                    setting.saveSettings("Assets/Other/Settings.txt");
                    setting.disappear();
                }
            }
            else{
                Return.setTexture(texture17);
            }


            if(isSpriteHover(Help.getGlobalBounds(), sf::Vector2f(worldPos.x, worldPos.y)) && gsManager.gState == GameStates::MENU){

                Help.setTexture(texture20);
                if(setting.Effect)
                {
                    Button_select.play();
                }

                if(event.type == sf::Event::MouseButtonReleased &&  event.mouseButton.button == sf::Mouse::Left)
                {

                    gsManager.changeState(GameStates::HELP);

                    if(setting.Effect)
                    {
                        Button_click.play();
                    }
                }
            }else{
                Help.setTexture(texture19);
            }



            // ---------------

            setting.resetHover();

            for(int i = 0; i<3; i++){

                if(isSpriteHover(setting.setYN[i].getGlobalBounds(), sf::Vector2f(worldPos.x, worldPos.y))){

                    setting.hoverYN(i);

                    if(setting.Effect){
                        Button_select.play();
                    }

                    if(event.type == sf::Event::MouseButtonReleased &&  event.mouseButton.button == sf::Mouse::Left){

                        if(setting.Effect){
                            Button_click.play();
                        }

                        if(*setting.aOptions[i]){
                            *setting.aOptions[i] = false;
                            if(i == 0){
                                *setting.aOptions[1] = false;
                                *setting.aOptions[2] = false;
                                BackG_Wii.stop();
                            }
                        }else{
                            if(i == 0 || i > 0 && *setting.aOptions[0]){
                                *setting.aOptions[i] = true;
                            }
                        }
                    }
                }

                //

                if(isSpriteHover(setting.tracks[i].getGlobalBounds(), sf::Vector2f(worldPos.x, worldPos.y))){

                    setting.hoverTrack(i);

                    if(setting.Effect){
                        Button_select.play();
                    }

                    if(event.type == sf::Event::MouseButtonReleased &&  event.mouseButton.button == sf::Mouse::Left){

                        if(setting.Effect){
                            Button_click.play();
                        }

                        setting.Track = i+1;
                    }
                }
            }

            setting.textureSwitcher(trackTextures, YNtextures);
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





        solutionRow = pacman.row;
        solutionCol = pacman.col;


         for(int x = 0; x<SIZEX; x++)
            {
                for(int y = 0; y<SIZEY; y++)
                {
                    Red_solution[y][x] = 0;
                    Blue_solution[y][x] = 0;
                    Pink_solution[y][x] = 0;
                    Orange_solution[y][x] = 0;
                }
            }


        //Red
        if(pacman.changedPosition()|| rGhost.changedPosition()){
            rGhost.updateOldRC();

            Red_PathCol.clear();
            Red_PathRow.clear();

            switch(rGhost.state){

            case CHASE:
                solvemaze(rGhost.col,rGhost.row,solutionRow,solutionCol, rGhost.direction, Red_solution,Red_PathCol,Red_PathRow,GameMatrix);
                break;
            case SCATTER:
                solvemaze(rGhost.col,rGhost.row,rGhost.scatterRow,rGhost.scatterCol, rGhost.direction, Red_solution,Red_PathCol,Red_PathRow,GameMatrix);
                break;
            case SCARED:
                ScaredSolver(rGhost.col,rGhost.row, rGhost.direction, Red_solution, Red_PathCol, Red_PathRow, GameMatrix);
                break;
            case DEAD:
                solvemaze(rGhost.col,rGhost.row,GhostHomeRow,GhostHomeCol, rGhost.direction, Red_solution,Red_PathCol,Red_PathRow,GameMatrix);
                break;
            }
            // printsolution(solutionRow,solutionCol,StartRow,StartCol,Red_solution,GameMatrix);
        }


        //Blue
         if(pacman.changedPosition() || bGhost.changedPosition()){
            bGhost.updateOldRC();

            Blue_PathCol.clear();
            Blue_PathRow.clear();

            solutionRow =  pacman.row;
            solutionCol = pacman.col;

            if(pacman.direction == UP){
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

            int tempSolutionRow = solutionRow - rGhost.row;
            int tempSolutionCol = solutionCol - rGhost.col;

            solutionRow = solutionRow + (tempSolutionRow*-1);
            solutionCol = solutionCol + (tempSolutionCol*-1);


            //rGhost.col
            //rGhost.row

            switch(bGhost.state){
            case CHASE:
                solvemaze(bGhost.col,bGhost.row,solutionRow,solutionCol, bGhost.direction, Blue_solution,Blue_PathCol,Blue_PathRow,GameMatrix);
                break;
            case SCATTER:
                solvemaze(bGhost.col,bGhost.row,bGhost.scatterRow,bGhost.scatterCol, bGhost.direction, Blue_solution,Blue_PathCol,Blue_PathRow,GameMatrix);
                break;
            case SCARED:
                ScaredSolver(bGhost.col,bGhost.row, bGhost.direction, Blue_solution, Blue_PathCol, Blue_PathRow, GameMatrix);
                break;
            case DEAD:
                solvemaze(bGhost.col,bGhost.row,GhostHomeRow,GhostHomeCol, bGhost.direction, Blue_solution,Blue_PathCol,Blue_PathRow,GameMatrix);
                break;
            }
            // printsolution(solutionRow,solutionCol,StartRow,StartCol,Blue_solution,GameMatrix);
        }


        //Orange
         if(pacman.changedPosition() || oGhost.changedPosition()){
            oGhost.updateOldRC();

            Orange_PathCol.clear();
            Orange_PathRow.clear();

            OrangePacDistance = pow(pacman.row-oGhost.row,2) + pow(pacman.col-oGhost.col,2);

            if(OrangePacDistance<80){
                solutionRow =  pacman.row;
                solutionCol = pacman.col;
            }else{
                solutionRow =  oGhost.scatterRow;
                solutionCol = oGhost.scatterCol;
            }

            switch(oGhost.state){

            case CHASE:
                solvemaze(oGhost.col,oGhost.row,solutionRow,solutionCol, oGhost.direction, Orange_solution,Orange_PathCol,Orange_PathRow,GameMatrix);
                break;
            case SCATTER:
                solvemaze(oGhost.col,oGhost.row,oGhost.scatterRow,oGhost.scatterCol, oGhost.direction, Orange_solution,Orange_PathCol,Orange_PathRow,GameMatrix);
                break;
            case SCARED:
                ScaredSolver(oGhost.col,oGhost.row, oGhost.direction, Orange_solution, Orange_PathCol, Orange_PathRow, GameMatrix);
                break;
            case DEAD:
                solvemaze(oGhost.col,oGhost.row,GhostHomeRow,GhostHomeCol, oGhost.direction, Orange_solution,Orange_PathCol,Orange_PathRow,GameMatrix);
                break;
            }
            // printsolution(solutionRow,solutionCol,StartRow,StartCol,Orange_solution,GameMatrix);
        }


        //Pink
         if(pacman.changedPosition() || pGhost.changedPosition()){
            oGhost.updateOldRC();

            Pink_PathCol.clear();
            Pink_PathRow.clear();

            solutionRow = pacman.row;
            solutionCol = pacman.col;

            if(pacman.direction == UP){
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


            switch(pGhost.state){

            case CHASE:
                solvemaze(pGhost.col,pGhost.row,solutionRow,solutionCol, pGhost.direction, Pink_solution,Pink_PathCol,Pink_PathRow,GameMatrix);
                break;
            case SCATTER:
                solvemaze(pGhost.col,pGhost.row,pGhost.scatterRow,pGhost.scatterCol, pGhost.direction, Pink_solution,Pink_PathCol,Pink_PathRow,GameMatrix);
                break;
            case SCARED:
                ScaredSolver(pGhost.col,pGhost.row, pGhost.direction, Pink_solution, Pink_PathCol, Pink_PathRow, GameMatrix);
                break;
            case DEAD:
                solvemaze(pGhost.col,pGhost.row,GhostHomeRow,GhostHomeCol, pGhost.direction, Pink_solution,Pink_PathCol,Pink_PathRow,GameMatrix);
                break;
            }
            // printsolution(solutionRow,solutionCol,StartRow,StartCol,Pink_solution,GameMatrix);
        }


        pacman.updateOldRC();


        if(DEBUG == true)
        {

            place = 0;
            for(int i = 0; i<31; i++)
            {
                for(int j = 0; j<28; j++)
                {

                    if(GameMatrix[i][j] == 0)
                    {
                        Tiles[place].setFillColor(sf::Color(0,255,255,128));
                    }
                    if(GameMatrix[i][j] == 8)
                    {
                        Tiles[place].setFillColor(sf::Color(0,255,255,128));
                    }
                    if(GameMatrix[i][j] == 6)
                    {
                        Tiles[place].setFillColor(sf::Color(255,255,0,128));
                    }
                    place++;
                }
            }


            for(int i = 0; i<Pink_PathCol.size(); i++)
            {
                Tiles[Pink_PathRow[i]*28 + Pink_PathCol[i]].setFillColor(sf::Color(255,105,180,128));
            }

            for(int i = 0; i<Orange_PathCol.size(); i++)
            {
                Tiles[Orange_PathRow[i]*28 + Orange_PathCol[i]].setFillColor(sf::Color(255,140,0,128));
            }

            for(int i = 0; i<Blue_PathCol.size(); i++)
            {
                Tiles[Blue_PathRow[i]*28+Blue_PathCol[i]].setFillColor(sf::Color(0,0,255,128));
            }

            for(int i = 0; i<Red_PathCol.size(); i++)
            {
                Tiles[Red_PathRow[i]*28+Red_PathCol[i]].setFillColor(sf::Color(255,0,0,128));
            }
        }



        //////////////



        PacManAvallibleDir = WallTest(GameMatrix, pacman.row, pacman.col, pacman.direction, stopPacMan);



        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)){

            if(gsManager.gState != GameStates::PAUSE && gsManager.gState != GameStates::MENU && gsManager.pauseTimer >10){

                gsManager.pauseTimer = 10;
                gsManager.changeState(GameStates::PAUSE);

                BackG_Pizza.pause();
                BackG_Subwooder.pause();
                BackG_Sweden.pause();
            }

            else if(gsManager.gState == GameStates::PAUSE && gsManager.pauseTimer > 30)
            {

                gsManager.changeState(GameStates::GAME);
                gsManager.pauseTimer = 0;

                if(setting.Music){
                    switch(setting.Track){
                        case 1:
                            BackG_Pizza.play();
                            break;
                        case 2:
                            BackG_Subwooder.play();
                            break;
                        case 3:
                            BackG_Sweden.play();
                            break;
                    }
                }
            }
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && gsManager.gState == GameStates::MENU){

            cout<<"play"<<endl;

            gsManager.changeState(GameStates::GAME);
            gsManager.reset();

            freeLife = true;
            PacLives = 3;
            Level = 0;

            score = 0;
            PowerUpEaten = 0;
            dotsEaten = 0;

            pacman.reset();

            rGhost.reset();
            oGhost.reset();
            pGhost.reset();
            rGhost.reset();

            PlaceLives(PacLife);

            resetDots(Dot, PowerUp);


            BackG_Wii.stop();
            if(setting.Effect)
            {
                Button_click.play();
                Mac_start.play();
            }

                if(setting.Music){
                    switch(setting.Track){
                        case 1:
                            BackG_Pizza.play();
                            break;
                        case 2:
                            BackG_Subwooder.play();
                            break;
                        case 3:
                            BackG_Sweden.play();
                            break;
                    }
                }
        }


    if(!pacman.dead){
        for(int i = 0; i<PacManAvallibleDir.size(); i++){

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && PacManAvallibleDir[i] == "Left"){

                pacman.goDirection(LEFT);

            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)&& PacManAvallibleDir[i] == "Right"){

                pacman.goDirection(RIGHT);
            }

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)&& PacManAvallibleDir[i] == "Up"){

                pacman.goDirection(UP);

            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)&& PacManAvallibleDir[i] == "Down"){

                pacman.goDirection(DOWN);
            }
        }
    }

        if(pacman.teleporter() && setting.Effect){
            XP_Tele.play();
        }

        // red teleporter
        if(rGhost.teleporter() && setting.Effect){
            XP_Tele.play();
        }

        // orange teleporter
        if(oGhost.teleporter() && setting.Effect){
            XP_Tele.play();
        }

        // blue teleporter
        if(bGhost.teleporter() && setting.Effect){
            XP_Tele.play();
        }

        // pink teleporter
        if(pGhost.teleporter() && setting.Effect){
            XP_Tele.play();
        }


        if(stopPacMan == true )
        {
            stopPacMan = false;
            pacman.setSpeed(0,0);
        }



        if(OutOfTheCloset(rGhost.row, rGhost.col, Red_PathCol, Red_PathRow, GhostHomeRow, GhostHomeCol, rGhost.state == DEAD)){

            rGhost.state = SCATTER;
            rGhost.direction = NONE;
        }

        if(OutOfTheCloset(oGhost.row, oGhost.col, Orange_PathCol, Orange_PathRow, GhostHomeRow, GhostHomeCol, oGhost.state == DEAD)){

            oGhost.state = SCATTER;
            oGhost.direction = NONE;
        }

        if(OutOfTheCloset(bGhost.row, bGhost.col, Blue_PathCol, Blue_PathRow, GhostHomeRow, GhostHomeCol, bGhost.state == DEAD))
        {

            bGhost.state = SCATTER;
            bGhost.direction = NONE;
        }

        if(OutOfTheCloset(pGhost.row, pGhost.col, Pink_PathCol, Pink_PathRow, GhostHomeRow, GhostHomeCol, pGhost.state == DEAD))
        {
            pGhost.state = SCATTER;
            pGhost.direction = NONE;
        }




        //Red
        rGhost.followPath(Red_PathCol[1],Red_PathRow[1],GhostSpeed,DeadSpeed);

        //Orange
        oGhost.followPath(Orange_PathCol[1],Orange_PathRow[1],GhostSpeed,DeadSpeed);

        //Blue
        bGhost.followPath(Blue_PathCol[1],Blue_PathRow[1],GhostSpeed,DeadSpeed);

        //Pink
        pGhost.followPath(Pink_PathCol[1],Pink_PathRow[1],GhostSpeed,DeadSpeed);


        // --Dot Hittest--

        for (int i = 0; i < Dot.size(); i++){
            if(pacman.sprite.getGlobalBounds().intersects(Dot[i].getGlobalBounds())){

                Dot[i].setPosition(Dot[i].getPosition().x+1000,Dot[i].getPosition().y);

                dotsEaten ++;
                score +=5;

                if(setting.Effect){
                    Dot_Chomp.play();
                }
            }
        }


        for (int i = 0; i < PowerUp.size(); i++){
            if(pacman.sprite.getGlobalBounds().intersects(PowerUp[i].getGlobalBounds())){

                PowerUp[i].setPosition(PowerUp[i].getPosition().x+1000,PowerUp[i].getPosition().y);

                if(setting.Effect)
                {
                    PowerSound.play();
                }

                gsManager.GhostScared = true;
                gsManager.powerUpTimer = 0;

                PowerUpEaten ++;
                score +=25;

                rGhost.changeState(SCARED);
                oGhost.changeState(SCARED);
                bGhost.changeState(SCARED);
                pGhost.changeState(SCARED);
            }
        }



        rGhost.scaredStop(gsManager.powerUpTimer);

        oGhost.scaredStop(gsManager.powerUpTimer);

        pGhost.scaredStop(gsManager.powerUpTimer);

        bGhost.scaredStop(gsManager.powerUpTimer);


        if(rGhost.state != SCARED || oGhost.state != SCARED || pGhost.state != SCARED || bGhost.state != SCARED){
             gsManager.GhostScared = false;
        }



        // ghost pacman hittest
        if(!pacman.dead && DEBUG == false){

            for(int i = 0; i<4; i++){

                if(pacman.sprite.getGlobalBounds().intersects((ghosts[i])->sprite.getGlobalBounds())){

                    if(ghosts[i]->state == SCARED){
                        score +=10;

                        if(setting.Effect)
                        {
                            Yay.play();
                        }

                        ghosts[i]->changeState(DEAD);


                    }else if(ghosts[i]->state != DEAD){

                        BackG_Pizza.pause();
                        BackG_Subwooder.pause();
                        BackG_Sweden.pause();

                        if(setting.Effect)
                        {
                            Dead.play();
                        }

                        pacman.dead = true;
                    }
                }
            }
        }


        if(pacman.sprite.getGlobalBounds().intersects(Berry.getGlobalBounds()))
        {

            Berry.setPosition(1000,1000);
            score +=10;

            if(setting.Effect)
            {
                Fortnite_Clap.play();
            }
        }



        if( gsManager.ghostState  == 60*5 ||  gsManager.ghostState  == 60*30||  gsManager.ghostState  == 60*55||  gsManager.ghostState  == 60*80){
            cout<<"Chase"<<endl;

            rGhost.changeState(CHASE);
            oGhost.changeState(CHASE);
            bGhost.changeState(CHASE);
            pGhost.changeState(CHASE);
        }

        else if( gsManager.ghostState == 60*25||  gsManager.ghostState  == 60*50||  gsManager.ghostState  == 60*75){
            cout<<"Scatter"<<endl;

            rGhost.changeState(SCATTER);
            oGhost.changeState(SCATTER);
            bGhost.changeState(SCATTER);
            pGhost.changeState(SCATTER);
        }




        if(freeLife && score>highscore){
            freeLife = false;
            PacLives++;
        }


        if(dotsEaten == 244 && PowerUpEaten==4){

            if(setting.Effect)
            {
                Mac_start.play();
            }

            Level++;

            dotsEaten = 0;
            PowerUpEaten = 0;

            gsManager.berryTimer = 0;
            gsManager.ghostState = -1;

            pacman.reset();

            rGhost.reset();
            oGhost.reset();
            pGhost.reset();
            bGhost.reset();

            resetDots(Dot, PowerUp);
        }


        if(pacman.killPac() && DEBUG == false){

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

            if(setting.Music){
                switch(setting.Track){
                    case 1:
                        BackG_Pizza.play();
                        break;
                    case 2:
                        BackG_Subwooder.play();
                        break;
                    case 3:
                        BackG_Sweden.play();
                        break;
                }
            }
        }



        if(PacLives == 0 && gsManager.gState == GameStates::GAME && DEBUG == false){
            //Game Over
            PacLives--;

            if(setting.Effect){
                XP_End.play();
            }

            SaveHS(highscore,score,HSString,NewHS);

            BackG_Pizza.stop();
            BackG_Subwooder.stop();
            BackG_Sweden.stop();

            gsManager.changeState(GameStates::GAMEOVER);
        }



        scoreUpdate(HsDis, scoreDis, score, highscore, scoreShow, HSString);
        PowerPelletAni(PowerUp, gsManager.glowTimer);


        if(gsManager.TitlePacTimer < 10){
            TitlePacMan.setTexture(PacTexture2);
        }else{
            TitlePacMan.setTexture(PacTexture1);
            gsManager.TitlePacTimer = 0;
        }


        BerryPlace(Berry, gsManager.berryTimer);


        if(gsManager.endGame() && setting.Music){
            BackG_Wii.play();
        }


        // set the textures of the ghosts
        if(feetTimer >= 20){
            feetTimer = 0;
        }else{
            feetTimer+=2;
        }

        pacman.updateAniTimer();

        pacman.textureSwitcher(PacTexture1,PacTexture2, deadTextures);

        rGhost.textureSwitcher(redTextures, scaredTextures, eyeTextures, feetTimer, gsManager.powerUpTimer);

        oGhost.textureSwitcher(orangeTextures, scaredTextures, eyeTextures, feetTimer, gsManager.powerUpTimer);

        pGhost.textureSwitcher(pinkTextures, scaredTextures, eyeTextures, feetTimer, gsManager.powerUpTimer);

        bGhost.textureSwitcher(blueTextures, scaredTextures, eyeTextures, feetTimer, gsManager.powerUpTimer);

        gsManager.increment();

        if(gsManager.gState == GameStates::GAME && !pacman.dead){

                pacman.sprite.move(pacman.xSpeed,pacman.ySpeed);
                rGhost.sprite.move(rGhost.xSpeed, rGhost.ySpeed);
                oGhost.sprite.move(oGhost.xSpeed, oGhost.ySpeed);
                bGhost.sprite.move(bGhost.xSpeed, bGhost.ySpeed);
                pGhost.sprite.move(pGhost.xSpeed, pGhost.ySpeed);
        }


        window.clear();
        window.setView(view);

        switch(gsManager.gState){

            case GameStates::MENU:
                window.draw(Menu);
                window.draw(Setting);
                window.draw(Help);
                window.draw(StartImage);
                window.draw(PreStart);
                window.draw(TitlePacMan);
                break;

            case GameStates::SETTINGS:
                for(int i = 0; i<3; i++){
                    window.draw(setting.tracks[i]);
                    window.draw(setting.setYN[i]);
                }
                window.draw(Settings_text_sprite);
                window.draw(Return);
                break;

            case GameStates::HELP:
                window.draw(Help_text_sprite);
                window.draw(Return);
                break;

            case GameStates::PAUSE:
                window.draw(Paused);
            case GameStates::GAME:

                window.draw(Background);

                if(DEBUG == true)
                {
                    int temp = 0;
                    for(int i = 0; i<31; i++)
                    {
                        for(int j = 0; j<28; j++)
                        {
                            if(GameMatrix[i][j] != 1)
                            {
                                window.draw(Tiles[temp]);
                            }
                            temp++;
                        }
                    }
                }

                for(int i = 0; i<Dot.size(); i++){
                    window.draw(Dot[i]);
                }

                for(int i = 0; i<4; i++){
                    window.draw(PowerUp[i]);
                }


                window.draw(rGhost.sprite);
                window.draw(oGhost.sprite);
                window.draw(bGhost.sprite);
                window.draw(pGhost.sprite);

                window.draw(pacman.sprite);

                window.draw(scoreDis);
                window.draw(Berry);


                for(int i = 0; i<PacLife.size(); i++){
                    window.draw(PacLife[i]);
                }
                break;

            case GameStates::GAMEOVER:
                window.draw(NewHS);
                window.draw(GameDone);
                break;

        };


        // window.draw(TestGhost);

        sf::View view = window.getView();
        window.display();
    }

    return 0;
}
