#include "AdoptoroLijn.h"
#include "BrickPi3.h"

using namespace std;

int error;

void sensorCalibration(){
	
	int BWValue;
	int CValue;

	
	sensor_light_t		Light;
	sensor_color_t		Color;
	sleep(2);
	error = 0;
	for(unsigned int i = 0; i < 10; i++){
		if(BP2.get_sensor(PORT_2, Light) == 0){
			BWValue += Light.reflected;
		}
		if(BP2.get_sensor(PORT_3,Color) == 0){
			CValue += Color.reflected_red;
		}
	
		cout << "Black/White Sensor Reflected: " << BWValue << "\n";
		cout << "Color Sensor Reflected: " << CValue << "\n";
		
		sleep(0.1);
	}
	BWValue /= 10;
	CValue /= 10;

	cout << "\nBlack/White Sensor Reflected: " << BWValue << "\n";
	cout << "Color Sensor Reflected: " << CValue << "\n";
	cout << "DONE" << '\n';
	
}

//================================
// Calibration Layout:

// Port S2 = Black/White Sensor

// Port S3 = Color Sensor
