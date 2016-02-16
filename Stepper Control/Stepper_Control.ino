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


#define xDirPin 5
#define yDirPin 6
#define zDirPin 7

#define xPulsePin 2
#define yPulsePin  3
#define zPulsePin 4


#define stepperEnable = 8



int speed = 600;
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
    }
    Serial.print(F("\r\nXbox Wireless Receiver Library Started"));
    



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
        
        //decrease stepper speed
        if (Xbox.getButtonPress(L)) {
            speed += 1;
            Serial.println("Speed Decreased...");
        }
        
        //increase stepper speed
        if (Xbox.getButtonPress(R)) {
            speed -= 1;
            Serial.println("Speed Increased...");
        }

        //move up
        if (Xbox.getButtonPress(UP)) {
            
            Y_Motor.moveForward(speed);
            Serial.println(" Up..");
        }
    
    
        //move down
        if (Xbox.getButtonPress(DOWN)) {
            Y_Motor.moveBackward(speed);
            Serial.println(" Down...");

            
        }
        //move left
        if (Xbox.getButtonPress(LEFT)) {
            X_Motor.moveForward(speed);
            Serial.println(" Left...");

            
        }
        //move right
        if (Xbox.getButtonPress(RIGHT)) {
            X_Motor.moveBackward(speed);
            Serial.println(" Right...");

            
        }
    //z up
    if (Xbox.getButtonPress(Y)) {
        Z_Motor.moveForward(speed);
        Serial.println("Z up...");
    }
    if (Xbox.getButtonPress(A)) {
        Z_Motor.moveBackward(speed);
        Serial.println("Z Down...");
    }
    
    }

    

    
   




