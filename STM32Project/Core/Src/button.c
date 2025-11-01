/*
 * button.c
 *
 *  Created on: Oct 13, 2025
 *      Author: mtri1
 */

#include "button.h"

// Define button pin in type
uint16_t pin_of_buttons[NO_BUTTON] = {
MODE_Pin,
TIME_Pin,
SET_Pin,
CONTROL_Pin,
};

// Declare number of button
keyInput button[NO_BUTTON];

//
int isButtonPress(int idx) {
	if (idx > NO_BUTTON || idx < 0) {
		return -1;
	} else {
		if (button[idx].flag == 1) {
			button[idx].flag = 0;
			return 1;
		}
	}
	return 0;
}
int isButtonHolding(int idx) {
	if (idx > NO_BUTTON || idx < 0) {
		return -1;
	} else {
		if (button[idx].isHoldingFlag == 1) {
			return 1;
		}
	}
	return 0;
}
// Kiểm tra MODE button
int isModePress() {
	return isButtonPress(MODE);
}
int isModeHold() {
	return isButtonHolding(MODE);
}

// Kiểm tra TIME button
int isTimePress() {
	return isButtonPress(TIME);
}
int isTimeHold() {
	return isButtonHolding(TIME);
}

// Kiểm tra SET button
int isSetPress() {
	return isButtonPress(SET);
}
int isSetHold() {
	return isButtonHolding(SET);
}

// Kiểm tra Control button
int isControlPress(){
	return isButtonPress(CONTROL);
}
void getKeyInput() {
	for (int i = 0; i < NO_BUTTON; i++) {
		// shifting the button registry history
		button[i].KeyReg2 = button[i].KeyReg1;
		button[i].KeyReg1 = button[i].KeyReg0;
		// Read current button state from hardware pin
		button[i].KeyReg0 = HAL_GPIO_ReadPin(GPIOA, pin_of_buttons[i]);

		// Checking button state is stable for 3 read
		if ((button[i].KeyReg0 == button[i].KeyReg1)
				&& (button[i].KeyReg1 == button[i].KeyReg2)) {
			//	Detect any change compare to the previous history state
			if (button[i].KeyReg2 != button[i].KeyReg3) {
				button[i].KeyReg3 = button[i].KeyReg2;

				//	If button is press, set flag to 1 and start counting for long press timer
				if (button[i].KeyReg3 == PRESS_STATE) {
					button[i].timeLongPress = timeOutForKeyPress;
					button[i].flag = 1;
				}
			} else {
				if (button[i].KeyReg3 == PRESS_STATE) {
					button[i].timeLongPress--;
					if (button[i].timeLongPress <= 0) {
						button[i].timeLongPress = timeOutForKeyPress;
						button[i].flag = 1;
						button[i].isHoldingFlag = 1;
					}
				} else {
					button[i].isHoldingFlag = 0;
				}
			}
		}
	}
}
