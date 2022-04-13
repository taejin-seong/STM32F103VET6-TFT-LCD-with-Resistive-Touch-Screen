/*
 * main.c
 *
 *  Created on: Mar 14, 2021
 *      Author: sungt
 */


#include "main.h"



int main(void)
{
	hwInit();
	apInit();

#ifdef BOARD_LED_TEST
 	apBoardLedTest();
#endif /* BOARD_LED_TEST */


#ifdef LCD_DEMO_TEST
	apLcdDemoTest();
#endif /* LCD_DEMO_TEST */


#ifdef LCD_TOUCH_ROTATION_TEST
    apLcdTouchRotationTest();
#endif /* LCD_TOUCH_ROTATION_TEST */


#ifdef LCD_TOUCH_MENU_TEST
	apLcdTouchMenuTest();
#endif /* LCD_TOUCH_MENU_TEST */


#ifdef LCD_TOUCH_BOARD_LED_TEST
	apLcdTouchBoardLedTest();
#endif /* LCD_TOUCH_BOARD_LED_TEST */


	return 0;
}
