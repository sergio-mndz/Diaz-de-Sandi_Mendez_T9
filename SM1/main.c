#include <stdio.h>
#include <stdint.h>
#include "MK64F12.h"
#include "GPIO.h"
#include "Bits.h"
#include "RGB.h"
#include "NVIC.h"
#include "PIT.h"

#define SYSTEM_CLOCK (21000000U)
#define DELAY (0.25F)

gpio_pin_control_register_t led_enable = GPIO_MUX1;
gpio_pin_control_register_t sw_enable = GPIO_MUX1 | GPIO_PE | GPIO_PS | INTR_FALLING_EDGE;

typedef enum
{
	INITIAL,
	GREEN,
	BLUE,
	PURPLE,
	RED,
	YELLOW
} SM_states_t;

uint8_t g_timer_end_flag = FALSE;

/* Function assigne to the PIT callback */
void pit_handler(void)
{
	/* Counter of times the delay time has passed */
	static uint8_t counter = 0;
	counter++;
	/* At four times (0.25 x 4) a second has passed */
	if(counter == 4)
	{
		/* Turn on respective flag and restart the count */
		g_timer_end_flag = TRUE;
		counter = 0;
	}
}

int main(void)
{
	/* Set to a state that won´t do anything */
	SM_states_t current_state = INITIAL;

	/* Enable clocks */
	GPIO_clock_gating(GPIO_A);
	GPIO_clock_gating(GPIO_B);
	GPIO_clock_gating(GPIO_C);
	GPIO_clock_gating(GPIO_E);

	/* Enable GPIO of leds and switches */
	GPIO_pin_control_register(GPIO_B, bit_21, & led_enable);
	GPIO_pin_control_register(GPIO_B, bit_22, & led_enable);
	GPIO_pin_control_register(GPIO_E, bit_26, & led_enable);
	GPIO_pin_control_register(GPIO_A, bit_4, & sw_enable);
	GPIO_pin_control_register(GPIO_C, bit_6, & sw_enable);

	/* Send leds to a safe value */
	red_off();
	blue_off();
	green_off();

	/* Enable leds as output and switches as input */
	GPIO_data_direction_pin(GPIO_B, GPIO_OUTPUT, bit_21);
	GPIO_data_direction_pin(GPIO_B, GPIO_OUTPUT, bit_22);
	GPIO_data_direction_pin(GPIO_E, GPIO_OUTPUT, bit_26);
	GPIO_data_direction_pin(GPIO_A, GPIO_INPUT, bit_4);
	GPIO_data_direction_pin(GPIO_C, GPIO_INPUT, bit_6);

	/* Enable interruption for SW2 and SW3 with same priority */
	NVIC_enable_interrupt_and_priotity(PORTA_IRQ,PRIORITY_5);
	NVIC_enable_interrupt_and_priotity(PORTC_IRQ,PRIORITY_5);

	/* Enable PIT clock */
	PIT_clock_gating();

	/* Enable PIT interruption */
	PIT_enable_interrupt(PIT_0, PRIORITY_4);
	NVIC_global_enable_interrupts;

	/* Assign function called by the PIT INT callback */
	pit_callback_init(pit_handler);

	/* Configure delay time with corresponding parameters */
	PIT_delay(PIT_0, SYSTEM_CLOCK, DELAY);

	/* Wait for a SW to be pressed and don´t enable the PIT untill then */
	while( (FALSE == GPIO_get_irq_status(GPIO_A)) &&
			(FALSE == GPIO_get_irq_status(GPIO_C)) )
	{
		PIT_disable();
	}
	PIT_enable();

	while(1)
	{
		/* As long as the other SW hasn't been pressed */
		while(TRUE == GPIO_get_irq_status(GPIO_A))
		{
			/* According to the specified SM turn on respective led */
			switch(current_state)
			{
				case GREEN:
					current_state = BLUE;
					blue_on();
				break;
				case BLUE:
					current_state = PURPLE;
					purple_on();
				break;
				case PURPLE:
					current_state = RED;
					red_on();
				break;
				case RED:
					current_state = YELLOW;
					yellow_on();
				break;
				case YELLOW:
					current_state = GREEN;
					green_on();
				break;
				default:
					current_state = GREEN;
					green_on();
				break;
			}
			/* Wait until a second (defined by g_timer_end_flag) has passed */
			while(FALSE == g_timer_end_flag)
			{
				/* Nothing */
			}
			g_timer_end_flag = FALSE;
		}

		/* As long as the other SW hasn't been pressed */
		while(TRUE == GPIO_get_irq_status(GPIO_C))
		{
			/* According to the specified SM turn on respective led */
			switch(current_state)
			{
				case YELLOW:
					current_state = RED;
					red_on();
				break;
				case RED:
					current_state = PURPLE;
					purple_on();
				break;
				case PURPLE:
					current_state = BLUE;
					blue_on();
				break;
				case BLUE:
					current_state = GREEN;
					green_on();
				break;
				case GREEN:
					current_state = YELLOW;
					yellow_on();
				break;
				default:
					current_state = YELLOW;
					yellow_on();
					break;
			}
			/* Wait until a second (defined by g_timer_end_flag) has passed */
			while(FALSE == g_timer_end_flag)
			{
				/* Nothing */
			}
			g_timer_end_flag = FALSE;
		}
	}

    return 0 ;
}
