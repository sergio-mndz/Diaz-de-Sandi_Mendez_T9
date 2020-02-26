/**
	\file
	\brief
		This is the source file for the GPIO device driver for Kinetis K64.
		It contains all the implementation for configuration functions and runtime functions.
		i.e., this is the application programming interface (API) for the GPIO peripheral.
	\author J. Luis Pizano Escalante, luispizano@iteso.mx
	\date	18/02/2019
	\todo
	    Interrupts are not implemented in this API implementation.
*/
#include "MK64F12.h"
#include "GPIO.h"
#include "bits.h"

static gpio_interrupt_flags_t g_intr_status_flag = {0};

void PORTC_IRQHandler(void)
{
	g_intr_status_flag.flag_port_c = TRUE;
	g_intr_status_flag.flag_port_a = FALSE;
	GPIO_clear_interrupt(GPIO_C);

}

void PORTA_IRQHandler(void)
{
	g_intr_status_flag.flag_port_a = TRUE;
	g_intr_status_flag.flag_port_c = FALSE;
	GPIO_clear_interrupt(GPIO_A);
}

void GPIO_clear_interrupt(gpio_port_name_t port_name)
{
	switch(port_name)/** Selecting the GPIO for clock enabling*/
	{
		case GPIO_A: /** GPIO A is selected*/
			PORTA->ISFR=0xFFFFFFFF;
			break;
		case GPIO_B: /** GPIO B is selected*/
			PORTB->ISFR=0xFFFFFFFF;
			break;
		case GPIO_C: /** GPIO C is selected*/
			PORTC->ISFR = 0xFFFFFFFF;
			break;
		case GPIO_D: /** GPIO D is selected*/
			PORTD->ISFR=0xFFFFFFFF;
			break;
		default: /** GPIO E is selected*/
			PORTE->ISFR=0xFFFFFFFF;
			break;

	}// end switch
}

void GPIO_clear_irq_status(gpio_port_name_t gpio)
{
	if(GPIO_A == gpio)
	{
		g_intr_status_flag.flag_port_a = FALSE;
	}
	else
	{
		g_intr_status_flag.flag_port_c = FALSE;
	}
}

uint8_t GPIO_get_irq_status(gpio_port_name_t gpio)
{
	uint8_t status = 0;

	if(GPIO_A == gpio)
	{
		status = g_intr_status_flag.flag_port_a;
	}
	else
	{
		status = g_intr_status_flag.flag_port_c;
	}

	return(status);
}

uint8_t GPIO_clock_gating(gpio_port_name_t port_name)
{
	switch(port_name)/** Selecting the GPIO for clock enabling*/
			{
				case GPIO_A: /** GPIO A is selected*/
					SIM->SCGC5 |= GPIO_CLOCK_GATING_PORTA; /** Bit 9 of SIM_SCGC5 is  set*/
					break;
				case GPIO_B: /** GPIO B is selected*/
					SIM->SCGC5 |= GPIO_CLOCK_GATING_PORTB; /** Bit 10 of SIM_SCGC5 is set*/
					break;
				case GPIO_C: /** GPIO C is selected*/
					SIM->SCGC5 |= GPIO_CLOCK_GATING_PORTC; /** Bit 11 of SIM_SCGC5 is set*/
					break;
				case GPIO_D: /** GPIO D is selected*/
					SIM->SCGC5 |= GPIO_CLOCK_GATING_PORTD; /** Bit 12 of SIM_SCGC5 is set*/
					break;
				case GPIO_E: /** GPIO E is selected*/
					SIM->SCGC5 |= GPIO_CLOCK_GATING_PORTE; /** Bit 13 of SIM_SCGC5 is set*/
					break;
				default: /**If doesn't exist the option*/
					return(FALSE);
			}// end switch
	/**Successful configuration*/
	return(TRUE);
}// end function

uint8_t GPIO_pin_control_register(gpio_port_name_t port_name, uint8_t pin,const gpio_pin_control_register_t*  pin_control_register)
{

	switch(port_name)
	{
		case GPIO_A:/** GPIO A is selected*/
			PORTA->PCR[pin] = *pin_control_register;
			break;
		case GPIO_B:/** GPIO B is selected*/
			PORTB->PCR[pin] = *pin_control_register;
			break;
		case GPIO_C:/** GPIO C is selected*/
			PORTC->PCR[pin] = *pin_control_register;
			break;
		case GPIO_D:/** GPIO D is selected*/
			PORTD->PCR[pin] = *pin_control_register;
			break;
		case GPIO_E: /** GPIO E is selected*/
			PORTE->PCR[pin]= *pin_control_register;
		default:/**If doesn't exist the option*/
			return(FALSE);
		break;
	}
	/**Successful configuration*/
	return(TRUE);
}

void GPIO_write_port(gpio_port_name_t port_name, uint32_t data)
{
	switch(port_name)
	{
		case GPIO_A:/** GPIO A is selected*/
			GPIOA->PDOR = data;	/* Direct assign to the port */
			break;
		case GPIO_B:/** GPIO B is selected*/
			GPIOB->PDOR = data;
			break;
		case GPIO_C:/** GPIO C is selected*/
			GPIOC->PDOR = data;
			break;
		case GPIO_D:/** GPIO D is selected*/
			GPIOD->PDOR = data;
			break;
		case GPIO_E: /** GPIO E is selected*/
			GPIOE->PDOR = data;
		default:/**If doesn't exist the option*/
			return;
		break;
	}
}
uint32_t GPIO_read_port(gpio_port_name_t port_name)
{
	switch(port_name)
	{
		case GPIO_A:/** GPIO A is selected*/
			return GPIOA->PDIR;	/* Register with the port read value */
			break;
		case GPIO_B:/** GPIO B is selected*/
			return GPIOB->PDIR;
			break;
		case GPIO_C:/** GPIO C is selected*/
			return GPIOC->PDIR;
			break;
		case GPIO_D:/** GPIO D is selected*/
			return GPIOD->PDIR;
			break;
		case GPIO_E: /** GPIO E is selected*/
			return GPIOE->PDIR;
		default:/**If doesn't exist the option*/
			return(FALSE);
		break;
	}
}
uint8_t GPIO_read_pin(gpio_port_name_t port_name, uint8_t pin)
{
	uint32_t return_value = 0;	/* Variable to store the read value */
	return_value = GPIO_read_port(port_name);	/* Read the whole port */
	return (uint8_t) (((return_value & (1 << pin)) >> pin));
}
void GPIO_set_pin(gpio_port_name_t port_name, uint8_t pin)
{
	switch(port_name)
	{
		case GPIO_A:/** GPIO A is selected*/
			GPIOA->PSOR |= (1<<pin);	/* Set only the desired pin */
			break;
		case GPIO_B:/** GPIO B is selected*/
			GPIOB->PSOR |= (1<<pin);
			break;
		case GPIO_C:/** GPIO C is selected*/
			GPIOC->PSOR |= (1<<pin);
			break;
		case GPIO_D:/** GPIO D is selected*/
			GPIOD->PSOR |= (1<<pin);
			break;
		case GPIO_E: /** GPIO E is selected*/
			GPIOE->PSOR |= (1<<pin);
		default:/**If doesn't exist the option*/
			return;
		break;
	}
}
void GPIO_clear_pin(gpio_port_name_t port_name, uint8_t pin)
{
	switch(port_name)
	{
		case GPIO_A:/** GPIO A is selected*/
			GPIOA->PCOR |= (1<<pin);	/* Clear only desired pin */
			break;
		case GPIO_B:/** GPIO B is selected*/
			GPIOB->PCOR |= (1<<pin);
			break;
		case GPIO_C:/** GPIO C is selected*/
			GPIOC->PCOR |= (1<<pin);
			break;
		case GPIO_D:/** GPIO D is selected*/
			GPIOD->PCOR |= (1<<pin);
			break;
		case GPIO_E: /** GPIO E is selected*/
			GPIOE->PCOR |= (1<<pin);
		default:/**If doesn't exist the option*/
			return;
		break;
	}
}
void GPIO_toogle_pin(gpio_port_name_t port_name, uint8_t pin)
{
	switch(port_name)
	{
		case GPIO_A:/** GPIO A is selected*/
			GPIOA->PTOR |= (1<<pin);	/* Toggle only desired pin */
			break;
		case GPIO_B:/** GPIO B is selected*/
			GPIOB->PTOR |= (1<<pin);
			break;
		case GPIO_C:/** GPIO C is selected*/
			GPIOC->PTOR |= (1<<pin);
			break;
		case GPIO_D:/** GPIO D is selected*/
			GPIOD->PTOR |= (1<<pin);
			break;
		case GPIO_E: /** GPIO E is selected*/
			GPIOE->PTOR |= (1<<pin);
		default:/**If doesn't exist the option*/
			return;
		break;
	}
}
void GPIO_data_direction_port(gpio_port_name_t port_name ,uint32_t direction)
{
	switch(port_name)
	{
		case GPIO_A:/** GPIO A is selected*/
			GPIOA->PDDR = direction; /* Assign the value to the PDDR register */
			break;
		case GPIO_B:/** GPIO B is selected*/
			GPIOB->PDDR = direction;
			break;
		case GPIO_C:/** GPIO C is selected*/
			GPIOC->PDDR = direction;
			break;
		case GPIO_D:/** GPIO D is selected*/
			GPIOD->PDDR = direction;
			break;
		case GPIO_E: /** GPIO E is selected*/
			GPIOE->PDDR = direction;
		default:/**If doesn't exist the option*/
			return;
		break;
	}
}
void GPIO_data_direction_pin(gpio_port_name_t port_name, uint8_t state, uint8_t pin)
{
	switch(port_name)
	{
		case GPIO_A:/** GPIO A is selected*/
			GPIOA->PDDR |= (state << pin);	/* Set state only for desired pin */
			break;
		case GPIO_B:/** GPIO B is selected*/
			GPIOB->PDDR |= (state << pin);
			break;
		case GPIO_C:/** GPIO C is selected*/
			GPIOC->PDDR |= (state << pin);
			break;
		case GPIO_D:/** GPIO D is selected*/
			GPIOD->PDDR |= (state << pin);
			break;
		case GPIO_E: /** GPIO E is selected*/
			GPIOE->PDDR |= (state << pin);
		default:/**If doesn't exist the option*/
			return;
		break;
	}
}
