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
	int Accelerator = 40;
	int Deaccelerator = 40;
	
	while(true){
		// Get value from sensors
		if(BPLine.get_sensor(PORT_2, Light) == 0){
			BWLine = Light.reflected;
			if(BPLine.get_sensor(PORT_3,Color) == 0){
				CLine = Color.reflected_red;
				
				// Ride for 1 step
				if(BWLine > calibratedInputs.borderValueBW){
					BPLine.set_motor_power(PORT_C, 15);
					BPLine.set_motor_power(PORT_B, Accelerator);
					
					if(Accelerator <= 60){
						Accelerator += 1;
						cout << Accelerator << " BW Accelerator\n";
						sleep(0.1);
					}
					if(Accelerator > 89 && Deaccelerator > -10){
						BPLine.set_motor_power(PORT_C, Deaccelerator);
						Deaccelerator -= 2;
					}
				}
				else if(CLine < calibratedInputs.borderValueC){
					BPLine.set_motor_power(PORT_B, 15);
					BPLine.set_motor_power(PORT_C, Accelerator);
					
					if(Accelerator <= 60){
						Accelerator += 1;
						cout << Accelerator << " C Accelerator\n";
						sleep(0.1);
					}
					if(Accelerator > 89 && Deaccelerator > -10){
						BPLine.set_motor_power(PORT_B, Deaccelerator);
						Deaccelerator -= 2;
					}
				}
				else{
					
					if(Deaccelerator < 40){
						Deaccelerator += 2;
						BPLine.set_motor_power(PORT_C, Deaccelerator);
						cout << Deaccelerator << " Deaccalerator\n";
					}
					Accelerator = 40;
					cout << "Accelerator set to 40\n"; 
				}
			}
		}
	}
}
