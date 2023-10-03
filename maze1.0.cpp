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
const int MAX_MOVES = 1000;

int maze[ROW][COL];

bool dfs(int row, int col) {
    if (row < 0 || row >= ROW || col < 0 || col >= COL || maze[row][col] == WALL) {
        return false;
    }
    if (maze[row][col] == END) {
        return true;
    }
    maze[row][col] = WALL; // Mark as visited
    bool result = dfs(row - 1, col) || dfs(row + 1, col) || dfs(row, col - 1) || dfs(row, col + 1);
    maze[row][col] = PATH; // Unmark as visited
    return result;
}

int boolian = 1;

void finisher(int currentRow, int currentCol){
            if(currentRow == 13 && currentCol == 11)    maze[13][12] = PATH;
    else if(currentRow == 12 && currentCol == 11)    maze[12][12] = maze[13][12] = PATH;
    else if(currentRow == 11 && currentCol == 11)    maze[12][11] = maze[12][12] = maze[13][12] = PATH;
    else if(currentRow == 11 && currentCol == 12)    maze[12][12] = maze[12][13] = PATH;
    else if(currentRow == 11 && currentCol == 13)    maze[12][13] = PATH;
    boolian = 0;
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
    int currentRow = 1; //radis
    int currentCol = 1; //soton
    int moves = 0;
    
    while ( (currentRow != ROW - 2 || currentCol != COL - 2) && moves < MAX_MOVES && boolian == 0) {
        int direction = rand() % 4;
        switch(direction) {
            case 0: // Move up
                if (currentRow > 1 && maze[currentRow - 2][currentCol] == WALL) {
                    maze[currentRow - 1][currentCol] = PATH;
                    maze[currentRow - 2][currentCol] = PATH;
                    currentRow -= 2;
                }
                if(currentRow >= 11 || currentCol >= 11){
                    finisher(currentRow,currentCol) ;  
                }
                break;
            case 1: // Move down
                if (currentRow < ROW - 2 && maze[currentRow + 2][currentCol] == WALL) {
                    maze[currentRow + 1][currentCol] = PATH;
                    maze[currentRow + 2][currentCol] = PATH;
                    currentRow += 2;
                }
                if(currentRow >= 11 || currentCol >= 11){
                    finisher(currentRow,currentCol) ;  
                }
                break;
            case 2: // Move left
                if (currentCol > 1 && maze[currentRow][currentCol - 2] == WALL) {
                    maze[currentRow][currentCol - 1] = PATH;
                    maze[currentRow][currentCol - 2] = PATH;
                    currentCol -= 2;
                }
                if(currentRow >= 11 || currentCol >= 11){
                    finisher(currentRow,currentCol) ;  
                }
                break;
            case 3: // Move right
                if (currentCol < COL - 2 && maze[currentRow][currentCol + 2] == WALL) {
                    maze[currentRow][currentCol + 1] = PATH;
                    maze[currentRow][currentCol + 2] = PATH;
                    currentCol += 2;
                }
                if(currentRow >= 11 || currentCol >= 11){
                    finisher(currentRow,currentCol) ;  
                }
                break;
        }
        moves++;
        // if(moves < MAX_MOVES){
        //     generateMaze();
        // }
    }    

    // while(1){
    //     int direct = rand() % 4;

    // }
    // while(1){
    //     // int direct = rand() % 4;
    //     int temp=(rand())%4+1; 

    //     if(temp==1) currentCol--; // حرکت به بالا
    //     else if(temp==2) currentRow++; // حرکت به راست
    //     else if(temp==3) currentCol++; // حرکت به پایین
    //     else if(temp==4) currentRow--; // حرکت به چپ

    //     // بررسی اینکه آیا خارج از محدوده نقشه رفته‌ایم یا نه و در صورت لزوم، بازگشت به محدوده مناسب
    //     if(currentCol==0) currentCol++;
    //     else if(currentCol==14) currentCol--;
    //     else if(currentRow==0) currentRow++;
    //     else if(currentRow==14) currentRow--;

    //     if(maze[currentCol][currentRow] == 3) break; // اگر به سوراخ بزرگ رسیدیم، حلقه while را قطع کن
    //     if(maze[currentCol][currentRow] == 2) continue; // اگر به نقطه شروع رسیدیم، هیچ کاری نکن و ادامه بده

    //     maze[currentCol][currentRow] = 1; // اگر به خانه‌ جدید رسیدیم، آن را به عنوان مسیر نشان بده
    //     moves++;

    //     if(moves > 60){ // اگر تعداد تلاش‌ها بیشتر از ۶۰ شد، نقشه را صفر کن و از اول شروع کن 
    //         for(int i = 0; i < 15; i++){
    //             for(int j = 0; j < 15; j++){
    //                 maze[i][j] = 0;
    //             }
    //         }
    //         maze[13][13] = 3;
    //         maze[1][1] = 2;

    //         currentRow = 1, currentCol = 1;
    //         moves = 0;
    //     }
    // }

    // while (/*maze[currentRow][currentCol] != 3*/ (currentRow != ROW - 2 || currentCol != COL - 2) && moves < MAX_MOVES) {
    // // while (maze[currentRow][currentCol] != END) {
    //     int direction = rand() % 4;
    //     switch(direction) {
    //         case 0: // Move up
    //             if (currentRow > 1 && maze[currentRow - 2][currentCol] == WALL) {
    //                 maze[currentRow - 1][currentCol] = PATH;
    //                 // maze[currentRow - 2][currentCol] = PATH;
    //                 // currentRow -= 2;
    //                 currentRow -= 1;
    //             }
    //             break;
    //         case 1: // Move down
    //             if (currentRow < ROW - 2 && maze[currentRow + 2][currentCol] == WALL) {
    //                 maze[currentRow + 1][currentCol] = PATH;
    //                 // maze[currentRow + 2][currentCol] = PATH;
    //                 // currentRow += 2;
    //                 currentRow += 1;
    //             }
    //             break;
    //         case 2: // Move left
    //             if (currentCol > 1 && maze[currentRow][currentCol - 2] == WALL) {
    //                 maze[currentRow][currentCol - 1] = PATH;
    //                 // maze[currentRow][currentCol - 2] = PATH;
    //                 // currentCol -= 2;
    //                 currentCol -= 1;
    //             }
    //             break;
    //         case 3: // Move right
    //             if (currentCol < COL - 2 && maze[currentRow][currentCol + 2] == WALL) {
    //                 maze[currentRow][currentCol + 1] = PATH;
    //                 // maze[currentRow][currentCol + 2] = PATH;
    //                 // currentCol += 2;
    //                 currentCol += 1;
    //             }
    //             break;
    //     }
    //     moves++;
    //     // if(moves < MAX_MOVES){
    //     //     generateMaze();
    //     // }
    // }
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

bool isWall(int row, int col) {
    return (row == 0 || col == 0 || row == ROW-1 || col == COL-1);
}

int main() {
    srand(time(NULL));
    generateMaze();
    
    while(!dfs(1,1)){
        generateMaze();
    }
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