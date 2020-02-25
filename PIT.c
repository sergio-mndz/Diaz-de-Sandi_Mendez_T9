/*
 * PIT.c
 *
 *  Created on: Feb 22, 2020
 *      Author: sergio_mndz
 */

#include "PIT.h"
#include "MK64F12.h"
#include "GPIO.h"
#include "NVIC.h"
#include "bits.h"

uint8_t pit_inter_status = FALSE;

void PIT0_IRQHandler(void){
	pit_inter_status = TRUE;
	PIT_clear_interrupt_flag();
}

void PIT_delay(PIT_timer_t pit_timer, My_float_pit_t system_clock, My_float_pit_t delay){
	float load_value = delay/(1/system_clock) - 1;
	PIT->CHANNEL[pit_timer].LDVAL = load_value;
}

void PIT_clock_gating(void){
	SIM->SCGC6 |= (1<<23);
}

uint8_t PIT_get_interrupt_flag_status(void){
	return (uint8_t)(PIT->CHANNEL[0].TFLG);
}

void PIT_clear_interrupt_flag(void){
//	PIT->CHANNEL[0].TFLG = 1;
	PIT->CHANNEL[0].TFLG |= PIT_TFLG_TIF_MASK;
//	uint32_t dummyRead = PIT->CHANNEL[0].TCTRL;
}

void PIT_enable(void){
	PIT->MCR &= ~(1<<1);
	PIT->CHANNEL[0].TCTRL = (1<<1) | (1<<0);
}

void PIT_enable_interrupt(PIT_timer_t pit){
//	NVIC_enable_interrupt_and_priotity(pit ,PRIORITY_10);
	NVIC_enable_interrupt_and_priotity(PIT_CH0_IRQ,PRIORITY_1);
}

