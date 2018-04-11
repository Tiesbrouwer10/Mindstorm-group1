//==================================
// Headerfile includes

#include "BrickPi3.h"
#include "AdoptoroMatrix.h"

//==================================

using namespace std; 

void matrix(borderValues calibratedInputs){
    
    BrickPi3 BPMatrix;
    
    BPMatrix.set_sensor_type(PORT_2, SENSOR_TYPE_NXT_LIGHT_ON);
    BPMatrix.set_sensor_type(PORT_3, SENSOR_TYPE_NXT_COLOR_FULL);
    
    sensor_light_t  Light;
    sensor_color_t  Color;
    
    int posX = 0;
    int posY = 0;
    

    while (true){
        // Get value from sensors
        if(BPLine.get_sensor(PORT_2, Light) == 0){
            BWLine = Light.reflected;
            if(BPLine.get_sensor(PORT_3,Color) == 0){
                CLine = Color.reflected_red;
                
                //controls if X coördinate is the same as the X goal
                while(posX != 4){
                    BPLine.set_motor_power(PORT_C, 40);
                    BPLine.set_motor_power(PORT_B, 40);
                    if(BWLine > calibratedInputs.borderValueBW &&  CLine < calibratedInputs.borderValueC){
                        BPLine.set_motor_power(PORT_C, 0);
                        BPLine.set_motor_power(PORT_B, 0);
                        X++;
                    }
                }
                turnRight();
                while(posY != 4){
                    BPLine.set_motor_power(PORT_C, 40);
                    BPLine.set_motor_power(PORT_B, 40);
                    if(BWLine > calibratedInputs.borderValueBW &&  CLine < calibratedInputs.borderValueC){
                        BPLine.set_motor_power(PORT_C, 0);
                        BPLine.set_motor_power(PORT_B, 0);
                        Y++;
                    }
                }
                
            }
        }
        break;
    }
}

void turnRight(){
    BPMatrix.set_motor_power(PORT_B,-40);
    BPMatrix.set_motor_power(PORT_C, 40);
    if(BWLine > calibratedInputs.borderValueBW){
        BPMatrix.set_motor_power(PORT_B,0);
        BPMatrix.set_motor_power(PORT_C,0);   
    }
}
