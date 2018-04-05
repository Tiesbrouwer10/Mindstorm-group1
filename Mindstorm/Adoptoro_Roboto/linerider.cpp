#include "AdoptoroLijn.h"

using namespace std;

BrickPi3 BPLine;

void lineRider(borderValues calibratedInputs){
	
	
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
