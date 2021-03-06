///
/// @file		Xbox_Stepper_Functions.h
/// @brief		Library header
/// @details	<#details#>
/// @n	
/// @n @b		Project Stepper Control
/// @n @a		Developed with [embedXcode+](http://embedXcode.weebly.com)
/// 
/// @author		Mike Monson
/// @author		Mike Monson
///
/// @date		2/16/16 3:01 AM
/// @version	<#version#>
/// 
/// @copyright	(c) Mike Monson, 2016
/// @copyright	<#license#>
///
/// @see		ReadMe.txt for references
///


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
#elif defined(SPARK) // Spark specific
#   include "application.h"
#elif defined(ARDUINO) // Arduino 1.0 and 1.5 specific
#   include "Arduino.h"
#else // error
#   error Platform not defined
#endif // end IDE
#ifndef Xbox_Stepper_Functions_cpp
#define Xbox_Stepper_Functions_cpp

class Stepper {
public:
    Stepper(int motorPin, int dirPin);
    void moveForward(int motorSpeed);
    void moveBackward(int motorSpeed);
    void moveSteps(long numSteps, int motorSpeed);
    long returnPostion();
    void setUpperBound();
    void clearUpperBound();
    long returnUpperBound();
    void setLowerBound();
    void clearLowerBound();
    long returnLowerBound();

private:
    int _motorPin;
    int _dirPin;
    long _position;
    long _upperStopBound;
    long _lowerStopBound;
};


#endif
