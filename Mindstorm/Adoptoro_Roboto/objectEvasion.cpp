#include "AdoptoroLijn.h"
#include "BrickPi3.h"

using namespace std;

int getDist(BrickPi3 &BPEva){
	
	// Gets the value from the ultrasonic sensor and returns the distance in Cm.
	
	sensor_ultrasonic_t Ultrasonic2;
	
	if(BPEva.get_sensor(PORT_1, Ultrasonic2) == 0){
		return Ultrasonic2.cm;
 	}
	
}

void turnHead90degrees(BrickPi3 &BPEva, int rotateDirection){
	
	// Rotates robot head 90* left or right.
	
	int rotation = 10;	// Creates rotation for robot
	if(rotateDirection == 2){
		rotation *= -1;
	}
	
    BPEva.offset_motor_encoder(PORT_A, BPEva.get_motor_encoder(PORT_A)); // Gets motor encoder
    BPEva.set_motor_power(PORT_A, rotation);
	
    while(BPEva.get_motor_encoder(PORT_A) >= -89 && BPEva.get_motor_encoder(PORT_A) <= 89 ){ // Rotates it until the desired rotation is met (90)
	    sleep(0.01);
    }
    BPEva.set_motor_power(PORT_A, 0); // Stops motor
}

void turnCar(BrickPi3 &BPEva, int rotateDirection){
	
	// Turns the car ~90* left or right. 
	
	int motorPower = 30; // Sets car to turn left or right
	if(rotateDirection == 2){
		motorPower *= -1;
	}
	
    BPEva.offset_motor_encoder(PORT_C, BPEva.get_motor_encoder(PORT_C)); // Gets motor encoders
    BPEva.set_motor_power(PORT_C, (motorPower * -1)); 
    BPEva.set_motor_power(PORT_B, motorPower);
	
    while(BPEva.get_motor_encoder(PORT_C) <= 520 && BPEva.get_motor_encoder(PORT_C) >= -520){ // Rotates it until desired rotation is met (90)
	    sleep(0.01);
    }
	
	// Shuts down the motors
    BPEva.set_motor_power(PORT_B, 0);
    BPEva.set_motor_power(PORT_C, 0);
}

void drivePastObject(BrickPi3 &BPEva, borderValues calibratedInputs, bool detectLine, bool objectFound, bool &foundLine){
	
	// Contains 2 while loops. First will detect if it has found an object, second one will detect
	// Wether it has passed the object. 
	
	unsigned int distanceToObject = 10;
	unsigned int objectCounter = 0;
	
	BPEva.set_motor_power(PORT_B, 20);
	BPEva.set_motor_power(PORT_C, 20);

	while(objectCounter < 500 && objectFound == false){ // Checks wether it has found the object
		cout << "In eerste while loop: " << objectCounter << "\n";
		// Checks if line is found
		if(detectLine == true){
			foundLine = findLine(calibratedInputs, BPEva, foundLine);
		}
		if(foundLine == true){ // If the line is found it will skip through the code
			return;
		}
		
		distanceToObject = getDist(BPEva); // Get distance to object 
		
		if(distanceToObject < 15 && distanceToObject > 0){ // Test if object is found
			cout << " OBJECT FOUND!\n";
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
	
	while(objectCounter < 500){ // Checks wether it has passed the object
		cout << "In eerste while loop: " << objectCounter << "\n";
		// Checks if line is found
		if(detectLine == true){
			foundLine = findLine(calibratedInputs, BPEva, foundLine);
		}
		if(foundLine == true){ // If the line is found it will skip through the code
			return;
		}
		
		distanceToObject = getDist(BPEva); // Gets distance to object
		
		if(distanceToObject > 15 && distanceToObject != 0){
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
	sleep(4);
}

bool findLine(borderValues calibratedInputs, BrickPi3 &BPEva, bool &foundLine){ // Checks wether the line was found
	
	// Declaration
	sensor_light_t	Light;
	sensor_color_t	Color;
	
	int BWLine = 0;
	int CLine = 0;
	
	// Checks if line was already found
	if(foundLine == true){ // Skips if line is already found (preventive)
		return foundLine;
	}
		if(BPEva.get_sensor(PORT_3,Color) == 0){
				CLine = Color.reflected_red;
		}
		if(CLine < calibratedInputs.borderValueC){ // Checks if black is detected
				foundLine = true;
		}
		else{
			foundLine = false; // No black detected
		}
return foundLine;
}

void returnToLine(BrickPi3 &BPEva, borderValues calibratedInputs, int rotateRight, int rotateLeft){
	
	sensor_light_t	Light;
	sensor_color_t	Color;
	
	// Declaration of the values needed
	int BWLine = 0;
	int CLine = 0;
	
	// Gets the sensor Values to go off of
	if(BPEva.get_sensor(PORT_2, Light) == 0){
			BWLine = Light.reflected;
		if(BPEva.get_sensor(PORT_3,Color) == 0){
				CLine = Color.reflected_red;
		}
	}
	
	// Checks wether it finds the line and stops the robot
	while(true){
		
		
		if(BPEva.get_sensor(PORT_2, Light) == 0){ // Checks light sensors
			BWLine = Light.reflected;
			if(BPEva.get_sensor(PORT_3,Color) == 0){
					CLine = Color.reflected_red;
			}
		}
		
		if(CLine < calibratedInputs.borderValueC){ // Drives until it finds white
			BPEva.set_motor_power(PORT_B, 60);
			BPEva.set_motor_power(PORT_C, -20);
		}
		else{
			sleep(0.5);
			BPEva.set_motor_power(PORT_B, 0); // Set right wheel to stop
			BPEva.set_motor_power(PORT_C, 0); // Set left wheel to stop
			sleep(2);
			break;
		}
		
	}
	
	// Second loop checks wether it finds black and then continues to follow line
	while(true){
		
		// Checks light sensors
		if(BPEva.get_sensor(PORT_2, Light) == 0){
			BWLine = Light.reflected;
			if(BPEva.get_sensor(PORT_3,Color) == 0){
					CLine = Color.reflected_red;
			}
		}
		
		if(CLine > calibratedInputs.borderValueC){
			BPEva.set_motor_power(PORT_B, 90);
			BPEva.set_motor_power(PORT_C, -10);
	}
			else{
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
	sleep(0.2);
	// Stops at Line and gets ready to continue
	BPEva.set_motor_power(PORT_B, 0);
	BPEva.set_motor_power(PORT_C, 0);
	turnHead90degrees(BPEva, rotateLeft);
	returnToLine(BPEva, calibratedInputs, rotateRight, rotateLeft); // Returns the robot to the line
	
    // End of object Evasion
	return;
}
