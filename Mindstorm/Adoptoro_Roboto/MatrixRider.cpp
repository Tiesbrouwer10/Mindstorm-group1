
//==================================
// Headerfile includes

#include "BrickPi3.h"
#include "AdoptoroLijn.h"

//==================================

using namespace std; 

/*

borderValues calibratedInputs = The struct with the values of what white is for the color and black/white sensor
BrickPi3 &BPMatrix = the syncronisation of all the sensors

*/

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
 	
	//if his position is not (4, 4) he will not stop
 	while(posX != 3 || posY != 3){
		//gets a value from the color value and black/white sensor
     		if(BPMatrix.get_sensor(PORT_2, Light) == 0){
	       		BWLine = Light.reflected;
	          	if(BPMatrix.get_sensor(PORT_3,Color) == 0){
	             		CLine = Color.reflected_red;
                
              			if(posY != 3 ){
                			riding(PORT_B, PORT_C, Accelerator, BPMatrix, CLine, BWLine, calibratedInputs.borderValueC, calibratedInputs.borderValueBW, orientation, posY);
					
					cout << posY << " :DE Y PLEK\n";
            			} 																					
				else if(posY == 3){
					cout << "IK GA BREAKEN\n";
					BPMatrix.set_motor_power(PORT_B, 0);
					BPMatrix.set_motor_power(PORT_C, 0);
					break;
				}
         		}
      		}
   	}
	cout << "UIT DE WHILE LOOP\n";
	BPMatrix.set_motor_power(PORT_B, 0);
	BPMatrix.set_motor_power(PORT_C, 0);
}
/*

uint8_t rightMotor = The motor that is on the right side
uint8_t leftMotor = The motor that is on the left side
float &Accelerator = The speed of the motor(s)  
BrickPi3 &BPMatrix = The syncronisation of all the sensors
int CLine = The value that the color sensor measures
int BWLine = The value that the black/white sensor measures
int borderValueC = The value for what the color sensor sees as white
int borderValueBW = The value for what the black/white sensor sees as white 
int orientation = what position he is facing (0 = N, 1 = E, 2 = S, 3 = W) 
int &Pos = The coördinate where he is or moving

*/
void riding(uint8_t rightMotor, uint8_t leftMotor, float &Accelerator, BrickPi3 &BPMatrix, int CLine, int BWLine, int borderValueC, int borderValueBW, int orientation, int &Pos){
     	// if both sensors doesn't measure white
	if(CLine < borderValueC && BWLine > borderValueBW){
     		cout << "ZIE EEN KRUISPUNT\n";
		Pos++;
		sleep(0.9);

     	}
	// if the black/white sensor doesn't measure white
     	else if(BWLine > borderValueBW){
		cout << "NAAR RECHTS BIJSTUREN\n";
		lineSeenM(leftMotor, rightMotor, Accelerator, BPMatrix);
    	}
	//if the color sensor doesn't measure white
    	else if(CLine < borderValueC){
		cout << "NAAR LINKS BIJSTUREN\n";
		lineSeenM(rightMotor, leftMotor, Accelerator, BPMatrix);
	}
	// if both sensors measures white
	else{
		BPMatrix.set_motor_power(rightMotor, 40);
		BPMatrix.set_motor_power(leftMotor, 40);
		Accelerator = 40;
    	}
}
/*

uint8_t insideMotor = The motor thats on the inside of the turn
uint8_t outsideMotor = The motor thats on the outside of the turn
float &Accelerator = 
BrickPi3 &BPMatrix = syncronisation of the sensors

*/
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

