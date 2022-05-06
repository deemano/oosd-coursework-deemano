#include <iostream>
#include "stdafx.h"
#include "FA_API.h"
#include <windows.h>
#include <conio.h>
#include "controls.h"
#include <math.h>
#include <vector>
#include "Stopwatch.h"

using namespace std;
using win32::Stopwatch;

// Global variables
int iPort;
int temp;
bool demo = false; // variable to activate Demo mode

// define symbolic constant names & hexadecimal values to identify keypresses
#define VK_KEY_W	0x57    //  ('W')	    W   Forward
#define VK_KEY_A	0x41    //  ('A')	    A   Left
#define VK_KEY_D	0x44    //  ('D')	    D   Right  
#define VK_KEY_S	0x53    //  ('S')	    S   Backward 
#define VK_KEY_Q	0x51    //  ('Q')	    Q   Cancel reverse keys
#define VK_KEY_Y    0x59    //  ('Y')	    Y   Accelerometer data read
#define VK_KEY_O	0x4F    //  ('O')	    O   Buttom Line sensor read
#define VK_KEY_T	0x54    //  ('T')       T   Turn 180 degrees
#define VK_KEY_U	0x55    //  ('U')	    U   Compass bear data read
#define VK_KEY_I	0x49    //  ('I')	    I   Light sensor data read
#define VK_KEY_P	0x50    //  ('P')	    P   IR distance sensor read
#define VK_KEY_0	0x30    //  ('0')	    0   Turn all x8 LED On (This is zero not the letter 'O')
#define VK_KEY_9	0x39    //  ('9')	    9   Turn all x8 LED Off
#define VK_KEY_R	0x52    //  ('R')	    R   Reset safety stop
#define VK_KEY_X	0x58    //  ('X')	    X   Restart COM port autoscan
#define VK_KEY_L	0x4C    //  ('L')	    L   Read 3D accelerometer data
#define VK_KEY_K	0x4B    //  ('K')	    K   Read actuators encoder data
#define VK_KEY_J	0x4A    //  ('J')	    J   Resets motors encoders
#define VK_RMENU	0xA5	//  (Right ALT))    Help key for drivng back-right / back-left

int DeviceOne::port() {
    int* temp = &comPort;
    *temp = 3; // setting new default COM value to override as proof of concept (run-time polymorphism)
    iPort = *temp;
    return iPort;
}
 
int Checker::autoScanPort() {
    // Autoscan starts with Demo mode Off
    demo = false;
    // Loop used to bypass the find COM port time for faster Debugging
    // If you are in Release, ignore it.
    /*for (int j = 0; j < 10; j++) {
        for (int i = 5; i < 6; i++) {
            FA_ComOpen(i);
            FA_PlayNote(i, 500, 100);
            Sleep(500);
            if (FA_ReadLight(i) > 0 || FA_ReadIR(i, 0) > 0) {
                cout << "Success!\nPort number: " << i << "\n";
                temp = i;
                autoSet_comPort();
                demo = false;
                goto jump;
            }
            else { cout << "fail\n"; }
        }
    }*/
    bool comFound = false;
    int k, i;
    cout << "Establishing connection with Rover.\n";
    // Loop to scan COM ports and establish connection. Sound confirms success.
    for (k = 0; k < 3; k++) {
        for (i = 1; i < 15; i++) { // The i value determines the number of COM ports scanned, 
            // but usually the device is found between first 15 ports.
            cout << "Trying COM port: " << i << "\n";
            FA_ComOpen(i);
            FA_PlayNote(i, 500, 100);
            Sleep(50);
            if (FA_ReadLight(i) > 0 || FA_ReadBearing(i) > 0) {
                cout << "COM port found: " << i << "\n";
                comFound = true;
                temp = i;
                goto jump; // break all loops and send execution to Jump point below
            }
        }
    }
jump: // Jump point

    // Exception handaling triggers Demo mode, when device is not connected
    try { // if COM port detected, confirm success (Normal drive mode)
        if (!comFound == false) {
            cout << "Autoscanning for your device COM port...\nCOM port found at: " << temp << "\n";
            autoSet_comPort();
        }
        else { // The exception
            cout << "\nException Handaling triggered by reaching port " << temp << ".\n\n";
            throw 505;
        }
    }
    catch (int myNum) { // Handler of exception (Demo mode triggering)
        cout << "===========================================================================================\n";
        cout << "\nDEVICE NOT DETECTED\n\n>>> DEMO MODE ACTIVATED <<<  \n    Port connection bypassed.\n    All commands are now in simulation mode & working as normal without the need of a device.\n\n\n";
        cout << "===========================================================================================\n";
        cout << "\nPress 'X' key to Rescan COM port.\n\n";
        temp = 0;
        demo = true;
    }
    return temp;
}

// Polymophism proof of concept. 
// Run-time function overriding
int Checker::autoSet_comPort() {
    int temp3 = port();
    int* temp2 = &temp3;
    // Polymorphism through run-time function overriding
    *temp2 = temp;
    iPort = *temp2;
    cout << "\nUsing Polymorphism to override port number function with value " << temp <<".\n";
    return iPort;
}

// Single function to handle all overridings of COM port
// Handles the last change
int Checker::migrateCom() {
    return temp;
}
//=========================================================================================
 
//  >>> All Rover movement commands & Data STARTS here:

// Turn 180 degrees with "T" keypress or when turn Home gets called (Home = future feature)
void MovementKeys::turn180() {
    bool temp180 = false; 
    if (GetAsyncKeyState(turn) < 0) { // Trigger event with 'T' keypress
        if (!temp180) {
            temp180 = true;
            cout << "\nRover turn 180 degrees.\n\n";
            FA_Left(iPort, 180);
            Sleep(250);
        }

    }
    else { // Detect key release & close event
        if (temp180) {
            temp180 = false;
            cout << "180 degrees turn executed.\n";
        }
    }
};

void MovementKeys::definedCommand() {
    // Sound check
    sounds(100);

    // Reseting motor encoder or distance data (mm)
    FA_EncoderReset(iPort);

    // Data class constructor needed int building keypress feature below
    Data data;
    Stopwatch sw;

    // time point reference to help calculate speed
    sw.Start();

    // Setting internal variables before main loop
    bool stopFwrd, stopBack, stopFront_L, stopFront_R, stopBack_L, stopBack_R = false;
    bool down = false;
    int count = 0;

    // Vector carrying data
    vector<double> stopper; // make this global to be able to use it outside the class/function

//  >>> Main control LOOP
    while (true && reset < 2)
    {
        // keep rover surface-limit detection updated
        // if lineSensor function is called with a attribute, it overloads the version without attribute
        lineSensor(0);

        //// IR reading stoppers
        frontIR = FA_ReadIR(iPort, 2);
        backIR = FA_ReadIR(iPort, 6);
        frontLeftIR = FA_ReadIR(iPort, 1);
        frontRightIR = FA_ReadIR(iPort, 3);
        backLeftIR = FA_ReadIR(iPort, 7);
        backRightIR = FA_ReadIR(iPort, 5);

        // Initialize vector to carry on IR readings
        stopper = { frontIR, backIR, frontLeftIR, frontRightIR, backLeftIR, backRightIR };

        // 180 degrees turn by pressing 'T' keyyy
        turn180(); 

        // Measurements rules to trigger Proximity Stops - countinuously updating
        if (stopper[0] > 2700) { stopFwrd = true; FA_SetMotors(iPort, 0, 0); }     else { stopFwrd = false; }
        if (stopper[1] > 2700) { stopBack = true; FA_SetMotors(iPort, 0, 0);}      else { stopBack = false; }
        if (stopper[2] > 2700) { stopFront_L = true; FA_SetMotors(iPort, 0, 0);}   else { stopFront_L = false; }
        if (stopper[3] > 2700) { stopFront_R = true; FA_SetMotors(iPort, 0, 0);}   else { stopFront_R = false; }
        if (stopper[4] > 2700) { stopBack_L = true; FA_SetMotors(iPort, 0, 0);}    else { stopBack_L = false; }
        if (stopper[5] > 2700) { stopBack_R = true; FA_SetMotors(iPort, 0, 0);}    else { stopBack_R = false; }

//      >>> Forwards driving
        if (GetAsyncKeyState(key_forward) < 0 && safety == true && stopFwrd == false) {
            if (!down) {
                down = true;
                //if(!demo) lineSensor(0); // Trigger safety stop when detects edge / surface limit
                cout << ("Forward\n");
                FA_SetMotors(iPort, 15, 15);
                if (FA_ReadLine(iPort, 1) < 25) {
                    FA_SetMotors(iPort, 0, 0);
                }
            }

        }

//      >>> Backwards driving
        else if (GetAsyncKeyState(key_backward) < 0 && stopBack == false) {
            if (!down) {
                down = true;
                //if(!demo) lineSensor(0); // Trigger safety stop when detects edge / surface limit
                cout << ("Backwards\n");
                FA_SetMotors(iPort, -15, -15);
            }
        }

//      >>> Forward-Left & Right OR Backwards-Left & Right
        /*  Programming SHIFT key to perfom 2 actions @ Left & Right:
            Forward-Left or Forward-Right & Backwards-Left or Backwards-Right */
        // Shift Key Toggle
        else if (GetAsyncKeyState(key_reverse) < 0 && count == 0) {
            if (!down) {
                cout << "Reverse Active: \n";
                reverse = 1;
                down = true;
                count = 1;
            }
        }
        else if (GetAsyncKeyState(key_reverse) < 0 && count == 1) {
            if (!down) {
                cout << "Reverse Disactivated!: \n";
                reverse = 0;
                down = true;
                count = 0;
            }
        }

//      >>> Forwards Left & Right driving:
        else if (reverse == 0) {
            // Forwards - Left driving
            if (GetAsyncKeyState(key_left) < 0 && safety == true && stopFwrd == false && stopFront_L == false) {
                if (!down) {
                    down = true;
                    //if(!demo) lineSensor(0); // Trigger safety stop when detects edge / surface limit
                    cout << ("Forwards left.\n");
                    FA_SetMotors(iPort, 10, 30);
                }
            }
            // Forwards - Right driving
            else if (GetAsyncKeyState(key_right) < 0 && safety == true && stopFwrd == false && stopFront_R == false) {
                if (!down) {
                    down = true;
                    //if(!demo) lineSensor(0); // Trigger safety stop when detects edge / surface limit
                    cout << ("Forwards right.\n");
                    FA_SetMotors(iPort, 30, 10);
                }
            }
            else {
                if (down) {
                    down = false;
                    FA_SetMotors(iPort, 0, 0);
                }
            }
        }

//      >>> Backwards Left & Right driving:
        else if (reverse == 1) {
            // Backwards-Left driving
            if (GetAsyncKeyState(key_left) < 0 && stopBack == false && stopBack_L == false) {
                if (!down) {
                    down = true;
                    //if(!demo) lineSensor(0); // Trigger safety stop when detects edge / surface limit
                    cout << ("Back left.\n");
                    FA_SetMotors(iPort, -10, -30);
                }
            }
            // Backwards-Right driving
            else if (GetAsyncKeyState(key_right) < 0 && stopBack == false && stopBack_R == false) {
                if (!down) {
                    down = true;
                    //if(!demo) lineSensor(0); // Trigger safety stop when detects edge / surface limit
                    cout << ("Back right.\n");
                    FA_SetMotors(iPort, -30, -10);
                }
            }
            else {
                if (down) {
                    down = false;
                    FA_SetMotors(iPort, 0, 0);
                }
            }
        }

 //     >>> Detecting any of the key released events and make device stop
        else {
            if (down) {

                down = false;
                cout << ("Stopped.\n");
                FA_SetMotors(iPort, 0, 0);
            }
        }

        // ====================================================
        // OPTIONAL change keys from within loop with ths code:
        // key_forward = VK_KEY_W; key_backward = VK_KEY_S; key_left = VK_KEY_A; key_right = VK_KEY_D; // may use it for future development

        // Switch keyboard default control from right-side Arrows to left W-A-S-D
        if (GetAsyncKeyState(VK_LCONTROL) < 0 && reset == 0) {
            cout << ("Main control changed to W - A - S - D letters.\n");
            reset++;
            break;
        } // Switch back to keyboard default control, right-side arrows
        if (GetAsyncKeyState(VK_RCONTROL) < 0 && reset == 1) {
            cout << ("Main control reset to default - Arrow Keys.\n");
            reset--;
            break;
        }
        // Define Honk
        if (GetAsyncKeyState(VK_TAB) < 0) {
            sounds(280, 286);
            Sleep(500);
        }
        // Option to exit program
        if (GetAsyncKeyState(VK_ESCAPE) < 0) {
            FA_ComClose(iPort);
            exit(0);
        }
        // Compass bearing data reading
        if (GetAsyncKeyState(VK_KEY_U) < 0) {
            sounds(iPort, 500, 100);
            compass();
            Sleep(250);
        }
        // Light sensor data reading
        if (GetAsyncKeyState(VK_KEY_I) < 0) {
            sounds(iPort, 500, 100);
            lightSensor();
            Sleep(250);
        }
        // Underneath Line sensor data reading
        if (GetAsyncKeyState(VK_KEY_O) < 0) {
            sounds(iPort, 500, 100);
            lineSensor();
            Sleep(250);
        }
        // IR distance sensor data reading
        if (GetAsyncKeyState(VK_KEY_P) < 0) {
            sounds(iPort, 500, 100);
            irSensor();
            Sleep(250);
        }
        // LED ON 
        if (GetAsyncKeyState(VK_KEY_9) < 0) {
            cout << "All 8 LED lights ON...\n\n";
            sounds(iPort, 500, 100);
            for (int k = 0; k < 8; k++) {
                FA_LEDOn(iPort, k);
            }
            Sleep(250);
        }
        // LED OFF 
        if (GetAsyncKeyState(VK_KEY_0) < 0) {
            cout << "All 8 LED lights OFF...\n\n";
            sounds(iPort, 500, 100);
            for (int k = 0; k < 8; k++) {
                FA_LEDOff(iPort, k);
            }
            Sleep(250);
        }
        // Reset safety STOP
        if(GetAsyncKeyState(VK_KEY_R) < 0 && safety == false){
            sounds(iPort, 500, 100);
            cout << "Safety stop reset...\n\n";
            safety = true;
        }
        // Rescan for COM port anytime while in Demo mode
        if (GetAsyncKeyState(VK_KEY_X) < 0) {
            Checker checker;
            checker.autoScanPort();
            cout << "\nRescanning for COM port.\n";
        }
        // Radar feedback - converted into cm
        if (GetAsyncKeyState(VK_KEY_Y) < 0) {
            sounds(iPort, 500, 100);
            cout << "     Radar \n";
            data.irProximityCheck();
            Sleep(250);
        }
        // Accelerometer raw data read
        if (GetAsyncKeyState(VK_KEY_L) < 0) {
            sounds(iPort, 500, 100);
            data.accelerometer();
            Sleep(250);
        }
        // Encode data read (both motors) & Speed
        if (GetAsyncKeyState(VK_KEY_K) < 0) {
            sounds(iPort, 500, 100);
            // grab distance data from both encoders
            double distance = (FA_EncoderRead(5, 1) + FA_EncoderRead(5, 2)) / 2;
            sw.Stop(); // set end time point
            double timeInterv = sw.ElapsedMilliseconds(); // get time interval 
            // speed is relative because rover speed differ by direction driven
            double speed = distance / timeInterv / 1.5; 
            cout << "\nDistance is: " << distance << "\n";
            double speedRound = round(speed * 100.0) / 100.0; // round to 2 decimal points
            cout << "Speed is: " << speedRound * 10 << " mm / s\n\n";
            Sleep(250);
        }
        // Reset encoder on demand
        if (GetAsyncKeyState(VK_KEY_J) < 0) {
            sounds(iPort, 500, 100);
            FA_EncoderReset(iPort);
            cout << "Encoders reset." << "\n\n";
            Sleep(250);
        }
    }
}

// read XYZ Accelerometer data. 
void Data::accelerometer() {
    cout << "Accelerometer 3D position:\nData reference point is the device startup position.\n";
    cout << "X = Left UP-DOWN & Right UP-DOWN axis rotation:    " << FA_ReadAxis(iPort, 0) << "\n";
    cout << "Y = Left-Right & Right-Left axis rotation:         " << FA_ReadAxis(iPort, 1) << "\n";
    cout << "Z = Front UP-DOWN & Back UP-DOWN axis rotation:    " << FA_ReadAxis(iPort, 2) << "\n\n";
}

// read Compass bearing data - position in referenced to the Earth's magnetic North pole
void Data::compass() {
    cout << "Compass bearing value: " << FA_ReadBearing(iPort) << "\n\n";
}

// print strings to the LCD
void Data::writeOnLCD() {
    cout << "Writing text on the LCD screen ";  // for (int t = 0; t < 10; t++) { cout << ". "; Sleep(500); } // << ancomment this at thee END 
	FA_LCDClear(iPort);
	FA_LCDPrintString(iPort, 39, 0, (unsigned char *) "Liverpool");
    FA_LCDPrintString(iPort, 20, 11, (unsigned char*) "Hope University");
	FA_LCDPrintString(iPort, 18, 25, (unsigned char *) "@Denis Manolescu");
    cout << "\nText added.\n";
}

// read ambiental Light sensor data
void Data::lightSensor() {
    cout << "Light sensor value: " << FA_ReadLight(iPort) << "\n\n";
}

// read Line sensors data (x2)
void Data::lineSensor() {
    int m = FA_ReadLine(iPort, 0); cout << "#1 Underneath Line sensor value: " << m << "\n";
    int n = FA_ReadLine(iPort, 1); cout << "#1 Underneath Line sensor value: " << n << "\n\n";
}
// Overriding function - whithout feedback. Needed for control checks
void Data::lineSensor(int tempHere) {
    int m = FA_ReadLine(iPort, tempHere);
    int n = FA_ReadLine(iPort, tempHere+1);
    if (n < 40 && m < 0 && demo == false) {
        if (demo == true) { cout << "Demo True\n"; }
        cout << "Rover Stopped. Not safe. No surface detected under the front-side.\n";
        safety = false;
    }
    else { safety = true; }
}

// Calculus - formula to convert IR data into distance, in cm.
double Data::irFormula(double dataIn) { 
    double a, b, c;
    a = 117.9264; b = -0.5249; c = 0.2055; 
    double distance = (a * pow(dataIn, b) + c);

    return distance;
}
// read Infrared seonsor data (x8). Count star from rover left wheel, clockwise.
void Data::irSensor() {
    cout << "Infrared distance sensor:\n";

    double ir1 = FA_ReadIR(iPort, 0); cout << "#1 IR sensor value: " << ir1 << "      =       " << irFormula(ir1) << " cm\n";
    double ir2 = FA_ReadIR(iPort, 1); cout << "#2 IR sensor value: " << ir2 << "      =       " << irFormula(ir2) << " cm\n";
    double ir3 = FA_ReadIR(iPort, 2); cout << "#3 IR sensor value: " << ir3 << "      =       " << irFormula(ir3) << " cm\n";
    double ir4 = FA_ReadIR(iPort, 3); cout << "#4 IR sensor value: " << ir4 << "      =       " << irFormula(ir4) << " cm\n";
    double ir5 = FA_ReadIR(iPort, 4); cout << "#5 IR sensor value: " << ir5 << "      =       " << irFormula(ir5) << " cm\n";
    double ir6 = FA_ReadIR(iPort, 5); cout << "#6 IR sensor value: " << ir6 << "      =       " << irFormula(ir6) << " cm\n";
    double ir7 = FA_ReadIR(iPort, 6); cout << "#7 IR sensor value: " << ir7 << "      =       " << irFormula(ir7) << " cm\n";
    double ir8 = FA_ReadIR(iPort, 7); cout << "#8 IR sensor value: " << ir8 << "      =       " << irFormula(ir8) << " cm\n\n";
}
void Data::irRadar() { 
    // future upgrade
    // to detect obstacles & distances to them using the IR readings
}

void Data::irProximityCheck() {
    unsigned int arr [8] = { FA_ReadIR(iPort, 0), FA_ReadIR(iPort, 1), FA_ReadIR(iPort, 2), FA_ReadIR(iPort, 3), FA_ReadIR(iPort, 4), FA_ReadIR(iPort, 5), FA_ReadIR(iPort, 6), FA_ReadIR(iPort, 7) };
    cout << " " << arr[0] << " === " << arr[1] << " === " << arr[2] << "\n" << "  |           |     \n" << " " << arr[3] << "           " << arr[4] << "\n";
    cout << "  |           |     \n" << " " << arr[5] << " === " << arr[6] << " === " << arr[7] << "\n";
}

// Function Overloading (next three) ===================:
//
void MovementKeys::sounds(int start) {
    FA_PlayNote(iPort, 500, start); // make start 100
    FA_PlayNote(iPort, 600, start);
    if(demo){ cout << "DEMO control simulation active & Ready for use.\n\n"; }
    else { cout << "Device connected & ready to use.\n\n"; }
}

/* Function below overloads the top one when it is called
with the apropriate number and type of arguments */

void MovementKeys::sounds(int start, int honk) {
    cout << "Honk sound...\n";
    FA_PlayNote(iPort, 50, start); // start = 500
    FA_PlayNote(iPort, 50, honk); // honk = 600
}

void MovementKeys::sounds(int one, int two, int three) {
    cout << "Data reading ...\n";
    FA_PlayNote(one, two, three); // make start 100
}
// Function Overloading END. ============================