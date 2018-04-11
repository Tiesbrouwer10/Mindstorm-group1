#include "AdoptoroLijn.h"
#include "BrickPi3.h"

using namespace std;

int error;

borderValues sensorCalibration(BrickPi3 & BPCalibration){
	
	int BWValue = 0;
	int CValue = 0;
	
	// Black/White and Color sensor port defenition
	BPCalibration.set_sensor_type(PORT_2, SENSOR_TYPE_NXT_LIGHT_ON);
	BPCalibration.set_sensor_type(PORT_3, SENSOR_TYPE_NXT_COLOR_FULL);
	BPCalibration.set_sensor_type(PORT_1, SENSOR_TYPE_NXT_ULTRASONIC);
		
	// Reset the motors
	BPCalibration.offset_motor_encoder(PORT_A, BPCalibration.get_motor_encoder(PORT_A));
	BPCalibration.offset_motor_encoder(PORT_B, BPCalibration.get_motor_encoder(PORT_B));
	BPCalibration.offset_motor_encoder(PORT_C, BPCalibration.get_motor_encoder(PORT_C));
	
	// Read the encoders
	int32_t EncoderA = BPCalibration.get_motor_encoder(PORT_A);
	int32_t EncoderB = BPCalibration.get_motor_encoder(PORT_B);
	int32_t EncoderC = BPCalibration.get_motor_encoder(PORT_C);
	
	BPCalibration.set_motor_limits(PORT_B, 70, 0);
	BPCalibration.set_motor_limits(PORT_C, 70, 0);
	
	sensor_light_t		Light;
	sensor_color_t		Color;
	
	error = 0;
	
	
	sleep(2);
	
	for(unsigned int i = 0; i < 10; i++){
		if(BPCalibration.get_sensor(PORT_2, Light) == 0){
			BWValue += Light.reflected;
		}
		if(BPCalibration.get_sensor(PORT_3,Color) == 0){
			CValue += Color.reflected_red;
		}
		
		sleep(0.1);
	}
	BWValue /= 10;
	CValue /= 10;
	
	// Check value average
	cout << "\nBlack/White Sensor Reflected: " << BWValue << "\n";
	cout << "Color Sensor Reflected: " << CValue << "\n";
	cout << "DONE" << '\n';
	
	// Setting Border Values
	borderValues calibratedInputs;
	calibratedInputs.borderValueBW = BWValue * 1.25;
	calibratedInputs.borderValueC = CValue * 0.75;

	
	return calibratedInputs;
	
}

//================================
// Calibration Layout:

// Port S2 = Black/White Sensor

// Port S3 = Color Sensor
