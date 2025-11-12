/*
 * global.c
 *
 *  Created on: Oct 28, 2025
 *      Author: mtri1
 */

#include "global.h"

int STATUS = INIT;

int TrafficTimer[3] = {5, 3, 2}; // RED - GREEN - AMBER

void run() {
	switch (STATUS) {
	case INIT:
		STATUS = ACTIVE_MODE;
		init_RED_GREEN();
		break;
	case ACTIVE_MODE:
		fsm_auto_run();
		break;
	case MANUAL_MODE:
		fsm_manual_run();
		break;
	default:
		break;
	}

}
