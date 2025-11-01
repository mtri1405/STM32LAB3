/*
 * fsm_manual.c
 *
 *  Created on: Oct 28, 2025
 *      Author: mtri1
 */
#include "fsm_manual.h"

int temp_red, temp_green, temp_amber;
int state_manual = 0;

void init_fsm_manual(){
	state_manual = RED;
	init_blinkLED(state_manual);
	setupTime(TIME_COUNT_PROGRAM, 20000);
	setupTime(ONE_SECOND, SECOND / 2);
	temp_red = Time_red;
	temp_amber = Time_amber;
	temp_green = Time_green;
}
void init_manual_control(){
	setupTime(ONE_SECOND, SECOND);
	// state_auto là trạng thái hiện tại của đèn giao thông
	if (state_auto == RED_AMBER) state_auto = GREEN_RED;
	if (state_auto == AMBER_RED) state_auto = RED_GREEN;
	switch (state_auto){
	case GREEN_RED:
		init_GREEN_RED();
		break;
	case RED_GREEN:
		init_RED_GREEN();
		break;
	}
}
// TODO đem switch ra ngoài
void manual_control_run(){
	// Giữ Mode và Set sẽ trở về chế độ auto
	if (isControlPress()){
			admin_mode = ACTIVE_MODE;
			come_back_auto();
			return;
	}
	// Nhấn Set sẽ chuyển đèn
	if (isSetPress()){
		switch(state_auto){
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
	update7SEG(0,0);
}
void fsm_manual_run(){
	if (actions[TIME_COUNT_PROGRAM].timer_flag == 1){
		admin_mode = ACTIVE_MODE;
		come_back_auto();
		return;
	}
	if (isControlPress()){
		admin_mode = MANUAL_CONTROL_MODE;
		init_manual_control();
		return;
	}
	if (isSetPress()){
		admin_mode = ACTIVE_MODE;

		switch (state_manual){
		case RED:
			if (temp_red < Time_red){
				Time_red = temp_red;
				Time_green = ceil(Time_red * 0.6);
				Time_amber = Time_red - Time_green;
			}
			if (temp_red > Time_red){
				Time_green = Time_green + ceil((temp_red- Time_red)*0.6);
				Time_red = temp_red;
				Time_amber = Time_red - Time_green;
			}
			break;
		case GREEN:
			Time_green = temp_green;
			Time_red = Time_green + Time_amber;
			break;
		case AMBER:
			Time_amber = temp_amber;
			Time_red = Time_green + Time_amber;
			break;
		default:
			break;
		}
		come_back_auto();
		return;
	}

	if (isModePress()){
		setupTime(ONE_SECOND, SECOND / 2);
		switch(state_manual){
		case RED:
			state_manual = GREEN;
			break;
		case GREEN:
			state_manual = AMBER;
			break;
		case AMBER:
			state_manual = RED;
			admin_mode = ACTIVE_MODE;
			come_back_auto();
			return;
		default:
			break;
		}
		init_blinkLED(state_manual);
		return;
	}
	if (isTimePress()){
		switch(state_manual){
		case RED:
			temp_red++;
			break;
		case GREEN:
			temp_green++;
			break;
		case AMBER:
			temp_amber++;
		}
		return;
	}
	if (actions[ONE_SECOND].timer_flag == 1){
		reset(ONE_SECOND);
		blinkLED(state_manual);
	}
	switch(state_manual){
	case RED:
		update7SEG(temp_red, temp_red);
		break;
	case GREEN:
		update7SEG(temp_green, temp_green);
		break;
	case AMBER:
		update7SEG(temp_amber, temp_amber);
		break;
	default:
		break;
	}
}

