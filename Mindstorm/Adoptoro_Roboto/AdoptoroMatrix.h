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

struct borderValues{ // Contains to be updated border values from calibration
	
	int borderValueBW;
	int borderValueC;
	
};


borderValues sensorCalibration(); // Calibrates Sensors

void exitSignalHandler(int signo); // Exits the program with no run-away motors

void MatrixRider(borderValues calibratedInputs); // Follows matrix


#endif /* MATRIX_HPP */
