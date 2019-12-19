/*
 * LCDFuctions.h
 *
 *  Created on: 16-Apr-2018
 *      Author: vishnu
 */

#ifndef LCDFunctions
#define LCDFunctions

#define LCDD0Port GPIOD
#define LCDD0Pin 0
#define LCDD1Port GPIOD
#define LCDD1Pin 1
#define LCDD2Port GPIOD
#define LCDD2Pin 2
#define LCDD3Port GPIOD
#define LCDD3Pin 3
#define LCDD4Port GPIOD
#define LCDD4Pin 4
#define LCDD5Port GPIOD
#define LCDD5Pin 5
#define LCDD6Port GPIOD
#define LCDD6Pin 6
#define LCDD7Port GPIOD
#define LCDD7Pin 7
#define LCDEnablePort GPIOC
#define LCDEnablePin 11
#define LCDRWPort GPIOA
#define LCDRWPin 13
#define LCDRSPort GPIOA
#define LCDRSPin 11
#define timeDelayBeforeEnable 40000
#define timeDelayBeforeDisable 80000

void notExactTimeDelay(int delay)
{
	for ( volatile int i=0; i < delay; i++){

	}
}

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

void intializeLCD(){
	setPortAndPin(LCDD0Port, LCDD0Pin);
	setPortAndPin(LCDD1Port, LCDD1Pin);
	setPortAndPin(LCDD2Port, LCDD2Pin);
	setPortAndPin(LCDD3Port, LCDD3Pin);
	setPortAndPin(LCDD4Port, LCDD4Pin);
	setPortAndPin(LCDD5Port, LCDD5Pin);
	setPortAndPin(LCDD6Port, LCDD6Pin);
	setPortAndPin(LCDD7Port, LCDD7Pin);
	setPortAndPin(LCDEnablePort, LCDEnablePin);
	setPortAndPin(LCDRSPort, LCDRSPin);
	setPortAndPin(LCDRWPort, LCDRWPin);
}

//to send bits
void sendBitToPortAndPin(GPIO_TypeDef *port, int pin, uint8_t stateBit)
{
	if (stateBit){
			port -> BSRR |= (1 << pin);
		}
	else{
			port -> BRR |= GPIO_BRR_BR_0;
		}

}

void LCDenable()
{
	notExactTimeDelay(timeDelayBeforeEnable);
	sendBitToPortAndPin(LCDEnablePort, LCDEnablePin, 1);
}

void LCDsetWrite()
{
	sendBitToPortAndPin(LCDRWPort, LCDRWPin, 0);
}

void LCDsetRead()
{
	sendBitToPortAndPin(LCDRWPort, LCDRWPin, 1);
}

void LCDCharacterMode()
{
	sendBitToPortAndPin(LCDRSPort, LCDRSPin, 1);
}

void LCDInstructionMode()
{
	sendBitToPortAndPin(LCDRSPort, LCDRSPin, 0);
}

void LCDSendAByteToTheLCDDataPins(char character)
{
	sendBitToPortAndPin(LCDD0Port, LCDD0Pin, character & 0b00000001);
	sendBitToPortAndPin(LCDD1Port, LCDD1Pin, character & 0b00000010);
	sendBitToPortAndPin(LCDD2Port, LCDD2Pin, character & 0b00000100);
	sendBitToPortAndPin(LCDD3Port, LCDD3Pin, character & 0b00001000);
	sendBitToPortAndPin(LCDD4Port, LCDD4Pin, character & 0b00010000);
	sendBitToPortAndPin(LCDD5Port, LCDD5Pin, character & 0b00100000);
	sendBitToPortAndPin(LCDD6Port, LCDD6Pin, character & 0b01000000);
	sendBitToPortAndPin(LCDD7Port, LCDD7Pin, character & 0b10000000);
	notExactTimeDelay(timeDelayBeforeDisable); // 80ns
	sendBitToPortAndPin(LCDEnablePort, LCDEnablePin, 0);
}


void LCDSendInstruction(char character)
{
	LCDsetWrite();
	LCDInstructionMode();
	LCDenable(); //40ns
	LCDSendAByteToTheLCDDataPins(character);
}

void LCDSendCharacter(char character)
{
	LCDsetWrite();
	LCDCharacterMode();
	LCDenable(); //40ns
	LCDSendAByteToTheLCDDataPins(character);
}

#endif /* LCDFUCTIONS_H_ */
