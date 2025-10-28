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
void fsm_manual_run(){
	if (actions[TIME_COUNT_PROGRAM].timer_flag == 1){
		admin_mode = ACTIVE_MODE;
		come_back_auto();
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

