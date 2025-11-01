/*
 * global.h
 *
 *  Created on: Oct 28, 2025
 *      Author: mtri1
 */

#ifndef INC_GLOBAL_H_
#define INC_GLOBAL_H_

#include "main.h"
#include <stdbool.h>
#include <math.h>
#include "7_SEGMENT.h"
#include "button.h"
#include "fsm_auto.h"
#include "fsm_manual.h"
#include "led.h"
#include "timer.h"

// Define state here

#define TIMER_CYCLE 100
#define LED_SEGMENT_CYCLE 200
#define SECOND 1000

#define INIT 				0
#define ACTIVE_MODE 		1
#define MANUAL_MODE 		2
#define MANUAL_CONTROL_MODE 3

#define RUNNING 1

#define RED    0
#define GREEN  1
#define AMBER  2

#define LED_SYS 0

#define CHANGE_LED 2
extern int TrafficTimer[3]; // RED - GREEN - AMBER
extern int admin_mode;


void run();

#endif /* INC_GLOBAL_H_ */
