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

	// KIỂM TRA CHUYỂN STATE NGAY TẠI ĐÂY
	switch (state_auto) {
	case RED_GREEN:
		if (lane2 == 0) { // Hết giờ Đèn Xanh (lane2)
			init_RED_AMBER();
		}
		break;
	case RED_AMBER:
		if (lane2 == 0) { // Hết giờ Đèn Vàng (lane2)
			init_GREEN_RED();
		}
		break;
	case GREEN_RED:
		if (lane1 == 0) { // Hết giờ Đèn Xanh (lane1)
			init_AMBER_RED();
		}
		break;
	case AMBER_RED:
		if (lane1 == 0) { // Hết giờ Đèn Vàng (lane1)
			init_RED_GREEN();
		}
		break;
	}
}

/*------------------------------------------------
 * Hàm xử lý sự kiện (được gọi mỗi 10ms)
 *------------------------------------------------*/
void handle_auto_events() {
	// Nhấn Mode → chuyển sang Manual Mode
	if (isModePress()) {
		STATUS = MANUAL_MODE;

		// Xóa tất cả các tác vụ của AUTO mode
		SCH_Delete_Task(taskDecrement_ID);
		SCH_Delete_Task(taskSysLed_ID);

		init_fsm_manual(); // Khởi tạo MANUAL mode
		return;
	}
}
/*------------------------------------------------
 * FSM AUTO MODE — chỉ xử lý logic theo state
 *------------------------------------------------*/
void fsm_auto_run() {
	handle_auto_events();
	if (STATUS == MANUAL_MODE)
		return;
	set7SEGValues(lane1, lane2);
}

/*------------------------------------------------
 * Hàm khôi phục lại trạng thái AUTO sau khi
 * thoát khỏi MANUAL MODE
 *------------------------------------------------*/
void come_back_auto() {
	SCH_Delete_Task(taskManualBlink_ID);
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
		init_RED_GREEN();
		break;
	case RED_AMBER:
		init_RED_AMBER();
		break;
	case GREEN_RED:
		init_GREEN_RED();
		break;
	case AMBER_RED:
		init_AMBER_RED();
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
	turn_on_LED(LED_A_RED);
	turn_on_LED(LED_B_GREEN);

	turn_off_LED(LED_A_AMBER);
	turn_off_LED(LED_A_GREEN);
	turn_off_LED(LED_B_RED);
	turn_off_LED(LED_B_AMBER);

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
	turn_on_LED(LED_A_RED);
	turn_on_LED(LED_B_AMBER);

	turn_off_LED(LED_A_AMBER);
	turn_off_LED(LED_A_GREEN);
	turn_off_LED(LED_B_RED);
	turn_off_LED(LED_B_GREEN);

	state_auto = RED_AMBER;
	lane2 = TrafficTimer[AMBER];
}

void init_GREEN_RED() {
	turn_on_LED(LED_A_GREEN);
	turn_on_LED(LED_B_RED);

	turn_off_LED(LED_A_AMBER);
	turn_off_LED(LED_A_RED);
	turn_off_LED(LED_B_GREEN);
	turn_off_LED(LED_B_AMBER);

	state_auto = GREEN_RED;
	lane1 = TrafficTimer[GREEN];
	lane2 = TrafficTimer[RED];
}

void init_AMBER_RED() {
	turn_on_LED(LED_A_AMBER);
	turn_on_LED(LED_B_RED);

	turn_off_LED(LED_A_RED);
	turn_off_LED(LED_A_GREEN);
	turn_off_LED(LED_B_GREEN);
	turn_off_LED(LED_B_AMBER);

	state_auto = AMBER_RED;
	lane1 = TrafficTimer[AMBER];
}

