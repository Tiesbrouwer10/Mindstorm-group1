#ifndef MATRIX_HPP
#define MATRIX_HPP

using namespace std;

//==================================
// Include guards

#include <iostream>
#include <unistd.h>
#include <vector>

//==================================
// Header content

//struct borderValues{ // Contains to be updated border values from calibration
	
//	int borderValueBW;
//	int borderValueC;
	
//};

//getDist(BrickPi3 &BPEva); //gets the distance of the nearest object infront of him

//turnAround(BrickPi3 &BPMatrix, int pos); // turns the robot around to last crossroad



borderValues sensorCalibration(BrickPi3 &BPMain); // Calibrates Sensors

void exitSignalHandler(int signo); // Exits the program with no run-away motors

void matrixRider(borderValues calibratedInputs, BrickPi3 & BPMatrix); // Follows matrix

void turning(uint8_t insideMotor, uint8_t outsideMotor, BrickPi3 &BPMatrix, borderValues calibratedInputs); // turning the robot

void lineSeen(uint8_t insideMotor, uint8_t outsideMotor, float &Accelerator, unsigned int &objectTimer, BrickPi3 &BPLine);//Turning function

void sound(); // Start sound effect

#endif /* MATRIX_HPP */
