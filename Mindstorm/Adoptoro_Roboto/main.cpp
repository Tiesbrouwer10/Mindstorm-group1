//==================================
// Headerfile includes

#include "BrickPi3.h"
#include "AdoptoroLijn.h"


//==================================
// Main code

using namespace std; 

BrickPi3 BPMain;

int main(){

	char modus;
	
	signal(SIGINT, exitSignalHandler); // Register the exit function for Ctrl+C0
	
	BPMain.detect(); // Make sure that the BrickPi3 is communicating and that the firmware is compatible with the drivers
	//sound(); // For fun
	// Get values from sensors
	// sensorCalibration();
	cout << "GEEF MODUS ROBOT, L voor line, M voor Matrix: ";
	cin >> modus;
	// Start lineriding function
	if(modus == 'L'){
		lineRider(sensorCalibration(BPMain), BPMain);
	}
	else if(modus == 'M'){
		matrix(sensorCalibration(BPMain), BPMain);
	}
	
}
