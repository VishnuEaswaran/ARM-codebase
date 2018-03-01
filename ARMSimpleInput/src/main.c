//include the Library
#include "stm32f30x_conf.h"

void main()
{
  //reset and clock control - advanced high-performance bus - port E pin 15 and port A pin 0
	RCC -> AHBENR |= RCC_AHBENR_GPIOEEN;
	RCC -> AHBENR |= RCC_AHBENR_GPIOAEN;

  //intialise registers for LED (output)

  //mode register
	GPIOE -> MODER |= GPIO_MODER_MODER8_0;
	GPIOE -> MODER &= ~(GPIO_MODER_MODER8_1);
  //output type register
	GPIOE -> OTYPER &= ~(GPIO_OTYPER_OT_8);
  //output speed register
	GPIOE -> OSPEEDR |= GPIO_OSPEEDER_OSPEEDR8;
  //pull-up pull-down register
	GPIOE -> PUPDR &= ~(GPIO_PUPDR_PUPDR8);

  //initialise Registers for switch (input)

  //mode register
	GPIOA -> MODER &= ~(GPIO_MODER_MODER0);
  //pull-up pull down register
	GPIOA -> PUPDR &= ~(GPIO_PUPDR_PUPDR0);

	while(1)
	{
		if(GPIOA -> IDR & GPIO_IDR_0)//check for button press IDR
		{
			//turn on led (BSRR)
			GPIOE -> BSRR |= GPIO_BSRR_BS_8;
		}


		else//check if button released
		{
			//turn off led (BRR)
			GPIOE -> BRR |= GPIO_BRR_BR_8;
		}

	}
}
