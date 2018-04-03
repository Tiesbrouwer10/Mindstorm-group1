//==================================
// Headerfile includes

#include "BrickPi3.h"
#include "AdoptoroLijn.h"
#include "AdoptoroMatrix.h"

//==================================
// Main code

using namespace std; 

BrickPi3 BP;

int main(){

	signal(SIGINT, exit_signal_handler); // Register the exit function for Ctrl+C
	
	BP.detect(); // Make sure that thye BrickPi3 is communicating and that the firmware is compatible with the drivers
	
	while(true){
		sensorCalibration();
	}
	
	
}
