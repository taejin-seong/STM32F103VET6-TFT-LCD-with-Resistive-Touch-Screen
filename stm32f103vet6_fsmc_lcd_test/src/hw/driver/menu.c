/*
 * menu.c
 *
 *  Created on: 2022. 4. 8.
 *      Author: sungt
 */

#include "menu.h"
#include "ili9341_lcd.h"



#ifdef  TEST_SELECT

/* NOT USE MENU */

#define MENU_ITEMS 0

uint16_t menuColordinate[][4]= { };

char *menuText[]={};
uint16_t menuBGColor[]={};
uint16_t selmenuBGColor = 0;

#endif /* TEST_SELECT */



/*
 * @ apLcdTouchMenuTest Parameter
 * @ Please See ap.c
 *
 */
#ifdef LCD_TOUCH_MENU_TEST
//                                x     y    w   h
uint16_t menuColordinate[][4]= { {0,    5,   40,  20},  //1st menu box size
								 {45,   5,   40,  20},  //2nd menu box size
								 {90,   5,   30,  20},  //3rd menu box size
								 {125,  5,   20,  20},  //4th menu box size
								 {150,  5,   20,  20},  //5th menu box size
								 {175,  5,   20,  20},  //6th menu box size
							   };

char *menuText[]={"DRAW", "DEMO", "RO","R", "G", "B"}; 			   //1st ~ 3th menu box name
uint16_t menuBGColor[]={COLOR_BLUE,COLOR_BLUE,COLOR_BLUE,COLOR_BLUE,COLOR_BLUE,COLOR_BLUE}; //1st ~ 3th menu box color
uint16_t selmenuBGColor=COLOR_GREEN; 					   //color when menu box is pressed

#endif /* LCD_TOUCH_MENU_TEST */



/*
 *
 * @ apLcdTouchBoardLedTest Parameter
 * @ Please See ap.c
 *
 */
#ifdef LCD_TOUCH_BOARD_LED_TEST
//                                x     y    w     h
uint16_t menuColordinate[][4]= { {30,   10,  120,  100},  //1st menu box size
								 {30,   120,  120,  100},  //2nd menu box size
							   };

char *menuText[]={"LED ON", "LED OFF"}; 			   //1st ~ 3th menu box name
uint16_t menuBGColor[]={COLOR_GREEN,COLOR_RED}; 	   //1st ~ 3th menu box color
uint16_t selmenuBGColor=COLOR_GRAY_200; 			   //color when menu box is pressed

#endif /* LCD_TOUCH_BOARD_LED_TEST */




void hideMenu()
{
#ifdef LCD_TOUCH_MENU_TEST
//	            x  y      w         h     color
	lcdFillRect(0, 0,lcdGetWidth(), 25, COLOR_BLACK);
#endif /* LCD_TOUCH_MENU_TEST */

#ifdef LCD_TOUCH_BOARD_LED_TEST
	;
#endif /* LCD_TOUCH_BOARD_LED_TEST */
}


void showMenu(uint8_t selectedIndex)
{
#ifdef LCD_TOUCH_MENU_TEST
	lcdSetTextFont(&Font12);
#endif /* LCD_TOUCH_MENU_TEST */


#ifdef LCD_TOUCH_BOARD_LED_TEST
	lcdSetTextFont(&Font20);
#endif /* LCD_TOUCH_BOARD_LED_TEST */


	if (selectedIndex > 0 && selectedIndex <= MENU_ITEMS)
	{
		if (activedMenuItem > 0 && activedMenuItem <= MENU_ITEMS)
		{
			int ti=activedMenuItem-1;
			lcdSetTextColor(COLOR_WHITE, menuBGColor[ti]);
			lcdFillRect(menuColordinate[ti][0], menuColordinate[ti][1], menuColordinate[ti][2], menuColordinate[ti][3], menuBGColor[ti]);

#ifdef LCD_TOUCH_MENU_TEST
			lcdSetCursor(menuColordinate[ti][0]+6, menuColordinate[ti][1]+4); //텍스트 위치 커서 조정
#endif /* LCD_TOUCH_MENU_TEST */

#ifdef LCD_TOUCH_BOARD_LED_TEST
			lcdSetCursor(menuColordinate[ti][0]+13, menuColordinate[ti][1]+40); //텍스트 위치 커서 조정
#endif /* LCD_TOUCH_BOARD_LED_TEST */

			lcdPrintf(menuText[ti]);
		}

		activedMenuItem=selectedIndex;
		selectedIndex--;
		lcdSetTextColor(COLOR_WHITE, selmenuBGColor);
		lcdFillRect(menuColordinate[selectedIndex][0], menuColordinate[selectedIndex][1], menuColordinate[selectedIndex][2], menuColordinate[selectedIndex][3], selmenuBGColor);

#ifdef LCD_TOUCH_MENU_TEST
		lcdSetCursor(menuColordinate[selectedIndex][0]+6, menuColordinate[selectedIndex][1]+4); //텍스트 위치 커서 조정
#endif /* LCD_TOUCH_MENU_TEST */

#ifdef LCD_TOUCH_BOARD_LED_TEST
		lcdSetCursor(menuColordinate[selectedIndex][0]+13, menuColordinate[selectedIndex][1]+40); //텍스트 위치 커서 조정
#endif /* LCD_TOUCH_BOARD_LED_TEST */

		lcdPrintf(menuText[selectedIndex]);
	}
	else
	{
#ifdef LCD_TOUCH_MENU_TEST
		hideMenu();
#endif /* LCD_TOUCH_MENU_TEST */

		activedMenuItem=0;
		for (int i=0;i<MENU_ITEMS;i++)
		{
			lcdSetTextColor(COLOR_WHITE, menuBGColor[i]);
			lcdFillRect(menuColordinate[i][0], menuColordinate[i][1], menuColordinate[i][2], menuColordinate[i][3], menuBGColor[i]);

#ifdef LCD_TOUCH_MENU_TEST
			lcdSetCursor(menuColordinate[i][0]+6, menuColordinate[i][1]+4); //텍스트 위치 커서 조정
#endif /* LCD_TOUCH_MENU_TEST */

#ifdef LCD_TOUCH_BOARD_LED_TEST
			lcdSetCursor(menuColordinate[i][0]+13, menuColordinate[i][1]+40); //텍스트 위치 커서 조정
#endif /* LCD_TOUCH_BOARD_LED_TEST */

			lcdPrintf(menuText[i]);
		}
	}
}


uint8_t getTouchMenItem(uint16_t x, uint16_t y)
{
	uint8_t ret = 0;
	for (int i=0;i<MENU_ITEMS;i++)
	{     //                       x                            x                     w
		if (x > menuColordinate[i][0] && x < menuColordinate[i][0] + menuColordinate[i][2] &&
				y > menuColordinate[i][1] && y < menuColordinate[i][1] + menuColordinate[i][3])
		 //                            y                            y                     h
		{
			ret = i+1;
			break;
		}
	}
	return ret;
}
