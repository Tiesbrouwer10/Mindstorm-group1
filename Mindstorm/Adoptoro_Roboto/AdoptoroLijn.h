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

borderValues sensorCalibration(); // Calibrates Sensors

void exitSignalHandler(int signo); // Exits the program with no run-away motors

void lineRider(borderValues calibratedInputs, BrickPi3 &BPLine); // Follows line, (Currently called from main for 1 step)

int getDist(BrickPi3 &BPEva); // Gets the distance the robot is away from object

void evadeObject(BrickPi3 &BPEva, borderValues &calibratedInputs); // Procedure to evading object

int getAcceleration(int MOTOR, float acceleration , bool setSpeed); // Acceleration fuction keeps track of motor speed and set motor speed

#endif /* LIJN_HPP */
