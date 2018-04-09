#include <stdio.h>
#include <iostream>
#include "BrickPi3.h"
#include <unistd.h>
#include <signal.h>

using namespace std;

void exit_signal_handler(int signo);


void stop(){
    BPmot.set_motor_power(PORT_A, 0);
    BPmot.set_motor_power(PORT_B, 0);
    BPmot.set_motor_power(PORT_C, 0);
}

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

void ObjectInDeWeg2(){
    BPmot.reset_all();
    BP.offset_motor_encoder(PORT_A, BP.get_motor_encoder(PORT_A));
    BP.offset_motor_encoder(PORT_B, BP.get_motor_encoder(PORT_B));
    BP.offset_motor_encoder(PORT_C, BP.get_motor_encoder(PORT_C));
    bool kant1 = true;
    bool kant2 = true;

    cout << "er komt een object in de weg." << endl;
    sleep(1);
    BPmot.set_motor_position(PORT_A, 90); //De robot draait de afstandssensor 90 gradenrichting het objec
    cout << "1 werkt" << endl;
    sleep(1);
    BPmot.set_motor_power(PORT_A, 0);
    BPmot.set_motor_position_relative(PORT_B, -450);
    BPmot.set_motor_position_relative(PORT_C, 450);

    cout << "2 werkt" << endl;
    //stop();
    BPmot.set_motor_power(PORT_B, 0);
    BPmot.set_motor_power(PORT_C, 0);
    
    cout << "hij komt voor de while" << endl;
    while(kant1 == true){
        cout << "hij komt in while" << endl;
        BPmot.set_motor_power(PORT_B, 40); 
        BPmot.set_motor_power(PORT_C, 40);
        sleep(2);
        BPmot.set_motor_power(PORT_B, 0);
        BPmot.set_motor_power(PORT_C, 0);
        if(getDist() > 15){
            kant1 == false;
        }
    }
        cout << "3 werkt" << endl;
    BPmot.set_motor_position_relative(PORT_B, -450);
    BPmot.set_motor_position_relative(PORT_C, 450);
    sleep(2);
    BPmot.set_motor_power(PORT_B, 0);
    BPmot.set_motor_power(PORT_C, 0);
        while(kant2 == true){
        BPmot.set_motor_power(PORT_B, 40); 
        BPmot.set_motor_power(PORT_C, 40);
        sleep(0.2);
        BPmot.set_motor_power(PORT_B, 0);
        BPmot.set_motor_power(PORT_C, 0);
        if(Ultrasonic2.cm > 15){
            kant2 == false;
        }
    }
    sleep(1);
    BPmot.set_motor_position_relative(PORT_B, -450);        //robot draait terug naar starspositie en is klaar
    BPmot.set_motor_position_relative(PORT_C, 450);
    sleep(0.2);
    BPmot.set_motor_power(PORT_B, 0);
    BPmot.set_motor_power(PORT_C, 0);
    sleep(1);
    BPmot.set_motor_position(PORT_A, -90); 
    
    sleep(0.1);

    BPmot.set_motor_power(PORT_A, 0);
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

                if(getDist() <= 8 ){
                    cout << "l" << endl;
                    stop();
                    sleep(1);
                    ObjectInDeWeg2();
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
