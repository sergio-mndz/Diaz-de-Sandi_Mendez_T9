/*
 * RGB.h
 *
 *  Created on: Feb 16, 2020
 *      Author: sergio_mndz
 */

#ifndef RGB_H_
#define RGB_H_

/**LED Turning on functions**/
/*
 *brief	 This function turns on the 22nd bit of the GPIOB
 *and turns off 21st bit of the GIOB and the 26th bit of
 *the GPIOE, to ensure that only the corresponding bit of the
 *red colour is on
 */
void red_on();


/*
 *brief	 This function turns on the 26th bit of the GPIOE
 *and turns off 21st and 22nd bits of the GIOB, to ensure
 *that only the corresponding bit of the green colour is on
 */
void green_on();


/*
 *brief	 This function turns on the 21st bit of the GPIOB
 *and turns off 22nd bit of the GIOB and the 26th bit of
 *the GPIOE, to ensure that only the corresponding bit of the
 *blue colour is on
 */
void blue_on();


/*
 *brief	  This function turns on the 22nd bit of the GPIOB
 * and the 26th bit of the GPIOE, as well as turning off the
 * 21st bit of the GPIOB, to let on only the bits that would
 * combine to show the yellow colour
 */
void yellow_on();


/*
 *brief	  This function turns on the 21st bit of the GPIOB
 * and the 26th bit of the GPIOE, as well as turning off the
 * 22nd bit of the GPIOB, to let on only the bits that would
 * combine to show the purple colour
 */
void purple_on();


/*
 *brief	  This function turns on the 21st and 22nd bits of the
 * GPIOB, as well as the 26th bit of the GPIOE, to turn the 3
 * 	RGB colors on and make it look white
 */
void white_on();



/**LED Turning off functions**/
/*
 * brief   	This function turns off the 22nd bit of the
 * GPIOB, so that if the red LED is on, it will turned off,
 * leaving the LED off if this was the only bit on
 */
void red_off();


/*
 * brief   This function turns off the 26th bit of the
 * GPIOE, so that if the green LED is on, it will be turned
 * off, leaving it totally off it it was the only bit turned
 * on
 */
void green_off();


/*
 * brief    This function turns off the 21st bit of the
 * GPIOB, so that if the blue LED is on, it will be turned
 * off, leaving it totally off if it was the only bit on
 */
void blue_off();


/*
 * brief   This function turns off the 21st and 22nd
 * bits of the GPIOB, so that the blue and red colors of
 * the LED are turned off. If both were on that would be
 * the purple color, so it will be turned off
 */
void purple_off();


/*
 * brief   This function turns off 22nd bit of the GPIOB,
 * as well as the 26th bit of the GPIOE, so that if the
 * yellow color was displayed it would be turned off
 */
void yellow_off();


/*
 * brief   This function turns off the 21st and 22nd bits
 * of the GPIOB, and the 26th bit of the GPIOE, so that the
 * LED will be completely turned off
 */
void all_off();

#endif /* RGB_H_ */
