#include "AdoptoroLijn.h"
#include "BrickPi3.h"

using namespace std;

void lineRider(borderValues calibratedInputs, BrickPi3 &BPLine){

	//==============================================================
	// Sensor Defenition and base values / defenitions
	
	
	sensor_light_t		Light;
	sensor_color_t		Color;
	
	int BWLine = 0;
	int CLine = 0;
	int Accelerator = 40;
	int distanceToObject = 0;
	
	int MOTOR_B =  2;
	int MOTOR_C = 4;
	
	while(true){
		
		// Checks if object is being detected
		//distanceToObject = getDist(BPLine);
		//if(distanceToObject < 7){
			//evadeObject(BPLine, calibratedInputs);
		//}
			if(true){
				if(BPLine.get_sensor(PORT_2, Light) == 0){
					BWLine = Light.reflected;
				if(BPLine.get_sensor(PORT_3,Color) == 0){
					CLine = Color.reflected_red;
			
				
					// Ride for 1 step
					if(BWLine > calibratedInputs.borderValueBW){
						cout << "TEST3\n";
						if(getAcceleration(MOTOR_B, 1, false) > 89){
							BPLine.set_motor_power(PORT_C, getAcceleration(MOTOR_C, -90, true));
						}
						else{
							BPLine.set_motor_power(PORT_C, getAcceleration(MOTOR_C, 15, true));
							BPLine.set_motor_power(PORT_B, getAcceleration(MOTOR_B, 1, false));
						}
						sleep(0.1);
					}
					else if(CLine < calibratedInputs.borderValueC){
				
						if(getAcceleration(MOTOR_C, 1, false) > 89){
							BPLine.set_motor_power(PORT_B, getAcceleration(MOTOR_C, -90, true));
						}
						else{
							BPLine.set_motor_power(PORT_B, getAcceleration(MOTOR_B, 15, true));
							BPLine.set_motor_power(PORT_C, getAcceleration(MOTOR_C, 1, true));
						}
						sleep(0.1);
					}
					else{
						BPLine.set_motor_power(PORT_C, getAcceleration(MOTOR_C, 40, true)); // Set Left wheel back to base value
						BPLine.set_motor_power(PORT_B, getAcceleration(MOTOR_C, 40, true)); // Set Right wheel back to base value
						Accelerator = 40; // Set back to average value and speed
					}
				}
			}
		}
	}
}
