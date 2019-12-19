#include "stm32f30x.h"
#include "LCDFuctions.h"

int main ()
{
	LCDSendInstruction(0b00111001); // 8-bit mode
	LCDSendInstruction(0b00001110); // turning on display and cursor
	LCDSendInstruction(0b00000110); // increment address by 1
	LCDSendInstruction(0b00000001);
	LCDSendCharacter('E');
	LCDSendCharacter('A');
	LCDSendCharacter('S');
	LCDSendCharacter('W');
	LCDSendCharacter('A');
	LCDSendCharacter('R');
	LCDSendCharacter('A');
	LCDSendCharacter('N');


	while(1){
		// infinite loop

	}
}
