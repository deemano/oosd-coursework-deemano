/*  // ==================================================================== \\
   ||                                                                        ||
   ||  Console app to control Formula Allcode robot-rover, model RB4420      ||
   ||  This is the LIGHT version, without the rover pre-defined commands     ||
   ||  Date: 5th Feb 2022. © Denis Manolescu, Liverpool Hope University      ||
   ||                                                                        ||
    \\ ==================================================================== //
 */
#include "stdafx.h"
#include "FA_API.h"
#include <iostream>
#include <windows.h>
#include <conio.h>


using namespace std;
// define symbolic constant names & hexadecimal values to identify keypresses

#define VK_KEY_W	0x57                //('W')	W  forward
#define VK_KEY_A	0x41                //('A')	A  left
#define VK_KEY_D	0x44                //('D')	D  right
#define VK_KEY_S	0x53                //('S')	S  backward
#define VK_KEY_Q	0x51                //('Q')	Q  cancel reverse keys

class DeviceOne {
public:
    // Member to use later to link to GUI

    void forward() {};
    void backward() {};
    void left() {};
    void right() {};
    void reverse() {};
    void cancel_reverse() {};
    char comPort_dvc1 = 5; // Device COM port
};

class MovementKeys {
    // member variables:
private:
    // keeping reference to deviceOne instead of copy; 
    // main() has to make sure deviceOne object out-lives MovementKeys object
    DeviceOne& deviceOne;
    int key_forward, key_backward, key_left, key_right, key_reverse, cancel_reverse;

public:
    char iPort = deviceOne.comPort_dvc1;
    int reset = 0;
    int reverse = 0;
    // constructor, which only sets deviceOne and keeps the keys name at their Default
    // deviceOne must be initialized before constructor function body
    // as references have no default value

    MovementKeys(DeviceOne& gr) : deviceOne(gr)
    { // Default list:

        key_forward     = VK_UP;
        key_backward    = VK_DOWN;
        key_left        = VK_LEFT;
        key_right       = VK_RIGHT;
        key_reverse     = VK_RSHIFT;
        cancel_reverse  = VK_BACK;
        int reverse = 0;
        /*string name;
        int comPort;*/
    }

    // loop to define rules of the keys pressed commands
    void definedCommand()
    {
        //FA_ComOpen(iPort);
        while (true && reset < 2)
        {
            // Forwards driving
            if (GetAsyncKeyState(key_forward) < 0)
            {
                cout << ("forward\n");
                FA_SetMotors(iPort, 30, 30);
                if (GetAsyncKeyState(key_forward) == 0)
                {
                    cout << ("Forwards stopped. \n");
                    FA_SetMotors(iPort, 0, 0);
                }
            }
            // Backwards driving
            if (GetAsyncKeyState(key_backward) < 0)
            {
                cout << ("backwards\n");
                FA_SetMotors(iPort, -30, -30);
                if (GetAsyncKeyState(key_backward) == 0)
                {
                    cout << ("Backwards stopped. \n");
                    FA_SetMotors(iPort, 0, 0);
                }
            }
            //====================================================
            // programming LEFT & RIGHT keys to perfom 2 actions 
            // Forward-Left or Forward-Right and Backwards-Left or Backwards-Right
            if (GetAsyncKeyState(key_reverse) < 0) { reverse = 1; }
            if (reverse == 0) {
                // Forwards-Left driving
                if (GetAsyncKeyState(key_left) < 0)
                {
                    cout << ("Forwards left.\n");
                    FA_SetMotors(iPort, 5, 30);
                    if (GetAsyncKeyState(key_left) == 0)
                    {
                        cout << ("Forwards left stopped. \n");
                        FA_SetMotors(iPort, 0, 0);
                    }
                }
                // Forwards-Right driving
                if (GetAsyncKeyState(key_right) < 0)
                {
                    cout << ("Forwards right.\n");
                    FA_SetMotors(iPort, 30, 5);
                    if (GetAsyncKeyState(key_right) == 0)
                    {
                        cout << ("Forwards right stopped. \n");
                        FA_SetMotors(iPort, 0, 0);
                    }
                }
            }
            if (reverse == 1) {
                // Backwards-Left driving
                if (GetAsyncKeyState(key_left) < 0)
                {
                    cout << ("back left\n");
                    FA_SetMotors(iPort, -5, -30);
                    if (GetAsyncKeyState(key_left) == 0)
                    {
                        cout << ("Back left stopped. \n");
                        FA_SetMotors(iPort, 0, 0);
                    }
                }
                if (GetAsyncKeyState(key_right) < 0)
                {
                    cout << ("backwards right\n");
                    // Backwards-Right driving
                    if (GetAsyncKeyState(key_right) < 0)
                    {
                        cout << ("Back right\n");
                        FA_SetMotors(iPort, -30, -5);
                        if (GetAsyncKeyState(key_right) == 0)
                        {
                            cout << ("Back right stopped. \n");
                            FA_SetMotors(iPort, 0, 0);
                        }
                    }
                }
            }
            if (GetAsyncKeyState(cancel_reverse) < 0) { reverse = 0; }
            // ====================================================
            // OPTIONAL change keys from within loop with ths code:
            // key_forward = VK_KEY_W; key_backward = VK_KEY_S; key_left = VK_KEY_A; key_right = VK_KEY_D;
            if (GetAsyncKeyState(VK_LCONTROL) < 0 && reset == 0) {
                cout << ("Main control changed to W - A - S - D letters.\n");
                reset++;
                break;
            }
            if (GetAsyncKeyState(VK_RCONTROL) < 0 && reset == 1) {
                cout << ("Main control reset to default - Arrow Keys.\n");
                reset--;
                break;
            }
            // define Honk
            if (GetAsyncKeyState(VK_TAB) < 0) {
                if (GetAsyncKeyState(VK_TAB) < 0) {
                    FA_PlayNote(iPort, 50, 280);
                    FA_PlayNote(iPort, 50, 286);
                    Sleep(3000);
                }
            }
            // option to exit program
            if (GetAsyncKeyState(VK_SPACE) < 0)
            {
                FA_ComClose(iPort);
                exit(0);
            }
        }
    }
    // function overloading
    void sounds(int start) {
            FA_PlayNote(iPort, 500, start); // make start 100
            FA_PlayNote(iPort, 600, start);
    }
    void sounds(int start, int honk) {
        FA_PlayNote(iPort, start, 100); // start = 500
        FA_PlayNote(iPort, honk, 100); // honk = 600
    }

    // function to change the key control values stored in the member variables
    // can be called by constructor or externally
    void changeKeys(int change_key_forward, int change_key_backward, int change_key_left, int change_key_right, int change_key_reverse, int change_key_cancel_reverse)
    {
        key_forward = change_key_forward;
        key_backward = change_key_backward;
        key_left = change_key_left;
        key_right = change_key_right;
        key_reverse = change_key_reverse;
        cancel_reverse = change_key_cancel_reverse;
    }
};

int main()
{
    DeviceOne deviceOne; // making a class object
    FA_ComOpen(deviceOne.comPort_dvc1); // open device COM port

    // 1.       making a class object referenced to previous class object
    // 2/3/4.   calling its member methods
    while (true) {
        MovementKeys control(deviceOne);
        control.sounds(100); 
        control.definedCommand();
        control.changeKeys(VK_KEY_W, VK_KEY_S, VK_KEY_A, VK_KEY_D, VK_LSHIFT, VK_KEY_Q);
        control.sounds(300, 400);
        control.definedCommand();
    }
    FA_ComClose(deviceOne.comPort_dvc1); // closing device COM port
}

// TO implement:
//
//	//Print a string to the LCD
//	FA_LCDClear(PortNumber);
//	FA_LCDPrintString(PortNumber, 19, 8, (unsigned char *) "Rover_Control_commands");
//	FA_LCDPrintString(PortNumber, 31, 16, (unsigned char *) "C++ Example");
//
