/*
 * led.h
 *
 *  Created on: Oct 28, 2025
 *      Author: mtri1
 */

#ifndef INC_LED_H_
#define INC_LED_H_

#include "global.h"
#define	LED_RED 		0

#define LED_A_RED		1
#define	LED_A_AMBER		2
#define	LED_A_GREEN		3
#define	LED_B_RED		4
#define	LED_B_AMBER		5
#define	LED_B_GREEN		6

void turn_on_LED(int);
void turn_off_LED(int);
void toggle_LED(int);

void init_blinkLED(int);
void blinkLED(int);
void task_ToggleSystemLed();
void task_UpdateTrafficLEDs(void);
#endif /* INC_LED_H_ */
