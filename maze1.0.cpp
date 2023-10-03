#include <iostream>
#include <cstdlib>
#include <ctime>
#include <conio.h>
using namespace std;

const int ROW = 15;
const int COL = 15;
const int WALL = 0;
const int PATH = 1;
const int START = 2;
const int END = 3;
const int MAX_MOVES = 150;

int maze[ROW][COL];

int boolian = 1;

// void finisher(int currentRow, int currentCol){
//          if(currentRow == 13 && currentCol == 11)    maze[13][12] = PATH;
//     else if(currentRow == 12 && currentCol == 11)    maze[12][12] = maze[13][12] = PATH;
//     else if(currentRow == 11 && currentCol == 11)    maze[12][11] = maze[12][12] = maze[13][12] = PATH;
//     else if(currentRow == 11 && currentCol == 12)    maze[12][12] = maze[12][13] = PATH;
//     else if(currentRow == 11 && currentCol == 13)    maze[12][13] = PATH;
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

    maze[1][1] = START;
    maze[13][13] = END;

    // masir = path
    int currentRow = 1; //radif
    int currentCol = 1; //soton
    int moves = 0;

    while (boolian == 1) {
        int direction = rand() % 4;
        switch(direction) {
            case 0: // Move up
                if (currentRow > 1 && maze[currentRow - 2][currentCol] == WALL) {
                    maze[currentRow - 1][currentCol] = PATH;
                    maze[currentRow - 2][currentCol] = PATH;
                    currentRow -= 2;
                }
                // if(currentRow >= 11 && currentCol >= 11){
                //     finisher(currentRow,currentCol) ;  
                // }
                if(currentRow >= ROW-4 && currentCol >= COL-4){
                    finisher(currentRow,currentCol) ;
                }
                break;
            case 1: // Move down
                if (currentRow < ROW - 2 && maze[currentRow + 2][currentCol] == WALL) {
                    maze[currentRow + 1][currentCol] = PATH;
                    maze[currentRow + 2][currentCol] = PATH;
                    currentRow += 2;
                }
                if(currentRow >= ROW - 4 && currentCol >= COL-4){
                    finisher(currentRow,currentCol) ;
                }
                break;
            case 2: // Move left
                if (currentCol > 1 && maze[currentRow][currentCol - 2] == WALL) {
                    maze[currentRow][currentCol - 1] = PATH;
                    maze[currentRow][currentCol - 2] = PATH;
                    currentCol -= 2;
                }
                if(currentRow >= ROW-4 && currentCol >= COL-4){
                    finisher(currentRow,currentCol) ;
                }
                break;
            case 3: // Move right
                if (currentCol < COL - 2 && maze[currentRow][currentCol + 2] == WALL) {
                    maze[currentRow][currentCol + 1] = PATH;
                    maze[currentRow][currentCol + 2] = PATH;
                    currentCol += 2;
                }
                if(currentRow >= ROW-4 && currentCol >= COL-4){
                    finisher(currentRow,currentCol) ;
                }
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
            maze[13][13] = END;
            currentRow = 1; //radif
            currentCol = 1; //soton
            moves = 0;
        }
    }
}

void printMaze(int currentRow, int currentCol) {
    for (int i = 0; i < ROW; i++) {
        for (int j = 0; j < COL; j++) {
            if (i == currentRow && j == currentCol) {
                cout << "x ";
            } else {
                switch(maze[i][j]) {
                    case WALL:
                        cout << "# ";
                        break;
                    case PATH:
                        cout << "  ";
                        break;
                    case START:
                        cout << "S ";
                        break;
                    case END:
                        cout << "E ";
                        break;
                }
            }
        }
        cout << endl;
    }
}

int main() {
    srand(time(NULL));
    // cout << time(0) << endl;
    // cout << time(NULL) << endl;
    generateMaze();
    int startTime = time(0);
    int currentRow = 1;
    int currentCol = 1;
    int moves =0;

    while (maze[currentRow][currentCol] != END) {
        system("cls");
        printMaze(currentRow, currentCol);
        
        char move;
        int arrow_key = getch();
             if(arrow_key == 80 || arrow_key == 's') move = 'd';
        else if(arrow_key == 72 || arrow_key == 'w') move = 'u';
        else if(arrow_key == 77 || arrow_key == 'd') move = 'r';
        else if(arrow_key == 75 || arrow_key == 'a') move = 'l';

        switch(move) {
            case 'u':
                if (currentRow > 1 && maze[currentRow - 1][currentCol] != WALL) {
                    currentRow--;
                    moves++;
                }
                break;
            case 'd':
                if (currentRow < ROW - 2 && maze[currentRow + 1][currentCol] != WALL) {
                    currentRow++;
                    moves++;
                }
                break;
            case 'l':
                if (currentCol > 1 && maze[currentRow][currentCol - 1] != WALL) {
                    currentCol--;
                    moves++;
                }
                break;
            case 'r':
                if (currentCol < COL - 2 && maze[currentRow][currentCol + 1] != WALL) {
                    currentCol++;
                    moves++;
                }
                break;
            default:
                cout << "Invalid move. Try again." << endl;
            continue;
        }
    }
    int endTime = time(0) - startTime;
    printMaze(currentRow, currentCol);
    cout << "\n**** You won this game in " << endTime << " seconds and with " << moves << " moves! ****" << endl;

    return 0;
}