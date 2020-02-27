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
	/* Turning on the 22nd bit of GPIOB */
	GPIOB->PCOR |= (1<<22);
	GPIOB->PSOR |= (1<<21);
	GPIOE->PSOR |= (1<<26);
}

void blue_on() {
	/* Turning on the 21st bit of GPIOB */
	GPIOB->PSOR |= (1<<22);
	GPIOB->PCOR |= (1<<21);
	GPIOE->PSOR |= (1<<26);
}
void green_on() {
	/* Turning on the 26th bit of GPIOE */
	GPIOB->PSOR |= (1<<22);
	GPIOB->PSOR |= (1<<21);
	GPIOE->PCOR |= (1<<26);
}

void yellow_on(){
	/* Turning on the 22nd bit of GPIOB and the
	 * 26th bit of GPIOE */
	GPIOB->PCOR |= (1<<22);
	GPIOB->PSOR |= (1<<21);
	GPIOE->PCOR |= (1<<26);
}

void purple_on(){
	/* Turning on the 21st and 22nd bit of GPIOB */
	GPIOB->PCOR |= (1<<22);
	GPIOB->PCOR |= (1<<21);
	GPIOE->PSOR |= (1<<26);
}

void white_on(){
	/* Turning on the 21st and 22nd bit of GPIOB,
	 * as well as the 26th bit of the GPIOE */
	GPIOB->PCOR |= (1<<22);
	GPIOB->PCOR |= (1<<21);
	GPIOE->PCOR |= (1<<26);
}

void red_off(){
	/* Turning on the 22nd bit of GPIOB */
	GPIOB->PSOR |= (1<<22);
}

void blue_off(){
	/* Turning on the 21st bit of GPIOB */
	GPIOB->PSOR |= (1<<21);
}

void green_off(){
	/* Turning on the 26th bit of GPIOE */
	GPIOE->PSOR |= (1<<26);
}

void purple_off(){
	/* Turning on the 21st and 22nd bit of GPIOB */
	GPIOB->PSOR |= (1<<22);
	GPIOB->PSOR |= (1<<21);
}

void yellow_off(){
	/* Turning on the 22nd bit of GPIOB, and the
	 * 26th bit of the GPIOE */
	GPIOB->PSOR |= (1<<22);
	GPIOE->PSOR |= (1<<26);
}

void all_off(){
	/* Turning on the 21st and 22nd bit of GPIOB,
	 * and the 26th bit of the GPIOE */
	GPIOB->PSOR |= (1<<22);
	GPIOB->PSOR |= (1<<21);
	GPIOE->PSOR |= (1<<26);
}
