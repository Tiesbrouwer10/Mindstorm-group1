//==================================
// Headerfile includes

#include "BrickPi3.h"
#include "AdoptoroLijn.h"
#include "AdoptoroMatrix.h"

//==================================
// Main code

using namespace std; 

BrickPi3 BPMain;

int main(){

	signal(SIGINT, exitSignalHandler); // Register the exit function for Ctrl+C0
	
	BPMain.detect(); // Make sure that the BrickPi3 is communicating and that the firmware is compatible with the drivers
	
	// Get values from sensors
	// sensorCalibration();
	
	// Start lineriding function
	lineRider(sensorCalibration(),BPMain);
	
}
