/*
 * ili9341_touch.c
 *
 *  Created on: 2022. 4. 7.
 *      Author: sungt
 */

#include "xpt2046_touch.h"
#include "spi.h"
#include "ili9341_lcd.h"

#define READ_X 0xD0
#define READ_Y 0x90


uint16_t cRawX_min = XPT2046_MIN_RAW_X;
uint16_t cRawX_max = XPT2046_MAX_RAW_X;
uint16_t cRawY_min = XPT2046_MIN_RAW_Y;
uint16_t cRawY_max = XPT2046_MAX_RAW_Y;


static void XPT2046_TouchSelect()
{
    HAL_GPIO_WritePin(XPT2046_CS_GPIO_Port, XPT2046_CS_Pin, GPIO_PIN_RESET);
}

void XPT2046_TouchUnselect()
{
    HAL_GPIO_WritePin(XPT2046_CS_GPIO_Port, XPT2046_CS_Pin, GPIO_PIN_SET);
}

bool XPT2046_TouchPressed()
{
    return HAL_GPIO_ReadPin(XPT2046_IRQ_GPIO_Port, XPT2046_IRQ_Pin) == GPIO_PIN_RESET;
}

void XPT2046_Init(void)
{
	MX_SPI2_Init();
}

bool XPT2046_TouchGetCoordinates(uint16_t* x, uint16_t* y)
{

	static const uint8_t cmd_read_x[] = { READ_X };
    static const uint8_t cmd_read_y[] = { READ_Y };
    static const uint8_t zeroes_tx[] = { 0x00, 0x00 };


    XPT2046_TouchSelect();

    uint32_t avg_x = 0;
    uint32_t avg_y = 0;
    uint8_t nsamples = 0;

    for(uint8_t i = 0; i < 16; i++)
    {
        if(!XPT2046_TouchPressed())
            break;

        nsamples++;

        uint8_t y_raw[2];
        uint8_t x_raw[2];


        HAL_SPI_Transmit(&XPT2046_SPI_PORT, (uint8_t*)cmd_read_y, sizeof(cmd_read_y), HAL_MAX_DELAY);
        HAL_SPI_TransmitReceive(&XPT2046_SPI_PORT, (uint8_t*)zeroes_tx, y_raw, sizeof(y_raw), HAL_MAX_DELAY);

        HAL_SPI_Transmit(&XPT2046_SPI_PORT, (uint8_t*)cmd_read_x, sizeof(cmd_read_x), HAL_MAX_DELAY);
        HAL_SPI_TransmitReceive(&XPT2046_SPI_PORT, (uint8_t*)zeroes_tx, x_raw, sizeof(x_raw), HAL_MAX_DELAY);


        avg_x += (((uint16_t)x_raw[0]) << 8) | ((uint16_t)x_raw[1]);
        avg_y += (((uint16_t)y_raw[0]) << 8) | ((uint16_t)y_raw[1]);
    }

    XPT2046_TouchUnselect();

    if(nsamples < 16)
        return false;

    uint32_t raw_x = (avg_x / 16);
    if(raw_x < XPT2046_MIN_RAW_X) raw_x = XPT2046_MIN_RAW_X;
    if(raw_x > XPT2046_MAX_RAW_X) raw_x = XPT2046_MAX_RAW_X;

    uint32_t raw_y = (avg_y / 16);
    if(raw_y < XPT2046_MIN_RAW_Y) raw_y = XPT2046_MIN_RAW_Y;
    if(raw_y > XPT2046_MAX_RAW_Y) raw_y = XPT2046_MAX_RAW_Y;

    // Uncomment this line to calibrate touchscreen:
    //printf("raw_x = %d, raw_y = %d\r\n", (int) raw_x, (int) raw_y);

    *x = (raw_x - XPT2046_MIN_RAW_X) * XPT2046_SCALE_X / (XPT2046_MAX_RAW_X - XPT2046_MIN_RAW_X);
    *y = (raw_y - XPT2046_MIN_RAW_Y) * XPT2046_SCALE_Y / (XPT2046_MAX_RAW_Y - XPT2046_MIN_RAW_Y);

    return true;
}



bool XPT2046_TouchCalibration(void)
{
	uint16_t x0=0,y0=0,x1=0,y1=0,x2=0,y2=0,x3=0,y3=0;
	bool correct=true;
	lcdOrientationTypeDef lot = lcdGetOrientation();
	lcdSetOrientation(LCD_ORIENTATION_PORTRAIT);

	lcdFillRGB(COLOR_BLACK);
	lcdDrawRect(0, 0, 6, 6, COLOR_YELLOW);
	//lcdSetCursor(20, 100);
	while(!XPT2046_TouchPressed()) ;
	if (!XPT2046_TouchGetCoordinates(&x0, &y0))
	{
		//lcdPrintf("Calibration Error!");
		lcdSetOrientation(lot);
		return false;
	}
	//lcdPrintf("Release Pen");
	lcdFillRGB(COLOR_BLACK);
	lcdDrawRect(0, lcdGetHeight()-6, 6, 6, COLOR_YELLOW);
	while(XPT2046_TouchPressed());
	HAL_Delay(1);

	//lcdSetCursor(20, 100);
	while(!XPT2046_TouchPressed());
	if(!XPT2046_TouchGetCoordinates(&x1, &y1))
	{
		//lcdPrintf("Calibration Error!");
		lcdSetOrientation(lot);
		return false;
	}
	//lcdPrintf("Release Pen");
	lcdFillRGB(COLOR_BLACK);
	lcdDrawRect(lcdGetWidth()-6, lcdGetHeight()-6, 6, 6, COLOR_YELLOW);
	while(XPT2046_TouchPressed());
	HAL_Delay(1);


	//lcdSetCursor(20, 100);
	while(!XPT2046_TouchPressed());
	if (!XPT2046_TouchGetCoordinates(&x2, &y2))
	{
		//lcdPrintf("Calibration Error!");
		lcdSetOrientation(lot);
		return false;
	}
	//lcdPrintf("Release Pen");
	lcdFillRGB(COLOR_BLACK);
	lcdDrawRect(lcdGetWidth()-6, 0, 6, 6, COLOR_YELLOW);
	while(XPT2046_TouchPressed());
	HAL_Delay(1);

	//lcdSetCursor(20, 100);
	while(!XPT2046_TouchPressed());
	if (!XPT2046_TouchGetCoordinates(&x3, &y3))
	{
		//lcdPrintf("Calibration Error!");
		lcdSetOrientation(lot);
		return false;
	}
	//lcdPrintf("Release Pen");
	while(XPT2046_TouchPressed());

	if ( (int)(x0-x1) < -1*XTP2046_CALI_DIFF  || (int)(x0-x1) > XTP2046_CALI_DIFF) correct=false;
	if ( (int)(y1-y2) < -1*XTP2046_CALI_DIFF  || (int)(y1-y2) > XTP2046_CALI_DIFF) correct=false;
	if ( (int)(x2-x3) < -1*XTP2046_CALI_DIFF  || (int)(x2-x3) > XTP2046_CALI_DIFF) correct=false;
	if ( (int)(y0-y3) < -1*XTP2046_CALI_DIFF  || (int)(y0-y3) > XTP2046_CALI_DIFF) correct=false;

	if (correct) {
		cRawX_min = (x0+x1)/2;
		cRawX_max = (x2+x3)/2;
		cRawY_min = (y0+y3)/2;
		cRawY_max = (y1+y2)/2;
	}


	lcdFillRGB(COLOR_BLACK);
	//lcdSetCursor(20, 100);
	//lcdPrintf("Calibration OK:\r\nx_min=%04x,\r\ny_min=%04x,\r\nx_max=%04x,\r\ny_max=%04x",cRawX_min,cRawY_min,cRawX_max,cRawY_max);
	lcdSetOrientation(lot);
	return correct;
}
