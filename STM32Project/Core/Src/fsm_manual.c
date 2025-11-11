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

enum ButtonEvent getButtonEvent() {
	if (isModePress())
		return MODE_PRESSED;
	if (isTimePress())
		return TIME_PRESSED;
	if (isTimeHold())
		return TIME_HOLDED;
	if (isSetPress())
		return SET_PRESSED;
	return NONE;
}

/*=====================[ INIT FUNCTIONS ]=====================*/
void init_fsm_manual() {
	state_manual = RED;
	temp_time = TrafficTimer[RED];
	init_blinkLED(state_manual);
	setupTime(TIME_COUNT_PROGRAM, 20000);
	setupTime(ONE_SECOND, SECOND / 2);
}

void handleButton() {
	if (isModePress()){
		// xử lý mode
		setupTime(ONE_SECOND, SECOND / 2);
		state_manual++;
		if (state_manual > AMBER) {
			state_manual = RED;
			STATUS = ACTIVE_MODE;
			come_back_auto();
			return;
		}
		temp_time = TrafficTimer[state_manual];
		init_blinkLED(state_manual);
	} else if (isTimePress()){
		// xử lý time
		if (++temp_time > 99)
			temp_time = 1; // Giới hạn mức tối đa
	}
	else if(isTimeHold()){
		if (++temp_time > 99)
			temp_time = 1; // Giới hạn mức tối đa
	} else if (isSetPress()){
		// xử lý set
		switch (state_manual) {
		case RED:
			TrafficTimer[RED] = temp_time;
			TrafficTimer[GREEN] = ceil(TrafficTimer[RED] *0.7);
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
/*=====================[ OUTPUT FUNCTIONS ]=====================*/
void handleBlinkLed() {
	if (actions[ONE_SECOND].timer_flag == 1) {
		reset(ONE_SECOND);
		blinkLED(state_manual);
	}
}
/*=====================[ FSM MAIN LOOP ]=====================*/
void fsm_manual_run() {
	handleButton();
	handleBlinkLed();
	switch (state_manual) {
	case RED:
		update7SEG(temp_time, DISPLAY_MODE_RED_ADJUST);
		break;
	case GREEN:
		update7SEG(temp_time, DISPLAY_MODE_GREEN_ADJUST);
		break;
	case AMBER:
		update7SEG(temp_time, DISPLAY_MODE_AMBER_ADJUST);
		break;
	}
}

