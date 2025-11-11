/*
 * button.h
 *
 *  Created on: Oct 13, 2025
 *      Author: mtri1
 */

#ifndef INC_BUTTON_H_
#define INC_BUTTON_H_

#include "main.h"

#define NO_BUTTON 3
#define PRESS_STATE RESET
#define NORMAL_STATE SET
#define timeOutForKeyPress 10

#define MODE 0
#define TIME 1
#define SET 2
#define CONTROL 3

// Define struct for debouncing input
typedef struct {
	int KeyReg0;
	int KeyReg1;
	int KeyReg2;
	int KeyReg3;
	int timeLongPress;
	int flag;
	int isHoldingFlag;
} keyInput;

// Checking if flag = 1
int isButtonPress(int);
int isButtonHolding(int);

// Kiểm tra MODE button
int isModePress();
int isModeHold();

// Kiểm tra TIME button
int isTimePress();
int isTimeHold();

// Kiểm tra SET button
int isSetPress();
int isSetHold();

// Read input from button
void getKeyInput();

#endif /* INC_BUTTON_H_ */
