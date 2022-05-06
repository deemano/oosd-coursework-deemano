
/*  // ==================================================================== \\
   ||                                                                        ||
   ||  Console app to control Formula Allcode robot-rover, model RB4420      ||
   ||  This is the console version, without the graphics,                    ||
   ||  Date: 5th Feb - 5th May 2022.                                         ||
   ||  © Denis Manolescu, Liverpool Hope University                          ||
   ||                                                                        ||
    \\ ==================================================================== //
 */

#include "stdafx.h"
#include "FA_API.h"
#include <iostream>
#include <windows.h>
#include <conio.h>
#include "controls.h"

using namespace std;

int main()
{
    // Constructors declaration
    DeviceOne deviceOne{}; // making a class object
    Checker checker;
    Data data;
    
    // COM port autoscan & autodetect device
    checker.autoScanPort();  // uncomment this when release

    // Pull out COM port number from checker class
    int iPort = checker.migrateCom();

    cout << "You device is connected to COM port " << iPort << ".\n";
    // Write data on device LCD
    data.writeOnLCD();

    // read distances to objects
    data.irRadar();

    // Main LOOP
    while (true) {
        // making class object referenced to previous class object
        MovementKeys control(deviceOne);

        /* Calling member methods :
           Basic movement commands function */
        control.definedCommand();

        // Overriding move commands keys & call control function again
        control.changeKeys(VK_KEY_W, VK_KEY_S, VK_KEY_A, VK_KEY_D, VK_LSHIFT);
        control.definedCommand();
    }
    FA_ComClose(iPort); // closing device COM port
}

// Implemented:
/*
    1. Autoscan & autoselect device COM port;                   ✓
    2. IR sensors data & distance generation;                   ✓
    3. Light sensor - detect edges / surface limits             ✓
    4. Try/throw/catch integration                              ✓
    5. 3D Accelerometer positioning                             ✓
    6. Class inheritance                                        ✓
    7. Polymorphism (run-time polymorphism via func overriding) ✓
    8. Functions                                                ✓
    9. Pointers & references                                    ✓
    10. Turn ON / OFF LED lights            ✓
*/

/*
1. Objects and Classes                      ✓
2. Inheritance                              ✓
3. Polymorphism                             ✓
4. Exception Handling                       ✓
5. Functions                                ✓
6. Arrays, Stringsand Vectors               ✓
7. Pointers and References                  ✓
8. Graphics libraries such as OpenGL        ✓ 
*/