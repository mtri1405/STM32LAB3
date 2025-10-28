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
#define INIT 0
#define ACTIVE_MODE 1
#define MANUAL_MODE 2

#define RUNNING 1

#define GREEN  3
#define AMBER  4
#define RED    5

#define CHANGE_LED 2

extern int admin_mode;
extern int Time_red;
extern int Time_amber;
extern int Time_green;

void run();

#endif /* INC_GLOBAL_H_ */
