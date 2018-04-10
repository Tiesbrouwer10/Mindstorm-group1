#include "AdoptoroLijn.h"
#include "BrickPi3.h"

using namespace std;
//comment
//You have been IP banned

void lineRider(borderValues calibratedInputs, BrickPi3 &BPLine){
	
	
	sensor_light_t		Light;
	sensor_color_t		Color;
	
	int BWLine = 0;
	int CLine = 0;
	float Accelerator = 40;
	int distanceToObject = 0;
	
	while(true){
		// Checks if distance is within range
		distanceToObject = getDist(BPLine);
		cout << distanceToObject << '\n';
		if(distanceToObject < 7){
			cout << "draai hoofd";
			evadeObject(BPLine, calibratedInputs);
		}
		
		// Get value from sensors
		else if(BPLine.get_sensor(PORT_2, Light) == 0){
			BWLine = Light.reflected;
			if(BPLine.get_sensor(PORT_3,Color) == 0){
				CLine = Color.reflected_red;
				
				if(CLine < calibratedInputs.borderValueC && BWLine > calibratedInputs.borderValueBW){
					BPLine.set_motor_power(PORT_C, 40);
					BPLine.set_motor_power(PORT_B, 40);
					Accelerator = 40;
				}
				
				// Ride for 1 step
				else if(BWLine > calibratedInputs.borderValueBW){
					if(Accelerator > 69){
						BPLine.set_motor_power(PORT_C, -60);
					}else{
						BPLine.set_motor_power(PORT_C, 15);
						BPLine.set_motor_power(PORT_B, Accelerator);
					}
					if(Accelerator <= 70){
						Accelerator += 0.1;
						//cout << Accelerator << " BW Accelerator\n";
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
						Accelerator += 0.1;
						//cout << Accelerator << " C Accelerator\n";
						sleep(0.01);
					}

				}
				else{
					BPLine.set_motor_power(PORT_C, 40);
					BPLine.set_motor_power(PORT_B, 40);
					Accelerator = 40;
					
					//cout << "Accelerator set to 40\n"; 
					
				}
			}
		}
	}
}
