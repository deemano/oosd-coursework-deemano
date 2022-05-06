# ======================================================================
   CONSOLE APPLICATION : Rover Control commands - project overview
  ====================================================================== 

## 🤓 Integrations: 🚀

    1. Objects and Classes                      ✓
    2. Inheritance                              ✓
    3. Polymorphism - run-time func overr       ✓
    4. Exception Handling - Try/throw/catch     ✓
    5. Functions                                ✓
    6. Arrays, Strings and Vectors              ✓
    7. Pointers and References                  ✓
    8. Graphics libs OpenGL, Vulkan, ImGui      ✓


## 💻 Implemented features: 

    1. Autoscan & autoselect device COM port                        ✓
    2. IR sensors data & distance to objects generation             ✓
    3. Light sensor - detect edges / surface limits                 ✓
    4. Light sensor - detect ambiental light                        ✓
    5. 3D Accelerometer positioning of rover in XYZ                 ✓
    6. Compass bearing data - position in ref to mag. N pole        ✓
    7. Encoders data read to determine distance driven              ✓
    8. Speed calculation via encoders                               ✓
    9. Set LCD Text                                                 ✓
    10. LED On/Off commands                                         ✓
    11. Objects collision & edge stops                              ✓
    12. Sounds                                                      ✓
    13. Left-to-right switch main driving commands                  ✓
    14. Multi-purpose keypress driving commands                     ✓
    15. User modes: Normal & Demo (without rover)                   ✓
    16. Auto-turn 180 degress                                       ✓
    17. Dynamic GUI (not linked yet)                                ✓

## 📝 Features in progress: 

    1. Auto-explore surroundings
    2. Turn Home command (follow the same path)
    3. Link GUI to commands and data

## 📚  Application Control Keys:

#define VK_KEY_W    0x57    //  ('W')       W   Forward
#define VK_KEY_A    0x41    //  ('A')       A   Left
#define VK_KEY_D    0x44    //  ('D')       D   Right  
#define VK_KEY_S    0x53    //  ('S')       S   Backward 
#define VK_KEY_Y    0x59    //  ('Y')       Y   Accelerometer data read
#define VK_KEY_O    0x4F    //  ('O')       O   Buttom Line sensor read
#define VK_KEY_T    0x54    //  ('T')       T   Turn 180 degrees
#define VK_KEY_U    0x55    //  ('U')       U   Compass bear data read
#define VK_KEY_I    0x49    //  ('I')       I   Light sensor data read
#define VK_KEY_P    0x50    //  ('P')       P   IR distance sensor read
#define VK_KEY_0    0x30    //  ('0')       0   Turn all x8 LED On (This is zero not the letter 'O')
#define VK_KEY_9    0x39    //  ('9')       9   Turn all x8 LED Off
#define VK_KEY_R    0x52    //  ('R')       R   Reset safety stop
#define VK_KEY_X    0x58    //  ('X')       X   Restart COM port autoscan
#define VK_KEY_L    0x4C    //  ('L')       L   Read 3D accelerometer data
#define VK_KEY_K    0x4B    //  ('K')       K   Read actuators encoder data
#define VK_KEY_J    0x4A    //  ('J')       J   Resets motors encoders

- key_forward     =             VK_UP          Drive forwards
- key_backward    =             VK_DOWN        Drive backwards
- key_left        =             VK_LEFT        Dive left
- key_right       =             VK_RIGHT       Drive right
- key_reverse     =             VK_RSHIFT      Activate / deactivate drive reverse left of right
- turn            =             VK_KEY_T       Turn 180 degress, on spot
