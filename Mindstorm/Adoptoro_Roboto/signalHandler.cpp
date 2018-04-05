#include "AdoptoroLijn.h"

using namespace std;

BrickPi3 BPMain;

// Signal handler that will be called when Ctrl+C is pressed to stop the program.

void exitSignalHandler(int signo){
	if(signo == SIGINT){
		BPMain.reset_all();		// Reset everything so t here are no run-away motors.
		exit(-2);
	}
}
