/*
 * showmessage.c
 *
 *  Created on: 2022. 4. 8.
 *      Author: sungt
 */

#include "showmessage.h"
#include "ili9341_lcd.h"


void showMessage(char* msg, uint8_t sec)
{
	unsigned int px,py;
	unsigned int x,y;
	uint8_t fw,fh;
	uint16_t *msgBuff;

	px = (lcdGetWidth()-210)/2;
	py = (lcdGetHeight()-110)/2;
	msgBuff = malloc(sizeof(uint16_t)*(210*110));
	lcdSetWindow(0, 0, lcdGetWidth(), lcdGetHeight());
	for (x=px; x < 210+px; x++)
	{
		for (y=py; y < 110+py;y++)
		{
		 msgBuff[(x-px)*110+y-py] = lcdReadPixel(x, y);
		}
	}
	lcdFillRect(px, py, 209, 109, COLOR_BLUE);
	lcdFillRect(px+5, py+5, 199, 99, COLOR_WHITE);
	lcdSetTextColor(COLOR_BLUE, COLOR_WHITE);
	lcdSetTextFont(&Font16);
	fw=Font16.Width;
	fh = Font16.Height;
	for (int posx=0, posy=0, i=0; i < strlen(msg);i++,posx++)
	{
		if (msg[i] == '\n' || (posx+1)*(fw) > 200-fw)
		{
			posy++;
			posx=0;
		}
		if (msg[i] == '\n') i++;
		lcdDrawChar(px+12+posx*fw, py+12+posy*(fh+2), msg[i], COLOR_BLUE, COLOR_WHITE);
	}

	HAL_Delay(sec*1000);

	lcdSetWindow(0, 0, lcdGetWidth(), lcdGetHeight());
	for (x=px; x < 210+px; x++)
	{
		for (y=py; y < 110+py; y++)
		{
		 lcdDrawPixel(x, y, msgBuff[(x-px)*110+y-py]);
		}
	}
	free(msgBuff);
	HAL_Delay(10);
}
