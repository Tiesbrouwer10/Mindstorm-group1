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
	int curSpeedB = 0;
    int curSpeedC = 0;
    int maxSpeed = 40;
    
	while(true){
		// Get value from sensors
		if(BPLine.get_sensor(PORT_2, Light) == 0){
			BWLine = Light.reflected;
			if(BPLine.get_sensor(PORT_3,Color) == 0){
                CLine = Color.reflected_red;
				// Ride for 1 step
				if(BWLine > calibratedInputs.borderValueBW){
                    if(curSpeedC > -128){
                        BPLine.set_motor_power(PORT_C, curSpeedC - 5);
                    }
				}
				else if(CLine < calibratedInputs.borderValueC){
                    if(curSpeedB > -128){
                        BPLine.set_motor_power(PORT_B, curSpeedB - 5);
                    }
				}
				else{
                    if(curSpeedB < maxSpeed){
                        BPLine.set_motor_power(PORT_C, curSpeedC + 5);
                    }
                    if(curSpeedC < maxSpeed){
                        BPLine.set_motor_power(PORT_B, curSpeedB + 5);
                    }
				}
			}
		}
        sleep(0.01);
	}
}
