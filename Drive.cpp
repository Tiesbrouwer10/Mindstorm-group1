#include "BrickPi3.h"
#include <unistd.h>

int DriveForward(){
	for(unsinged i = 0; i < 25; i++){
		set_motor_power(PORT_B, i);
		set_motor_power(PORT_C, i);
		sleep(10);
	}
}
