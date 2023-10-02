#include <iostream>
#include <conio.h>
#include <ctime>
#include <cstdlib>

using namespace std;

const int MAP_SIZE = 15;

struct Map {
    int path = 0;
};

// Function to initialize game map
void initGameMap(Map (&gameMap)[MAP_SIZE][MAP_SIZE]) {
    for (int i = 0; i < MAP_SIZE; i++) {
        for (int j = 0; j < MAP_SIZE; j++) {
            gameMap[i][j].path = 0;
        }
    }
    gameMap[13][13].path = 3;
    gameMap[1][1].path = 2;
}

// Function to create paths in game map
void createPaths(Map (&gameMap)[MAP_SIZE][MAP_SIZE]) {
    srand(time(0));
    int i = 1, j = 1, counter = 0;
    while (true) {
        // Generate random number between 1 and 4
        int direction = rand() % 4 + 1;

        switch (direction) {
            case 1: // Move up
                i--;
                break;
            case 2: // Move right
                j++;
                break;
            case 3: // Move down
                i++;
                break;
            case 4: // Move left
                j--;
                break;
        }

        // Check boundaries and path types
        if (i <= 0) {
            i++;
        } else if (i >= MAP_SIZE - 1) {
            i--;
        } else if (j <= 0) {
            j++;
        } else if (j >= MAP_SIZE - 1) {
            j--;
        }

        if (gameMap[i][j].path == 3) {
            break; // Exit loop when end point is reached
        } else if (gameMap[i][j].path == 2) {
            continue; // Skip current iteration when start point is reached
        } else {
            gameMap[i][j].path = 1; // Create path in game map
            counter++;
        }

        // Reset game map when path creation takes too long
        if (counter > 60) {
            initGameMap(gameMap);
            i = 1, j = 1;
            counter = 0;
        }
    }

    // Create additional paths in game map
    int k = 2;
    for (int counterT = 0; counterT < 6; counterT++) {
        i = 0;
        while (gameMap[k][i].path != 1) {
            i++;
        }

        j = k;
        counter = 0;
        while (counter < 10) {
            // Generate random number between 1 and 4
            int direction = rand() % 4 + 1;

            switch (direction) {
                case 1: // Move up
                    j--;
                    break;
                case 2: // Move right
                    i++;
                    break;
                case 3: // Move down
                    j++;
                    break;
                case 4: // Move left
                    i--;
                    break;
            }

            // Check boundaries and path types
            if (i < 0 || i >= MAP_SIZE || j < 0 || j >= MAP_SIZE) {
                j = k;
                i = 0;
                while (gameMap[k][i].path != 1) {
                    i++;
                }
            } else if (gameMap[j][i].path != 2) {
                gameMap[j][i].path = 1; // Create path in game map
                counter++;
            }
        }
        k += 2;
    }
}

// Function to display game map on screen
void displayGameMap(Map (&gameMap)[MAP_SIZE][MAP_SIZE], int i, int j) {
    for (int n = 0; n < MAP_SIZE; n++) {
        for (int m = 0; m < MAP_SIZE; m++) {
            if (i == n && j == m) {
                cout << "x ";
            } else {
                cout << gameMap[n][m].path << " ";
            }
        }
        cout << endl;
    }
}

int main() {
    Map gameMap[MAP_SIZE][MAP_SIZE];
    initGameMap(gameMap);
    createPaths(gameMap);
    system("cls");
    int currentLoc = 0;
    int i = 1, j = 1;
    while (currentLoc != 3) {
        displayGameMap(gameMap, i, j);
        int arrowKey = getch();
        switch (arrowKey) {
            case 80: // Arrow keydown
                if (gameMap[i + 1][j].path != 0) {
                i++;
                }
                break;
        case 72: // Arrow key up
                if (gameMap[i - 1][j].path != 0) {
                i--;
                }
                break;
        case 77: // Arrow key right
                if (gameMap[i][j + 1].path != 0) {
                j++;
                }
                break;
        case 75: // Arrow key left
                if (gameMap[i][j - 1].path != 0) {
                j--;
                }
                break;
        }
        currentLoc = gameMap[i][j].path;
        system("cls");
    }
    return 0;
}