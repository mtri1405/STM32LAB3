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
#define TIMER_CYCLE 100

#define TIME_COUNT_PROGRAM  0
#define ONE_SECOND 			1
#define TIME_SEGMENT 		3
#define TIME_LED 			4
extern int counter1;
extern int flag1;
typedef struct{
	int time;
	int timer_counter;
	int timer_flag;
} detail_time;

extern detail_time actions[NUMBER_OF_ACTIONS];
void setupTime(int index, int duration);
void reset(int index);
void timerRun();
void timer1();
#endif /* INC_TIMER_H_ */
