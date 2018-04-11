#include "AdoptoroLijn.h"
#include "BrickPi3.h"
#include "AdoptoroMatrix.h"

using namespace std;
//comment
//You have been IP banned

void lineRider(borderValues calibratedInputs, BrickPi3 &BPLine){
	
	
	sensor_light_t		Light;
	sensor_color_t		Color;
	
	int BWLine = 0;
	int CLine = 0;
	float Accelerator = 40;
	unsigned int objectTimer = 0;
	
	while(true){
	
		// Check if object is within range
		objectDetection(BPLine, objectTimer);
		
		if(CLine < calibratedInputs.borderValueC && BWLine > calibratedInputs.borderValueBW){
			BPLine.set_motor_power(PORT_C, 40);
			BPLine.set_motor_power(PORT_B, 40);
			Accelerator = 40;
		}
				
		// Ride for 1 step
		if(BWLine > calibratedInputs.borderValueBW){
			lineSeen(PORT_C, PORT_B, Accelerator, objectTimer, BPLine);
		}
		else if(CLine < calibratedInputs.borderValueC){
			lineSeen(PORT_B, PORT_C, Accelerator, objectTimer, BPLine);

		}
		else{
			BPLine.set_motor_power(PORT_C, 40);
			BPLine.set_motor_power(PORT_B, 40);
			Accelerator = 40;
					
			//cout << "Accelerator set to 40\n"; 
					
		}
	}
}


void objectDetection(BrickPi3 BPLine, unsigned int &objectTimer, borderValues calibratedInputs){
	int distanceToObject = 0;
	distanceToObject = getDist(BPLine);
	if(distanceToObject < 8 && distanceToObject > 0){
			objectTimer += 1;
			if(objectTimer > 500){
				evadeObject(BPLine, calibratedInputs);
			}
		}
	else{
		objectTimer -=1
	}
}

void lineSeen(uint8_t insideMotor, uint8_t outsideMotor, float &Accelerator, unsigned int &objectTimer, BrickPi3 &BPLine){
	if(Accelerator > 69){
		BPLine.set_motor_power(insideMotor, -60);
	}else{
		BPLine.set_motor_power(insideMotor, 15);
		BPLine.set_motor_power(outsideMotor, Accelerator);
	}
	if(Accelerator <= 70){
		Accelerator += 0.2;
		sleep(0.01);
	}
}
