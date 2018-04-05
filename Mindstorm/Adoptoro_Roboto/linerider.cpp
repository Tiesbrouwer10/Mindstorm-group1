#include "AdoptoroLijn.h"
#include "BrickPi3.h"

using namespace std;



void lineRider(borderValues calibratedInputs){
	
	BrickPi3 BPLine;
	sensor_light_t		Light;
	sensor_color_t		Color;
	
	while(true){
		// Get value from sensors
		cout << "ZIT IN DE WHILE LOOP";
		if(BPLine.get_sensor(PORT_2, Light) == 0){
			if(BPLine.get_sensor(PORT_3,Color) == 0){
				cout << "BW SCANNED: " << Light.reflected << " BWVALUE = " << calibratedInputs.borderValueBW << '\n';
				cout << "C  SCANNED: " << Color.reflected_red << "  CVALUE = " << calibratedInputs.borderValueC << '\n';
				sleep(1);
				cout << "SLEEP DONE\n";
				// Ride for 1 step
				if(Light.reflected > calibratedInputs.borderValueBW){
					BPLine.set_motor_power(PORT_C, 10);
				}
				else if(Color.reflected_red < calibratedInputs.borderValueC){
			BPLine.set_motor_power(PORT_B, 10);
				}
				else{
					BPLine.set_motor_power(PORT_C, 20);
					BPLine.set_motor_power(PORT_B, 20);
				}
			}
		}
	}
}
