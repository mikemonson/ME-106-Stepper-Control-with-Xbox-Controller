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

// Define structures and classes


// Define variables and constants


#define xDir 5
#define yDir 6
#define zDir 7

#define xPulse 2
#define yPulse  3
#define zPulse 4


#define stepperEnable = 8

int speed = 600;
int count = 0;
bool FLAG = true;


USB Usb;
XBOXRECV Xbox(&Usb);

// Prototypes


// Add setup code
void setup()
{
//initalize pins for stepper motors
    for (int i = 2 ; i <= 8; i++) {
        pinMode(i, OUTPUT);
    }
    
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

        //move barrel up
        if (Xbox.getButtonPress(UP)) {
            digitalWrite(yDir, HIGH);
            digitalWrite(yPulse, HIGH);
            delayMicroseconds(speed);
            digitalWrite(yPulse, LOW);
            Serial.println(" Up..");
        }
    
    
        //move barrel down
        if (Xbox.getButtonPress(DOWN)) {
            digitalWrite(yDir, LOW);
            digitalWrite(yPulse, HIGH);
            delayMicroseconds(speed);
            digitalWrite(yPulse, LOW);
            Serial.println(" Down...");

            
        }
        //move barrel left
        if (Xbox.getButtonPress(LEFT)) {
            digitalWrite(xDir, HIGH);
            digitalWrite(xPulse, HIGH);
            delayMicroseconds(speed);
            digitalWrite(xPulse, LOW);
            Serial.println(" Left...");

            
        }
        //move barrel right
        if (Xbox.getButtonPress(RIGHT)) {
            digitalWrite(xDir, LOW);
            digitalWrite(xPulse, HIGH);
            delayMicroseconds(speed);
            digitalWrite(xPulse, LOW);
            Serial.println(" Right...");

            
        }
    
    if (Xbox.getButtonClick(A)) {
        digitalWrite(zPulse, HIGH);
        delayMicroseconds(700);
        digitalWrite(zPulse, LOW);
        Serial.println("Toggle...");

    }
    
    }

    

    
   




