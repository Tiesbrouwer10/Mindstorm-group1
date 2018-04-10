#include "AdoptoroLijn.h"
#include "BrickPi3.h"

using namespace std;

/*


*/
void lineRider(borderValues calibratedInputs, BrickPi3 &BPLine){
	
	// Turns the light and color sensor on
	BPLine.set_sensor_type(PORT_2, SENSOR_TYPE_NXT_LIGHT_ON);
	BPLine.set_sensor_type(PORT_3, SENSOR_TYPE_NXT_COLOR_FULL);
	
	// Creates the required structs
	sensor_light_t		Light;
	sensor_color_t		Color;
	
	// Create variables
	int BWLine = 0;
	int CLine = 0;
	int Accelerator = 40;
	int distanceToObject = 0;
	
	while(true){
		// Checks if distance is within range
		distanceToObject = getDist(BPLine);
		if(distanceToObject < 7){
			evadeObject(BPLine, calibratedInputs);
		}
		
		// Get value from sensors, if they are ready to be used
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
						Accelerator += 1;
						sleep(0.1);
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
						Accelerator += 1;
						sleep(0.1);
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
