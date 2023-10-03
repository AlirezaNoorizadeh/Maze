#include <windows.h>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <conio.h>
#include <algorithm>
using namespace std;


const int ROW = 20;
const int COL = 20;
const int WALL = 0;
const int PATH = 1;
const int START = 2;
const int END = 3;
const int MAX_MOVES = 200;

int maze[ROW][COL];

int boolian = 1;

// void finisher(int currentRow, int currentCol){
//          if(currentRow == ROW-2 && currentCol == COL-4)    maze[ROW-2][COL-3] = PATH;
//     else if(currentRow == ROW-3 && currentCol == COL-4)    maze[ROW-3][COL-3] = maze[ROW-2][COL-3] = PATH;
//     else if(currentRow == ROW-4 && currentCol == COL-4)    maze[ROW-3][COL-4] = maze[ROW-3][COL-3] = maze[ROW-2][COL-3] = PATH;
//     else if(currentRow == ROW-4 && currentCol == COL-3)    maze[ROW-3][COL-3] = maze[ROW-3][COL-2] = PATH;
//     else if(currentRow == ROW-4 && currentCol == COL-2)    maze[ROW-3][COL-2] = PATH;
//     boolian = 0;
// }
void finisher(int currentRow, int currentCol){
         if(currentRow == ROW-2 && currentCol == COL-4)    maze[ROW-2][COL-3] = PATH;
    else if(currentRow == ROW-3 && currentCol == COL-4)    maze[ROW-3][COL-3] = maze[ROW-2][COL-3] = PATH;
    else if(currentRow == ROW-4 && currentCol == COL-4)    maze[ROW-3][COL-4] = maze[ROW-3][COL-3] = maze[ROW-2][COL-3] = PATH;
    else if(currentRow == ROW-4 && currentCol == COL-3)    maze[ROW-3][COL-3] = maze[ROW-3][COL-2] = PATH;
    else if(currentRow == ROW-4 && currentCol == COL-2)    maze[ROW-3][COL-2] = PATH;
    boolian = 0;
}
void generateMaze() {
    // maze walls
    for (int i = 0; i < ROW; i++) {
        for (int j = 0; j < COL; j++) {
            maze[i][j] = WALL;
        }
    }
    boolian = 1;
    maze[1][1] = START;
    maze[ROW-2][COL-2] = END;

    // masir = path
    int currentRow = 1 , currentCol = 1 , moves = 0; //radif  soton

    while (boolian == 1) {
        int direction = rand() % 4;
        switch(direction) {
            case 0: // Move up
                if (currentRow > 2 && maze[currentRow - 2][currentCol] == WALL) {
                    maze[currentRow - 1][currentCol] = PATH;
                    maze[currentRow - 2][currentCol] = PATH;
                    currentRow -= 2;
                }
                if((currentRow == ROW-3 && currentCol == COL-3) || (currentCol == ROW-3 && currentRow == COL-3)) {maze[currentRow+1][currentCol]=PATH; boolian=0;}
                // if(currentRow >= ROW-4 && currentCol >= COL-4) finisher(currentRow,currentCol);
                break;
            case 1: // Move down
                if (currentRow < ROW - 3 && maze[currentRow + 2][currentCol] == WALL) {
                    maze[currentRow + 1][currentCol] = PATH;
                    maze[currentRow + 2][currentCol] = PATH;
                    currentRow += 2;
                }
                if((currentRow == ROW-3 && currentCol == COL-3) || (currentCol == ROW-3 && currentRow == COL-3)) {maze[currentRow+1][currentCol]=PATH; boolian=0;}
                // if(currentRow >= ROW - 4 && currentCol >= COL-4) finisher(currentRow,currentCol);
                break;
            case 2: // Move left
                if (currentCol > 2 && maze[currentRow][currentCol - 2] == WALL) {
                    maze[currentRow][currentCol - 1] = PATH;
                    maze[currentRow][currentCol - 2] = PATH;
                    currentCol -= 2;
                }
                if((currentRow == ROW-3 && currentCol == COL-3) || (currentCol == ROW-3 && currentRow == COL-3)) {maze[currentRow][currentCol+1]=PATH; boolian=0;}
                // if(currentRow >= ROW-4 && currentCol >= COL-4) finisher(currentRow,currentCol);
                break;
            case 3: // Move right
                if (currentCol < COL - 3 && maze[currentRow][currentCol + 2] == WALL) {
                    maze[currentRow][currentCol + 1] = PATH;
                    maze[currentRow][currentCol + 2] = PATH;
                    currentCol += 2;
                }
                if((currentRow == ROW-3 && currentCol == COL-3) || (currentCol == ROW-3 && currentRow == COL-3)) {maze[currentRow][currentCol+1]=PATH; boolian=0;}
                // if(currentRow >= ROW-4 && currentCol >= COL-4) finisher(currentRow,currentCol);
                break;
        }
        moves++;
        if(moves > MAX_MOVES){
            for (int i = 0; i < ROW; i++) {
                for (int j = 0; j < COL; j++) {
                    maze[i][j] = WALL;
                }
            }
            maze[1][1] = START;
            maze[ROW-2][COL-2] = END;
            currentRow = 1; //radif
            currentCol = 1; //soton
            moves = 0;
        }
    }


    int counter = 0;
    while (counter < 20) {
        do{ 
            currentRow = rand() % (ROW-2) +1;
            currentCol = rand() % (COL-2) +1;
        }while(maze[currentRow][currentCol] != PATH);
        int direction = rand() % 4;
        switch(direction) {
            case 0: // Move up
                if (currentRow > 3) {
                    maze[currentRow - 1][currentCol] = PATH;
                    maze[currentRow - 2][currentCol] = PATH;
                }
                counter++;
                break;
            case 1: // Move down
                if (currentRow < ROW-4) {
                    maze[currentRow + 1][currentCol] = PATH;
                    maze[currentRow + 2][currentCol] = PATH;
                }
                counter++;
                break;
            case 2: // Move left
                if (currentCol > 3) {
                    maze[currentRow][currentCol - 1] = PATH;
                    maze[currentRow][currentCol - 2] = PATH;
                }
                counter++;
                break;
            case 3: // Move right
                 if (currentCol < COL-4) {
                    maze[currentRow][currentCol + 1] = PATH;
                    maze[currentRow][currentCol + 2] = PATH;
                }
                counter++;
                break;
            default:cout << "hole erorr." << endl;break;

        }
    }    
    
}

void printMaze(int currentRow, int currentCol) {
    HANDLE col = GetStdHandle(STD_OUTPUT_HANDLE);
    cout << endl;
    for (int i = 0; i < ROW; i++) {
        cout << "    ";
        for (int j = 0; j < COL; j++) {
            if (i == currentRow && j == currentCol) {
                SetConsoleTextAttribute(col, 15);
                cout << "X ";
            } else {
                switch(maze[i][j]) {
                    case WALL:
                        if(i == 0 || i == ROW-1 || j == 0 || j == ROW-1){SetConsoleTextAttribute(col, 7); cout << "O ";}
                        else{SetConsoleTextAttribute(col, 12); cout << "# ";}
                        break;
                    case PATH:
                        cout << "  ";
                        break;
                    case START:
                        SetConsoleTextAttribute(col, 10);
                        cout << "S ";
                        break;
                    case END:
                        SetConsoleTextAttribute(col, 2);
                        cout << "E ";
                        break;
                }
            }
        }
        cout << endl;
    }
}

struct User {
    string name="anonymous";
    int score=1000;
};

bool compareUsers(User a, User b) {
    if (a.score == b.score) { return a.name < b.name; }
    else { return a.score < b.score; }
}

int main() {
    srand(time(NULL));
    User list[4];
    int order=-1, startTime=time(0), currentRow=1, currentCol=1, moves=0, endTime;
    char move;
    while(1){
        system("cls");
        generateMaze();
        startTime = time(0);
        currentRow = 1;
        currentCol = 1;
        moves = 0;

        while (maze[currentRow][currentCol] != END) {
            system("cls");
            printMaze(currentRow, currentCol);
            int arrow_key = getch();
                 if(arrow_key == 'x' || arrow_key == 's') move = 'd';
            else if(arrow_key == 'w') move = 'u';
            else if(arrow_key == 'd') move = 'r';
            else if(arrow_key == 'a') move = 'l';
            else if(arrow_key == 'q') move = 'q'; //u+l
            else if(arrow_key == 'e') move = 'e'; //u+r
            else if(arrow_key == 'z') move = 'z'; //d+l
            else if(arrow_key == 'c') move = 'c'; //d+r
            fflush(stdin);

            switch(move) {
                case 'u': 
                    if (currentRow > 1 && maze[currentRow - 1][currentCol] != WALL) { currentRow--; moves++; }
                    break;
                case 'd':
                    if (currentRow < ROW - 2 && maze[currentRow + 1][currentCol] != WALL) { currentRow++; moves++; }
                    break;
                case 'l':
                    if (currentCol > 1 && maze[currentRow][currentCol - 1] != WALL) { currentCol--; moves++; }
                    break;
                case 'r':
                    if (currentCol < COL - 2 && maze[currentRow][currentCol + 1] != WALL) { currentCol++; moves++; }
                    break;
                case 'q': //u+l
                    if (currentRow > 1 && currentCol > 1 && maze[currentRow-1][currentCol-1] != WALL) { currentRow--; currentCol--; moves++; }
                    break;
                case 'e': //u+r
                    if (currentRow > 1 && currentCol < COL - 2 && maze[currentRow-1][currentCol+1] != WALL) { currentRow--; currentCol++; moves++; }
                    break;
                case 'z': //d+l
                    if (currentRow < ROW - 2 && currentCol > 1 && maze[currentRow+1][currentCol-1] != WALL) { currentRow++; currentCol--; moves++; }
                    break;    
                case 'c': //dr
                    if (currentRow < ROW - 2 && currentCol < COL - 2 && maze[currentRow+1][currentCol+1] != WALL) { currentRow++; currentCol++; moves++; }
                    break;    
                default:
                    cout << "Invalid move. Try again." << endl;
                continue;
            }
        }

        endTime = time(0) - startTime;
        system("cls");
        cout << "\n **** You won this game in " << endTime << " seconds and with " << moves << " moves! ****" << "\n Press any key to continue..."  << getch() <<endl;
        fflush(stdin);
        system("cls");
        cout << "\n  Score : " << endTime <<"\n  Name : ";
        order++;
        if(order>3)order=3;
        cin >> list[order].name;
        list[order].score=endTime;
        sort(list, list + 4, compareUsers);
        system("cls");
        cout << "\n List of top 3 players:" << endl;
        for (int i = 0; i < 3; i++) {
            if(list[i].name == "anonymous" && list[i].score == 1000) cout << "  " << i+1 << ") " << endl;
            else{cout << "  " << i+1 << ") " << list[i].name << ": " << list[i].score << endl;}
        }
        cout << "\n If you want to exit the game, press zero(0), otherwise press any key to continue...";
        if(getch() == '0') break;
    }
    system("cls");
    cout<< "\n  **********  THE END   **********\n";
}

// چه تغییری در برنامه ایجاد کنم تا بتوانم هرسری ابعاد بازی را تغیر دهم؟