/*
 * button.h
 *
 *  Created on: Oct 13, 2025
 *      Author: mtri1
 */

#ifndef INC_BUTTON_H_
#define INC_BUTTON_H_

#include "main.h"

#define NO_BUTTON 1

typedef struct{
	int KeyReg0;
	int KeyReg1;
	int KeyReg2;
	int longPress;
	int flag;
} keyInput;

void getKeyInput();

#endif /* INC_BUTTON_H_ */
