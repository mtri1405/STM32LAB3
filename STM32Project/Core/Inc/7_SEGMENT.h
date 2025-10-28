/*
 * 7_SEGMENT.h
 *
 *  Created on: Oct 27, 2025
 *      Author: mtri1
 */

#ifndef INC_7_SEGMENT_H_
#define INC_7_SEGMENT_H_

#include "global.h"

const uint8_t seg_pattern[10][7];

uint16_t segPins_A[7];
uint16_t segPins_B[7];

void display7SEG(int, uint16_t*);
void update7SEG(int, int);
#endif /* INC_7_SEGMENT_H_ */
