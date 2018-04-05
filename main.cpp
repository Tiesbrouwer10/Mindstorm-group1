#include <stdio.h>
#include "BrickPi3.h"
#include "Adoptorolijn.h"
#include "AdoptoroMTRIX.H"

using namespace std;

void accelerator(){
    for(unsigned int i=0;i<25;i+5){
        set_motor_power(PORT_C,i);
        set_motor_power(PORT_B,i)
        Sleep(0.1);
    }
}

int main(int argc, char **argv)
{
	printf("hello world\n");
	return 0;
}
