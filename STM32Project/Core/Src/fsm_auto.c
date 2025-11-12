/*
 * fsm_auto.c
 *
 *  Created on: Oct 28, 2025
 *      Author: MinhTri
 */

#include "fsm_auto.h"

int state_auto = RED_GREEN;
int lane1 = 0;
int lane2 = 0;

uint8_t taskDecrement_ID = 0;
uint8_t taskSysLed_ID = 0;
uint8_t taskManualBlink_ID = 0;

// Tác vụ này đếm ngược 2 đồng hồ
void task_DecrementTimers() {
	// Chỉ chạy nếu đang ở AUTO_MODE
	if (STATUS != ACTIVE_MODE)
		return;

	if (lane1 > 0)
		lane1--;
	if (lane2 > 0)
		lane2--;

//	// KIỂM TRA CHUYỂN STATE NGAY TẠI ĐÂY
//	switch (state_auto) {
//	case RED_GREEN:
//		if (lane2 == 0) { // Hết giờ Đèn Xanh (lane2)
//			init_RED_AMBER();
//		}
//		break;
//	case RED_AMBER:
//		if (lane2 == 0) { // Hết giờ Đèn Vàng (lane2)
//			init_GREEN_RED();
//		}
//		break;
//	case GREEN_RED:
//		if (lane1 == 0) { // Hết giờ Đèn Xanh (lane1)
//			init_AMBER_RED();
//		}
//		break;
//	case AMBER_RED:
//		if (lane1 == 0) { // Hết giờ Đèn Vàng (lane1)
//			init_RED_GREEN();
//		}
//		break;
//	}
}

/*------------------------------------------------
 * FSM AUTO MODE — chỉ xử lý logic theo state
 *------------------------------------------------*/
void fsm_auto_run() {
	if (isModePress()) {
		STATUS = MANUAL_MODE;
		// Xóa các tác vụ của AUTO mode
		SCH_Delete_Task(taskDecrement_ID);
		SCH_Delete_Task(taskSysLed_ID);
		// Reset ID để báo hiệu task đã bị xóa
		taskDecrement_ID = 0;
		taskSysLed_ID = 0;

		init_fsm_manual();
		return;
	}
	switch (state_auto) {
	case RED_GREEN:
		if (lane2 == 0) { // Hết giờ Đèn Xanh
			init_RED_AMBER(); // Chỉ gọi hàm init logic
		}
		break;
	case RED_AMBER:
		if (lane2 == 0) {// Hết giờ Đèn Vàng
			init_GREEN_RED();
		}
		break;
	case GREEN_RED:
		if (lane1 == 0) { // Hết giờ Đèn Xanh
			init_AMBER_RED(); // Chỉ gọi hàm init logic
		}
		break;
	case AMBER_RED:
		if (lane1 == 0) {// Hết giờ Đèn Vàng
			init_RED_GREEN();
		}
		break;
	default:
		break;
	}

	set7SEGValues(lane1, lane2);
}

/*------------------------------------------------
 * Hàm khôi phục lại trạng thái AUTO sau khi
 * thoát khỏi MANUAL MODE
 *------------------------------------------------*/
void come_back_auto() {
	SCH_Delete_Task(taskManualBlink_ID);
	taskManualBlink_ID = 0; // Reset ID
	// Thêm lại các tác vụ của AUTO mode
	if (taskDecrement_ID == 0) {
		taskDecrement_ID = SCH_Add_Task(task_DecrementTimers, 1000, 1000);
	}
	if (taskSysLed_ID == 0) {
		taskSysLed_ID = SCH_Add_Task(task_ToggleSystemLed, 500, 500);
	}
	// Khởi động lại logic FSM tại state hiện tại
	switch (state_auto) {
	case RED_GREEN:
		lane1 = TrafficTimer[RED];
		lane2 = TrafficTimer[GREEN];
		break;
	case RED_AMBER:
		lane2 = TrafficTimer[AMBER];
		break;
	case GREEN_RED:
		lane2 = TrafficTimer[RED];
		lane1 = TrafficTimer[GREEN];
		break;
	case AMBER_RED:
		lane1 = TrafficTimer[AMBER];
		break;
	default:
		init_RED_GREEN();
		break;
	}
}

/*------------------------------------------------
 * Các hàm khởi tạo trạng thái đèn
 *------------------------------------------------*/
void init_RED_GREEN() {
	state_auto = RED_GREEN;

	lane1 = TrafficTimer[RED];
	lane2 = TrafficTimer[GREEN];
	if (taskDecrement_ID == 0) {
		taskDecrement_ID = SCH_Add_Task(task_DecrementTimers, 1000, 1000);
	}
	if (taskSysLed_ID == 0) {
		taskSysLed_ID = SCH_Add_Task(task_ToggleSystemLed, 500, 500);
	}
}

void init_RED_AMBER() {
	state_auto = RED_AMBER;
	lane2 = TrafficTimer[AMBER];
}

void init_GREEN_RED() {
	state_auto = GREEN_RED;
	lane1 = TrafficTimer[GREEN];
	lane2 = TrafficTimer[RED];
}

void init_AMBER_RED() {
	state_auto = AMBER_RED;
	lane1 = TrafficTimer[AMBER];
}

