/*
 * menu.h
 *
 *  Created on: 2022. 4. 8.
 *      Author: sungt
 */

#ifndef SRC_COMMON_HW_INCLUDE_MENU_H_
#define SRC_COMMON_HW_INCLUDE_MENU_H_

#include "hw_def.h"



#ifdef _USE_HW_MENU






#ifdef LCD_TOUCH_MENU_TEST

#define MENU_ITEMS	6
#define DRAWINGITEM	1
#define DEMOITEM	2
#define LCDORIITEM	3
#define RITEM		4
#define GITEM		5
#define BITEM		6

#endif /* LCD_TOUCH_MENU_TEST */




#ifdef LCD_TOUCH_BOARD_LED_TEST

#define MENU_ITEMS	2
#define LEDONITEM	1
#define LEDOFFITEM	2

#endif /* LCD_TOUCH_BOARD_LED_TEST */


uint8_t activedMenuItem;
uint8_t menuActived;





void showMenu(uint8_t selectedIndex);
void hideMenu(void);
uint8_t getTouchMenItem(uint16_t x, uint16_t y);








#endif /* _USE_HW_MENU */
#endif /* SRC_COMMON_HW_INCLUDE_MENU_H_ */
