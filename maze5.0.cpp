#include <iostream>
#include <cstdlib>
#include <ctime>
#include <conio.h>
#include <queue>
using namespace std;

const int ROW = 15;
const int COL = 15;
const int WALL = 0;
const int PATH = 1;
const int START = 2;
const int END = 3;
const int MAX_MOVES = 100;

int maze[ROW][COL];

bool isWall(int row, int col) {
    return (row == 0 || col == 0 || row == ROW-1 || col == COL-1);
}

void generateMaze() {
    // Initialize maze with walls
    for (int i = 0; i < ROW; i++) {
        for (int j = 0; j < COL; j++) {
            maze[i][j] = WALL;
        }
    }

    // Set start and end points
    maze[1][1] = START;
    maze[13][13] = END;

    // Generate random path
    int currentRow = 1;
    int currentCol = 1;
    int moves = 0;
    bool foundPath = false;
    while (!foundPath && moves < MAX_MOVES) {
        // Reset maze
        for (int i = 1; i < ROW - 1; i++) {
            for (int j = 1; j < COL - 1; j++) {
                maze[i][j] = WALL;
            }
        }
        maze[1][1] = START;
        maze[13][13] = END;

        // Generate random path
        currentRow = 1;
        currentCol = 1;
        foundPath = true;
        while ((currentRow != ROW - 2 || currentCol != COL - 2) && moves < MAX_MOVES) {
            int direction = rand() % 4;
            switch(direction) {
                case 0: // Move up
                    if (currentRow > 1 && maze[currentRow - 2][currentCol] == WALL) {
                        maze[currentRow - 1][currentCol] = PATH;
                        maze[currentRow - 2][currentCol] = PATH;
                        currentRow -= 2;
                    }
                    break;
                case 1: // Move down
                    if (currentRow < ROW - 2 && maze[currentRow + 2][currentCol] == WALL) {
                        maze[currentRow + 1][currentCol] = PATH;
                        maze[currentRow + 2][currentCol] = PATH;
                        currentRow += 2;
                    }
                    break;
                case 2: // Move left
                    if (currentCol > 1 && maze[currentRow][currentCol - 2] == WALL) {
                        maze[currentRow][currentCol - 1] = PATH;
                        maze[currentRow][currentCol - 2] = PATH;
                        currentCol -= 2;
                    }
                    break;
                case 3: // Move right
                    if (currentCol < COL - 2 && maze[currentRow][currentCol + 2] == WALL) {
                        maze[currentRow][currentCol + 1] = PATH;
                        maze[currentRow][currentCol + 2] = PATH;
                        currentCol += 2;
                    }
                    break;
            }
            moves++;
        }

        // Check if a path from start to end exists
        bool visited[ROW][COL];
        for (int i = 0; i < ROW; i++) {
            for (int j = 0; j < COL; j++) {
                visited[i][j] = false;
            }
        }
        queue<pair<int, int>> q;
        q.push({1, 1});
        visited[1][1] = true;
        while (!q.empty()) {
            pair<int, int> current = q.front();
            q.pop();
            int row = current.first;
            int col = current.second;
            if (row == ROW - 2 && col == COL - 2) {
                break;
            }
            if (row > 1 && visited[row - 1][col] == false && maze[row - 1][col] != WALL) {
                q.push({row - 1, col});
                visited[row - 1][col] = true;
            }
            if (row < ROW - 2 && visited[row + 1][col] == false && maze[row + 1][col] != WALL) {
                q.push({row + 1, col});
                // visited[row +1, col});
visited[row + 1][col] = true;
}
if (col > 1 && visited[row][col - 1] == false && maze[row][col - 1] != WALL) {
q.push({row, col - 1});
visited[row][col - 1] = true;
}
if (col < COL - 2 && visited[row][col + 1] == false && maze[row][col + 1] != WALL) {
q.push({row, col + 1});
visited[row][col + 1] = true;
}
}
foundPath = visited[ROW - 2][COL - 2];
}

if (!foundPath) {
    cout << "Failed to generate a valid path!" << endl;
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
generateMaze();

int currentRow = 1;
int currentCol = 1;

while (maze[currentRow][currentCol] != END) {
    system("cls");
    printMaze(currentRow, currentCol);

    char move;
    // cout << "Enter a move (u/d/l/r): ";
    int arrow_key = getch();
    if(arrow_key == 80) move = 'd';
    else if(arrow_key == 72) move = 'u';
    else if(arrow_key == 77) move = 'r';
    else if(arrow_key == 75) move = 'l';
    // cin >> move;

    switch(move) {
        case 'u':
            if (currentRow > 1 && maze[currentRow - 1][currentCol] != WALL) {
                currentRow--;
            }
            break;
        case 'd':
            if (currentRow < ROW - 2 && maze[currentRow + 1][currentCol] != WALL) {
                currentRow++;
            }
            break;
        case 'l':
            if (currentCol > 1 && maze[currentRow][currentCol - 1] != WALL) {
                currentCol--;
            }
            break;
        case 'r':
            if (currentCol < COL - 2 && maze[currentRow][currentCol + 1] != WALL) {
                currentCol++;
            }
            break;
        default:
            cout << "Invalid move. Try again." << endl;
        continue;
    }

    if (isWall(currentRow, currentCol)) {
        // Player hit a wall, reset maze
        cout << "You hit a wall! Maze reset." << endl;
        generateMaze();
        currentRow = 1;
        currentCol = 1;
    }
}
// Player reached the end, game over
printMaze(currentRow, currentCol);
cout << "Congratulations, you made it to the end!" << endl;

return 0;
}