/*
 * ADC in ARM
 *
 * Author : Vishnu Easwaran E 
 *
 */
#include "stm32f30x_conf.h"

int main (void)
{
	//ADC calibration
	ADC1->CR &= ~ADC_CR_ADEN; //0 in ADCEN to diable ADC.

//	ADC1->CR

	ADC1->CR |= ADC_CR_ADCAL; //put a 1 in calibration register

	while ((ADC1->CR & ADC_CR_ADCAL) != 0) {} //waiting till the calibration is over

	//select a clock source
	RCC->AHBENR |= RCC_AHBENR_ADC12EN;

	//ADc

	while(1)
	{
		//start conversion
	}

}
