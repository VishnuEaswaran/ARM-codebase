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
	ADC1->CR &= ~ADC_CR_ADEN;
	ADC1->CR |= ADC_CR_ADCAL;
	while ((ADC1->CR & ADC_CR_ADCAL) != 0)
	  {
	    //waiting till the calibration is over; ie the bit turns 0
	  }

	//select a clock source
	RCC->AHBENR |= RCC_AHBENR_ADC12EN;
	RCC->CR |= RCC_CR_HSEON;
	while((RCC->CR & RCC_CR_HSERDY) != 1)
	  {
	    //to make sure the clock has started
	  }
	ADC1_2->CCR = ADC12_CCR_CKMODE;

	// enable ADC
	ADC1->CR  = ADC_CR_ADEN;
	ADC1_2->CCR |= ADC12_CCR_TSEN;
	while((ADC1->ISR & ADC_ISR_ADRD) == 0)
	  {
	    //waiting to get ready
	  }

	//sampling time - set to maximum
	ADC1->SMPR1 |= ADC_SMPR1_SMP0_0 | ADC_SMPR1_SMP0_1 | ADC_SMPR1_SMP0_2;

	//set the channel - here internal temp register
	ADC1->SQR1 &= ~ADC_SQR1_SQ1_1 | ~ADC_SQR1_SQ1_2 | ~ADC_SQR1_SQ1_3;
	ADC1->SQR1 |= ADC_SQR1_SQ1_4;

	ADC1->SQR1 &= ~ADC_SQR1_L;

	//wake up the temp sensor
	ADC1_2->CCR |= ADC12_CCR_VREFEN;

	//enabling continuous conversion mode
	ADC1->CFGR |= ADC_CFGR_CONT;

	while(1)
	{
		//start conversion
	    ADC1->CR |=ADC_CR_ADSTART;
	    while((ADC1->ISR & ADC_ISR_EOC) != 1)
	      {
		//wait for conversion to finish
	      }
	}

}
