#include "AdoptoroLijn.h"
#include "BrickPi3.h"

using namespace std;

BrickPi3 BP2;

// Signal handler that will be called when Ctrl+C is pressed to stop the program.

void exitSignalHandler(int signo){
	if(signo == SIGINT){
		BP2.reset_all();		// Reset everything so t here are no run-away motors.
		exit(-2);
	}
}
