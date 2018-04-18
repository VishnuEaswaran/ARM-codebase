/*
 * Toggling an LED using a push button and does software debouncing.
 * One push for ON and next push turns OFF the LED
 *
 * Author : Vishnu Easwaran on 6/3/2018
 *
 */

//include the Library
#include "stm32f30x_conf.h"

void main()
{
  //reset and clock control - advanced high-performance bus - port E pin 15 and port A pin 0
	RCC -> AHBENR |= RCC_AHBENR_GPIOEEN; //LED
	RCC -> AHBENR |= RCC_AHBENR_GPIOAEN; //switch

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

  //intialisations
  volatile char ledState = 0;
  volatile char buttonPressed = 0; //button pressed variable
  volatile int buttonPressedConfidenseLevel = 0; //button pressed confidence level
  volatile int buttonReleasedConfidenceLevel = 0; //button released confidence level
  volatile int pressedThreshold = 200;//button threshold
	while(1)
	{
		if(GPIOA -> IDR & GPIO_IDR_0)//check for button press IDR
		{
			if(buttonPressed == 0)
			{

				// check if confidence exceeds the confidence threshold
				if (buttonPressedConfidenseLevel > pressedThreshold )
				{
					//toggle the LED
					if(ledState == 0)
					{
						ledState = 1;
						//turn OFF led
						GPIOE -> BRR |= GPIO_BSRR_BS_8;
					}
					else
					{
						ledState = 0;
						//turn ON led
						GPIOE -> BSRR |= GPIO_BSRR_BS_8;
					}
					//update button pressed variable to 1
					buttonPressed = 1;
				}
				else
				{
					//increment the confidence of button pressed
					buttonPressedConfidenseLevel ++;
					buttonReleasedConfidenceLevel = 0;
				}

			}

		}

		else//check if button released
		{
			if(buttonPressed == 1)
			{
				//increment button confidence of button released
				buttonReleasedConfidenceLevel ++;
				buttonPressedConfidenseLevel = 0;
				//when button released confidence exceeds the threshold
				if(buttonReleasedConfidenceLevel > pressedThreshold)
				{
					//update the button pressed variable to 0
					buttonPressed = 0;
				}

		     }

		}

	}

}
