/*
 * fsm_manual.c
 *
 *  Created on: Oct 28, 2025
 *      Author: mtri1
 */
#include "fsm_manual.h"

/*=====================[ GLOBAL VARIABLES ]=====================*/
int state_manual = 0;   // 3 state RED - 0, GREEN - 1, AMBER - 2
int temp_time;

void task_ManualBlink() {
    // Chỉ nháy khi đang ở MANUAL_MODE
    if(STATUS == MANUAL_MODE) {
        blinkLED(state_manual);
    }
}
/*=====================[ INIT FUNCTIONS ]=====================*/
void init_fsm_manual() {
	state_manual = RED;
	temp_time = TrafficTimer[RED];
	init_blinkLED(state_manual);
	taskManualBlink_ID = SCH_Add_Task(task_ManualBlink, 500, 500);
}

void handleButton() {
	if (isModePress()) {
		// xử lý mode
		state_manual++;
		if (state_manual > AMBER) {
			state_manual = RED;
			STATUS = ACTIVE_MODE;
			come_back_auto();
			return;
		}
		temp_time = TrafficTimer[state_manual];
		init_blinkLED(state_manual);
	} else if (isTimePress()) {
		// xử lý time
		if (++temp_time > 99)
			temp_time = 1; // Giới hạn mức tối đa
	} else if (isTimeHold()) {
		temp_time++;
		if (temp_time > 99) temp_time = 1;
			 // Giới hạn mức tối đa
	} else if (isSetPress()) {
		// xử lý set
		switch (state_manual) {
		case RED:
			TrafficTimer[RED] = temp_time;
			TrafficTimer[GREEN] = ceil(TrafficTimer[RED] * 0.7);
			TrafficTimer[AMBER] = TrafficTimer[RED] - TrafficTimer[GREEN];

			break;
		case GREEN:
			TrafficTimer[GREEN] = temp_time;
			TrafficTimer[RED] = TrafficTimer[GREEN] + TrafficTimer[AMBER];
			break;
		case AMBER:
			TrafficTimer[AMBER] = temp_time;
			TrafficTimer[RED] = TrafficTimer[GREEN] + TrafficTimer[AMBER];
			break;
		}
		STATUS = ACTIVE_MODE;
		come_back_auto();

	}
}
/*=====================[ FSM MAIN LOOP ]=====================*/
void fsm_manual_run() {
	handleButton();
	switch (state_manual) {
	case RED:
		set7SEGValues(temp_time, DISPLAY_MODE_RED_ADJUST);
		break;
	case GREEN:
		set7SEGValues(temp_time, DISPLAY_MODE_GREEN_ADJUST);
		break;
	case AMBER:
		set7SEGValues(temp_time, DISPLAY_MODE_AMBER_ADJUST);
		break;
	}
}

