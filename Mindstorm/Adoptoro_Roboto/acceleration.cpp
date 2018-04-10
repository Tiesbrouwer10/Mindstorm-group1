#include "AdoptoroLijn.h"
#include "BrickPi3.h"

using namespace std;

	int MOTOR_B = 2; // Value of motor B
	int MOTOR_C = 4; // Value of motor C
	
	int accelerationB = 0; // Acceleration value of B
	int accelerationC = 0; // Acceleration value of C

int getAcceleration(int MOTOR, int acceleration = 0 ,bool setSpeed = false){
	
	int returnSpeed = 0; // Return statement value
	
	switch(MOTOR){
	
		case 2:// Motor Right
			if((accelerationB < 90 && acceleration <= 0) || (accelerationB > -90 && acceleration >= 0) && setSpeed != true){
				
				accelerationB += acceleration;
					if(accelerationB > 90){
						accelerationB = 90; // Hard limits the negative speed limits
					}
					else if(accelerationB < -90){
						accelerationB = -90; // Hard limits the negative speed limits
					}
			}
			else{
				accelerationB = acceleration; // If not setspeed acceleration is the set value
			}
			returnSpeed = accelerationB;
			break;
		
		case 4: // Motor Left
			if((accelerationC < 90 && acceleration <= 0) || (accelerationC > -90 && acceleration >= 0) && setSpeed != true){
				
				accelerationC += acceleration;
					if(accelerationC > 90){
						accelerationC = 90; // Hard limits the negative speed limits
					}
					else if(accelerationC < -90){
						accelerationC = -90; // Hard limits the negative speed limits
					}
			}
			else{
				accelerationC = acceleration; // If not setspeed acceleration is the set value
			}
			returnSpeed = accelerationC;
			break;
	}
	return returnSpeed;
}
