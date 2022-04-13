/*
 * lcd_test_func.h
 *
 *  Created on: 2022. 4. 8.
 *      Author: sungt
 */

#ifndef SRC_AP_LCD_TEST_FUNC_H_
#define SRC_AP_LCD_TEST_FUNC_H_

#include "hw_def.h"


#define min(a,b) (((a)<(b))?(a):(b))


void demoLCD(int i);

unsigned long testFillScreen();
unsigned long testText();
unsigned long testLines(uint16_t color);
unsigned long testFastLines(uint16_t color1, uint16_t color2);
unsigned long testRects(uint16_t color);
unsigned long testFilledRects(uint16_t color1, uint16_t color2);
unsigned long testFilledCircles(uint8_t radius, uint16_t color);
unsigned long testCircles(uint8_t radius, uint16_t color);
unsigned long testTriangles();
unsigned long testFilledTriangles();
unsigned long testRoundRects();
unsigned long testFilledRoundRects();
unsigned long testDrawImage();

#endif /* SRC_AP_LCD_TEST_FUNC_H_ */
