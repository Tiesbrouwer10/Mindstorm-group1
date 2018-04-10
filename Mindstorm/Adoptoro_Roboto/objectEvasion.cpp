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

void turnMotor(int port, int degrees, BrickPi3 &BPEva){
    int speed = 40;
    if (degrees < 0){
	    speed = -40;
    }
    if(port == 1){
	    BPEva.offset_motor_encoder(PORT_A, BPEva.get_motor_encoder(PORT_A));
	    BPEva.set_motor_power(PORT_A, 10);
	    while(BPEva.get_motor_encoder(PORT_A) < (degrees+1)){
		    cout << BPEva.get_motor_encoder(PORT_A) << "\n";
		    sleep(0.01);
	    }
	    BPEva.set_motor_power(PORT_A, 0);
    }
    if(port == 2){
	    BPEva.offset_motor_encoder(PORT_B, BPEva.get_motor_encoder(PORT_B));
	    BPEva.set_motor_power(PORT_B, speed);
	    while(BPEva.get_motor_encoder(PORT_B) < (degrees+1)){
		    cout << BPEva.get_motor_encoder(PORT_B) << "\n";
		    sleep(0.01);
	    }
	    BPEva.set_motor_power(PORT_B, 0);
    }  
    if(port == 3){
	    BPEva.offset_motor_encoder(PORT_C, BPEva.get_motor_encoder(PORT_C));
	    BPEva.set_motor_power(PORT_C, speed);
	    while(BPEva.get_motor_encoder(PORT_C) < (degrees+1)){
		    cout << BPEva.get_motor_encoder(PORT_C) << "\n";
		    sleep(0.01);
	    }
	    BPEva.set_motor_power(PORT_C, 0);
    }    
}

void evadeObject(BrickPi3 &BPEva, borderValues &calibratedInputs){
	
	sensor_light_t	Light;
	sensor_color_t	Color;
	
	int BWLine = 0;
	int CLine = 0;
    
	// Get value from sensors (temporary)
		if(BPEva.get_sensor(PORT_2, Light) == 0 && BPEva.get_sensor(PORT_3,Color) == 0){
			BWLine = Light.reflected;
			CLine = Color.reflected_red;
		}
				
    BPEva.set_motor_power(PORT_B, 0); // Set right wheel to stop
    BPEva.set_motor_power(PORT_C, 0); // Set left wheel to stop
    cout << "heloo its me";
    turnMotor(1, 90, BPEva);
    turnMotor(2, 450, BPEva);
    turnMotor(3, -450, BPEva);
    sleep(500);
}
