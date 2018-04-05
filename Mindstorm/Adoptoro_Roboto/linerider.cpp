#include "AdoptoroLijn.h"
#include "BrickPi3.h"

using namespace std;



void lineRider(borderValues calibratedInputs){
	
	BrickPi3 BPLine;
	sensor_light_t		Light;
	sensor_color_t		Color;
	
	while(true){
		// Get value from sensors
		BPLine.get_sensor(PORT_2, Light);
		BPLine.get_sensor(PORT_3,Color);
		
		// Ride for 1 step
		if(Light.reflected > borderValueBW){
			BPLine.set_motor_power(PORT_C, 10);
		}
		if(Color.reflected_red < borderValueC){
			BPLine.set_motor_power(PORT_B, 10);
		}
		else{
			BPLine.set_motor_power(PORT_C, 20);
			BPLine.set_motor_power(PORT_B, 20);
		}
	}
}
