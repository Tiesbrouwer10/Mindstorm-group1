#include "AdoptoroLijn.h"
#include "BrickPi3.h"

using namespace std;

int getDist(){
 
      BP.set_sensor_type(PORT_2, SENSOR_TYPE_NXT_ULTRASONIC);
      sensor_ultrasonic_t Ultrasonic2;
    
    return Ultrasonic2.cm;
    
}

void evadeObject(BrickPi3 &BPEva, borderValues &calibratedInputs){
    
	// Get value from sensors (temporary)
		if(BPLine.get_sensor(PORT_2, Light) == 0 && BPLine.get_sensor(PORT_3,Color) == 0){
			BWLine = Light.reflected;
			CLine = Color.reflected_red;
		}
				
    BPEva.set_motor_power(PORT_B, 0); // Set right wheel to stop
    BPEva.set_motor_power(PORT_C, 0); // Set left wheel to stop
    
    BPEva.set_motor_power(PORT_A, 10);
    sleep(1);
    BPEva.set_motor_power(PORT_A, 0);
}