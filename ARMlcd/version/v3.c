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

//to initialize
void setPortAndPin (GPIO_TypeDef *port, int pin)
{
	if (port == GPIOA){
		RCC -> AHBENR |= RCC_AHBENR_GPIOAEN;
	}
	if (port == GPIOB){
			RCC -> AHBENR |= RCC_AHBENR_GPIOBEN;
		}
	if (port == GPIOC){
			RCC -> AHBENR |= RCC_AHBENR_GPIOCEN;
		}
	if (port == GPIOD){
			RCC -> AHBENR |= RCC_AHBENR_GPIODEN;
		}
	if (port == GPIOE){
			RCC -> AHBENR |= RCC_AHBENR_GPIOEEN;
		}
	if (port == GPIOF){
			RCC -> AHBENR |= RCC_AHBENR_GPIOFEN;
		}

	port -> MODER &= ~(1 << ((pin*2)+1));
	port -> MODER |= ((1 << pin*2));
	port -> OTYPER &= ~((1 << (pin*2)) | (1 << ((pin*2)+1)));
	port -> OSPEEDR |= (1 << ((pin*2)+1)) | (1 << pin*2);
	port -> PUPDR &= ~((1 << (pin*2)) | (1 << ((pin*2)+1)));
}


//to send bits
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
//to send character
void sendCharacter(char character)
{
	sendBit(LCDport , LCDD0pin, character & 0b00000001);
	sendBit(LCDport , LCDD1pin, character & 0b00000010);
	sendBit(LCDport , LCDD2pin, character & 0b00000100);
	sendBit(LCDport , LCDD3pin, character & 0b00001000);
	sendBit(LCDport , LCDD4pin, character & 0b00010000);
	sendBit(LCDport , LCDD5pin, character & 0b00100000);
	sendBit(LCDport , LCDD6pin, character & 0b01000000);
	sendBit(LCDport , LCDD7pin, character & 0b10000000);
}

void intializeLED(){
	setPortAndPin(LCDport, LCDD0pin);
	setPortAndPin(LCDport, LCDD1pin);
	setPortAndPin(LCDport, LCDD2pin);
	setPortAndPin(LCDport, LCDD3pin);
	setPortAndPin(LCDport, LCDD4pin);
	setPortAndPin(LCDport, LCDD5pin);
	setPortAndPin(LCDport, LCDD6pin);
	setPortAndPin(LCDport, LCDD7pin);
}

int main ()
{
	//Enable the ports and initialize

	intializeLED();

	sendCharacter('A');

	while(1){
		// infinite loop

	}
}
