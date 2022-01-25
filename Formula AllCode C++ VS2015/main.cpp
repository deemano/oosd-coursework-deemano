#include "stdafx.h"
#include "FA_API.h"

#include <conio.h>
#include <iostream>
using namespace std;

#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_LEFT 75
#define KEY_RIGHT 77

int main()
{
	//Assign and open the COM port
	char iPort = 5;
	FA_ComOpen(iPort);
	//Draw a triangle
	//for (int i = 0; i < 3; i++)
	
		/*FA_Forwards(iPort, 1000);
		FA_Left(iPort, 100);
		FA_Forwards(iPort, 200);
		FA_Right(iPort, 100);
		FA_Forwards(iPort, 200);*/
	
	//Close the COM port
	//FA_ComClose(iPort);

    int c = 0;
    while (1)
    {
        c = 0;

        switch ((c = _getch())) {
        case KEY_UP:
            cout << endl << "Up" << endl;//key up
            FA_Forwards(iPort, 500);
            break;
        case KEY_DOWN:
            cout << endl << "Down" << endl;   // key down
            break;
        case KEY_LEFT:
            cout << endl << "Left" << endl;  // key left
            FA_Left(iPort, 10);
            break;
        case KEY_RIGHT:
            cout << endl << "Right" << endl;  // key right
            FA_Right(iPort, 10);
            break;
        default:
            cout << endl << "null" << endl;  // not arrow
            break;
        }

    }
    FA_ComClose(iPort);
	return 0;
}



