#include "stm32f30x.h"
#include "LCDFuctions.h"

int main ()
{
	//Enable the ports and initialize
	intializeLED();
	sendCharacter('A');

	while(1){
		// infinite loop

	}
}
