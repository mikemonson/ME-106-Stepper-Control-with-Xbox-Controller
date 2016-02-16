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
}
void Stepper::moveForward(int motorSpeed)
{
    digitalWrite(_dirPin, HIGH);
    digitalWrite(_motorPin, HIGH);
    delayMicroseconds(motorSpeed);
    digitalWrite(_motorPin, LOW);
}

void Stepper::moveBackward(int motorSpeed) {
    digitalWrite(_dirPin, LOW);
    digitalWrite(_motorPin, HIGH);
    delayMicroseconds(motorSpeed);
    digitalWrite(_motorPin, LOW);
}
