#include <stdio.h>
#include <iostream>
#include "BrickPi3.h"
#include <unistd.h>
using namespace std;
BrickPi3 BPafs;
BrickPi3 BPmot;

void stop(void){
    BPmot.set_motor_power(PORT_B, 0);
    BPmot.set_motor_power(PORT_C, 0);
}

void ObjectInDeWeg(){
    cout << "hij komt in objecetindeweg" << endl;
    BPafs.detect();
    BPafs.set_sensor_type(PORT_1, SENSOR_TYPE_NXT_ULTRASONIC);
    sensor_ultrasonic_t Ultrasonic2;
    
    //motor heeft 3 standen; (1) = motor aan, (0) = motor uit, (-1) = achteruit
        BPmot.set_motor_position(PORT_A, 90);            //De robot draait de afstandssensor 90 gradenrichting het object
        BPmot.set_motor_position_relative(PORT_B, -450);
        BPmot.set_motor_position_relative(PORT_C, 450); //De robot draait hier de hele robot 90 graden
        sleep(3);                                       //dit is ervoor zodat de motoren niet gaan rijden tijdens het draaien
        BPmot.set_motor_power(PORT_B, 20); 
        BPmot.set_motor_power(PORT_C, 20);              //hier gaan de motoren draaien
        while(BPafs.get_sensor(PORT_1, Ultrasonic2)<=100){ // de while loop bestaat totdat hij langs het object is
        }
        
        sleep(1);
        stop();                                            // hier zorg ik ervoor dat alles soepel verloopt met het stoppen op de gewenste positie
        sleep(1);
        BPmot.set_motor_position_relative(PORT_B, 450);     //motoren draaien terug naar de tweede positie
        BPmot.set_motor_position_relative(PORT_C, -450);            
        sleep(3);
        BPmot.set_motor_power(PORT_B, 20);
        BPmot.set_motor_power(PORT_C, 20);    
        sleep(1);
        while(BPafs.get_sensor(PORT_1, Ultrasonic2)<=100){       //while loop gaat weer door tot het object weg is
        }
        
        sleep(2);
        stop();
        sleep(1);
        BPmot.set_motor_position_relative(PORT_B, -450);        //robot draait terug naar starspositie en is klaar
        BPmot.set_motor_position_relative(PORT_C, 450);
        BPmot.set_motor_position(PORT_A, 1); 
        sleep(1);
        BPmot.set_motor_power(PORT_B, 20);
        BPmot.set_motor_power(PORT_C, 20);     
}

void SensorAfstand(){
    BPafs.detect();
    BPafs.set_sensor_type(PORT_1, SENSOR_TYPE_NXT_ULTRASONIC);
    sensor_ultrasonic_t Ultrasonic2;
  char keuze;
    cout << "T voor testen, G voor gebruiken:\t" << endl;
    cin >> keuze;
    if(keuze == 'T'){       //deze functie is alleen voor het testen van de sensor
        for(;;){
            if(BPafs.get_sensor(PORT_1, Ultrasonic2) == 0){
                cout << "Ultrasonic sensor (S2): "   << Ultrasonic2.cm << "cm" << endl;
            }
        }
    }
    if(keuze == 'G'){       //deze functie is om de eigenlijke functie te testen
        while(true){
            cout << "Ultrasonic sensor (S2): "   << Ultrasonic2.cm << "cm" << endl;
            if(BPafs.get_sensor(PORT_1, Ultrasonic2) <= 10){
                cout << "l" << endl;
                ObjectInDeWeg();
            }
        }
    }  
    
}



int main(){
    

    SensorAfstand();
    
    return 0;
}