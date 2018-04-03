#ifndef LIJN_HPP
#define LIJN_HPP

using namespace std;

//==================================
// Include guards

#include <iostream>
#include <unistd.h>
#include <vector>
#include <iomanip>
#include <signal.h>

//==================================
// Header content

void sensorCalibration(); // Calibrates Sensors

void exitSignalHandler(int signo); // Exits the program with no run-away motors

#endif /* LIJN_HPP */
