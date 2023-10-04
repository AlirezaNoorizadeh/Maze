#include <windows.h>  //GetStdHandle  //setColor
#include <algorithm>  //sort  //min
#include <iostream>   //cin   //cout
#include <conio.h>    //getch
#include <cstdlib>    //rand  //srand
#include <iomanip>    //setw  //left
#include <vector>     //vector
#include <ctime>      //time
using namespace std;

struct User {
    string name="anonymous";
    int score=1000;
    int id=0; 
};

const int WALL = 0;
const int PATH = 1;
const int START = 2;
const int END = 3;
FILE *file;
vector<User> list;

bool compareUsers(User a, User b) {
    if (a.score == b.score) { return a.name < b.name; }
    else { return a.score < b.score; }
}

class Program {
private:
    int** maze;
    int boolian = 1, ROW=14, COL=14, MAX_MOVES = ROW*10, wallColor=12, cursorColor=15, menu;
    int order=-1, startTime=time(0), currentRow=1, currentCol=1, moves=0, lengthTime, endTime;
    string fileName = "scores2.txt", difficultyTypeName = "Normal";

public:
    void mainMenu();
    void Rename();
    void colorSeter();
    void setDifficulty();
    void setColor(int color);
    void generateMaze();
    void printMaze();
    void Moving();
    void mainBasic();
    void fileReader();
    void saveScores();
    void setTypeOfDifficulty();
};

int main() {
    srand(time(NULL));
    Program program;
    program.fileReader();
    program.mainBasic();
    return 0;
}

void Program::Moving(){
    while (maze[currentRow][currentCol] != END) {
        system("cls");
        printMaze();
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
                break;
        }
    }
}

void Program::mainBasic(){
    while(1){
        mainMenu();
        system("cls");
        generateMaze();
        startTime = time(0);
        currentRow = 1;
        currentCol = 1;
        moves = 0;
        Moving();

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

        bool userExists = false;
        for (int i = 0; i < (int)list.size(); i++) {
            if (list[i].name == newUser.name) {
                userExists = true;
                if (newUser.score < list[i].score) {
                    list[i].score = newUser.score;
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
        cout << "\n List of top 3 players in the "<< difficultyTypeName <<" section:" << endl;
        int numPlayers = ((int)list.size() < 3) ? (int)list.size() : 3;
        for (int i = 0; i < numPlayers; i++) {
            cout << left << setw(3) << " " << i+1 << +") " << setw(7) << list[i].name << "    score: " << setw(3) << list[i].score << "  id: " << setw(4) << list[i].id << endl;
        }

        cout << "\n Press any key to return to the menu..." << getch() << fflush(stdin); 
    }
}

void Program::generateMaze() {
    fflush(stdin);
    // Create dynamic 2D array
    maze = new int*[ROW];
    for (int i = 0; i < ROW; i++) {
        maze[i] = new int[COL];
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
                } else if (ROW % 2 == 1 && currentRow > 1 && maze[currentRow - 1][currentCol] == WALL) {
                    maze[currentRow - 1][currentCol] = PATH;
                    currentRow -= 1;
                }
                if((currentRow == ROW-3 && currentCol == COL-3) || (currentCol == ROW-3 && currentRow == COL-3)) {maze[currentRow+1][currentCol]=PATH; boolian=0;}
                break;
            case 1: // Move down
                if (currentRow < ROW - 3 && maze[currentRow + 2][currentCol] == WALL) {
                    maze[currentRow + 1][currentCol] = PATH;
                    maze[currentRow + 2][currentCol] = PATH;
                    currentRow += 2;
                } else if (ROW % 2 == 1 && currentRow < ROW - 2 && maze[currentRow + 1][currentCol] == WALL) {
                    maze[currentRow + 1][currentCol] = PATH;
                    currentRow += 1;
                }
                if((currentRow == ROW-3 && currentCol == COL-3) || (currentCol == ROW-3 && currentRow == COL-3)) {maze[currentRow+1][currentCol]=PATH; boolian=0;}
                break;
            case 2: // Move left
                if (currentCol > 2 && maze[currentRow][currentCol - 2] == WALL) {
                    maze[currentRow][currentCol - 1] = PATH;
                    maze[currentRow][currentCol - 2] = PATH;
                    currentCol -= 2;
                } else if (COL % 2 == 1 && currentCol > 1 && maze[currentRow][currentCol - 1] == WALL) {
                    maze[currentRow][currentCol - 1] = PATH;
                    currentCol -= 1;
                }
                if((currentRow == ROW-3 && currentCol == COL-3) || (currentCol == ROW-3 && currentRow == COL-3)) {maze[currentRow][currentCol+1]=PATH; boolian=0;}
                break;
            case 3: // Move right
                if (currentCol < COL - 3 && maze[currentRow][currentCol + 2] == WALL) {
                    maze[currentRow][currentCol + 1] = PATH;
                    maze[currentRow][currentCol + 2] = PATH;
                    currentCol += 2;
                } else if (COL % 2 == 1 && currentCol < COL - 2 && maze[currentRow][currentCol + 1] == WALL) {
                    maze[currentRow][currentCol + 1] = PATH;
                    currentCol += 1;
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
    while (counter < ROW+5) {
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

void Program::printMaze() {
    fflush(stdin);
    // cout << "Use Q,W,E   ↖↑↗ for move to 8 side\n    A,S,D = ←↓→\n    Z,X,C   ↙↓↘"  << endl << endl;
    cout << "Make sure your keyboard is in English\nUse Q,W,E for move to 8 side\n    A,S,D \n    Z,X,C"  << endl << endl;
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
                        setColor(10);
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
                    default: cout<<"error printMaze"<<endl; break;
                }
            }
        }
        cout << endl;
    }
}



void Program::setDifficulty(){
    fflush(stdin);
    system("cls");
    list.clear();
    cout << "\n Select difficulty: \n" << "  1)Esay\n  2)Normal\n  3)Hard"<<endl;
        int difficulty = getch()-48;
        switch(difficulty){
            case 1: ROW=10; COL=10; fileName = "scores1.txt"; break;
            case 2: ROW=16; COL=16; fileName = "scores2.txt"; break;
            case 3: ROW=20; COL=20; fileName = "scores3.txt"; break;
            default: ROW=15; COL=15; fileName = "scores2.txt"; cout<<"\n The difficulty remained in the default state "<<ROW<<"x"<<COL<<"\n press any key to continue..."; getch(); fflush(stdin); break;
        }
}

void Program::colorSeter(){
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
        setColor(12);
        cout << " This number is not in the range of 1-255\n The cursor color remained in the default state\n Press any key to return to the menu...." ;
        getch();
        cout << endl;
        cursorColor=14;
        setColor(7);
    }
}

void Program::mainMenu(){
    fflush(stdin);
    setColor(7);
    bool main = true;
    while(main){
        fflush(stdin);
        system("cls");
        list.clear();
        fileReader();
        setTypeOfDifficulty();
        cout << "\n menu:\n  1)Play\n  2)Rename\n  3)Difficulty("<< difficultyTypeName <<")\n  4)Set color\n  5)EXIT" <<endl;
        menu = getch()-48;
        switch(menu){
            case 1: main=false; break;
            case 2: fflush(stdin); Rename(); break;
            case 3: fflush(stdin); setDifficulty(); break;
            case 4: fflush(stdin); colorSeter(); break;
            case 5: system("cls"); setColor(13); cout<< "\n ********** THE END **********\n\n"; exit(0); break;
            default: cout<<" this not be valid try 1-5\n press any key to continue..."; getch(); fflush(stdin); break;
        }
    }
}

void Program::Rename(){
    fflush(stdin);
    system("cls");
    cout << "\n List of all players in the "<< difficultyTypeName <<" section:" << endl;
    for (int i = 0; i < (int)list.size(); i++) {
        cout << left << setw(3) << " " << i+1 << +") " << setw(8) << list[i].name << "   score: " << setw(3) << list[i].score << "  id: " << setw(4) << list[i].id << endl;
    }
    string newName,idTemp;
    int id;
    fflush(stdin);
    cout << "\n Enter id: ";
    bool isNumber = true;
    while (isNumber) {
        cin >> idTemp;
        for (char c : idTemp) {
            if (!isdigit(c)) {
                isNumber = false;
                break;
            }
        }

        if (isNumber) {
            id = stoi(idTemp);
            break;
        } else {
            id = 0;
            break;
        }
    }
    cout << " Enter new name: ";
    cin >> newName;
    bool test = true;
    for (int i = 0; i < (int)list.size(); i++) {
        if (list[i].id == id) {
            test = false;
        }
    }
    if(test) { cout<<"\n This ID does not exist \n Press any key to return to the menu...."; getch(); mainMenu();}
    else{ cout<<"\n This ID has been successfully renamed \n Press any key to return to the menu...."; getch(); }

    for (int i = 0; i < (int)list.size(); i++) {
        if (list[i].id == id) {
            list[i].name = newName;
            break;
        }
    }
    saveScores();
}

void Program::fileReader(){
    fflush(stdin);
    // Load scores from file
    file = fopen(fileName.c_str(), "r");
    if (file != NULL) {
        char name[100];
        int score, id;
        while (fscanf(file, "%s %d %d\n", name, &score, &id) == 3) { // be tedad mavared daron tabe ,fscanf adad khoroji meidahad be hamin dalil ba 3 moghayese shode
            User newUser;
            newUser.name = name;
            newUser.score = score;
            newUser.id = id;
            
            list.push_back(newUser);
        }
        fclose(file);
    }
    sort(list.begin(), list.end(), compareUsers);
}

void Program::saveScores(){
    fflush(stdin);
    file = fopen(fileName.c_str(), "w");
    for (int i = 0; i < (int)list.size(); i++) {
        fprintf(file, "%s %d %d\n", list[i].name.c_str(), list[i].score, list[i].id);
    }
    fclose(file);
}

void Program::setColor(int color) {
    fflush(stdin);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

void Program::setTypeOfDifficulty(){
         if (fileName == "scores1.txt"){difficultyTypeName = "Esay";}
    else if (fileName == "scores2.txt"){difficultyTypeName = "Normal";}
    else if (fileName == "scores3.txt"){difficultyTypeName = "Hard";}
}