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
	
    while(BPEva.get_motor_encoder(PORT_C) <= 469 && BPEva.get_motor_encoder(PORT_C) >= -469){
	    sleep(0.01);
    }
    BPEva.set_motor_power(PORT_B, 0);
    BPEva.set_motor_power(PORT_C, 0);
}

void drivePastObject(BrickPi3 &BPEva, borderValues calibratedInputs, bool detectLine, bool objectFound){
	
	unsigned int distanceToObject = 10;
	unsigned int objectCounter = 0;
	
	BPEva.set_motor_power(PORT_B, 20);
	BPEva.set_motor_power(PORT_C, 20);

	while(((distanceToObject >= 8 && distanceToObject != 0) && objectCounter < 500) || objectFound == false){
		
		distanceToObject = getDist(BPEva); // Get distance to object 
		
		if(distanceToObject < 8 && distanceToObject > 0){ // Test if object is found
			cout << " OBJECT FOUND! Object counter:" << objectCounter << "\n";
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
	
	while((distanceToObject <= 8 && distanceToObject > 0) && objectCounter < 500){
		distanceToObject = getDist(BPEva);
		cout << "2de While loop engaged!\n";
		if(distanceToObject > 8 && distanceToObject != 0){
			cout << "Driving past object! Object counter: " << objectCounter < "\n";
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
	
}

void evadeObject(BrickPi3 &BPEva, borderValues &calibratedInputs){
	
	sensor_light_t	Light;
	sensor_color_t	Color;
	
	int BWLine = 0;
	int CLine = 0;
	const unsigned int rotateLeft = 1;
	const unsigned int rotateRight = 2;
	int distanceToObject = 0;
    
	// Get value from sensors (temporary)
		if(BPEva.get_sensor(PORT_2, Light) == 0 && BPEva.get_sensor(PORT_3,Color) == 0){
			BWLine = Light.reflected;
			CLine = Color.reflected_red;
		}
				
    BPEva.set_motor_power(PORT_B, 0); // Set right wheel to stop
    BPEva.set_motor_power(PORT_C, 0); // Set left wheel to stop
    turnHead90degrees(BPEva, rotateRight);
    turnCar(BPEva, rotateLeft);
    drivePastObject(BPEva, calibratedInputs, false, true);
    turnCar(BPEva, rotateRight);
    drivePastObject(BPEva, calibratedInputs, false, false);
    turnCar(BPEva, rotateRight);
    turnHead90degrees(BPEva, rotateLeft);
	
	    
    sleep(500);
}
