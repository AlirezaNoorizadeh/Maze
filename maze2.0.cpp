#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

const int ROWS = 15;
const int COLS = 15;
const int WALL = 0;
const int PATH = 1;
const int START = 2;
const int END = 3;
const int PLAYER = 4;

int maze[ROWS][COLS];
int playerRow, playerCol;

void generateMaze() {
    // Initialize maze with walls
    for (int row = 0; row < ROWS; row++) {
        for (int col = 0; col < COLS; col++) {
            maze[row][col] = WALL;
        }
    }

    // Set start and end points
    maze[0][0] = START;
    maze[ROWS - 1][COLS - 1] = END;

    // Generate random walk
    srand(time(0));
    int row = 0;
    int col = 0;
    while (row != ROWS - 1 || col != COLS - 1) {
        maze[row][col] = PATH;
        int direction = rand() % 4;
        switch (direction) {
            case 0: // Up
                if (row > 0) row--;
                break;
            case 1: // Down
                if (row < ROWS - 1) row++;
                break;
            case 2: // Left
                if (col > 0) col--;
                break;
            case 3: // Right
                if (col < COLS - 1) col++;
                break;
        }
    }

    // Set player position to start
    playerRow = 0;
    playerCol = 0;
}

void printMaze() {
    for (int row = 0; row < ROWS; row++) {
        for (int col = 0; col < COLS; col++) {
            if (row == playerRow && col == playerCol) {
                cout << 'x';
            } else {
                switch (maze[row][col]) {
                    case WALL:
                        cout << ' ';
                        break;
                    case PATH:
                        cout << '.';
                        break;
                    case START:
                        cout << 'S';
                        break;
                    case END:
                        cout << 'E';
                        break;
                }
            }
        }
        cout << endl;
    }
}

void movePlayer(int dRow, int dCol) {
    int newRow = playerRow + dRow;
    int newCol = playerCol + dCol;

    if (newRow >= 0 && newRow < ROWS && newCol >= 0 && newCol < COLS && maze[newRow][newCol] != WALL) {
        playerRow = newRow;
        playerCol = newCol;
    }
}

int main() {
    generateMaze();
    while (maze[playerRow][playerCol] != END) {
        printMaze();
        char input;
        cin >> input;

        switch (input) {
            case 'w':
                movePlayer(-1, 0);
                break;
            case 's':
                movePlayer(1, 0);
                break;
            case 'a':
                movePlayer(0, -1);
                break;
            case 'd':
                movePlayer(0, 1);
                break;
        }
    }

    cout << "You win!" << endl;

    return 0;
}
