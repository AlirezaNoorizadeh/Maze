#include <windows.h> //GetStdHandle  //setColor 
#include <iostream>  //cin  //cout
#include <cstdlib>  //rand //srand 
#include <ctime>  //time 
#include <conio.h>  //getch 
#include <algorithm>  //sort  //min
#include <vector>   //vector
#include <iomanip>  //setw  //left
using namespace std;

struct User {
    string name="anonymous";
    int score=1000;
    int endTime=0;
    int startTime=0;
    int id=0; 
};

const int WALL = 0;
const int PATH = 1;
const int START = 2;
const int END = 3;
int** maze;
int boolian = 1, ROW=14, COL=14, wallColor=12, cursorColor=15, menu;
int order=-1, startTime=time(0), currentRow=1, currentCol=1, moves=0, lengthTime, endTime;
FILE *file;
vector<User> list;

void setColor(int color);
void saveScores();
void fileReader();
void Rename();
void mainMenu();
void colorSeter();
void setDifficulty();
bool compareUsers(User a, User b);
void printMaze(int currentRow, int currentCol,int ROW, int COL, int wallColor, int cursorColor);
void generateMaze(int row, int col);

int main() {
    srand(time(NULL));
    fileReader();
    
    while(1){
        mainMenu();
        system("cls");
        generateMaze(ROW,COL);
        startTime = time(0);
        currentRow = 1;
        currentCol = 1;
        moves = 0;

        while (maze[currentRow][currentCol] != END) {
            system("cls");
            printMaze(currentRow, currentCol, ROW, COL, wallColor, cursorColor);
            char move;
            int arrow_key = getch();
                 if(arrow_key == 'x' || arrow_key == 's' || arrow_key== '2' || arrow_key=='5' || arrow_key == 80) move = 'd';
            else if(arrow_key == 'w' || arrow_key == '8' || arrow_key == 72) move = 'u';
            else if(arrow_key == 'd' || arrow_key == '6' || arrow_key == 77) move = 'r';
            else if(arrow_key == 'a' || arrow_key == '4' || arrow_key == 75) move = 'l';
            else if(arrow_key == 'q' || arrow_key == '7' ) move = 'q'; //u+l
            else if(arrow_key == 'e' || arrow_key == '9' ) move = 'e'; //u+r
            else if(arrow_key == 'z' || arrow_key == '1' ) move = 'z'; //d+l
            else if(arrow_key == 'c' || arrow_key == '3' ) move = 'c'; //d+r
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
        cout << "\n **** You won this game in " << lengthTime << " seconds and with " << moves << " moves! ****\n Press any key to continue..." << getch() << endl;
        fflush(stdin);
        system("cls");
        cout << "\n(Your score = The duration of the game*2 + the number of moves you have made in the game/2)\n Score : " << (lengthTime*2)+(moves/2) <<" \n Name : ";
        
        User newUser;
        fflush(stdin);
        cin >> newUser.name;
        newUser.score=(lengthTime*2)+(moves/2);
        newUser.startTime=startTime;
        newUser.endTime=endTime;

        bool userExists = false;
        for (int i = 0; i < list.size(); i++) {
            if (list[i].name == newUser.name) {
                userExists = true;
                if (newUser.score < list[i].score) {
                    list[i].score = newUser.score;
                    list[i].startTime = newUser.startTime;
                    list[i].endTime = newUser.endTime;
                }
                setColor(2);
                cout << "\n Hi " << list[i].name << " (ID = " << list[i].id << ")" << " your best score is " << list[i].score << " now.\n Press any key to continue..." << endl;
                getch();
                setColor(7);
                newUser.id = list[i].id;
                break;
            }
        }
        if (!userExists) {
            newUser.id=startTime%10000;
            list.push_back(newUser);
        }

        sort(list.begin(), list.end(), compareUsers);
        saveScores();

        system("cls");
        cout << "\n List of top 3 players:" << endl;
        int numPlayers = (list.size() < 3) ? list.size() : 3;
        for (int i = 0; i < numPlayers; i++) {
            cout << left << setw(3) << " " << i+1 << +") " << setw(7) << list[i].name << "    score: " << setw(3) << list[i].score << "  id: " << setw(4) << list[i].id << endl;
        }

        cout << "\n Press any key to return to the menu..." << getch() << fflush(stdin); 
    }
    return 0;
}

void generateMaze(int row, int col) {
    fflush(stdin);
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
    fflush(stdin);
    cout << endl;
    for (int i = 0; i < ROW; i++) {
        cout << "    ";
        for (int j = 0; j < COL; j++) {
            if (i == currentRow && j == currentCol) {
                setColor(cursorColor);
                cout << "X ";
            } else {
                switch(maze[i][j]) {
                    case WALL:
                        if(i == 0 || i == ROW-1 || j == 0 || j == ROW-1){setColor(7); cout << "O ";}
                        else{setColor(wallColor); cout << "# ";}
                        break;
                    case PATH:
                        cout << "  ";
                        break;
                    case START:
                        setColor(10);
                        cout << "S ";
                        break;
                    case END:
                        setColor(2);
                        cout << "E ";
                        break;
                }
            }
        }
        cout << endl;
    }
}

bool compareUsers(User a, User b) {
    if (a.score == b.score) { return a.name < b.name; }
    else { return a.score < b.score; }
}

void setDifficulty(){
    fflush(stdin);
    system("cls");
    cout << "\n Select difficulty: \n" << "  1)Esay\n  2)Medium\n  3)Hard"<<endl;
        int difficulty = getch()-48;
        switch(difficulty){
            case 1: ROW=10; COL=10; break;
            case 2: ROW=16; COL=16; break;
            case 3: ROW=20; COL=20; break;
            default: cout<<"\n The difficulty remained in the default state 14*14\n press any key to continue..."; getch(); break;
        }
}

void colorSeter(){
    fflush(stdin);
    system("cls");
    for (int col_code = 1; col_code < 256; col_code++) {
        setColor(col_code);
        cout << col_code <<" ";
    }
    setColor(7);
    cout << "\n\n  Select Wall Color (a num between 1-255 , ";
    setColor(wallColor);
    cout << "now=" << wallColor ;
    setColor(7); 
    cout<<"): ";
    fflush(stdin);
    cin >> wallColor;
    if(wallColor<1 || wallColor>255){
        setColor(12);
        cout << " This number is not in the range of 1-255\n The wall color remained in the default state\n press any key to continue..." ;
        getch();
        cout << endl;
        wallColor=12;
    }
    setColor(7);
    cout << "  Select Cursor Color (a num between 1-255 , ";
    setColor(cursorColor);
    cout << "now=" << cursorColor ;
    setColor(7); 
    cout<<"): ";
    fflush(stdin);
    cin >> cursorColor;
    if(cursorColor<1 || cursorColor>255){
    // if(!(cursorColor>0 && cursorColor<255)){
        setColor(12);
        cout << " This number is not in the range of 1-255\n The cursor color remained in the default state\n Press any key to return to the menu...." ;
        getch();
        cout << endl;
        cursorColor=14;
        setColor(7);
    }
}

void mainMenu(){
    fflush(stdin);
    setColor(7);
    bool main = true;
    while(main){
        system("cls");
        cout << "\n menu:\n  1)Play\n  2)Rename\n  3)Set Difficulty\n  4)Set color\n  5)EXIT" <<endl;
        menu = getch()-48;
        switch(menu){
            case 1: main=false; break;
            case 2: fflush(stdin); Rename(); break;
            case 3: fflush(stdin); setDifficulty(); break;
            case 4: fflush(stdin); colorSeter(); break;
            case 5: system("cls"); setColor(13); cout<< "\n ********** THE END **********\n\n"; exit(0); break;
            default: cout<<" this not be valid try 1-5\n press any key to continue..."; getch(); break;
        }
    }
}

void Rename(){
    fflush(stdin);
    system("cls");
    cout << "\n List of all players:" << endl;
    for (int i = 0; i < list.size(); i++) {
        cout << left << setw(3) << " " << i+1 << +") " << setw(8) << list[i].name << "   score: " << setw(3) << list[i].score << "  id: " << setw(4) << list[i].id << endl;
    }
    string newName;
    int id;
    fflush(stdin);
    cout << "\n Enter id: ";
    cin >> id;
    cout << " Enter new name: ";
    cin >> newName;
    bool test = true;
    for (int i = 0; i < list.size(); i++) {
        if (list[i].id == id) {
            test = false;
        }
    }
    if(test) { cout<<"\n This ID does not exist \n Press any key to return to the menu...."; getch(); mainMenu();}
    else{ cout<<"\n This ID has been successfully renamed \n Press any key to return to the menu...."; getch(); }

    for (int i = 0; i < list.size(); i++) {
        if (list[i].id == id) {
            list[i].name = newName;
            break;
        }
    }
    saveScores();
    // // Save scores to file
    // file = fopen("scores.txt", "w");
    // if (file == NULL) {
    //     cout << "Error opening file" << endl;
    //     exit(1);
    // }
    // for (int i = 0; i < list.size(); i++) {
    //     fprintf(file, "%s %d %d %d %d\n", list[i].name.c_str(), list[i].score, list[i].startTime, list[i].endTime, list[i].id);
    // }
    // fclose(file);
}


void fileReader(){
    fflush(stdin);
    // Load scores from file
    file = fopen("scores.txt", "r");
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
}
void saveScores(){
    fflush(stdin);
    // Save scores to file
    file = fopen("scores.txt", "w");
    // if (file == NULL) {
    //     cout << "Error opening file" << endl;
    //     exit(1);
    // }
    for (int i = 0; i < list.size(); i++) {
        fprintf(file, "%s %d %d %d %d\n", list[i].name.c_str(), list[i].score, list[i].startTime, list[i].endTime, list[i].id);
    }
    fclose(file);
}

void setColor(int color) {
    fflush(stdin);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}