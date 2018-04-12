
//==================================
// Headerfile includes

#include "BrickPi3.h"
#include "AdoptoroLijn.h"

//==================================

using namespace std; 

void matrix(borderValues calibratedInputs, BrickPi3 &BPMatrix){
	
	sensor_light_t  Light;
 	sensor_color_t  Color;
    
 	int posX = 0;
 	int posY = 0;
 	int CLine = 0;
 	int BWLine = 0;
 	int distanceToObject = 0;
 	float Accelerator = 40;
 	int orientation = 0;
 
 	while(posX != 4 && posY != 4){
     		if(BPMatrix.get_sensor(PORT_2, Light) == 0){
	       		BWLine = Light.reflected;
	          	if(BPMatrix.get_sensor(PORT_3,Color) == 0){
	             		CLine = Color.reflected_red;
                
              			if(orientation == 0 && posY != 4 ){
                			riding(PORT_B, PORT_C, Accelerator, BPMatrix, CLine, BWLine, calibratedInputs.borderValueC, calibratedInputs.borderValueBW, orientation, posY);
					posY++;
					cout << posY << " :DE Y PLEK\n";
            			} 																					
				else{
					break;
				}
         		}
      		}
   	}
}

void riding(uint8_t rightMotor, uint8_t leftMotor, float &Accelerator, BrickPi3 &BPMatrix, int CLine, int BWLine, int borderValueC, int borderValueBW, int orientation, int &Pos){
     	if(CLine < borderValueC && BWLine > borderValueBW){
     		sleep(0.5);
		BPMatrix.set_motor_power(rightMotor, 0);
		BPMatrix.set_motor_power(leftMotor, 0);
		cout << "ZIE EEN KRUISPUNT\n";
     	}
     	else if(BWLine > borderValueBW){
		lineSeenM(leftMotor, rightMotor, Accelerator, BPMatrix);
    	}
    	else if(CLine < borderValueC){
		lineSeenM(rightMotor, leftMotor, Accelerator, BPMatrix);
	}
	else{
		BPMatrix.set_motor_power(rightMotor, 40);
		BPMatrix.set_motor_power(leftMotor, 40);
		Accelerator = 40;
    	}
}

void lineSeenM(uint8_t insideMotor, uint8_t outsideMotor, float &Accelerator, BrickPi3 &BPMatrix){
	if(Accelerator > 69){
		BPMatrix.set_motor_power(insideMotor, -60);
	}else{
		BPMatrix.set_motor_power(insideMotor, 15);
		BPMatrix.set_motor_power(outsideMotor, Accelerator);
	}
	if(Accelerator <= 70){
		Accelerator += 0.2;
		sleep(0.01);
	}
}

