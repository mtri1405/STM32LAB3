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
#define timeOutForKeyPress 50

#define MODE 0
#define TIME 1
#define SET 2

// Define struct for debouncing input
typedef struct{
	int KeyReg0;
	int KeyReg1;
	int KeyReg2;
	int KeyReg3;
	int timeLongPress;
	int flag;
} keyInput;

// Checking if flag = 1
int isButtonPress(int);

// Checking for each mode
int isModePress();
int isTimePress();
int isSetPress();

// Read input from button
void getKeyInput();

#endif /* INC_BUTTON_H_ */
