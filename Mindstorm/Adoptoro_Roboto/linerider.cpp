#include "AdoptoroLijn.h"
#include "BrickPi3.h"

using namespace std;
//comment

void lineRider(borderValues calibratedInputs, BrickPi3 &BPLine){
	
	BPLine.set_sensor_type(PORT_2, SENSOR_TYPE_NXT_LIGHT_ON);
	BPLine.set_sensor_type(PORT_3, SENSOR_TYPE_NXT_COLOR_FULL);
	
	sensor_light_t		Light;
	sensor_color_t		Color;
	
	int BWLine = 0;
	int CLine = 0;
	float Accelerator = 40;
	
	while(true){
		// Get value from sensors
		if(BPLine.get_sensor(PORT_2, Light) == 0){
			BWLine = Light.reflected;
			if(BPLine.get_sensor(PORT_3,Color) == 0){
				CLine = Color.reflected_red;
				
				// Ride for 1 step
				if(BWLine > calibratedInputs.borderValueBW){
					if(Accelerator > 69){
						BPLine.set_motor_power(PORT_C, -60);
					}else{
						BPLine.set_motor_power(PORT_C, 15);
						BPLine.set_motor_power(PORT_B, Accelerator);
					}
					if(Accelerator <= 70){
						Accelerator += 0.05;
						sleep(0.01);
					}
				}
				else if(CLine < calibratedInputs.borderValueC){
					if(Accelerator > 69){
						BPLine.set_motor_power(PORT_B, -60);
					}else{
						BPLine.set_motor_power(PORT_B, 15);
						BPLine.set_motor_power(PORT_C, Accelerator);
					}
					if(Accelerator <= 70){
						Accelerator += 0.05;
						sleep(0.01);
					}
				}
				else{
					BPLine.set_motor_power(PORT_C, 40);
					BPLine.set_motor_power(PORT_B, 40);
					Accelerator = 40;
				}
			}
		}
	}
}
