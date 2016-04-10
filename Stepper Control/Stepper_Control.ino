///
/// @mainpage	Stepper Control
///
/// @details	Description of the project
/// @n
/// @n
/// @n @a		Developed with [embedXcode+](http://embedXcode.weebly.com)
///
/// @author		Mike Monson
/// @author		Mike Monson
/// @date		1/29/16 11:42 AM
/// @version	<#version#>
///
/// @copyright	(c) Mike Monson, 2016
/// @copyright	Licence
///
/// @see		ReadMe.txt for references
///


///
/// @file		Stepper_Control.ino
/// @brief		Main sketch
///
/// @details	<#details#>
/// @n @a		Developed with [embedXcode+](http://embedXcode.weebly.com)
///
/// @author		Mike Monson
/// @author		Mike Monson
/// @date		1/29/16 11:42 AM
/// @version	<#version#>
///
/// @copyright	(c) Mike Monson, 2016
/// @copyright	Licence
///
/// @see		ReadMe.txt for references
/// @n
/// For NEMA 17 200 pulses makes one full cycle


// Core library for code-sense - IDE-based
#if defined(WIRING) // Wiring specific
#   include "Wiring.h"
#elif defined(MAPLE_IDE) // Maple specific
#   include "WProgram.h"
#elif defined(ROBOTIS) // Robotis specific
#   include "libpandora_types.h"
#   include "pandora.h"
#elif defined(MPIDE) // chipKIT specific
#   include "WProgram.h"
#elif defined(DIGISPARK) // Digispark specific
#   include "Arduino.h"
#elif defined(ENERGIA) // LaunchPad specific
#   include "Energia.h"
#elif defined(LITTLEROBOTFRIENDS) // LittleRobotFriends specific
#   include "LRF.h"
#elif defined(MICRODUINO) // Microduino specific
#   include "Arduino.h"
#elif defined(TEENSYDUINO) // Teensy specific
#   include "Arduino.h"
#elif defined(REDBEARLAB) // RedBearLab specific
#   include "Arduino.h"
#elif defined(RFDUINO) // RFduino specific
#   include "Arduino.h"
#elif defined(SPARK) || defined(PARTICLE) // Particle / Spark specific
#   include "application.h"
#elif defined(ESP8266) // ESP8266 specific
#   include "Arduino.h"
#elif defined(ARDUINO) // Arduino 1.0 and 1.5 specific
#   include "Arduino.h"
#else // error
#   error Platform not defined
#endif // end IDE

// Include application, user and local libraries
#include <XBOXRECV.h>
#include "Xbox_Stepper_Functions.h"

// Define structures and classes
//Stepper Motor Constructors


// Define variables and constants


#define xDirPin 2
#define yDirPin 4
#define zDirPin 6

#define xPulsePin 3
#define yPulsePin  5
#define zPulsePin 7


#define stepperEnable = 8



long speed = 200 ;
int count = 0;
bool FLAG = true;

// Prototypes

USB Usb;
XBOXRECV Xbox(&Usb);

Stepper X_Motor(xPulsePin,xDirPin);
Stepper Y_Motor(yPulsePin,yDirPin);
Stepper Z_Motor(zPulsePin,zDirPin);

// Add setup code
void setup()
{
//XBOX CONTROLLER SETUP
    Serial.begin(115200);
#if !defined(__MIPSEL__)
    while (!Serial); // Wait for serial port to connect - used on Leonardo, Teensy and other boards with built-in USB CDC serial connection
#endif
    if (Usb.Init() == -1) {
        Serial.print(F("\r\nOSC did not start"));
        while (1); //halt
    }    Serial.print(F("\r\nXbox Wireless Receiver Library Started"));
    



}

// Add loop code
void loop()
{
    Usb.Task();
    
    if (FLAG && Xbox.Xbox360Connected[0]) {
        Xbox.setAllOff();
        delay(500);
        Xbox.setLedOn(LED1);
        delay(500);
        Xbox.setLedOn(LED2);
        delay(500);
        Xbox.setLedOn(LED4);
        delay(500);
        Xbox.setLedOn(LED3);
        delay(500);
        Xbox.setLedOn(LED1);
        
        
        FLAG = false;
        Serial.print(F("\nController Connected!\n"));
    }
    
    //set y upper stop, provide one rumble indicating stop is set.
        if (Xbox.getButtonClick(UP)) {
            Y_Motor.setUpperBound();
            Serial.print("Y upper bound: ");
            Serial.println(Y_Motor.returnUpperBound());
            Xbox.setRumbleOn(100, 100);
            delay(200);
            Xbox.setRumbleOff();
        }
    //set x left stop, provide one rumbe indicating stop is set.
    if (Xbox.getButtonClick(LEFT)) {
        X_Motor.setLowerBound();
        Serial.print("X upper bound: ");
        Serial.println(X_Motor.returnUpperBound());
        Xbox.setRumbleOn(100, 100);
        delay(200);
        Xbox.setRumbleOff();
        
    }
    
    //set x right stop, provide oen rumble indicating stop is set.
        
        //increase stepper speed
        if (Xbox.getButtonClick(START)) {
            speed = speed - 10;
            Serial.println(speed);
        }

//        //move up
//        if (Xbox.getButtonPress(UP)) {
//            
//            Y_Motor.moveForward(speed);
//            Serial.println(" Up..");
//        }
//    
//    
//        //move down
//        if (Xbox.getButtonPress(DOWN)) {
//            Y_Motor.moveBackward(speed);
//            Serial.println(" Down...");
//
//            
//        }
//        //move left
//        if (Xbox.getButtonPress(LEFT)) {
//            X_Motor.moveForward(speed);
//            Serial.println(" Left...");
//
//            
//        }
//        //move right
//        if (Xbox.getButtonPress(RIGHT)) {
//            X_Motor.moveBackward(speed);
//            Serial.println(" Right...");
//
//}
    if (Xbox.getButtonPress(X)) {
        //Cut left, X lead screw ccw
        X_Motor.moveBackward(speed);
        Serial.println("Cut left, X lead screw ccw");
    }
    if (Xbox.getButtonPress(B)) {
        //Cut right x lead screw cw
        X_Motor.moveForward(speed);
        Serial.println("Cut right x lead screw cw");
    }
    
    if (Xbox.getButtonPress(Y)) {
        //Cut up, rotate y lead screw ccw
        //check upper bound, if location is less than upper bound make cut
        if (Y_Motor.returnPostion() < Y_Motor.returnUpperBound()) {
            Y_Motor.moveBackward(speed);
            Serial.println("Cut up, rotate y lead screw ccw");
        }
        else {
            Serial.println("Motor at Y Upper Bound Limit");
        }

        
    }
    
    if (Xbox.getButtonPress(A)) {
        //Cut down, rotate y lead screw cw
        Y_Motor.moveForward(speed);
        Serial.println("Cut down, rotate y lead screw cw");
        
    }
    
    if (Xbox.getButtonPress(Y)) {

        analogWrite(3, speed);
        

    }
    
    if (Xbox.getButtonPress(BACK)) {
        Serial.print("X Position: ");
        Serial.println(X_Motor.returnPostion());
        
        Serial.print("Y Position: ");
        Serial.println(Y_Motor.returnPostion());
        
        Serial.print("Z Position: ");
        Serial.println(Z_Motor.returnPostion());

        
    }
    
}

    

    
   




