#include "AdoptoroLijn.h"
#include "BrickPi3.h"

using namespace std;

int getDist(BrickPi3 &BPEva){
      	sensor_ultrasonic_t Ultrasonic2;
	if(BPEva.get_sensor(PORT_1, Ultrasonic2) == 0){
		cout << "De sensor meet afstand: " << Ultrasonic2.cm<< "\n";
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
	    cout << BPEva.get_motor_encoder(PORT_A) << "\n";
	    sleep(0.01);
    }
    BPEva.set_motor_power(PORT_A, 0); 
}
void turnCar(BrickPi3 &BPEva, int rotateDirection){
	
	int motorPower = 30; // Sets car to turn left or right
	if(rotateDirection == 2){
		motorPower *= -1;
	}
	
    BPEva.offset_motor_encoder(PORT_B, BPEva.get_motor_encoder(PORT_B));
    BPEva.set_motor_power(PORT_B, (motorPower * -1));
    BPEva.set_motor_power(PORT_C, motorPower);
	
    while(BPEva.get_motor_encoder(PORT_B) <= 469 && BPEva.get_motor_encoder(PORT_B) >= -469){
	    cout << BPEva.get_motor_encoder(PORT_B) << "\n";
	    sleep(0.01);
    }
    BPEva.set_motor_power(PORT_B, 0);
    BPEva.set_motor_power(PORT_C, 0);
}

void evadeObject(BrickPi3 &BPEva, borderValues &calibratedInputs){
	
	sensor_light_t	Light;
	sensor_color_t	Color;
	
	int BWLine = 0;
	int CLine = 0;
	const unsigned int rotateLeft = 1;
	const unsigned int rotateRight = 2;
    
	// Get value from sensors (temporary)
		if(BPEva.get_sensor(PORT_2, Light) == 0 && BPEva.get_sensor(PORT_3,Color) == 0){
			BWLine = Light.reflected;
			CLine = Color.reflected_red;
		}
				
    BPEva.set_motor_power(PORT_B, 0); // Set right wheel to stop
    BPEva.set_motor_power(PORT_C, 0); // Set left wheel to stop
    cout << "heloo its me";
    turnHead90degrees(BPEva, rotateLeft);
    turnCar(BPEva, rotateLeft);
    sleep(500);
}
