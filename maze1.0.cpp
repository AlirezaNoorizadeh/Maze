#include <windows.h>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <conio.h>
#include <algorithm>
#include <vector>
#include <cstdlib>
using namespace std;

const int WALL = 0;
const int PATH = 1;
const int START = 2;
const int END = 3;
int** maze;
int boolian = 1;

void generateMaze(int row, int col) {
    int ROW = row;
    int COL = col;
    int MAX_MOVES = row*10;
    // Create dynamic 2D array
    maze = new int*[row];
    for (int i = 0; i < row; i++) {
        maze[i] = new int[col];
    }
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
                break;
            case 1: // Move down
                if (currentRow < ROW - 3 && maze[currentRow + 2][currentCol] == WALL) {
                    maze[currentRow + 1][currentCol] = PATH;
                    maze[currentRow + 2][currentCol] = PATH;
                    currentRow += 2;
                }
                if((currentRow == ROW-3 && currentCol == COL-3) || (currentCol == ROW-3 && currentRow == COL-3)) {maze[currentRow+1][currentCol]=PATH; boolian=0;}
                break;
            case 2: // Move left
                if (currentCol > 2 && maze[currentRow][currentCol - 2] == WALL) {
                    maze[currentRow][currentCol - 1] = PATH;
                    maze[currentRow][currentCol - 2] = PATH;
                    currentCol -= 2;
                }
                if((currentRow == ROW-3 && currentCol == COL-3) || (currentCol == ROW-3 && currentRow == COL-3)) {maze[currentRow][currentCol+1]=PATH; boolian=0;}
                break;
            case 3: // Move right
                if (currentCol < COL - 3 && maze[currentRow][currentCol + 2] == WALL) {
                    maze[currentRow][currentCol + 1] = PATH;
                    maze[currentRow][currentCol + 2] = PATH;
                    currentCol += 2;
                }
                if((currentRow == ROW-3 && currentCol == COL-3) || (currentCol == ROW-3 && currentRow == COL-3)) {maze[currentRow][currentCol+1]=PATH; boolian=0;}
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

void printMaze(int currentRow, int currentCol,int ROW, int COL, int wallColor, int cursorColor) {
    HANDLE col = GetStdHandle(STD_OUTPUT_HANDLE);
    cout << endl;
    for (int i = 0; i < ROW; i++) {
        cout << "    ";
        for (int j = 0; j < COL; j++) {
            if (i == currentRow && j == currentCol) {
                SetConsoleTextAttribute(col, cursorColor);
                cout << "X ";
            } else {
                switch(maze[i][j]) {
                    case WALL:
                        if(i == 0 || i == ROW-1 || j == 0 || j == ROW-1){SetConsoleTextAttribute(col, 7); cout << "O ";}
                        else{SetConsoleTextAttribute(col, wallColor); cout << "# ";}
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
    int endTime=0;
    int startTime=0;
    int id=0; 
};

bool compareUsers(User a, User b) {
    if (a.score == b.score) { return a.name < b.name; }
    else { return a.score < b.score; }
}

int main() {
    srand(time(NULL));
    vector<User> list;
    int order=-1, startTime=time(0), currentRow=1, currentCol=1, moves=0, lengthTime, endTime;
    char move;
    int menu;
    int ROW=14;
    int COL=14;
    cout << "Select difficulty: \n" << " 1) esay\n 2) medium\n 3) hard"<<endl;
    int difficulty = getch()-48;
    switch(difficulty){
        case 1: ROW=10; COL=10; break;
        case 2: ROW=16; COL=16; break;
        case 3: ROW=20; COL=20; break;
        default: cout<<"set difficul 14*14"; break;
    }
    int wallColor=12;
    int cursorColor=15;
    cout << "Select Color: \n" << " 1) Wall Color (a num between 1-15 , now=12):" ;
    cin >> wallColor;
    cout << " 2) Cursor Color (a num between 1-15 , now=15):" ;
    cin >> cursorColor;

    // Load scores from file
    FILE *file = fopen("scores.txt", "r");
    if (file != NULL) {
        char name[100];
        int score, startTime, endTime, id;
        while (fscanf(file, "%s %d %d %d %d\n", name, &score, &startTime, &endTime, &id) == 5) {
            User newUser;
            newUser.name = name;
            newUser.score = score;
            newUser.startTime = startTime;
            newUser.endTime = endTime;
            newUser.id = id;
            
            list.push_back(newUser);
        }

        fclose(file);
    }

    while(1){
        system("cls");
        generateMaze(ROW,COL);
        startTime = time(0);
        currentRow = 1;
        currentCol = 1;
        moves = 0;

        while (maze[currentRow][currentCol] != END) {
            system("cls");
            printMaze(currentRow, currentCol, ROW, COL, wallColor, cursorColor);
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

        endTime = time(0);
        lengthTime = endTime - startTime;
        system("cls");
        cout << "\n **** You won this game in " << lengthTime << " seconds and with " << moves << " moves! ****" << "\n Press any key to continue..." << getch() <<endl;
        fflush(stdin);
        system("cls");
        cout << "\n Score : " << lengthTime <<"\n Name : ";
        
        User newUser;
        cin >> newUser.name;
        newUser.score=lengthTime;
        newUser.startTime=startTime;
        newUser.endTime=endTime;
        newUser.id=startTime%10000;
        

        list.push_back(newUser);

        sort(list.begin(), list.end(), compareUsers);

        // Save scores to file
        file = fopen("scores.txt", "w");
        if (file == NULL) {
            cout << "Error opening file" << endl;
            exit(1);
        }

        for (int i = 0; i < list.size(); i++) {
            fprintf(file, "%s %d %d %d %d\n", list[i].name.c_str(), list[i].score, list[i].startTime, list[i].endTime, list[i].id);
        }

        fclose(file);

        system("cls");
        cout << "\n List of top 3 players:" << endl;
        for (int i = 0; i < min(3, (int)list.size()); i++) {
            cout << " " << i+1 << ") " << list[i].name << ": " << list[i].score << "    id: " << list[i].id << endl;;
        }
        
        string newName;
        cout << "\n If you want to exit the game, press zero(0), otherwise press any key to continue...";
        cout << "\n menu:\n 1)continue\n 2)rename whit id\n 3)EXIT";
        menu = getch()-48;
        switch(menu){
            case 1: break;
            case 2:
                int id;
                cout << "\n Enter id: ";
                cin >> id;
                cout << " Enter new name: ";
                cin >> newName;

                for (int i = 0; i < list.size(); i++) {
                    if (list[i].id == id) {
                        list[i].name = newName;
                        break;
                    }
                }

                // Save scores to file
                file = fopen("scores.txt", "w");
                if (file == NULL) {
                    cout << "Error opening file" << endl;
                    exit(1);
                }

                for (int i = 0; i < list.size(); i++) {
                    fprintf(file, "%s %d %d %d %d\n", list[i].name.c_str(), list[i].score, list[i].startTime, list[i].endTime, list[i].id);
                }

                fclose(file);
                break;

            case 3: system("cls"); cout<< "\n ********** THE END **********\n\n"; exit(0); break;
            default: cout<<"set difficul num 3 and Exit"; exit(0); break;
        }

    }
    return 0;
}