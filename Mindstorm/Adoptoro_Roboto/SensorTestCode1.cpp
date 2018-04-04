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
    //motor heeft 3 standen; (1) = motor aan, (0) = motor uit, (-1) = achteruit
        BPmot.set_motor_position(PORT_A, 90);            //De robot draait de afstandssensor 90 gradenrichting het object
        BPmot.set_motor_position_relative(PORT_B, -450);
        BPmot.set_motor_position_relative(PORT_C, 450); //De robot draait hier de hele robot 90 graden
        sleep(3);                                       //dit is ervoor zodat de motoren niet gaan rijden tijdens het draaien
        BPmot.set_motor_power(PORT_B, 20); 
        BPmot.set_motor_power(PORT_C, 20);              //hier gaan de motoren draaien
        while(BPafs.get_sensor(PORT_1, Ultrasonic <=100)){ // de while loop bestaat totdat hij langs het object is
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
        while(BPafs.get_sensor(PORT_1, Ultrasonic <=100)){       //while loop gaat weer door tot het object weg is
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
    
  char keuze;
    cout << "T voor testen, G voor gebruiken:\t" << endl;
    cin >> keuze;
    if(keuze == 'T'){       //deze functie is alleen voor het testen van de sensor
        for(;;){
            if(BPafs.get_sensor(PORT_1, Ultrasonic) == 0){
                cout << "Ultrasonic sensor (S2): "   << Ultrasonic2.cm << "cm" << endl;
            }
        }
    }
    if(keuze == 'G'){       //deze functie is om de eigenlijke functie te testen
        FOR(;;){
            cout << "Ultrasonic sensor (S2): "   << Ultrasonic2.cm << "cm" << endl;
            if(BPafs.get_sensor(PORT_1, Ultrasonic2) <= 50){
                ObjectInDeWeg();
            }
        }
    }  
    
}



int main(){
    
    BPafs.detect();
    BPafs.set_sensor_type(PORT_1, SENSOR_TYPE_NXT_ULTRASONIC);
    
    SensorAfstand();
    
    return 0;
}
