//==================================
// Headerfile includes

#include "BrickPi3.h"
#include "AdoptoroMatrix.h"

//==================================

using namespace std; 

void matrixRider(borderValuesMatrix calibratedInputs, BrickPi3 &BPMatrix){
    
    sensor_light_t  Light;
    sensor_color_t  Color;
    
    int posX = 0;
    int posY = 0;
    int CLine = 0;
    int BWline = 0;
    int distanceToObject = 0;
    float Accelerator = 40
    int orientation = 0;
    
    while(posX != 4 && posY != 4){
        if(BPLine.get_sensor(PORT_2, Light) == 0){
			BWLine = Light.reflected;
			if(BPLine.get_sensor(PORT_3,Color) == 0){
	            CLine = Color.reflected_red;
                
                if(orientation == 0 && posY != 4 ){
                    riding(posY, PORT_B, PORTC, Accelerator, BPMatrix, orientation, Light.reflected, Color.reflected_red);
                    cout << "posY\n";
                }
                else if(orientation == 0 && posY == 4){
                    turning(PORT_B, PORT_C, BPMatrix, Light.reflected, BWLine);
                }
                else if(orientation == 1 && posX != 4){
                    riding(posX, PORT_B, PORTC, Accelerator, BPMatrix, orientation, Light.reflected, Color.reflected_red);
                }
                else if(orientation == 2 && posY != 0){
                    riding(posY, PORT_B, PORTC, Accelerator, BPMatrix, orientation, Light.reflected, Color.reflected_red);
                }
                else if(orientation == 3 && posX != 0){
                    riding(posX, PORT_B, PORTC, Accelerator, BPMatrix, orientation, Light.reflected, Color.reflected_red);
                } 
            }
        }
    }
}

void turning(uint8_t insideMotor, uint8_t outsideMotor, BrickPi3 &BPMatrix, int calibratedInputs, int sensor){
    
    BPMatrix.set_motor_power(insideMotor,-40);
    BPMatrix.set_motor_power(outsideMotor, 40);
    if(sensor > calibratedInputs){
        BPMatrix.set_motor_power(insideMotor,0);
        BPMatrix.set_motor_power(outsideMotor,0); 
        
    }
}

int turnAround(BrickPi3 &BPMatrix, int pos){
       
}

void riding(int &Pos, uint8_t PORT_B, uint8_t PORTC, int &Accelerator, BrickPi3 &BPMatrix, int orientation, int borderValueBW, int borderValueC){
     if(CLine < borderValueC && BWLine > borderValueBW){
         if(orientation == 0 || orientation == 1){
            Pos++;
         }
         else{
            Pos--;
         }
     }
     else if(BWLine > borderValueBW){
		lineSeenM(PORT_C, PORT_B, Accelerator, BPLine);
    }
    else if(CLine < borderValueC){
		lineSeenM(PORT_B, PORT_C, Accelerator, BPLine);
	}
	else{
		BPMatrix.set_motor_power(PORT_C, 40);
		BPMatrix.set_motor_power(PORT_B, 40);
		Accelerator = 40;
    }
}
                
void lineSeenM(uint8_t insideMotor, uint8_t outsideMotor, float &Accelerator, BrickPi3 &BPMatrix){
	if(Accelerator > 69){
		BPMatrix.set_motor_power(insideMotor, -60);
	}else{
		BPMatrix.set_motor_power(insideMotor, 15);
		BPMatrix.set_motor_power(outsideMotor, Accelerator);
	}
	if(Accelerator <= 70){
		Accelerator += 0.2;
		sleep(0.01);
	}
}
