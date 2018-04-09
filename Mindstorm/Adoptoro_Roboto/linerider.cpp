#include "AdoptoroLijn.h"
#include "BrickPi3.h"

using namespace std;

const int PORT_b = 2;
const int PORT_c = 4;

int acceleration_B = 0;
int acceleration_C = 0;
int getAcceleration(int &motor, int8_t do_up_down=0, bool set=false)
{
	//0x02 = B
	//0x04 = C
	int returnval = 0;
	switch(motor)
	{
		case PORT_b: //motor rechts
			if((acceleration_B < 90 && do_up_down <=0) || (acceleration_B > -90 && do_up_down >= 0) && !set)
			{
				acceleration_B += do_up_down;
				if(acceleration_B > 90) acceleration_B=90;//limit.
				else if(acceleration_B < -90) acceleration_B=-90;//limit.
			}
			acceleration_B = do_up_down;
			returnval = acceleration_B;
			break;
		case PORT_c: //motor links
			if((acceleration_C < 90 && do_up_down <=0) || (acceleration_C > -90 && do_up_down >= 0) && !set)
			{
				acceleration_C += do_up_down;
				if(acceleration_C > 90) acceleration_C=90;//limit.
				else if(acceleration_C < -90) acceleration_C=-90;//limit.
			}
			acceleration_C = do_up_down;
			returnval = acceleration_C;
			break;
		default:break;
	}
	return returnval;
}

void lineRider(borderValues calibratedInputs, BrickPi3 &BPLine){
	
	//BrickPi3 BPLine;
	
	BPLine.set_sensor_type(PORT_2, SENSOR_TYPE_NXT_LIGHT_ON); //light sensor
	BPLine.set_sensor_type(PORT_3, SENSOR_TYPE_NXT_COLOR_FULL); //color sensor
	
	sensor_light_t		Light; 
	sensor_color_t		Color;
	
	int BWLine = 0;
	int CLine = 0;
	int Accelerator = 40;
	
	while(true){
		// Get value from sensors
		if(BPLine.get_sensor(PORT_2, Light) == 0){ //check if sensor available
			BWLine = Light.reflected;
			if(BPLine.get_sensor(PORT_3,Color) == 0){ //check if sensor available
				CLine = Color.reflected_red;
				
				// Ride for 1 step
				if(BWLine > calibratedInputs.borderValueBW){ //0-1000 (x1.25) (de-amplifying)
					//moet naar rechts.
					int acc = getAcceleration(PORT_b);
					if(acc > 89){
						BPLine.set_motor_power(PORT_C, getAcceleration(PORT_c,-90,true)); //draaien om as (reverse andere wiel)
					}else{
						BPLine.set_motor_power(PORT_C, getAcceleration(PORT_c,15,true)); //zet linker motor trager
						BPLine.set_motor_power(PORT_B, getAcceleration(PORT_b)); //standard = 40
					}
					getAcceleration(PORT_b, 1);
					cout << Accelerator << " BW Accelerator\n";
					sleep(0.1);
				}
				else if(CLine < calibratedInputs.borderValueC){ //color sensor wijkt af.
					int acc = getAcceleration(PORT_C);
					if( acc > 89){
						BPLine.set_motor_power(PORT_B, getAcceleration(PORT_c,-90,true));
					}else{
						BPLine.set_motor_power(PORT_B, getAcceleration(PORT_b,15,true));
						BPLine.set_motor_power(PORT_B, getAcceleration(PORT_c));
					}
					getAcceleration(PORT_B, 1);
					cout << Accelerator << " C Accelerator\n";
					sleep(0.1);
				}
				else{
					BPLine.set_motor_power(PORT_C, 40);
					BPLine.set_motor_power(PORT_B, 40);
					Accelerator = 40;
					
					cout << "Accelerator set to 40\n";
				}
			}
		}
	}
}
