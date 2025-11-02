/*
 * global.c
 *
 *  Created on: Oct 28, 2025
 *      Author: mtri1
 */

#include "global.h"

int admin_mode = INIT;

int TrafficTimer[3] = {10, 7, 3}; // RED - GREEN - AMBER

void run(){
	switch (admin_mode){
	case INIT:
		admin_mode = ACTIVE_MODE;
		setupTime(SYSTEM_LED, 500);
		setupTime(TIME_SEGMENT, LED_SEGMENT_CYCLE / 2);
		setupTime(ONE_SECOND, SECOND);
		init_RED_GREEN();
		break;
	case ACTIVE_MODE:

		fsm_auto_run();
		break;
	case MANUAL_MODE:
		fsm_manual_run();
		break;
	case MANUAL_CONTROL_MODE:
		manual_control_run();
		break;
	default:
		break;
	}
}
