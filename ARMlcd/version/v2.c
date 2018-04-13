#include "stm32f30x.h"

#define LCDport GPIOD
#define LCDD0pin 0
#define LCDD1pin 1
#define LCDD2pin 2
#define LCDD3pin 3
#define LCDD4pin 4
#define LCDD5pin 5
#define LCDD6pin 6
#define LCDD7pin 7

// function for sending bits
void sendBit(GPIO_TypeDef *port, int pin, uint8_t stateBit)
{
	if (stateBit)
		{
			port -> BSRR |= (1 << pin);
		}
	else
		{
			port -> BRR |= GPIO_BRR_BR_0;
		}

}


int main ()
{
	// initialization
	// setup the pin (mode, type, speed, pupd)
	RCC -> AHBENR |= RCC_AHBENR_GPIODEN; // enabling the D
	GPIOD -> MODER = 0b01010101010101010101010101010101; // general purpose output mode; 0x55555555
	GPIOD -> OTYPER = 0; // output push-pull
	GPIOD -> OSPEEDR = 0xFFFFFFFF; // high speed
	GPIOD -> PUPDR = 0;

	//send the character "a" bit by bit

	char character ='A'; //essentially 0b01000001

	// send each bit to each pin of the port D by using masks

	sendBit(LCDport , LCDD0pin, character & 0b00000001);
	sendBit(LCDport , LCDD1pin, character & 0b00000010);
	sendBit(LCDport , LCDD2pin, character & 0b00000100);
	sendBit(LCDport , LCDD3pin, character & 0b00001000);
	sendBit(LCDport , LCDD4pin, character & 0b00010000);
	sendBit(LCDport , LCDD5pin, character & 0b00100000);
	sendBit(LCDport , LCDD6pin, character & 0b01000000);
	sendBit(LCDport , LCDD7pin, character & 0b10000000);

	while(1){
		// infinite loop

	}
}
