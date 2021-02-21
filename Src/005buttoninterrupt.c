/*
 * 001ledtoggle.c
 *
 *  Created on: Feb 17, 2021
 *      Author: matt
 */

#include <string.h>
#include "stm32f407xx.h"

void delay(void){
	for(uint32_t i = 0; i < 500000; i++){

	};
}

int main(void){

	GPIO_Handle_t Gpioled, Gpiobtn;
	memset(&Gpioled,0,sizeof(Gpioled));
	memset(&Gpiobtn,0,sizeof(Gpiobtn));


	//GPIO configuration for LED output
	Gpioled.pGPIOx = GPIOD;
	Gpioled.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_12;
	Gpioled.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_OUT;
	Gpioled.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_FAST;
	Gpioled.GPIO_PinConfig.GPIO_PinOPType = GPIO_OP_TYPE_PP;
	Gpioled.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_NO_PUPD;

	//GPIO configuration for button input, interrupt on falling edge
	Gpiobtn.pGPIOx = GPIOA;
	Gpiobtn.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_0;
	Gpiobtn.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_IT_FT;
	Gpiobtn.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_FAST;
	Gpiobtn.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_PIN_PU;
	Gpiobtn.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_NO_PUPD;

	//initialize peripheral clock and LED pin
	GPIO_PeriClockControl(GPIOD, ENABLE);
	GPIO_Init(&Gpioled);

	GPIO_PeriClockControl(GPIOA, ENABLE);
	GPIO_Init(&Gpiobtn);

	GPIO_WriteToOutputPin(GPIOD, GPIO_PIN_NO_12, 0);
	//IRQ configuration
	GPIO_IRQPriorityConfig(IRQ_NO_EXTI0, 15);
	GPIO_IRQInterruptConfig(IRQ_NO_EXTI0, ENABLE);


	while(1){
		//GPIO_ToggleOutputPin(GPIOD, GPIO_PIN_NO_12);
		//delay();
	}
	return 0;
}

//ISR for button press
void EXTI0_IRQHandler(void){
	delay();
	GPIO_IRQHandling(GPIO_PIN_NO_0);
	GPIO_ToggleOutputPin(GPIOD, GPIO_PIN_NO_12);
}
