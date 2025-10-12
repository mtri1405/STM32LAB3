/*
 * softTimer.c
 *
 *  Created on: Oct 12, 2025
 *      Author: mtri1
 */

#include <timer.h>

detail_time actions[NUMBER_OF_ACTIONS];

void setupTime(int index, int duration) {
	actions[index].time = duration / TIMER_CYCLE;
	actions[index].timer_counter = duration / TIMER_CYCLE;
	actions[index].timer_flag = 0;
}

void reset(int index) {
	actions[index].timer_counter = actions[index].time;
	actions[index].timer_flag = 0;
}

void timerRun() {
	for (int i = 0; i < NUMBER_OF_ACTIONS; i++) {
		if (actions[i].timer_counter > 0) {
			actions[i].timer_counter--;
			if (actions[i].timer_counter <= 0) {
				actions[i].timer_flag = 1;
			}
		}
	}
}
