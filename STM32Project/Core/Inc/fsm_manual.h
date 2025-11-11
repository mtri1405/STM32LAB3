/*
 * fsm_manual.h
 *
 *  Created on: Oct 28, 2025
 *      Author: mtri1
 */

#ifndef INC_FSM_MANUAL_H_
#define INC_FSM_MANUAL_H_
#include "global.h"

enum ButtonEvent {
	NONE,
	MODE_PRESSED,
	TIME_PRESSED,
	TIME_HOLDED,
	SET_PRESSED
};
#define DISPLAY_MODE_RED_ADJUST   2
#define DISPLAY_MODE_GREEN_ADJUST 3
#define DISPLAY_MODE_AMBER_ADJUST 4

void init_fsm_manual();
void init_manual_control();


void handleBlinkLed();
void handleControlMode();
void handleButton();
void manual_control_run();
void fsm_manual_run();

#endif /* INC_FSM_MANUAL_H_ */
