#pragma once
#include "stdafx.h"
#include "FA_API.h"
#include <iostream>
#include <windows.h>
#include <conio.h>
#include <math.h>
#include <string>
#include <vector>
#include <chrono>

using namespace std;

// define symbolic constant names & hexadecimal values to identify keypresses
#define VK_KEY_W	0x57    //  ('W')	    W   forward
#define VK_KEY_A	0x41    //  ('A')	    A   left
#define VK_KEY_D	0x44    //  ('D')	    D   right  
#define VK_KEY_S	0x53    //  ('S')	    S   backward 
#define VK_KEY_Q	0x51    //  ('Q')	    Q   cancel reverse keys
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
#define VK_RMENU	0xA5	//  (Right ALT))    Cancel drivng back-right / back-left feature

// default Com Port number for DeviceOne
class DeviceOne {
private:
    int comPort = 1; // default value
public:
    int port();
};

class Checker: public DeviceOne {
public:
    int temp{};
    int autoScanPort();
    int autoSet_comPort();
    int migrateCom();
};

// this is to prove the concept of inheritance
// also, makes it easier to add future commands.
// MovementKeys contains the keypress variables to be used by OtherMovements
class Data{
public:
    // data functions
    bool safety = true; // used for safety stops in control
    void accelerometer();
    void compass();
    void writeOnLCD();
    void lightSensor();
    void lineSensor(int tempHere);
    void lineSensor();
    void irSensor();
    double irFormula(double dataIn);
    void irProximityCheck();
    void irRadar();
};

// This defines the basic rover move commands
class MovementKeys:public Data {
    // member variables:
private:
    // keeping reference to deviceOne instead of copy; 
    // main() has to make sure deviceOne object out-lives MovementKeys object
    DeviceOne& deviceOne;
    int key_forward{}, key_backward{}, key_left{}, key_right{}, key_reverse{};

public:
    int turn;
    int reset = 0;
    int reverse = 0;
    //// IR reading variables:
    double frontIR{}, backIR{}, frontLeftIR{}, frontRightIR{}, backLeftIR{}, backRightIR{};

    // constructor, which only sets deviceOne and keeps the keys name at their Default
    // deviceOne must be initialized before constructor function body
    // as references have no default value
    MovementKeys(DeviceOne& gr) : deviceOne(gr)
    { // Default list:
        key_forward     = VK_UP;        // Drive forwards
        key_backward    = VK_DOWN;      // Drive backwards
        key_left        = VK_LEFT;      // Dive left
        key_right       = VK_RIGHT;     // Drive right
        key_reverse     = VK_RSHIFT;    // Activate / deactivate drive reverse left of right
        turn            = VK_KEY_T;     // Turn 180 on spot
        int reverse = 0;
        int comPort{};
       int iPort {};
    }

    // loop to define rules of the keys pressed commands
    void definedCommand();
    void turn180();
    // function overloading
    void sounds(int start);
    void sounds(int start, int honk);
    void sounds(int one, int two, int three);

    // function to change the key control values stored in the member variables
    // can be called by constructor or externally
    void changeKeys(int change_key_forward, int change_key_backward, int change_key_left, int change_key_right, int change_key_reverse)
    {
        key_forward = change_key_forward;
        key_backward = change_key_backward;
        key_left = change_key_left;
        key_right = change_key_right;
        key_reverse = change_key_reverse;
    }
};

