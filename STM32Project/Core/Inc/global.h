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
#include "scheduler.h"

// Define state here

#define TIMER_CYCLE 10
#define LED_SEGMENT_CYCLE 200

#define INIT 				0
#define ACTIVE_MODE 		1
#define MANUAL_MODE			2

//#define RUNNING 1

#define RED    0
#define GREEN  1
#define AMBER  2

#define LED_SYS 0

//#define CHANGE_LED 2

// Biến hệ thống
extern int STATUS;
extern int TrafficTimer[3]; // RED - GREEN - AMBER

// Biến FSM Auto
extern int state_auto;
extern int lane1;
extern int lane2;

// Biến FSM Manual
extern int state_manual;
extern int temp_time;

// Biến ID Tác vụ (Task IDs)
extern uint8_t taskKeyInput_ID;
extern uint8_t taskRunFSM_ID;
extern uint8_t taskUpdate7SEG_ID;
extern uint8_t taskUpdateTrafficLEDs_ID; // Thêm ID cho task LED
extern uint8_t taskDecrement_ID;
extern uint8_t taskSysLed_ID;
extern uint8_t taskManualBlink_ID;

void run();

#endif /* INC_GLOBAL_H_ */
