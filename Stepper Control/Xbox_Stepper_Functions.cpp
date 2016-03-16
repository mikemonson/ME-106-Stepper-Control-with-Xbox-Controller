//
// Xbox_Stepper_Functions.cpp 
// Library C++ code
// ----------------------------------
// Developed with embedXcode+ 
// http://embedXcode.weebly.com
//
// Project 		Stepper Control
//
// Created by 	Mike Monson, 2/16/16 3:01 AM
// 				Mike Monson
//
// Copyright 	(c) Mike Monson, 2016
// Licence		<#license#>
//
// See 			Xbox_Stepper_Functions.h and ReadMe.txt for references
//


// Library header
#include "Xbox_Stepper_Functions.h"
 Stepper::Stepper(int motorPin, int dirPin)
{  
    pinMode(motorPin, OUTPUT);
    pinMode(dirPin, OUTPUT);
    _motorPin=motorPin;
    _dirPin=dirPin;
    _position = 0;
}
void Stepper::moveForward(int motorSpeed)
{   noInterrupts();
    PORTD = B00001100;
    delayMicroseconds(motorSpeed);
    PORTD = B00000100;
    _position++;
    interrupts();
    
    
}

void Stepper::moveBackward(int motorSpeed) {
    noInterrupts();
    PORTD = B00001000;
    delayMicroseconds(motorSpeed);
    PORTD = B00000000;
    _position--;
    interrupts();


}

void Stepper::moveSteps(long numSteps, int motorSpeed) {
    for (long i = 0 ; i < numSteps; i++) {
        
        noInterrupts();
        digitalWrite(_dirPin, HIGH);
        digitalWrite(_motorPin, HIGH);
        delayMicroseconds(motorSpeed);
        digitalWrite(_motorPin, LOW);
        delayMicroseconds(motorSpeed);
        _position++;
        interrupts();
    }
}

long Stepper::returnPostion() {
    return _position;
}
