#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

const int ROWS = 15;
const int COLS = 15;
int maze[ROWS][COLS];

// Function to generate the maze
void generateMaze() {
    // Initialize the maze with walls and paths
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            if (i == 0 || i == ROWS - 1 || j == 0 || j == COLS - 1) {
                maze[i][j] = 0;
            } else {
                maze[i][j] = 1;
            }
        }
    }
    // Set the start and end points
    maze[1][1] = 2;
    maze[13][13] = 3;

    // Use a random walk to generate the maze
    int x = 1;
    int y = 1;
    while (x != 13 || y != 13) {
        int direction = rand() % 4;
        if (direction == 0 && x > 1) {
            x--;
        } else if (direction == 1 && x < ROWS - 2) {
            x++;
        } else if (direction == 2 && y > 1) {
            y--;
        } else if (direction == 3 && y < COLS - 2) {
            y++;
        }
        if (maze[x][y] == 3) {
            break;
        } else if (maze[x][y] == 1) {
            maze[x][y] = 0;
        }
    }
}

// Function to print the maze
void printMaze(int playerX, int playerY) {
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            if (i == playerX && j == playerY) {
                cout << "x ";
            } else if (maze[i][j] == 0) {
                cout << "# ";
            } else if (maze[i][j] == 2) {
                cout << "S ";
            } else if (maze[i][j] == 3) {
                cout << "E ";
            } else {
                cout << "@ ";
            }
        }
        cout << endl;
    }
}

int main() {
    srand(time(0));
    generateMaze();
    int playerX = 1;
    int playerY = 1;
    while (playerX != 13 || playerY != 13) {
        printMaze(playerX, playerY);
        char move;
        cin >> move;
        if (move == 'w' && playerX > 1 && maze[playerX -1][playerY]!=0){
            playerX--;
        } else if(move=='s'&&playerX<ROWS-2&&maze[playerX+1][playerY]!=0){
            playerX++;
        } else if(move=='a'&&playerY>1&&maze[playerX][playerY-1]!=0){
            playerY--;
        } else if(move=='d'&&playerY<COLS-2&&maze[playerX][playerY+1]!=0){
            playerY++;
        }
    }
    printMaze(playerX,playerY);
    cout<<"You won!"<<endl;
}
