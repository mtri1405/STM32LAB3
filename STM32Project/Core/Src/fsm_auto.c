/*
 * fsm_auto.c
 *
 *  Created on: Oct 28, 2025
 *      Author: mtri1
 */

#include "fsm_auto.h"

int state_auto = 0;
int lane1 = 0;
int lane2 = 0;

void fsm_auto_run(){
	if (isModePress()){
		admin_mode = MANUAL_MODE;
		init_fsm_manual();
		return;
	}

	if (actions[ONE_SECOND].timer_flag == 1){
		lane1--;
		lane2--;
		reset(ONE_SECOND);
	}

	if (actions[TIME_COUNT_PROGRAM].timer_flag == 1){
		switch(state_auto){
		case RED_GREEN:
			init_RED_AMBER();
			break;
		case RED_AMBER:
			init_GREEN_RED();
			break;
		case GREEN_RED:
			init_AMBER_RED();
			break;
		case AMBER_RED:
			init_RED_GREEN();
			break;
		default:
			break;
		}
	}

	update7SEG(lane1, lane2);


}

void init_RED_GREEN(){
	turn_on_LED(LED_A_RED);
	turn_on_LED(LED_B_GREEN);

	turn_off_LED(LED_A_AMBER);
	turn_off_LED(LED_A_GREEN);
	turn_off_LED(LED_B_RED);
	turn_off_LED(LED_B_AMBER);

	state_auto = RED_GREEN;
	setupTime(TIME_COUNT_PROGRAM, Time_green * SECOND);
	lane1 = Time_red;
	lane2 = Time_green;
	reset(ONE_SECOND);
}

void init_RED_AMBER(){
	turn_on_LED(LED_A_RED);
	turn_on_LED(LED_B_AMBER);

	turn_off_LED(LED_A_AMBER);
	turn_off_LED(LED_A_GREEN);
	turn_off_LED(LED_B_RED);
	turn_off_LED(LED_B_GREEN);

	state_auto = RED_AMBER;
	setupTime(TIME_COUNT_PROGRAM, Time_amber * SECOND);
	lane2 = Time_amber;
	reset(ONE_SECOND);
}

void init_GREEN_RED(){
	turn_on_LED(LED_A_GREEN);
	turn_on_LED(LED_B_RED);

	turn_off_LED(LED_A_AMBER);
	turn_off_LED(LED_A_RED);
	turn_off_LED(LED_B_GREEN);
	turn_off_LED(LED_B_AMBER);

	state_auto = GREEN_RED;
	setupTime(TIME_COUNT_PROGRAM, Time_green * SECOND);
	lane1 = Time_green;
	lane2 = Time_red;
	reset(ONE_SECOND);
}

void init_AMBER_RED(){
	turn_on_LED(LED_A_AMBER);
	turn_on_LED(LED_B_RED);

	turn_off_LED(LED_A_RED);
	turn_off_LED(LED_A_GREEN);
	turn_off_LED(LED_B_GREEN);
	turn_off_LED(LED_B_AMBER);

	state_auto = AMBER_RED;
	setupTime(TIME_COUNT_PROGRAM, Time_amber * SECOND);
	lane1 = Time_amber;
	reset(ONE_SECOND);
}
