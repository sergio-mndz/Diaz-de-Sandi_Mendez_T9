#include <stdio.h>
#include <stdint.h>
#include "MK64F12.h"
#include "GPIO.h"
#include "Bits.h"
#include "RGB.h"
#include "NVIC.h"
#include "PIT.h"

#define SYSTEM_CLOCK (21000000U)
#define DELAY (1.0F)

gpio_pin_control_register_t led_enable = GPIO_MUX1;
gpio_pin_control_register_t sw_enable = GPIO_MUX1 | GPIO_PE | GPIO_PS |
										INTR_FALLING_EDGE;


uint8_t g_timer_end_flag = FALSE;

/**
 * pit_handler is a void function that manages the control of the 1 second
 * delay, activating a flag that signals the end of the 1 second delay
 */

void pit_handler(void)
{
	g_timer_end_flag = TRUE;
}

int main(void)
{
	/**
	 *  Array of functions that contains the sequence of LEDs
	 */
	void (*led_turn[5])();
	/**
	 *  Assign each function of RGB in the order of the sequence
	 */
	led_turn[0] = yellow_on;
	led_turn[1] = red_on;
	led_turn[2] = purple_on;
	led_turn[3] = blue_on;
	led_turn[4] = green_on;

	/**
	 *  Enable clocks of GPIO
	 */
	GPIO_clock_gating(GPIO_A);
	GPIO_clock_gating(GPIO_B);
	GPIO_clock_gating(GPIO_C);
	GPIO_clock_gating(GPIO_E);

	/**
	 *  Enable GPIO of leds and switches
	 */
	GPIO_pin_control_register(GPIO_B, bit_21, & led_enable);
	GPIO_pin_control_register(GPIO_B, bit_22, & led_enable);
	GPIO_pin_control_register(GPIO_E, bit_26, & led_enable);
	GPIO_pin_control_register(GPIO_A, bit_4, & sw_enable);
	GPIO_pin_control_register(GPIO_C, bit_6, & sw_enable);

	/**
	 *  Send leds to a safe value
	 */
	red_off();
	blue_off();
	green_off();

	/**
	 *  Enable leds as output and switches as input
	 */
	GPIO_data_direction_pin(GPIO_B, GPIO_OUTPUT, bit_21);
	GPIO_data_direction_pin(GPIO_B, GPIO_OUTPUT, bit_22);
	GPIO_data_direction_pin(GPIO_E, GPIO_OUTPUT, bit_26);
	GPIO_data_direction_pin(GPIO_A, GPIO_INPUT, bit_4);
	GPIO_data_direction_pin(GPIO_C, GPIO_INPUT, bit_6);

	/**
	 *  Enables port A and port C interruption, that correspond to the
	 *  push buttons
	 */
	NVIC_enable_interrupt_and_priotity(PORTA_IRQ,PRIORITY_5);
	NVIC_enable_interrupt_and_priotity(PORTC_IRQ,PRIORITY_5);

	/**
	 *  Enable PIT clock
	 */
	PIT_clock_gating();

	/**
	 *  Enable PIT interruption in channel 0
	 */
	PIT_enable_interrupt(PIT_0, PRIORITY_4);
	NVIC_global_enable_interrupts;

	/**
	 * Callback to the handler that gives us the 1 second delay
	 */
	pit_callback_init(pit_handler);

	/**
	 *  Configure delay time with corresponding parameters, in this case
	 *  the delay would be of 1 second, and it would be done on channel 0
	 */
	PIT_delay(PIT_0, SYSTEM_CLOCK, DELAY);

	int8_t led_counter = 0;	/* Counter of the sequence */
	led_turn[led_counter]();

	while( (FALSE == GPIO_get_irq_status(GPIO_A)) &&
			(FALSE == GPIO_get_irq_status(GPIO_C)) )
	{
		PIT_disable();
	}

	PIT_enable();

	while(1)
	{
		while(TRUE == GPIO_get_irq_status(GPIO_A))
		{
			led_counter++;
			if(5 == led_counter)	/* If the sequence overflowed */
			{
				led_counter = 0;	/* Restart */
			}
			led_turn[led_counter]();

			while(FALSE == g_timer_end_flag)
			{
				/* Nothing */
			}
			g_timer_end_flag = FALSE;
		}

		while(TRUE == GPIO_get_irq_status(GPIO_C))
		{
			led_counter--;
			if(-1 == led_counter)	/* If the sequence overflowed */
			{
				led_counter = 4;	/* Restart */
			}
			led_turn[led_counter](); /* Execute the function of the sequence */

			while(FALSE == g_timer_end_flag)
			{
				/* Nothing */
			}
			g_timer_end_flag = FALSE;
		}
	}

    return 0 ;
}
