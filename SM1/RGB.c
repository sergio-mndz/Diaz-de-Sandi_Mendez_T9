/*
 * RGB.c
 *
 *  Created on: Feb 16, 2020
 *      Author: sergio_mndz
 */

#include "MK64F12.h"
#include "GPIO.h"
#include "bits.h"
#include "RGB.h"

void red_on(){
	GPIOB->PCOR |= (1<<22);
	GPIOB->PSOR |= (1<<21);
	GPIOE->PSOR |= (1<<26);
}

void blue_on() {
	GPIOB->PSOR |= (1<<22);
	GPIOB->PCOR |= (1<<21);
	GPIOE->PSOR |= (1<<26);
}
void green_on() {
	GPIOB->PSOR |= (1<<22);
	GPIOB->PSOR |= (1<<21);
	GPIOE->PCOR |= (1<<26);
}

void yellow_on(){
	GPIOB->PCOR |= (1<<22);
	GPIOB->PSOR |= (1<<21);
	GPIOE->PCOR |= (1<<26);
}

void purple_on(){
	GPIOB->PCOR |= (1<<22);
	GPIOB->PCOR |= (1<<21);
	GPIOE->PSOR |= (1<<26);
}

void white_on(){
	GPIOB->PCOR |= (1<<22);
	GPIOB->PCOR |= (1<<21);
	GPIOE->PCOR |= (1<<26);
}

void red_off(){
	GPIOB->PSOR |= (1<<22);
}

void blue_off(){
	GPIOB->PSOR |= (1<<21);
}

void green_off(){
	GPIOE->PSOR |= (1<<26);
}

void purple_off(){
	GPIOB->PSOR |= (1<<22);
	GPIOB->PSOR |= (1<<21);
}

void yellow_off(){
	GPIOB->PSOR |= (1<<22);
	GPIOE->PSOR |= (1<<26);
}

void all_off(){
	GPIOB->PSOR |= (1<<22);
	GPIOB->PSOR |= (1<<21);
	GPIOE->PSOR |= (1<<26);
}

