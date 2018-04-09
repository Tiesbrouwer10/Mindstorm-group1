#include <stdio.h>
#include <iostream>
#include "BrickPi3.h"
#include <unistd.h>
#include <signal.h>
BrickPi3 BP;
using namespace std;

void exit_signal_handler(int signo);



int getDist(){
 
      BP.set_sensor_type(PORT_2, SENSOR_TYPE_NXT_ULTRASONIC);
      sensor_ultrasonic_t Ultrasonic2;
    
    return Ultrasonic2.cm;
    
}

void evadeObject(BrickPi3 &BPEva, borderValues &calibratedInputs){
    
    BPEva.set_motor_power(PORT_B, 0); // Set right wheel to stop
    BPEva.set_motor_power(PORT_C, 0); // Set left wheel to stop
    
    BPEva.set_motor_power(PORT_A, 10);
    sleep(1);
    BPEva.set_motor_power(PORT_A, 0);
}




void SensorAfstand(){

    BP.detect();
    BP.set_sensor_type(PORT_1, SENSOR_TYPE_NXT_ULTRASONIC);
    sensor_ultrasonic_t Ultrasonic2;
  char keuze;
    cout << "T voor testen, G voor gebruiken:\t" << endl;
    cin >> keuze;
    if(keuze == 'T'){       //deze functie is alleen voor het testen van de sensor
        for(;;){
            if(BP.get_sensor(PORT_1, Ultrasonic2) == 0){
                if(Ultrasonic2.cm >=20){
                    cout << "Ultrasonic sensor (S2): "   << Ultrasonic2.cm << "cm" << endl;
                    
                }
            }
        }
    }
    if(keuze == 'G'){
        sleep(1);   //deze functie is om de eigenlijke functie te testen
        BP.set_motor_power(PORT_B, 40);
        BP.set_motor_power(PORT_C, 40);
        while(true){
            if(BP.get_sensor(PORT_1, Ultrasonic2) == 0){
                //sleep(1);
                cout << "Ultrasonic sensor (S2): "   << getDist() << "cm" << endl;

                if(getDist() <= 8 ){
                    cout << "l" << endl;
                    stop();
                    sleep(1);
                    evadeObject();
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
