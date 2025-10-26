/*
 * button.c
 *
 *  Created on: Oct 13, 2025
 *      Author: mtri1
 */

#include "button.h"

keyInput button[NO_BUTTON];

void getKeyInput(){
	for (int i = 0; i < NO_BUTTON; i++){
		button[i].KeyReg0 = button[i].KeyReg1;
		button[i].KeyReg1 = button[i].KeyReg2;
		button[i].KeyReg2 = HAL_GPIO_ReadPin(Button_1_GPIO_Port, Button_1_Pin);

		if ((button[i].KeyReg0 == button[i].KeyReg1) && (button[i].KeyReg1 == button[i].KeyReg2)){

		}
	}
}
