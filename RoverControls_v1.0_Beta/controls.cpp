#include <iostream>
#include "stdafx.h"
#include "FA_API.h"
#include <windows.h>
#include <conio.h>
#include "controls.h"
#include <math.h>
#include <vector>
#include "Stopwatch.h"
#include <sstream>

using namespace std;
using win32::Stopwatch; // Class used to creat time points

// Global variables
int iPort, temp, entry; // global integer variables to carry data
bool trigger = false;   // universal boolean variable to carry data
bool demo = false;      // variable linked to Demo mode
bool edgeStop = false;  // helps exchange data between Data & Control classes with minimal code
bool stopBack = false;  // bug fix caused by uneven terrain & back object collision (hardware cause)

// symbolic constant names & hexadecimal values to identify keypresses
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
#define VK_KEY_B	0x42    //  ('B')	    B	Space Speed booster
#define VK_RMENU	0xA5	//  (Right ALT))    Help key for drivng back-right / back-left


// Base class. Change the private default COM-port value using pointer
int DeviceMain::port(int portGiven) {
    portGiven = 3;
    int* var = &comPort;
    *var = portGiven; // assign change to default COM port using pointer
    temp = *var;
    return temp;

}

// Take user input to define COM port 
int DeviceMain::port() {
    entry = 0;
    string in = "";         // empty string
    int n = 0;
    cout << "Hi,\nThanks for using " << softwareNameVer << "\n\nYou are about to drive a " << producer << " " << series << " series,\nmodel " << model << ", " << color << ", from " << yearReleased << ".\n\n";
    cout << "Please enter your device COM port number:\nOr press ENTER to automatically detect it.\n";
    getline(cin, in);       // get & store user input
    stringstream s(in);     // assign input to string
    if (s >> n) {           // when input is NOT empty, not Enter key
        entry = stoi(in);   // convert string to integer, if posible & store it
    }
    return entry; 
}

// Derrived class - main COM port selection method
int Device::port() {
    demo = false;           // Autoscan starts only with Demo mode Off
    bool comFound = false;  // variable to carry on the connection port status
    int k, i;               // local variables to execute multiple loops
    cout << "Establishing connection with device.\n";
    // Try to connect to device using the user input COM port from Base class
    if (entry > 0) {
        for (k = 0; k < 20; k++) {
            cout << " Trying COM port: " << entry << "\n";
            FA_ComOpen(entry);
            FA_PlayNote(entry, 500, 100);
            Sleep(80);
            if (FA_ReadLight(entry) > 0 || FA_ReadBearing(entry) > 0) {
                cout << " COM port found: " << entry << "\n";
                comFound = true;
                temp = entry;
                goto jump; // break all loops and send execution to Jump point below
            }
        }
    }
    if (entry == 0) {
        // Loop to scan COM ports and establish connection. Sound confirms success.
        for (k = 0; k < 3; k++) {
            // The i value determines the number of COM ports scanned
                // usually the device is found between first 15 ports.
            for (i = 1; i < 16; i++) {       
                cout << " Trying COM port: " << i << "\n";
                FA_ComOpen(i);              // COM port stream function (external)
                FA_PlayNote(i, 500, 100);   // sound confirmation for connection established
                Sleep(150);
                // Device connection reconfirmation
                if (FA_ReadLight(i) > 0 || FA_ReadBearing(i) > 0) {
                    cout << " COM port found: " << i << "\n";
                    comFound = true;
                    temp = i;               // temp is a variable that carries COM port between classes
                    goto jump;              // break all loops and send execution to Jump point below
                }
            }
        }
    }
jump: // Jump point
    // Exception Handaling triggers DEMO mode, when device is NOT connected
    try { 
        // if COM port detected, confirm success (Normal drive mode)
        if (comFound) {
            cout << "Analysing the connection with your Rover...\nPort number " << temp << " connection confirmed.\n";
        }
        else { // The exception
            cout << "\nException Handaling triggered by reaching the maximum number of attempts.\n\n";
            throw 505;
        }
    }
    // Handler of exception ( = Demo mode triggered)
    catch (...) { 
        cout << "===========================================================================================\n";
        cout << "\nDEVICE NOT DETECTED\n\n>>> DEMO MODE ACTIVATED <<<  \n    Port connection bypassed.\n" << 
            "    All commands are now in simulation mode & working as normal without the need for a device.\n\n\n";
        cout << "===========================================================================================\n";
        cout << "\nPress 'X' key to scan again for a COM-port connection.\n\n";
        temp = 0;
        demo = true;
    }
    iPort = temp; // global personalized data carrier for COM port
    return temp;
}

// Polymophism - proof of concept: 
// Run-time function overriding
int DeviceMain::autoSet_comPort() {
    Device device;
    DeviceMain* checkCOM = &device; // Base class pointer referenced to an object of derived class (stored)
    port();                         // First, execute base class function that will be overriden 
    checkCOM->port();               // Call the Derived class method - override the base class method  
    cout << "\nUsing Polymorphism to override the port number function with the new value.\n";
    return iPort;
}

//=========================================================================================
//
//  >>> All Rover movement commands & Data START here:

// Turn 180 degrees with "T" keypress or when turn Home gets called (Home = future feature)
void Control::turn180() {
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

// Speed boost method - Ludicrous Nitro feature
int Control::boostSpeed() {
    if (GetAsyncKeyState(VK_KEY_B) < 0 && countBoost == 0) {
        if (!down) {
            cout << "Speed Booster activated!\n";
            down = true;
            speedVal = 100;
            countBoost = 1;
            cout << "1st Count is: " << countBoost << "\n";
        }
    }
    if (GetAsyncKeyState(VK_KEY_B) < 0 && countBoost == 1) {
        if (!down) {
            cout << "Speed Booster deactivated. 2nd Count is: "<< countBoost << "\n";
            down = true;
            speedVal = 20;
            countBoost = 0;
        }
    }
    return speedVal;
}

// MAIN commands method
void Control::definedCommand() {
    // Sound check
    sounds(100);

    // Reseting motor encoder & distance data (in mm)
    FA_EncoderReset(iPort);

    // Data class constructor used to help build keypress features
    Data data;

    // Constructor used to define time points
    Stopwatch sw;

    // Time point reference for speed calculus
    sw.Start();

    // Setting internal variables before main loop.
    bool stopBack = false; bool stopFront_L = false; bool stopFront_R = false; bool stopBack_L = false; bool stopBack_R = false;
    int count = 0;
    bool stopFwrd = false;
    bool acceleroRead = false;
    bool uniTrigger = false;

    // Vector carrying data IR sensors data
    vector<double> stopper; 

//  >>> Main control LOOP
    while (true && reset < 2)
    {
        /* Keep rover surface-limit detection updated
           if lineSensor function is called with attribute, it overloads the version without attribute */
        lineSensor(0);

        // define IR reading stoppers
        frontIR = FA_ReadIR(iPort, 2);
        backIR = FA_ReadIR(iPort, 6);
        frontLeftIR = FA_ReadIR(iPort, 1);
        frontRightIR = FA_ReadIR(iPort, 3);
        backLeftIR = FA_ReadIR(iPort, 7);
        backRightIR = FA_ReadIR(iPort, 5);

        /* Initialize vector to carry on IR readings.
           This may not be the best use of vector, but is a proof on functionality */
        stopper = { frontIR, backIR, frontLeftIR, frontRightIR, backLeftIR, backRightIR };

        // 180 degrees turn by pressing 'T' key
        turn180();  

//      >>> Measurements rules to trigger Proximity Stops - countinuously updating
        if (stopper[0] > 2500 && stopFwrd == false) {
            stopFwrd = true;
            cout << "Front stop active. Object detected.\n";
            FA_Backwards(iPort, 5); FA_SetMotors(iPort, 0, 0); Sleep(250);
        }
        else if (stopper[0] < 2500) { if (stopFront_L == true || stopFront_R == true) { stopFwrd = true; } else { stopFwrd = false; } }
        //=================================================================
        if (stopper[1] > 2500 && stopBack == false) {
            stopBack = true; edgeStop = false;
            cout << "Back stop active. Object detected.\n";
            FA_Forwards(iPort, 5); FA_SetMotors(iPort, 0, 0); Sleep(250);
        }
        else if (stopper[1] < 2500) { if (stopBack_L == true || stopBack_R == true) { stopBack = true; } else { stopBack = false; } }
        //=================================================================
        if (stopper[2] > 2500 && stopFront_L == false) {
            stopFwrd = true; stopFront_L = true;
            cout << "Front-left stop active. Object detected.\n";
        }
        else if (stopper[2] < 2500) { stopFront_L = false; }
        //=================================================================
        if (stopper[3] > 2500 && stopFront_R == false) {
            stopFwrd = true; stopFront_R = true;
            cout << "Front-right stop active. Object detected.\n";
        }
        else if (stopper[3] < 2500) { stopFront_R = false; }
        //=================================================================
        if (stopper[4] > 2500 && stopBack_L == false) {
            stopBack_L = true; stopBack_L = true; edgeStop = false;
            cout << "Back-left stop active. Object detected.\n";
        }
        else if (stopper[4] < 2500) { stopBack_L = false; }
        //=================================================================
        if (stopper[5] > 2500 && stopBack_R == false) {
            stopBack_R = true; stopBack_R = true; edgeStop = false;
            cout << "Back-right stop active. Object detected.\n";
        }
        else if (stopper[5] < 2500) { stopBack_R = false; }
        //=================== Proximity Stops END =========================

        boostSpeed();

//      >>> Forwards driving - by Arrow UP key
        if (GetAsyncKeyState(key_forward) < 0 && safety == true && stopFwrd == false && edgeStop == false) {
            if (!down) {
                down = true;
                if (!demo) lineSensor(0); // Trigger safety stop when detects edge / surface limit
                cout << ("Forward\n");
                boostSpeed();
                FA_SetMotors(iPort, speedVal, speedVal);
                if (FA_ReadLine(iPort, 1) < 15) { // surface edge limit
                    FA_SetMotors(iPort, 0, 0);
                }
            }

        }

//      >>> Backwards driving - by Arrow DOWN key
        else if (GetAsyncKeyState(key_backward) < 0 && stopBack == false) {
            if (!down) {
                down = true;
                edgeStop = false; // Only backward movement is allowed when edge detected
                cout << ("Backwards\n");
                FA_SetMotors(iPort, -20, -20);
            }
        }

        /*  Programming SHIFT key to perfom 2 actions with left & right arrow keys
//      >>> Forward-left & Forward-right OR backwards-left & backwards-right driving */
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

//      >>> Forward-left & forward-right driving:
        else if (reverse == 0) {
            // Forwards - Left driving
            if (GetAsyncKeyState(key_left) < 0 && safety == true && stopFwrd == false && stopFront_L == false && edgeStop == false) {
                if (!down) {
                    down = true;
                    if (!demo) lineSensor(0); // Trigger safety stop when detects edge / surface limit
                    cout << ("Forwards left.\n");
                    FA_SetMotors(iPort, 5, 20);
                }
            }
            // Forwards - Right driving
            else if (GetAsyncKeyState(key_right) < 0 && safety == true && stopFwrd == false && stopFront_R == false && edgeStop == false) {
                if (!down) {
                    down = true;
                    if (!demo) lineSensor(0); // Trigger safety stop when detects edge / surface limit
                    cout << ("Forwards right.\n");
                    FA_SetMotors(iPort, 20, 5);
                }
            }
            else {
                if (down) {
                    down = false;
                    FA_SetMotors(iPort, 0, 0);
                }
            }
        }

//      >>> Backwards-Left & Backwards-Right driving:
        else if (reverse == 1) {
            // Backwards-Left driving
            if (GetAsyncKeyState(key_left) < 0 && stopBack == false && stopBack_L == false) {
                if (!down) {
                    down = true;
                    cout << ("Back left.\n");
                    FA_SetMotors(iPort, -10, -30);
                }
            }
            // Backwards-Right driving
            else if (GetAsyncKeyState(key_right) < 0 && stopBack == false && stopBack_R == false) {
                if (!down) {
                    down = true;
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

//     >>> Detecting any of the key released events and STOP device
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
        // ====================================================
         
        // Switch keyboard default control from right-side Arrows to left W-A-S-D keys
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

 /*     // Compass bearing data reading
            BIG BUG HERE caused by sensor interference. Not related to software.
            This sensor makes the IR sensor read wrong values & triggers safety stops
            Need more time on this. For now will be diabled. 

        if (GetAsyncKeyState(VK_KEY_U) < 0) {
            sounds(iPort, 500, 100);
            compass();
        } */

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
            sounds(iPort, 500, 100);
            cout << "All 8 LED lights ON...\n\n";
            for (int k = 0; k < 8; k++) {
                FA_LEDOn(iPort, k);
            }
            Sleep(250);
        }

        // LED OFF 
        if (GetAsyncKeyState(VK_KEY_0) < 0) {
            sounds(iPort, 500, 100);
            cout << "All 8 LED lights OFF...\n\n";
            for (int k = 0; k < 8; k++) {
                FA_LEDOff(iPort, k);
            }
            Sleep(250);
        }

        // Reset safety STOP
        if (GetAsyncKeyState(VK_KEY_R) < 0 && safety == false) {
            sounds(iPort, 500, 100);
            cout << "Safety stop reset...\n\n";
            safety = true;
        }

        // Rescan for COM port anytime while in Demo mode
        if (GetAsyncKeyState(VK_KEY_X) < 0) {
            cout << "\nRescanning for COM port.\n";
            deviceMain.autoSet_comPort();
        }

        // Radar feedback - converted into cm
        if (GetAsyncKeyState(VK_KEY_Y) < 0) {
            sounds(iPort, 500, 100);
            cout << "     Radar \n";
            data.irProximityCheck();
            Sleep(250);
        }

/*      // Accelerometer raw data read
           This data reading is isolated by key release event otherwise it interferes with the IR sensors */
        if (!trigger) {
            if (GetAsyncKeyState(VK_KEY_L) < 0) {
                if (!acceleroRead) {
                    acceleroRead = true;
                    data.accelerometer();
                }
            }
            else {
                if (acceleroRead) {
                    acceleroRead = false;
                }
            }
        }

        // Encode data read (both motors) & Speed
        if (GetAsyncKeyState(VK_KEY_K) < 0 && acceleroRead == false) {
            sounds(iPort, 500, 100);
            // grab distance data from both encoders
            double distance = (FA_EncoderRead(iPort, 1) + FA_EncoderRead(iPort, 2)) / 2;
            sw.Stop(); // set end time point
            double timeInterv = sw.ElapsedMilliseconds(); // get time interval 
            // speed is relative because rover speed differ by direction driven
            double speed = distance / timeInterv / 1.5;
            cout << "Distance is: " << distance << " mm\n";
            double speedRound = round(speed * 100.0) / 100.0; // round to 2 decimal points
            cout << "Speed is: " << speedRound * 10 << " mm / s\n\n";
            acceleroRead = true;
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

// >>> define DATA class methods: =====================================
// 
// read XYZ Accelerometer data. 
int Data::accelerometer() {
    cout << "Accelerometer 3D position:\nData reference point is the device startup position.\n";
    cout << "X = Left UP-DOWN & Right UP-DOWN axis rotation:    " << FA_ReadAxis(iPort, 0) << "\n";
    cout << "Y = Left-Right & Right-Left axis rotation:         " << FA_ReadAxis(iPort, 1) << "\n";
    cout << "Z = Front UP-DOWN & Back UP-DOWN axis rotation:    " << FA_ReadAxis(iPort, 2) << "\n\n";
    return 0;
}

// read Compass bearing data - position in referenced to the Earth's magnetic North pole
void Data::compass() {
    cout << "Compass bearing value: " << FA_ReadBearing(iPort) << "\n\n";
}

// print strings to the LCD
void Data::writeOnLCD() {
    cout << "Writing text on the LCD screen ";  // for (int t = 0; t < 10; t++) { cout << ". "; Sleep(500); } // << ancomment this at thee END 
    FA_LCDClear(iPort);
    FA_LCDPrintString(iPort, 39, 0, (unsigned char*)"Liverpool");
    FA_LCDPrintString(iPort, 20, 11, (unsigned char*)"Hope University");
    FA_LCDPrintString(iPort, 18, 25, (unsigned char*)"@Denis Manolescu");
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
    int n = FA_ReadLine(iPort, tempHere + 1);
    if (n < 1 && m > 0 && demo == false) {
 /*     // The Line sensor is not accurate and detects surface limits in every sudden stop
        FA_Backwards(iPort, 5); FA_SetMotors(iPort, 0, 0); Sleep(250);
        cout << "\nRover Stopped.\nNo surface detected under the front-side.\nAll forwards commands disabled.\n";
        edgeStop = true;*/
    } 
}

// Calculus - formula to convert IR data into distance, in cm.
double Data::irFormula(double dataIn) {
    double a, b, c;
    a = 117.9264; b = -0.5249; c = 0.2055;
    double distance = (a * pow(dataIn, b) + c);

    return distance;
}

// read Infrared sensors data (x8). Count start from rover left wheel, clockwise.
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
    unsigned int arr[8] = { FA_ReadIR(iPort, 0), FA_ReadIR(iPort, 1), FA_ReadIR(iPort, 2), FA_ReadIR(iPort, 3), FA_ReadIR(iPort, 4), FA_ReadIR(iPort, 5), FA_ReadIR(iPort, 6), FA_ReadIR(iPort, 7) };
    cout << " " << arr[0] << " === " << arr[1] << " === " << arr[2] << "\n" << "  |           |     \n" << " " << arr[3] << "           " << arr[4] << "\n";
    cout << "  |           |     \n" << " " << arr[5] << " === " << arr[6] << " === " << arr[7] << "\n";
}

// Function Overloading (next three) ===================
//
void Control::sounds(int start) {
    FA_PlayNote(iPort, 500, start); // make start 100
    FA_PlayNote(iPort, 600, start);
    if (demo) { cout << "DEMO control simulation active & Ready for use.\n\n"; }
    else { cout << "Device connected & ready to use. Have FUN!\n\n"; }
}

/* Function below overloads the top one when it gets called
   with the apropriate number and type of arguments */

void Control::sounds(int start, int honk) {
    cout << "Honk sound...\n";
    FA_PlayNote(iPort, 50, start);  // start = 500
    FA_PlayNote(iPort, 50, honk);   // honk = 600
}

void Control::sounds(int one, int two, int three) {
    cout << "\nData reading ...\n";
    FA_PlayNote(one, two, three);   // make start 100
}
// Function Overloading END. ============================