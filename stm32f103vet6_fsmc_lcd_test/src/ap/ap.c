/*
 * ap.c
 *
 *  Created on: Mar 14, 2021
 *      Author: sungt
 *
 *
 * based:
 * https://rfwumcu.blogspot.com/2021/02/interface-tft-display-with-stm32-in-16.html
 *
 *
 */

#ifndef SRC_AP_AP_C_
#define SRC_AP_AP_C_


#include "ap.h"
#include "lcd_demo.h"






 void apInit(void)
{
	 ;
}



#ifdef BOARD_LED_TEST
void apBoardLedTest(void)
{

  while(1)
  {

    ledToggle(_DEF_LED1);
    ledToggle(_DEF_LED2);
    delay_ms(100);
  }

}
#endif /* BOARD_LED_TEST */







uint8_t penWidth		=1;
uint8_t tempIgnoralEXTI	=0;
uint16_t cx 			=0;
uint16_t cy 			=0;
bool isCalbriating;




void HAL_GPIO_EXTI_Callback (uint16_t GPIO_Pin)
{
 if (GPIO_Pin == T_PEN_Pin)
 {
	 if (tempIgnoralEXTI || isCalbriating) return;

	  if(XPT2046_TouchPressed())
	  {
		  tempIgnoralEXTI=1;
		  XPT2046_TouchGetCoordinates(&cx, &cy);

		  if (menuActived)
		  {
			  uint8_t i=getTouchMenItem(cx, cy);
			  if (i > 0)
			  {
				 showMenu(i);

#ifdef  LCD_TOUCH_MENU_TEST
				  switch (i)
				  {
					case DRAWINGITEM:
						lcdFillRect(1, 26, lcdGetWidth()-2, lcdGetHeight()-2, COLOR_BLACK);
						lcdDrawRect(1, 26, lcdGetWidth()-2, lcdGetHeight()-2, COLOR_WHITE);
					    break;

					case DEMOITEM:
						  menuActived=0;
						  break;

					case LCDORIITEM:
						  menuActived=0;
						  break;

					case RITEM:
						  menuActived=0;
						  break;

				    case GITEM:
				    	  menuActived=0;
						  break;

				    case BITEM:
						 menuActived=0;
					     break;
				  }
#endif /* LCD_TOUCH_MENU_TEST */


#ifdef  LCD_TOUCH_BOARD_LED_TEST
				  switch (i)
				  {
					case LEDONITEM:
						  menuActived=0;
						  break;

					case LEDOFFITEM:
						  menuActived=0;
						  break;
				  }
#endif /* LCD_TOUCH_BOARD_LED_TEST */

			  }
		  }

#ifdef  LCD_TOUCH_MENU_TEST
		  if (activedMenuItem == DRAWINGITEM)
		  {
			  if (cx > 1 && cx < lcdGetWidth()-1 && cy > 26 && cy < lcdGetHeight()-1 )
								  lcdFillCircle(cx, cy, penWidth, COLOR_GREENYELLOW);
		  }
		  tempIgnoralEXTI=0;
#endif /* LCD_TOUCH_MENU_TEST */

	  }
   }
}







#ifdef LCD_DEMO_TEST
void apLcdDemoTest(void)
{
	/*
	 * 22 / 04 / 11
	 * LCD Demo TEST
	 ***********************************/
	 int i = 0;

	  while (1)
	  {
	       demoLCD(i);
		   i++;
	  }
}
#endif /* LCD_DEMO_TEST */




#ifdef LCD_TOUCH_ROTATION_TEST
void apLcdTouchRotationTest(void)
{
	/*
	 * 22 / 04 /11
	 * LCD Rotation TEST
	 * *********************************/

	 lcdFillRGB(COLOR_BLACK);

	 while (1)
	 {
		if(XPT2046_TouchPressed())
		{
			lcdFillRGB(COLOR_BLACK);
			lcdSetOrientation((lcdGetOrientation()+1)%4);
			testDrawImage();

		}
	}
}
#endif /* LCD_TOUCH_ROTATION_TEST */




#ifdef LCD_TOUCH_MENU_TEST
void apLcdTouchMenuTest(void)
{
	/*
	 * 22 / 04 / 11
	 * LCD Touch Menu Test
	 * *********************************/

	 activedMenuItem=0;
	 menuActived=0;

	 lcdFillRGB(COLOR_BLACK);
//   lcdSetOrientation(LCD_ORIENTATION_LANDSCAPE);
     lcdSetOrientation(LCD_ORIENTATION_PORTRAIT_MIRROR);


	/************** Start Calibrating **************/

	 isCalbriating = true;

	 showMessage("Start Calibration",2);

	 while(!XPT2046_TouchCalibration())
	 {
		showMessage("Calibration Error!!!\n Try again", 2);
	 }

	 isCalbriating = false;

	 showMessage("Calibrate\n successfully",2);

	 menuActived = 1;

	/************** End Calibrating **************/


	showMenu(0);

	while (1)
	{
		switch(activedMenuItem)
		{
			case DRAWINGITEM:
				break;

			case DEMOITEM:
				tempIgnoralEXTI=1;

				demoLCD(6); // -> (6) % 4 = 2 : LCD_ORIENTATION_PORTRAIT_MIRROR mode setting
				showMenu(0);

				tempIgnoralEXTI=0;
				menuActived=1;
				break;

			case LCDORIITEM:
				tempIgnoralEXTI=1;

				lcdFillRGB(COLOR_BLACK);
				lcdSetOrientation((lcdGetOrientation()+1)%4);
			    showMenu(0);

			    tempIgnoralEXTI=0;
				menuActived=1;
				break;

			case RITEM:
				tempIgnoralEXTI=1;

				lcdFillRGB(COLOR_RED);
				showMenu(0);

				tempIgnoralEXTI=0;
				menuActived=1;
				break;

			case GITEM:
				tempIgnoralEXTI=1;

				lcdFillRGB(COLOR_GREEN);
				showMenu(0);

				tempIgnoralEXTI=0;
				menuActived=1;
				break;

			case BITEM:
				tempIgnoralEXTI=1;

				lcdFillRGB(COLOR_BLUE);
				showMenu(0);

				tempIgnoralEXTI=0;
				menuActived=1;
				break;
		}
	 }
}
#endif /* LCD_TOUCH_MENU_TEST */





#ifdef LCD_TOUCH_BOARD_LED_TEST
void apLcdTouchBoardLedTest(void)
{
	/*
	 * 22 / 04 / 12
	 * LCD Touch Board Led Test
	 * *********************************/


	 activedMenuItem=0;
	 menuActived=0;

	 lcdFillRGB(COLOR_BLACK);
     lcdSetOrientation(LCD_ORIENTATION_PORTRAIT_MIRROR);

	/************** Start Calibrating **************/

	 isCalbriating = true;

//	 showMessage("Start Calibration",2);
/*
	 while(!XPT2046_TouchCalibration())
	 {
		showMessage("Calibration Error!!!\n Try again", 2);
	 }
*/
	 isCalbriating = false;

//	 showMessage("Calibrate\n successfully",2);

	 menuActived = 1;

	/************** End Calibrating **************/

	 showMenu(0);

	 while (1)
	 {

		 switch(activedMenuItem)
		{
			case LEDONITEM:
				tempIgnoralEXTI=1;

				ledOn(_DEF_LED1);
				ledOn(_DEF_LED2);

				showMenu(0);

				tempIgnoralEXTI=0;
				menuActived=1;
				break;


			case LEDOFFITEM:
				tempIgnoralEXTI=1;

				ledOff(_DEF_LED1);
				ledOff(_DEF_LED2);

				showMenu(0);

				tempIgnoralEXTI=0;
				menuActived=1;
				break;
		}


	}
}
#endif /* LCD_TOUCH_BOARD_LED_TEST */





#endif /* SRC_AP_AP_C_ */
