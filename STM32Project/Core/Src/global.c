/*
 * global.c
 *
 *  Created on: Oct 28, 2025
 *      Author: mtri1
 */

#include "global.h"

int STATUS = INIT;

int TrafficTimer[3] = {10, 7, 3}; // RED - GREEN - AMBER

void run() {
	switch (STATUS) {
	case INIT:
		STATUS = ACTIVE_MODE;
		SCH_Add_Task(getKeyInput, 0, 10); // Quét nút nhấn mỗi 10ms
		SCH_Add_Task(run, 10, 10); // Chạy hàm này mỗi 10ms
		SCH_Add_Task(task_Update7SEG, 20, 100); // Update 7Seg mỗi 100ms
		init_RED_GREEN();
		break;
	case ACTIVE_MODE:
		fsm_auto_run();
		break;
	case MANUAL_MODE:
		fsm_manual_run();
		break;
	default:
		break;
	}

}
