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

void evadeObject(BrickPi3 &BPEva, borderValues &calibratedInputs); // 

//int getAcceleration(const int &motor, int do_up_down=0, bool set=false);

#endif /* LIJN_HPP */
