#include "stm32f30x.h"

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

	if (character & 0b00000001)
	{
		GPIOD -> BSRR |= GPIO_BSRR_BS_0;
	}
	else
	{
		GPIOD -> BRR |= GPIO_BRR_BR_0;
	}

	if (character & 0b00000010)
		{
			GPIOD -> BSRR |= GPIO_BSRR_BS_1;
		}
		else
		{
			GPIOD -> BRR |= GPIO_BRR_BR_1;
		}

	if (character & 0b00000100)
		{
			GPIOD -> BSRR |= GPIO_BSRR_BS_2;
		}
		else
		{
			GPIOD -> BRR |= GPIO_BRR_BR_2;
		}

	if (character & 0b00001000)
		{
			GPIOD -> BSRR |= GPIO_BSRR_BS_3;
		}
		else
		{
			GPIOD -> BRR |= GPIO_BRR_BR_3;
		}

	if (character & 0b00010000)
		{
			GPIOD -> BSRR |= GPIO_BSRR_BS_4;
		}
		else
		{
			GPIOD -> BRR |= GPIO_BRR_BR_4;
		}

	if (character & 0b00100000)
		{
			GPIOD -> BSRR |= GPIO_BSRR_BS_5;
		}
		else
		{
			GPIOD -> BRR |= GPIO_BRR_BR_5;
		}

	if (character & 0b01000000)
		{
			GPIOD -> BSRR |= GPIO_BSRR_BS_6;
		}
		else
		{
			GPIOD -> BRR |= GPIO_BRR_BR_6;
		}

	if (character & 0b10000000)
		{
			GPIOD -> BSRR |= GPIO_BSRR_BS_7;
		}
		else
		{
			GPIOD -> BRR |= GPIO_BRR_BR_7;
		}

	while(1){
		// infinite loop

	}
}
