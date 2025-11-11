/*
 * fsm_auto.h
 *
 *  Created on: Oct 28, 2025
 *      Author: mtri1
 */

#ifndef INC_FSM_AUTO_H_
#define INC_FSM_AUTO_H_

#include "global.h"

#define RED_GREEN 0
#define RED_AMBER 1
#define GREEN_RED 2
#define AMBER_RED 3

extern uint8_t taskAutoTransition_ID;
extern uint8_t taskDecrement_ID;
extern uint8_t taskSysLed_ID;
extern uint8_t taskManualBlink_ID;
extern int state_auto;
extern int lane1;
extern int lane2;
void task_DecrementTimers();
void task_FsmAutoTransition();
void handle_auto_events();
void fsm_auto_run();
void come_back_auto();
void init_RED_GREEN();
void init_RED_AMBER();
void init_GREEN_RED();
void init_AMBER_RED();
#endif /* INC_FSM_AUTO_H_ */
