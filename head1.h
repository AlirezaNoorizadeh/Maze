#include <windows.h>  //GetStdHandle  //setColor
#include <iostream>   //cin   //cout
#include <cstdlib>    //rand  //srand#include <ctime>      //time
using namespace std;



class Program {
private:
    int** maze;
    int boolian = 1, ROW=14, COL=14, MAX_MOVES = ROW*10, wallColor=12, cursorColor=15, menu;
    int order=-1, startTime=time(0), currentRow=1, currentCol=1, moves=0, lengthTime, endTime;
    string fileName = "scores2.txt", difficultyTypeName = "Normal";

public:
    void mainMenu();
    void Rename();
    void colorSeter();
    void setDifficulty();
    void setColor(int color);
    void generateMaze();
    void printMaze();
    void Moving();
    void mainBasic();
    void fileReader();
    void saveScores();
    void setTypeOfDifficulty();
};