#ifndef LIJN_HPP
#define LIJN_HPP

using namespace std;

//==================================
// Include guards

#include <iostream>
#include <unistd.h>
#include <vector>
#include <signal.h>
#include "BrickPi3.h"



//==================================
// Structs 

struct borderValues{ // Contains to be updated border values from calibration
	
	int borderValueBW;
	int borderValueC;
	
};

//==================================
// Header content

borderValues sensorCalibration(BrickPi3 &BPMain); // Calibrates Sensors

void exitSignalHandler(int signo); // Exits the program with no run-away motors

void lineRider(borderValues calibratedInputs, BrickPi3 &BPLine); // Follows line, (Currently called from main for 1 step)

int getDist(BrickPi3 &BPEva); // Gets the distance the robot is away from object

void evadeObject(BrickPi3 &BPEva, borderValues &calibratedInputs); // Procedure to evading object

void turnHead90degrees(BrickPi3 &BPEva, int rotateDirection); // Rotates the sonar sensor 90 degrees, 1 for left, 2 for right

void turnCar(BrickPi3 &BPEva, int rotateDirection); // Rotates the car 90 degrees, 1 for left, 2 for right

void lineSeen(uint8_t insideMotor, uint8_t outsideMotor, float &Accelerator, unsigned int &objectTimer, BrickPi3 &BPLine); // Turning function

void drivePastObject(BrickPi3 &BPEva, borderValues calibratedInputs, bool detectLine, bool objectFound); // Driving past object and detecting object to turn past

void sound(); // Start sound effect

//EXCLUSIVE TO MATRIX

void matrix(borderValues calibratedInputs, BrickPi3 &BPMatrix);

void lineSeenM(uint8_t insideMotor, uint8_t outsideMotor, float &Accelerator, BrickPi3 &BPMatrix);
	
void riding(uint8_t PORT_B, uint8_t PORT_C, float &Accelerator, BrickPi3 &BPMatrix);	

//void objectDetection(BrickPi3 BPLine, unsigned int &objectTimer, borderValues calibratedInputs); // Check if object is within range

#endif /* LIJN_HPP */
