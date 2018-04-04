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

	signal(SIGINT, exitSignalHandler); // Register the exit function for Ctrl+C
	
	BP.detect(); // Make sure that thye BrickPi3 is communicating and that the firmware is compatible with the drivers
	
	BP2.set_sensor_type(PORT_2, SENSOR_TYPE_NXT_LIGHT_ON); // Blacc/White Sensor Port Defenition
	BP2.set_sensor_type(PORT_3, SENSOR_TYPE_NXT_COLOR_FULL);	// Color Sensor Port Defenition
	while(true){
		sensorCalibration();
	}
	
	
}
