#include "AdoptoroLijn.h"
#include "BrickPi3.h"

using namespace std;


void lineRider(borderValues calibratedInputs){
	
	BrickPi3 BPLine;
	
	BPLine.set_sensor_type(PORT_2, SENSOR_TYPE_NXT_LIGHT_ON);
	BPLine.set_sensor_type(PORT_3, SENSOR_TYPE_NXT_COLOR_FULL);
	
	sensor_light_t		Light;
	sensor_color_t		Color;
	
	int BWLine = 0;
	int CLine = 0;
	int Brake = 90;
	int BrakeCounter = 0;
	
	while(true){
		// Get value from sensors
		if(BPLine.get_sensor(PORT_2, Light) == 0){
			BWLine = Light.reflected;
			if(BPLine.get_sensor(PORT_3,Color) == 0){
				CLine = Color.reflected_red;
				
				// Ride for 1 step
				if(BWLine > calibratedInputs.borderValueBW){
					BPLine.set_motor_power(PORT_C, Brake-60);
					BPLine.set_motor_power(PORT_B, 70);
					
					// Slow down one bot's wheels gradually
					BrakeCounter += 1;
					if(BrakeCounter % 10 == 0){
						Brake *= 0.8;
					}
				}
				else if(CLine < calibratedInputs.borderValueC){
					BPLine.set_motor_power(PORT_B, Brake-60);
					BPLine.set_motor_power(PORT_C, 70);
					
					// Slow down one bot's wheels gradually
					BrakeCounter += 1;
					if(BrakeCounter % 10 == 0){
						Brake *= 0.8;
					}
				}
				else{
					BPLine.set_motor_power(PORT_C, 35);
					BPLine.set_motor_power(PORT_B, 35);
					Brake = 90;
				}
			}
		}
	}
}
