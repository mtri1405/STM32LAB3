/*
 * scheduler.h
 *
 *  Created on: Nov 11, 2025
 *      Author: MinhTri
 */

#ifndef INC_SCHEDULER_H_
#define INC_SCHEDULER_H_

#include <stdint.h>

typedef struct {
	void (*pTask)(void);
	uint32_t Delay;
	uint32_t Period;
	uint32_t RunMe;
	uint32_t TaskID;
}sTask;

#define SCH_MAX_TASKS 20

void SCH_INIT(void);

void SCH_Add_Task (void (*pFunction), uint32_t Delay, uint32_t Period);

void SCH_Update(void);

void SCH_Dispatch_Tasks(void);
#endif /* INC_SCHEDULER_H_ */
