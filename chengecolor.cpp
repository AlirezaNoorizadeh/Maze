// #include <stdafx.h> // Used with MS Visual Studio Express. Delete line if using something different
#include <conio.h> // Just for WaitKey() routine
#include <iostream>
#include <string>
#include <windows.h>

using namespace std;

HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE); // For use of SetConsoleTextAttribute()

void WaitKey();

int main()
{

    int len = 0,x, y=240; // 240 = white background, black foreground 
    
    string text = "Hello World. I feel pretty today!";
    len = text.length();
    cout << endl << endl << endl << "\t\t"; // start 3 down, 2 tabs, right
    for ( x=0;x<len;x++)
    {
        SetConsoleTextAttribute(console, y); // set color for the next print
        cout << text[x];
        y++; // add 1 to y, for a new color
        if ( y >254) // There are 255 colors. 255 being white on white. Nothing to see. Bypass it
            y=240; // if y > 254, start colors back at white background, black chars
        // Sleep(250); // Pause between letters 
    }

    SetConsoleTextAttribute(console, 15); // set color to black background, white chars
    WaitKey(); // Program over, wait for a keypress to close program
}


void WaitKey()
{
    cout  << endl << endl << endl << "\t\t\tPress any key";
    while (_kbhit()) _getch(); // Empty the input buffer
    _getch(); // Wait for a key
    while (_kbhit()) _getch(); // Empty the input buffer (some keys sends two messages)
}

// // C++ program to illustrate coloring
// #include <iostream>
// #include <conio.h>
// #include <stdlib.h>
// using namespace std;

// // Driver Code
// int main()
// {
//     textcolor(RED);
// cprintf("H");
// textcolor(BLUE);
// cprintf("e");
// 	// B for background Color(Light Aqua)
// 	// 5 for text color(Purple)
// 	system("Color B5");
// 	cout << "Geeks";

// 	// 1 for background Color(Blue)
// 	// 6 for text color(Yellow)
// 	system("Color 16");
// 	cout << " For ";

// 	// D for background Color(Light Purple)
// 	// E for text color(Light Yellow)
// 	system("Color DE");
// 	cout << "Geeks";

// 	return 0;
// }
