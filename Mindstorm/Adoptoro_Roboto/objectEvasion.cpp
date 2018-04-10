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
    sleep(5);
    cout << "heloo its me";
    BPEva.offset_motor_encoder(PORT_A, Eva.get_motor_encoder(PORT_A));
    BPEva.set_motor_position_relative(PORT_A, 90);
    BPEva.set_motor_position_relative(PORT_B, -450);
    BPEva.set_motor_position_relative(PORT_C, 450);
    sleep(10);
    BPEva.set_motor_power(PORT_A, 0);
}
