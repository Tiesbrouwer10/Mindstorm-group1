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
	
	// Steering Variables
	int BWAccelerator = 40;
	int CAccelerator = 40;
	int BWBrake = 20;
	int CBrake = 20;
	
	while(true){
		// Get value from sensors
		if(BPLine.get_sensor(PORT_2, Light) == 0){
			BWLine = Light.reflected;
			if(BPLine.get_sensor(PORT_3,Color) == 0){
				CLine = Color.reflected_red;
			
				// Ride for 1 step
				if(BWLine > calibratedInputs.borderValueBW){
					BPLine.set_motor_power(PORT_C, BWBrake);
					BPLine.set_motor_power(PORT_B, BWAccelerator);
					
					if(BWAccelerator <= 125){
							BWAccelerator += 2;
							//BWBrake -= 1;
					}
				}
				else if(CLine < calibratedInputs.borderValueC){
					BPLine.set_motor_power(PORT_B, CBrake);
					BPLine.set_motor_power(PORT_C, CAccelerator);
					
					if(CAccelerator <= 125){
						CAccelerator += 2;
						//CBrake -= 1;
					}
				}
				else{
					BPLine.set_motor_power(PORT_C, 40);
					BPLine.set_motor_power(PORT_B, 40);
					BWAccelerator = 50;
					CAccelerator = 50;
					BWBrake = 20;
					CBrake = 20;
				}
			}
		}
	}
}
