#ifndef MATRIX_HPP
#define MATRIX_HPP

using namespace std;

//==================================
// Include guards

#include <iostream>
#include <unistd.h>
#include <vector>
#include "BrickPi3.h"
#include "AdoptoroLijn.h"

//==================================
// Header content

//getDist(BrickPi3 &BPEva); //gets the distance of the nearest object infront of him

//turnAround(BrickPi3 &BPMatrix, int pos); // turns the robot around to last crossroad

void exitSignalHandler(int signo); // Exits the program with no run-away motors

void matrixRider(borderValues calibratedInputs, BrickPi3 & BPMatrix); // Follows matrix

void turning(uint8_t insideMotor, uint8_t outsideMotor, BrickPi3 &BPMatrix, int calibratedInputs, int sensor); // turning the robot

void lineSeenM(uint8_t insideMotor, uint8_t outsideMotor, float &Accelerator, unsigned int &objectTimer, BrickPi3 &BPLine);//Turning function

void sound(); // Start sound effect

void riding(int &Pos, uint8_t PORT_B, uint8_t PORTC, int &Accelerator, BrickPi3 &BPMatrix, int orientation, int borderValueBW, int borderValueC);//Drives forward

#endif /* MATRIX_HPP */
