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

void lineSeen(uint8_t insideMotor, uint8_t outsideMotor, int &Accelerator, unsigned int &objectTimer, BrickPi3 &BPLine); //if the robor drives and sees a line it changes the motor speed to adjust the robot

void drivePastObject(BrickPi3 &BPEva, borderValues calibratedInputs, bool detectLine, bool objectFound, bool &foundLine); // Driving past object and detecting object to turn past

bool findLine(borderValues calibratedInputs, BrickPi3 &BPEva, bool &foundLine); // Checks if the robot as found the line from objectevasion

void returnToLine(BrickPi3 &BPEva, borderValues calibratedInputs, int rotateRight, int rotateLeft); // Returns bot on top of line to continue line riding

void sound(); // Start sound effect



//EXCLUSIVE TO MATRIX

void matrix(borderValues calibratedInputs, BrickPi3 &BPMatrix); // Starts the matrix code

void lineSeenM(uint8_t insideMotor, uint8_t outsideMotor, float &Accelerator, BrickPi3 &BPMatrix); // The robot reposition itself until its correctly on the line

void riding(uint8_t rightMotor, uint8_t leftMotor, float &Accelerator, BrickPi3 &BPMatrix, int borderValueC, int borderValueBW, int &Pos, sensor_light_t &Light, sensor_color_t &Color, int &orientation); //Checks what his position on the line is
	
void turnRight(uint8_t insideMotor, uint8_t outsideMotor, BrickPi3 &BPMatrix, int calibratedInputs, sensor_light_t &Light, int &orientation); // The robot turns to the right until it sees the black line again

//void objectDetection(BrickPi3 BPLine, unsigned int &objectTimer, borderValues calibratedInputs); // Check if object is within range

#endif /* LIJN_HPP */
