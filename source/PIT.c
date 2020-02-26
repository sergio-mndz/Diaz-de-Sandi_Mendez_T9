#include "PIT.h"
#include "MK64F12.h"
#include "GPIO.h"
#include "NVIC.h"
#include "bits.h"

static void (*pit_callback)(void) = 0;

void pit_callback_init(void (*handler)(void))
{
	pit_callback = handler;
}

/* When called only enable interrupt global flag */
void PIT0_IRQHandler(void){
	pit_callback();
	PIT_clear_interrupt_flag();
}

/* Calculate load value with Manuals formula */
void PIT_delay(PIT_timer_t pit_timer, My_float_pit_t system_clock ,
				My_float_pit_t delay) {
	float load_value = delay/(1/system_clock) - 1;
	PIT->CHANNEL[pit_timer].LDVAL = load_value;
}

/* Bit 23 in SCGC6 corresponds to the PIT */
void PIT_clock_gating(void) {
	SIM->SCGC6 |= (1<<23);
}

/* Read the flag status */
uint8_t PIT_get_interrupt_flag_status(void) {
	return (uint8_t)(PIT->CHANNEL[0].TFLG);
}

/* Self explanatory */
void PIT_clear_interrupt_flag(void) {
	PIT->CHANNEL[0].TFLG |= PIT_TFLG_TIF_MASK;
}


void PIT_enable(void) {
	PIT->MCR &= ~(1<<1); /* Enable PIT */
	PIT->CHANNEL[0].TCTRL = (1<<1) | (1<<0); /* PIT timer, Timer interruption */
}

void PIT_disable(void) {
	PIT->MCR |= (1<<1); /* Disable PIT */
}

/* Depending on the PIT selected enable interruption */
void PIT_enable_interrupt(PIT_timer_t pit, priority_level_t priority) {
	switch(pit) {
		case PIT_0:
			NVIC_enable_interrupt_and_priotity(PIT_CH0_IRQ,priority);
		break;
		case PIT_1:
			NVIC_enable_interrupt_and_priotity(PIT_CH1_IRQ,priority);
		break;
		case PIT_2:
			NVIC_enable_interrupt_and_priotity(PIT_CH2_IRQ,priority);
		break;
		case PIT_3:
			NVIC_enable_interrupt_and_priotity(PIT_CH3_IRQ,priority);
		break;
	}
}

