#include "AdoptoroLijn.h"

using namespace std;

BrickPi3 BP;

void sensorCalibration(){
	
	int BWValue = 0;
	int CValue = 0;

	BP.set_sensor_type(PORT_2, SENSOR_TYPE_NXT_LIGHT_ON); // Blacc/White Sensor Port Defenition
	BP.set_sensor_type(PORT_3, SENSOR_TYPE_NXT_COLOR_FULL);	// Color Sensor Port Defenition
	
	sensor_light_t		Light;
	sensor_color_t		Color;

	error = 0;
	if(BP.get_sensor(PORT_2, Light) == 0){
		BWValue = Light.reflected;
	}
	if(BP.get_sensor(PORT_3,Color) == 0){
		CValue = Color.reflected_red;
	}

	cout << "Black/White Sensor Reflected: " << BWValue << "\n";
	cout << "Color Sensor Reflected: " << CValue << "\n";

		
	sleep(1);
		
	
}

//================================
// Calibration Layout:

// Port S2 = Black/White Sensor

// Port S3 = Color Sensor
