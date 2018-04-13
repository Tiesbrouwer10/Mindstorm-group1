// Authors Jasper de WInther, Tony van der Krogt

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
	int temp = 0;
 	
	//if his position is not (4, 4) he will not stop
 	while(posX != 4 || posY != 4){
		//gets a value from the color value and black/white sensor
     		
		cout << posY << ", " << posX << ", " << orientation << "\n";
		BPMatrix.set_motor_power(PORT_B, 0);
		BPMatrix.set_motor_power(PORT_C, 0);
		for(unsigned int i = 0; i < 5; i++){ // Asks for 5 ultrasonic values
			temp = getDist(BPMatrix);
			if(temp > 0){
				distanceToObject += temp;
			}else if(i >= 0){ // If ultrasonic error is detected, (value 0) it will ask for another value
				i--;
			}
		}
		distanceToObject /= 8; 
		if(distanceToObject < 25){ // Driving around object
			
			turnRight(PORT_B, PORT_C, BPMatrix, calibratedInputs.borderValueBW, Light, orientation); // Turns right
			cout << distanceToObject << " distance \n";
			riding(PORT_B, PORT_C, Accelerator, BPMatrix, calibratedInputs.borderValueC, calibratedInputs.borderValueBW, posX, Light, Color, orientation); // Drives straight ahead until crossroad
			cout << distanceToObject << " distance \n";
			turnLeft(PORT_C, PORT_B, BPMatrix, calibratedInputs.borderValueC, Color, orientation); // Turns back left
      			riding(PORT_B, PORT_C, Accelerator, BPMatrix, calibratedInputs.borderValueC, calibratedInputs.borderValueBW, posX, Light, Color, orientation);
			turnLeft(PORT_C, PORT_B, BPMatrix, calibratedInputs.borderValueC, Color, orientation);
		}
		else if(((posY < 4 && posY > -1) && (orientation == 0 ||orientation == 2)) || ((posX < 4 && posX > -1) && (orientation == 1 ||orientation == 3))){ // If within grid
			
			//Object orientation driving, remembers the orientation and drives remembering the orientation and position in the grid
			if (orientation == 0){
				riding(PORT_B, PORT_C, Accelerator, BPMatrix, calibratedInputs.borderValueC, calibratedInputs.borderValueBW, posY, Light, Color, orientation);																					
			}else if(orientation == 1){
				riding(PORT_B, PORT_C, Accelerator, BPMatrix, calibratedInputs.borderValueC, calibratedInputs.borderValueBW, posX, Light, Color, orientation);	
			}else if(orientation == 2){
				riding(PORT_B, PORT_C, Accelerator, BPMatrix, calibratedInputs.borderValueC, calibratedInputs.borderValueBW, posY, Light, Color, orientation);
			}else if(orientation == 3){
				riding(PORT_B, PORT_C, Accelerator, BPMatrix, calibratedInputs.borderValueC, calibratedInputs.borderValueBW, posX, Light, Color, orientation);
			}
			sleep(0.2);
		}else{
			turnRight(PORT_B, PORT_C, BPMatrix, calibratedInputs.borderValueBW, Light, orientation); // If about to leave matrix it will turn right
		}
	}
	
	// Stops the motors
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
void riding(uint8_t rightMotor, uint8_t leftMotor, float &Accelerator, BrickPi3 &BPMatrix, int borderValueC, int borderValueBW, int &Pos, sensor_light_t  &Light, sensor_color_t  &Color, int &orientation){
	int CLine = 0;
 	int BWLine = 0;
	while(true){
		if(BPMatrix.get_sensor(PORT_2, Light) == 0){ 
	       		BWLine = Light.reflected;
	          	if(BPMatrix.get_sensor(PORT_3,Color) == 0){
	             		CLine = Color.reflected_red;
				// if both sensors doesn't measure white
				if(CLine < borderValueC && BWLine > borderValueBW){ // Checks if it rotates the right way
					BPMatrix.set_motor_power(rightMotor, 40);
					BPMatrix.set_motor_power(leftMotor, 40);
					Accelerator = 40;
					if(orientation == 0 || orientation == 1){ // Changes position based on orientation
						Pos++; // Changes position (+1)
					}
					else{
						Pos--; // Changes position (-1)
					}
					sleep(1);
					return;

				}
				// if the black/white sensor doesn't measure white
				if(BWLine > borderValueBW){
					lineSeenM(leftMotor, rightMotor, Accelerator, BPMatrix);
				}
				//if the color sensor doesn't measure white
				else if(CLine < borderValueC){
					lineSeenM(rightMotor, leftMotor, Accelerator, BPMatrix);
				}
				// if both sensors measures white
				else{
					BPMatrix.set_motor_power(rightMotor, 40);
					BPMatrix.set_motor_power(leftMotor, 40);
					Accelerator = 40;
				}
			}
    		}
	}
}
/*
uint8_t insideMotor = The motor thats on the inside of the turn
uint8_t outsideMotor = The motor thats on the outside of the turn
float &Accelerator = Accelerates and gets higher value the longer the sensor detects a black line
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

void turnRight(uint8_t insideMotor, uint8_t outsideMotor, BrickPi3 &BPMatrix, int calibratedInputs, sensor_light_t  &Light, int &orientation){ // Turns the robot right
	int BWLine = 0;
	BPMatrix.set_motor_power(insideMotor,-40); // Motor power for turning right
	BPMatrix.set_motor_power(outsideMotor, 40);
	sleep(1);
	while(true){
		if(BPMatrix.get_sensor(PORT_2, Light) == 0){
			BWLine = Light.reflected;
			if(BWLine > calibratedInputs){ // Detects if it finds a black line
				BPMatrix.set_motor_power(insideMotor, 0); // Stops robot
				BPMatrix.set_motor_power(outsideMotor, 0);
				orientation++; // Changes orientation to rotate right (+1)
				if(orientation == 4){ // If orientation surpasses the 4th angle it will reset to the first
					orientation = 0;
				}
				break;
			}
		}
	}
}

void turnLeft(uint8_t insideMotor, uint8_t outsideMotor, BrickPi3 &BPMatrix, int calibratedInputs, sensor_color_t  &Color, int &orientation){ // Turns the robot left
	int CLine = 0;
	BPMatrix.set_motor_power(insideMotor,-40); // Motor power for turning left
	BPMatrix.set_motor_power(outsideMotor, 40);
	sleep(1);
	while(true){
		if(BPMatrix.get_sensor(PORT_3, Color) == 0){
			CLine = Color.reflected_red;
			if(CLine < calibratedInputs){ // Detects if it finds a black line
				BPMatrix.set_motor_power(insideMotor, 0); // Stops robot
				BPMatrix.set_motor_power(outsideMotor, 0);
				orientation--; // Changes orientation to rotate left (-1)
				if(orientation == -1){ // If orientation surpasses the 4th angle it will reset to the first
					orientation = 3;
				}
				break;
			}
		}
	}
}
