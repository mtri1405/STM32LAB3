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
	if (isModePress()) return MODE_PRESSED;
	if (isTimePress()) return TIME_PRESSED;
	if (isSetPress())  return SET_PRESSED;
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

void init_manual_control() {
	setupTime(ONE_SECOND, SECOND);

	// Điều chỉnh lại trạng thái hiện tại của auto
	if (state_auto == RED_AMBER)
		state_auto = GREEN_RED;
	if (state_auto == AMBER_RED)
		state_auto = RED_GREEN;

	switch (state_auto) {
	case GREEN_RED: init_GREEN_RED(); break;
	case RED_GREEN: init_RED_GREEN(); break;
	default: break;
	}
}

/*=====================[ INPUT HANDLERS ]=====================*/
// Nếu Control Mode được nhấn, ghi đè và chuyển sang Control
void handleControlMode() {
	if (!isControlPress())
		return;

	admin_mode = MANUAL_CONTROL_MODE;
	init_manual_control();
}

void handleButton() {
	switch (getButtonEvent()) {
	case MODE_PRESSED:
		// xử lý mode
		setupTime(ONE_SECOND, SECOND / 2);
		state_manual++;
		if (state_manual > AMBER) {
			state_manual = RED;
			admin_mode = ACTIVE_MODE;
			come_back_auto();
			return;
		}
		temp_time = TrafficTimer[state_manual];
		init_blinkLED(state_manual);
		break;
	case TIME_PRESSED:
		// xử lý time
		if (++temp_time > 99)
			temp_time = 1; // Giới hạn mức tối đa
		break;
	case SET_PRESSED:
		// xử lý set
		switch (state_manual) {
		case RED:
			TrafficTimer[RED] = temp_time;
			TrafficTimer[GREEN] = TrafficTimer[RED] - TrafficTimer[AMBER];
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
		admin_mode = ACTIVE_MODE;
		come_back_auto();
		break;
	default:
		break;
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
	switch (state_manual) {
	case RED:
		update7SEG(temp_time, 2);
		handleButton();
		handleBlinkLed();
		break;

	case GREEN:
		update7SEG(temp_time, 3);
		handleButton();
		handleBlinkLed();
		break;

	case AMBER:
		update7SEG(temp_time, 4);
		handleButton();
		handleBlinkLed();
		break;
	}
}
/*=====================[ MANUAL CONTROL MODE ]=====================*/

void manual_control_run() {
	// Giữ Mode và Set sẽ trở về chế độ auto
	if (isControlPress()) {
		admin_mode = ACTIVE_MODE;
		come_back_auto();
		return;
	}
	// Nhấn Set sẽ chuyển đèn
	if (isSetPress()) {
		switch (state_auto) {
		case GREEN_RED:
			state_auto = RED_GREEN;
			init_RED_GREEN();
			break;
		case RED_GREEN:
			state_auto = GREEN_RED;
			init_GREEN_RED();
			break;
		default:
			break;
		}
		return;
	}
	update7SEG(0, 0);
}
