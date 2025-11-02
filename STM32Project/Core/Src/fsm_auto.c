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

/*------------------------------------------------
 * Hàm xử lý các sự kiện chung (button, timer)
 *------------------------------------------------*/
void handle_auto_events() {
    // 1. Nhấn Mode → chuyển sang Manual Mode
    if (isModePress()) {
        admin_mode = MANUAL_MODE;
        init_fsm_manual();
        return;
    }

    // 2. Nhấp nháy đèn hệ thống (System LED)
    if (actions[SYSTEM_LED].timer_flag) {
        toggle_LED(LED_SYS);
        reset(SYSTEM_LED);
        return;
    }

    // 3. Cập nhật mỗi giây → giảm timer cho 2 làn
    if (actions[ONE_SECOND].timer_flag) {
        if (lane1 > 0) lane1--;
        if (lane2 > 0) lane2--;
        reset(ONE_SECOND);
        return;
    }
}

/*------------------------------------------------
 * FSM AUTO MODE — chỉ xử lý logic theo state
 *------------------------------------------------*/
void fsm_auto_run() {
    switch (state_auto) {
    case RED_GREEN:
    	handle_auto_events();
        if (actions[TIME_COUNT_PROGRAM].timer_flag) {
            init_RED_AMBER();
        }
        update7SEG(lane1, lane2);
        break;

    case RED_AMBER:
    	handle_auto_events();
        if (actions[TIME_COUNT_PROGRAM].timer_flag) {
            init_GREEN_RED();
        }
        update7SEG(lane1, lane2);
        break;

    case GREEN_RED:
    	handle_auto_events();
        if (actions[TIME_COUNT_PROGRAM].timer_flag) {
            init_AMBER_RED();
        }
        update7SEG(lane1, lane2);
        break;

    case AMBER_RED:
    	handle_auto_events();
        if (actions[TIME_COUNT_PROGRAM].timer_flag) {
            init_RED_GREEN();
        }
        update7SEG(lane1, lane2);
        break;

    default:
        init_RED_GREEN();
        break;
    }


}

/*------------------------------------------------
 * Hàm khôi phục lại trạng thái AUTO sau khi
 * thoát khỏi MANUAL MODE
 *------------------------------------------------*/
void come_back_auto() {
    setupTime(ONE_SECOND, SECOND);

    switch (state_auto) {
    case RED_GREEN:  init_RED_GREEN();  break;
    case RED_AMBER:  init_RED_AMBER();  break;
    case GREEN_RED:  init_GREEN_RED();  break;
    case AMBER_RED:  init_AMBER_RED();  break;
    default:         init_RED_GREEN();  break;
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
	setupTime(TIME_COUNT_PROGRAM, TrafficTimer[GREEN] * SECOND);
	lane1 = TrafficTimer[RED];
	lane2 = TrafficTimer[GREEN];
	reset(ONE_SECOND);
}

void init_RED_AMBER() {
	turn_on_LED(LED_A_RED);
	turn_on_LED(LED_B_AMBER);

	turn_off_LED(LED_A_AMBER);
	turn_off_LED(LED_A_GREEN);
	turn_off_LED(LED_B_RED);
	turn_off_LED(LED_B_GREEN);

	state_auto = RED_AMBER;
	setupTime(TIME_COUNT_PROGRAM, TrafficTimer[AMBER] * SECOND);
	lane2 = TrafficTimer[AMBER];
	reset(ONE_SECOND);
}

void init_GREEN_RED() {
	turn_on_LED(LED_A_GREEN);
	turn_on_LED(LED_B_RED);

	turn_off_LED(LED_A_AMBER);
	turn_off_LED(LED_A_RED);
	turn_off_LED(LED_B_GREEN);
	turn_off_LED(LED_B_AMBER);

	state_auto = GREEN_RED;
	setupTime(TIME_COUNT_PROGRAM, TrafficTimer[GREEN] * SECOND);
	lane1 = TrafficTimer[GREEN];
	lane2 = TrafficTimer[RED];
	reset(ONE_SECOND);
}

void init_AMBER_RED() {
	turn_on_LED(LED_A_AMBER);
	turn_on_LED(LED_B_RED);

	turn_off_LED(LED_A_RED);
	turn_off_LED(LED_A_GREEN);
	turn_off_LED(LED_B_GREEN);
	turn_off_LED(LED_B_AMBER);

	state_auto = AMBER_RED;
	setupTime(TIME_COUNT_PROGRAM, TrafficTimer[AMBER] * SECOND);
	lane1 = TrafficTimer[AMBER];
	reset(ONE_SECOND);
}

