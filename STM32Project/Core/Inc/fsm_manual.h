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
	SET_PRESSED
};

void init_fsm_manual();
void init_manual_control();


void handleBlinkLed();
void handleControlMode();
void handleButton();
void manual_control_run();
void fsm_manual_run();

#endif /* INC_FSM_MANUAL_H_ */
