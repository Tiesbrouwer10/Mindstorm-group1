
//==================================
// Headerfile includes

#include "BrickPi3.h"
#include "AdoptoroLijn.h"

//==================================

using namespace std; 

void matrix(borderValues calibratedInputs, BrickPi3 &BPLine){
	
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
                				cout << "ORIEN0\n";
              				}
              				else if(orientation == 0 && posY == 4){
                 				cout << "ORIEN0 EN posY 4\n";
              				}
              				else if(orientation == 1 && posX != 4){
                				cout << "ORIEN1\n";
              				}
              				else if(orientation == 2 && posY != 0){
                 				cout << "ORIEN2\n";
              				}
              				else if(orientation == 3 && posX != 0){
                 				cout << "ORIEN3\n";
            				} 
         			}
      			}
   		}
}

