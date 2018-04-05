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
	int BWAccelerator = 0;
	int CAccelerator = 0;
	int BWBrake = 0;
	int CBrake = 0;
	
	while(true){
		// Get value from sensors
		if(BPLine.get_sensor(PORT_2, Light) == 0){
			BWLine = Light.reflected;
			if(BPLine.get_sensor(PORT_3,Color) == 0){
				CLine = Color.reflected_red;
				cout << "BW SCANNED: " << Light.reflected << " BWVALUE = " << calibratedInputs.borderValueBW << '\n';
				cout << "C  SCANNED: " << Color.reflected_red << "  CVALUE = " << calibratedInputs.borderValueC << '\n';
				// Ride for 1 step
				if(BWLine > calibratedInputs.borderValueBW){
					BPLine.set_motor_power(PORT_C, BWBrake);
					BPLine.set_motor_power(PORT_B, BWAccelerator);
					
					if(BWAccelerator <= 125 & BWBrake >= -125){
							BWAccelerator += 4;
							BWBrake -= 1;
					}
				}
				else if(CLine < calibratedInputs.borderValueC){
					BPLine.set_motor_power(PORT_B, CBrake);
					BPLine.set_motor_power(PORT_C, CAccelerator);
					
					if(CAccelerator <= 125 & CBrake >= -125){
						CAccelerator += 4;
						CBrake -= 1;
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
