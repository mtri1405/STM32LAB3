/*
 * led.c
 *
 *  Created on: Oct 28, 2025
 *      Author: mtri1
 */

#include "led.h"

int state_led = 0;

uint16_t array_led_pins[] = { LED_RED_Pin, LED_A_RED_Pin, LED_A_AMBER_Pin,
		LED_A_GREEN_Pin, LED_B_RED_Pin, LED_B_AMBER_Pin, LED_B_GREEN_Pin };

void turn_on_LED(int pos) {
	HAL_GPIO_WritePin(GPIOA, array_led_pins[pos], GPIO_PIN_SET);
}

void turn_off_LED(int pos) {
	HAL_GPIO_WritePin(GPIOA, array_led_pins[pos], GPIO_PIN_RESET);
}

void toggle_LED(int pos) {
	HAL_GPIO_TogglePin(GPIOA, array_led_pins[pos]);
}

void init_blinkLED(int color) {
	switch (color) {
	case RED:
		turn_on_LED(LED_A_RED);
		turn_on_LED(LED_B_RED);

		turn_off_LED(LED_A_GREEN);
		turn_off_LED(LED_B_GREEN);

		turn_off_LED(LED_A_AMBER);
		turn_off_LED(LED_B_AMBER);
		break;
	case AMBER:
		turn_on_LED(LED_A_AMBER);
		turn_on_LED(LED_B_AMBER);

		turn_off_LED(LED_A_RED);
		turn_off_LED(LED_B_RED);

		turn_off_LED(LED_A_AMBER);
		turn_off_LED(LED_B_AMBER);
		break;
	case GREEN:
		turn_on_LED(LED_A_GREEN);
		turn_on_LED(LED_B_GREEN);

		turn_off_LED(LED_A_RED);
		turn_off_LED(LED_B_RED);

		turn_off_LED(LED_A_AMBER);
		turn_off_LED(LED_B_AMBER);
		break;
	default:
		break;
	}
}

void blinkLED(int color) {
	switch (color) {
	case RED:
		toggle_LED(LED_A_RED);
		toggle_LED(LED_B_RED);
		break;
	case AMBER:
		toggle_LED(LED_A_AMBER);
		toggle_LED(LED_B_AMBER);
		break;
	case GREEN:
		toggle_LED(LED_A_GREEN);
		toggle_LED(LED_B_GREEN);
		break;
	default:
		break;
	}
}
