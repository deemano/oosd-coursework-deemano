#include "stdafx.h"
#include "FA_API.h"
#include <iostream>
#include <windows.h>
#include <conio.h>
#include "controls.h"

using namespace std;

int main()
{
    // Class objects:
    DeviceOne deviceOne;
    Checker checker;
    Data data;

    // COM port autoscan & autodetect device method
    deviceOne.autoSet_comPort(); 

    // Write data on device LCD
    data.writeOnLCD();

    // Main rover control LOOP
    while (true) {
        // making class object referenced to previous class object
        MovementKeys control(deviceOne);

        /* Calling member methods =========
        Main basic movement commands function */
        control.definedCommand();

        // Overriding default move-command keys if user prefer switching
        control.changeKeys(VK_KEY_W, VK_KEY_S, VK_KEY_A, VK_KEY_D, VK_LSHIFT);

        // Re-enter main control method
        control.definedCommand();
    }
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
    10. Turn ON / OFF LED lights                                ✓


Others:

1. Objects and Classes                      ✓
2. Inheritance                              ✓
3. Polymorphism                             ✓
4. Exception Handling                       ✓
5. Functions                                ✓
6. Arrays, Stringsand Vectors               ✓
7. Pointers and References                  ✓
8. Graphics libraries such as OpenGL        ✓ 
*/
