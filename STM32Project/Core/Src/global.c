/*
 * global.c
 *
 *  Created on: Oct 28, 2025
 *      Author: mtri1
 */

#include "global.h"

int admin_mode = 0;
int Time_red = 10;
int Time_amber = 3;
int Time_green = 7;

void run(){
	switch (admin_mode){
	case INIT:
		admin_mode = ACTIVE_MODE;
		setupTime(TIME_SEGMENT, LED_SEGMENT_CYCLE);
		setupTime(ONE_SECOND, SECOND);
		init_RED_GREEN();
		break;
	case ACTIVE_MODE:
		fsm_auto_run();
	case MANUAL_MODE:
		fsm_manual_run();
	default:
		break;
	}
}
