/*
 * fsm_manual.h
 *
 *  Created on: Oct 28, 2025
 *      Author: mtri1
 */

#ifndef INC_FSM_MANUAL_H_
#define INC_FSM_MANUAL_H_
#include "global.h"

void init_fsm_manual();
void init_manual_control();

void handleModeButton();
void handleTimeButton();
void handleSetButton();
void handleBlinkLed();
void handleControlMode();

void manual_control_run();
void fsm_manual_run();

#endif /* INC_FSM_MANUAL_H_ */
