#include "AdoptoroLijn.h"

using namespace std;

BrickPi3 BP;

// Signal handler that will be called when Ctrl+C is pressed to stop the program.

void exitSignalHandler(int signo){
	if(signo == SIGINT){
		BP.reset_all();		// Reset everything so t here are no run-away motors.
		exit(-2);
	}
}