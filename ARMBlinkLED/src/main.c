#include "stm32f30x_conf.h"

// create function for waiting
void waitMoment(int Moment)
{
	volatile int i, j;

	for (i = 0; i < Moment; ++i) {
		j++;
	}
}
void main()
{
//	enable the GPIO clock at port E using the AHB and GCC
	RCC -> AHBENR |= RCC_AHBENR_GPIOEEN; // 0000 0000 0000 0000 0000 0000 0000 0000 | 0x00080000
//	Set any Control register for LED; here port PE9
//	moder
	GPIOE -> MODER |= GPIO_MODER_MODER8_0;
	GPIOE -> MODER &= ~(GPIO_MODER_MODER8_1);
//	Otyper
	GPIOE -> OTYPER &= ~(GPIO_OTYPER_OT_8);
//	Ospeedr
	GPIOE -> OSPEEDR |= GPIO_OSPEEDER_OSPEEDR8;
//	PUPDr
	GPIOE -> PUPDR &= ~(GPIO_PUPDR_PUPDR8);

	while(1)
	{
//		Turn ON the LED
//		BSRR
		GPIOE -> BSRR |= GPIO_BSRR_BS_8;
//		Wait
		waitMoment(2000000);
//		Turn OFF the LED
//		BRR
		GPIOE -> BRR |= GPIO_BRR_BR_8;
//		Wait
		waitMoment(2000000);
	}
}
