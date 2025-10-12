/*
 * softTimer.h
 *
 *  Created on: Oct 12, 2025
 *      Author: mtri1
 */

#ifndef INC_TIMER_H_
#define INC_TIMER_H_
#include <stdbool.h>

#define NUMBER_OF_ACTIONS 10
#define TIMER_CYCLE 10

typedef struct{
	int time;
	int timer_counter;
	int timer_flag;
} detail_time;

extern detail_time actions[NUMBER_OF_ACTIONS];
void setupTime(int index, int duration);
void reset(int index);
void timerRun();

#endif /* INC_TIMER_H_ */
