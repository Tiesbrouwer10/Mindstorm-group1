#include "AdoptoroLijn.h"
#include "BrickPi3.h"

using namespace std;

int getDist(BrickPi3 &BPEva){
      	sensor_ultrasonic_t Ultrasonic2;
	if(BPEva.get_sensor(PORT_1, Ultrasonic2) == 0){
		return Ultrasonic2.cm;
 	}
	
}

void turnHead90degrees(BrickPi3 &BPEva, int rotateDirection){
	
	int rotation = 10;	// Creates rotation for robot
	if(rotateDirection == 2){
		rotation *= -1;
	}
	
    BPEva.offset_motor_encoder(PORT_A, BPEva.get_motor_encoder(PORT_A));
    BPEva.set_motor_power(PORT_A, rotation);
	
    while(BPEva.get_motor_encoder(PORT_A) >= -89 && BPEva.get_motor_encoder(PORT_A) <= 89 ){
	    sleep(0.01);
    }
    BPEva.set_motor_power(PORT_A, 0); 
}

void turnCar(BrickPi3 &BPEva, int rotateDirection){
	
	int motorPower = 30; // Sets car to turn left or right
	if(rotateDirection == 2){
		motorPower *= -1;
	}
	
    BPEva.offset_motor_encoder(PORT_C, BPEva.get_motor_encoder(PORT_C));
    BPEva.set_motor_power(PORT_C, (motorPower * -1));
    BPEva.set_motor_power(PORT_B, motorPower);
	
    while(BPEva.get_motor_encoder(PORT_C) <= 489 && BPEva.get_motor_encoder(PORT_C) >= -489){
	    sleep(0.01);
    }
    BPEva.set_motor_power(PORT_B, 0);
    BPEva.set_motor_power(PORT_C, 0);
}

void drivePastObject(BrickPi3 &BPEva, borderValues calibratedInputs, bool detectLine, bool objectFound, bool &foundLine){
	
	unsigned int distanceToObject = 10;
	unsigned int objectCounter = 0;
	
	BPEva.set_motor_power(PORT_B, 20);
	BPEva.set_motor_power(PORT_C, 20);

	while(objectCounter < 500 && objectFound == false){
		
		// Checks if line is found
		if(detectLine == true){
			foundLine = findLine(calibratedInputs, BPEva, foundLine);
		}
		if(foundLine == true){
			return;
		}
		
		distanceToObject = getDist(BPEva); // Get distance to object 
		
		if(distanceToObject < 15 && distanceToObject > 0){ // Test if object is found
			cout << " OBJECT FOUND! OBject counter:" << objectCounter << "\n";
			objectCounter += 1;
		}
		else if(objectCounter > 0){
			objectCounter -= 1;
		}
		else{
			continue;
		}
	}
	
	objectCounter = 0;
	
	while(objectCounter < 500){
		
		// Checks if line is found
		if(detectLine == true){
			foundLine = findLine(calibratedInputs, BPEva, foundLine);
		}
		if(foundLine == true){
			return;
		}
		
		distanceToObject = getDist(BPEva);
		
		cout << "2de While loop engaged!\n";
		if(distanceToObject > 15 && distanceToObject != 0){
			cout << "Driving past object! Object counter: " << objectCounter << "\n";
			objectCounter += 1;
		}
		else if(objectCounter > 0){
			objectCounter -= 1;
			continue;
		}
		else{
			continue;
		}
		
	}
	sleep(3);
}

bool findLine(borderValues calibratedInputs, BrickPi3 &BPEva, bool &foundLine){
	
	// Declaration
	sensor_light_t	Light;
	sensor_color_t	Color;
	
	int BWLine = 0;
	int CLine = 0;
	
	// Checks if line was already found
	if(foundLine == true){
		return foundLine;
	}
	
	if(BPEva.get_sensor(PORT_2, Light) == 0){
		BWLine = Light.reflected;
		if(BPEva.get_sensor(PORT_3,Color) == 0){
				CLine = Color.reflected_red;
		}
		if(BWLine > calibratedInputs.borderValueBW){
				foundLine = true;
			}
		if(CLine < calibratedInputs.borderValueC){
				foundLine = true;
		}
		else{
			foundLine = false;
		}
	}
	return foundLine;
}

void returnToLine(BrickPi3 &BPEva, borderValues calibratedInputs, int rotateRight, int rotateLeft){
	
	// Declaration
	sensor_light_t	Light;
	sensor_color_t	Color;
	
	int BWLine = 0;
	int CLine = 0;
	int speedPositive = 30;
	int speedNegative = -30;
	
	// Gets the sensor Values for the first time
	if(BPEva.get_sensor(PORT_2, Light) == 0){
			BWLine = Light.reflected;
		if(BPEva.get_sensor(PORT_3,Color) == 0){
				CLine = Color.reflected_red;
		}
	}

	cout << "Hij bereikt de While loop!\n";
	while(true){
		
		// Checks light sensors
		if(BPEva.get_sensor(PORT_2, Light) == 0){
			BWLine = Light.reflected;
			if(BPEva.get_sensor(PORT_3,Color) == 0){
					CLine = Color.reflected_red;
			}
		}
		// Decides how to turn
		if(BWLine > calibratedInputs.borderValueBW && CLine < calibratedInputs.borderValueC){
			cout << "Hij draait nu op de lijn1\n";
			// Turns right or left based on speed
			BPEva.set_motor_power(PORT_B, speedPositive*2);
			BPEva.set_motor_power(PORT_C, speedNegative); 
		}
		else if(BWLine < calibratedInputs.borderValueBW && CLine < calibratedInputs.borderValueC){
			cout << "Hey ik ben er\n";
			//Turns right motor off to correct left side
			BPEva.set_motor_power(PORT_B, 0); 
			BPEva.set_motor_power(PORT_C, speedNegative); 
		}
		else if(BWLine > calibratedInputs.borderValueBW && CLine > calibratedInputs.borderValueC){
			cout << "Hallo!\n";
			// Turns left motor off to correct right side
			BPEva.set_motor_power(PORT_B, speedPositive*2); 
			BPEva.set_motor_power(PORT_C, 0); 
		}
		else{
			cout << "Hij is klaar!\n";
			BPEva.set_motor_power(PORT_B, 0); // Set right wheel to stop
			BPEva.set_motor_power(PORT_C, 0); // Set left wheel to stop
			sleep(2);
			break;
		}
	}
	return;
}

void evadeObject(BrickPi3 &BPEva, borderValues &calibratedInputs){
	
	//==========================================================================
	// Declaration
	const unsigned int rotateLeft = 1; // Base case = 1
	const unsigned int rotateRight = 2; // Base case = 2
	//  If want to invert rotate angle, swap values.
	bool foundLine = false;
	
	// Stops both motors and sets up object evasion procedure
	BPEva.set_motor_power(PORT_B, 0); // Set right wheel to stop
    BPEva.set_motor_power(PORT_C, 0); // Set left wheel to stop
				
	//==========================================================================
	// Steps to evade object
	
    turnHead90degrees(BPEva, rotateRight);
    turnCar(BPEva, rotateLeft);
    drivePastObject(BPEva, calibratedInputs, false, true, foundLine);
	
	// Keeps turning and driving around object until it finds a line
	while(foundLine == false){
		turnCar(BPEva, rotateRight);
		drivePastObject(BPEva, calibratedInputs, true, false, foundLine);
	}
	// Stops at Line and gets ready to continue
	BPEva.set_motor_power(PORT_B, 0);
	BPEva.set_motor_power(PORT_C, 0);
	turnHead90degrees(BPEva, rotateLeft);
	returnToLine(BPEva, calibratedInputs, rotateRight, rotateLeft); // Returns the robot to the line
	
    sleep(1); // End of object Evasion
	return;
}