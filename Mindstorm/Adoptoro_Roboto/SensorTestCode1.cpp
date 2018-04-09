#include <stdio.h>
#include <iostream>
#include "BrickPi3.h"
#include <unistd.h>
#include <signal.h>
using namespace std;
BrickPi3 BPafs;
BrickPi3 BPmot;
BrickPi3 BP;

void exit_signal_handler(int signo);


void stop(void){
    BPmot.set_motor_power(PORT_A, 0);
    BPmot.set_motor_power(PORT_B, 0);
    BPmot.set_motor_power(PORT_C, 0);
}

void ObjectInDeWeg(){

    cout << "er komt een object in de weg." << endl;
    BPafs.detect();
    BPafs.set_sensor_type(PORT_1, SENSOR_TYPE_NXT_ULTRASONIC);
    sensor_ultrasonic_t Ultrasonic2;
    
    //motor heeft 3 standen; (1) = motor aan, (0) = motor uit, (-1) = achteruit
    BPmot.set_motor_position(PORT_A, 90); //De robot draait de afstandssensor 90 gradenrichting het object
    sleep(0.2);
    stop();

    sleep(1);
    BPmot.set_motor_position_relative(PORT_B, -450);
    BPmot.set_motor_position_relative(PORT_C, 450);
    sleep(0.2);//De robot draait hier de hele robot 90 graden
    stop();
    sleep(3);                                       //dit is ervoor zodat de motoren niet gaan rijden tijdens het draaien
    BPmot.set_motor_power(PORT_B, 10); 
    BPmot.set_motor_power(PORT_C, 10);              //hier gaan de motoren draaien
    while(Ultrasonic2.cm <=25){ // de while loop bestaat totdat hij langs het object is
        sleep(0.01);
    }
    
    sleep(1);
    stop();                                            // hier zorg ik ervoor dat alles soepel verloopt met het stoppen op de gewenste positie
    sleep(1);
    BPmot.set_motor_position_relative(PORT_B, 450);     //motoren draaien terug naar de tweede positie
    BPmot.set_motor_position_relative(PORT_C, -450);  
    sleep(0.2);
    stop();
    sleep(3);
    BPmot.set_motor_power(PORT_B, 20);
    BPmot.set_motor_power(PORT_C, 20);    
    sleep(1);
    while(Ultrasonic2.cm <=25){       //while loop gaat weer door tot het object weg is
        sleep(0.01);
    }
    
    sleep(2);
    stop();
    sleep(1);
    BPmot.set_motor_position_relative(PORT_B, -450);        //robot draait terug naar starspositie en is klaar
    BPmot.set_motor_position_relative(PORT_C, 450);
    sleep(0.2);
    stop();
    sleep(1);
    BPmot.set_motor_position(PORT_A, 1); 
    sleep(0.1);
    stop();
    sleep(1);
    BPmot.set_motor_power(PORT_B, 20);
    BPmot.set_motor_power(PORT_C, 20);
    cout << "hij komt ook aan het einde" << endl;
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
                if(Ultrasonic2.cm >=20){
                    cout << "Ultrasonic sensor (S2): "   << Ultrasonic2.cm << "cm" << endl;
                    
                }
            }
        }
    }
    if(keuze == 'G'){
        sleep(1);   //deze functie is om de eigenlijke functie te testen
        BPmot.set_motor_power(PORT_B, 40);
        BPmot.set_motor_power(PORT_C, 40);
        while(true){
            if(BPafs.get_sensor(PORT_1, Ultrasonic2) == 0){
                //sleep(1);
                cout << "Ultrasonic sensor (S2): "   << Ultrasonic2.cm << "cm" << endl;

                if(Ultrasonic2.cm <= 15 ){
                    cout << "l" << endl;
                    stop();
                    sleep(1);
                    ObjectInDeWeg();
                }
                
            }
        }
    }  
    
}



int main(){
    signal(SIGINT, exit_signal_handler); // register the exit function for Ctrl+C

    SensorAfstand();
    
    return 0;
}

// Signal handler that will be called when Ctrl+C is pressed to stop the program
void exit_signal_handler(int signo){
  if(signo == SIGINT){
    BP.reset_all();    // Reset everything so there are no run-away motors
    exit(-2);
  }
}
