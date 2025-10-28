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

extern int state_auto;
extern int lane1;
extern int lane2;

void fsm_auto_run();

void init_RED_GREEN();
void init_RED_AMBER();
void init_GREEN_RED();
void init_AMBER_RED();

#endif /* INC_FSM_AUTO_H_ */
