#include <iostream>
#include <stack>
#include <cstdlib>
#include <ctime>
#include <vector>
using namespace std;

const int ROW = 15;
const int COL = 15;
const int WALL = 0;
const int PATH = 1;
const int START = 2;
const int END = 3;

int maze[ROW][COL];

struct Cell {
    int row;
    int col;
};

void generateMaze() {
    // Initialize maze with walls
    for (int i = 0; i < ROW; i++) {
        for (int j = 0; j < COL; j++) {
            maze[i][j] = WALL;
        }
    }

    // Set start and end points
    maze[1][1] = START;
    maze[ROW - 2][COL - 2] = END;

    // Generate random path using DFS
    stack<Cell> cellStack;
    Cell currentCell = {1, 1};
    int visitedCells = 1;
    while (visitedCells < ((ROW - 1) / 2) * ((COL - 1) / 2)) {
        // Find all neighbors of current cell with all walls intact
        vector<Cell> neighbors;
        if (currentCell.row > 2 && maze[currentCell.row - 2][currentCell.col] == WALL) {
            neighbors.push_back({currentCell.row - 2, currentCell.col});
        }
        if (currentCell.row < ROW - 3 && maze[currentCell.row + 2][currentCell.col] == WALL) {
            neighbors.push_back({currentCell.row + 2, currentCell.col});
        }
        if (currentCell.col > 2 && maze[currentCell.row][currentCell.col - 2] == WALL) {
            neighbors.push_back({currentCell.row, currentCell.col - 2});
        }
        if (currentCell.col < COL - 3 && maze[currentCell.row][currentCell.col + 2] == WALL) {
            neighbors.push_back({currentCell.row, currentCell.col + 2});
        }

        if (!neighbors.empty()) {
            // Choose one of the neighbors at random
            int randIndex = rand() % neighbors.size();
            Cell chosenNeighbor = neighbors[randIndex];

            // Knock down the wall between the current cell and the chosen neighbor
            if (chosenNeighbor.row == currentCell.row) {
                if (chosenNeighbor.col < currentCell.col) {
                    maze[currentCell.row][currentCell.col - 1] = PATH;
                } else {
                    maze[currentCell.row][currentCell.col + 1] = PATH;
                }
            } else {
                if (chosenNeighbor.row < currentCell.row) {
                    maze[currentCell.row - 1][currentCell.col] = PATH;
                } else {
                    maze[currentCell.row + 1][currentCell.col] = PATH;
                }
            }

            // Push the current cell to the stack
            cellStack.push(currentCell);

            // Make the chosen cell the current cell and mark it as visited
            currentCell = chosenNeighbor;
            maze[currentCell.row][currentCell.col] = PATH;
            visitedCells++;
        } else {
            // Pop a cell from the stack and make it the current cell
            currentCell = cellStack.top();
            cellStack.pop();
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
                        cout << " ";
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
        cout << "Enter a move (u/d/l/r): ";
        cin >> move;

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
    }

    // Player reached the end, game over
    printMaze(currentRow, currentCol);
    cout << "Congratulations, you made it to the end!" << endl;

    return 0;
}
