#include <AdoptoroLijn.h>

using namespace std;

void sound(){
    
/*before this function is usable you need to install mplayer on your linux system with the command: "sudo apt-get install mplayer"
and a mp3 file that you want to be played
this function tells the command line interface to execute a command that reads "mplayer beep.mp3" where beep.mp3 the name is of
the mp3 file that you want to be played
*/

    system("mplayer beep.mp3");
    
}
