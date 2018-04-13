// Authors: Niels, Jasper, Tony, Marc

#include "AdoptoroLijn.h"
#include "BrickPi3.h"


using namespace std;

void lineRider(borderValues calibratedInputs, BrickPi3 &BPLine){
	
	sensor_light_t		Light;
	sensor_color_t		Color;
	
	int BWLine = 0;
	int CLine = 0;
	int Accelerator = 40;
	int distanceToObject = 0;
	unsigned int objectTimer = 0;
	
	while(true){
		// Checks if distance is within range
		distanceToObject = getDist(BPLine);
		if(distanceToObject < 8 && distanceToObject > 0){
			objectTimer += 1;
			if(objectTimer > 50){
				evadeObject(BPLine, calibratedInputs);
			}
		}
		
		// Get value from sensors
		else if(BPLine.get_sensor(PORT_2, Light) == 0){
			BWLine = Light.reflected;
			if(BPLine.get_sensor(PORT_3,Color) == 0){
				CLine = Color.reflected_red;
				
				// if both the color and black/white sensors see something that is not white he ignores it and continues driving
				if(CLine < calibratedInputs.borderValueC && BWLine > calibratedInputs.borderValueBW){
					BPLine.set_motor_power(PORT_C, 40);
					BPLine.set_motor_power(PORT_B, 40);
					Accelerator = 40;
					if(objectTimer > 0){
						objectTimer -= 1;
					}
				}
				
				// Ride for 1 step
				if(BWLine > calibratedInputs.borderValueBW){
					// if the value of the Black/White sensor is higher than the value it has as white 
					lineSeen(PORT_C, PORT_B, Accelerator, objectTimer, BPLine);
				}
				else if(CLine < calibratedInputs.borderValueC){
					//if the value of the color sensor is lower than the value it has as white
					lineSeen(PORT_B, PORT_C, Accelerator, objectTimer, BPLine);

				}
				else{
					// set a base speed for the robot if it rides a straight line
					BPLine.set_motor_power(PORT_C, 40);
					BPLine.set_motor_power(PORT_B, 40);
					Accelerator = 40;
					if(objectTimer > 0){
						objectTimer -= 1;
					}
				}
			}
		}
	}
}
/*
uint8_t insideMotor = The motor thats on the inside when turning
uint8_t outsideMotor = The motor thats on the outside when turning
float &Accelerator = Accelerates and gets higher value the longer the sensor detects a black line
unsigned int &objectTimer = Times how many clock pulses an object is in its way, to prevent errors
BrickPi3 &BPLine = BrickPi3 BPMain version of BP (As stated in main)
*/


void lineSeen(uint8_t insideMotor, uint8_t outsideMotor, int &Accelerator, unsigned int &objectTimer, BrickPi3 &BPLine){

	if(Accelerator > 99){
		BPLine.set_motor_power(insideMotor, -20);
	}
	else if(Accelerator < 100){
		Accelerator += 1;
		BPLine.set_motor_power(insideMotor, 15);
		BPLine.set_motor_power(outsideMotor, Accelerator);
		if(objectTimer > 0){
			objectTimer -= 1;
		}
	}

}
