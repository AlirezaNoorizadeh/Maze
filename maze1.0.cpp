#include <windows.h>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <conio.h>
#include <algorithm>

using namespace std;

class MazeGame {
public:
    const int ROW = 15;
    const int COL = 15;
    const int WALL = 0;
    const int PATH = 1;
    const int START = 2;
    const int END = 3;
    const int MAX_MOVES = 150;

    int maze[ROW][COL];
    int boolian;
    int currentRow, currentCol, moves;

    MazeGame() {
        srand(time(NULL));
        boolian = 1;
        currentRow = 1;
        currentCol = 1;
        moves = 0;
    }

    void finisher(int currentRow, int currentCol) {
        if (currentRow == ROW - 2 && currentCol == COL - 4) maze[ROW - 2][COL - 3] = PATH;
        else if (currentRow == ROW - 3 && currentCol == COL - 4) maze[ROW - 3][COL - 3] = maze[ROW - 2][COL - 3] = PATH;
        else if (currentRow == ROW - 4 && currentCol == COL - 4) maze[ROW - 3][COL - 4] = maze[ROW - 3][COL - 3] = maze[ROW - 2][COL - 3] = PATH;
        else if (currentRow == ROW - 4 && currentCol == COL - 3) maze[ROW - 3][COL - 3] = maze[ROW - 3][COL - 2] = PATH;
        else if (currentRow == ROW - 4 && currentCol == COL - 2) maze[ROW - 3][COL - 2] = PATH;
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
        maze[ROW - 2][COL - 2] = END;

        // masir = path

        while (boolian == 1) {
            int direction = rand() % 4;
            switch (direction) {
            case 0: // Move up
                if (currentRow > 1 && maze[currentRow - 2][currentCol] == WALL) {
                    maze[currentRow - 1][currentCol] = PATH;
                    maze[currentRow - 2][currentCol] = PATH;
                    currentRow -= 2;
                }
                if (currentRow >= ROW - 4 && currentCol >= COL - 4) finisher(currentRow, currentCol);
                break;
            case 1: // Move down
                if (currentRow < ROW - 2 && maze[currentRow + 2][currentCol] == WALL) {
                    maze[currentRow + 1][currentCol] = PATH;
                    maze[currentRow + 2][currentCol] = PATH;
                    currentRow += 2;
                }
                if (currentRow >= ROW - 4 && currentCol >= COL - 4) finisher(currentRow, currentCol);
                break;
            case 2: // Move left
                if (currentCol > 1 && maze[currentRow][currentCol - 2] == WALL) {
                    maze[currentRow][currentCol - 1] = PATH;
                    maze[currentRow][currentCol - 2] = PATH;
                    currentCol -= 2;
            }
            if (currentRow >= ROW - 4 && currentCol >= COL - 4) finisher(currentRow, currentCol);
            break;
            case 3: // Move right
                if (currentCol < COL - 2 && maze[currentRow][currentCol + 2] == WALL) {
                    maze[currentRow][currentCol + 1] = PATH;
                    maze[currentRow][currentCol + 2] = PATH;
                    currentCol += 2;
                }
                if (currentRow >= ROW - 4 && currentCol >= COL - 4) finisher(currentRow, currentCol);
                break;
            }
        }

        // add extra paths
        for (int i = 0; i < ROW; i++) {
            for (int j = 0; j < COL; j++) {
                int pathCount = 0;
                if (maze[i][j] != WALL) continue;

                if (i > 0 && maze[i - 1][j] == PATH) pathCount++;
                if (j > 0 && maze[i][j - 1] == PATH) pathCount++;
                if (i < ROW - 1 && maze[i + 1][j] == PATH) pathCount++;
                if (j < COL - 1 && maze[i][j + 1] == PATH) pathCount++;

                if (pathCount == 1 && rand() % 100 < 50) maze[i][j] = PATH;
            }
        }
    }

    void printMaze() {
        system("cls");
        for (int i = 0; i < ROW; i++) {
            for (int j = 0; j < COL; j++) {
                switch (maze[i][j]) {
                case WALL:
                    cout << char(219) << char(219);
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
            cout << endl;
        }
    }

    void main() {
        generateMaze();
        printMaze();

        while (1) {
            int key = _getch();
            switch (key) {
            case 72: // Move up
                if (maze[currentRow - 1][currentCol] != WALL) {
                    maze[currentRow][currentCol] = PATH;
                    currentRow--;
                    moves++;
                }
                break;
            case 80: // Move down
                if (maze[currentRow + 1][currentCol] != WALL) {
                    maze[currentRow][currentCol] = PATH;
                    currentRow++;
                    moves++;
                }
                break;
            case 75: // Move left
                if (maze[currentRow][currentCol - 1] != WALL) {
                    maze[currentRow][currentCol] = PATH;
                    currentCol--;
                    moves++;
                }
                break;
            case 77: // Move right
                if (maze[currentRow][currentCol + 1] != WALL) {
                    maze[currentRow][currentCol] = PATH;
                    currentCol++;
                    moves++;
                }
                break;
            default:
                break;
            }

            printMaze();
            if (currentRow == ROW - 2 && currentCol == COL - 2) {
                cout << "Congratulations! You've completed the maze!\n";
                cout << "Number of moves taken: " << moves << endl;
                break;
            }
            if (moves >= MAX_MOVES) {
                cout << "Sorry, you couldn't complete the maze in time.\n";
                break;
            }
        }

        system("pause");
    }
};

int main() {
    MazeGame mazeGame;
    mazeGame.main();
    return 0;
}