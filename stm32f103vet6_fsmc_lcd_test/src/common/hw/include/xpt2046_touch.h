/*
 * ili9341_touch.h
 *
 *  Created on: 2022. 4. 7.
 *      Author: sungt
 */

#include "hw_def.h"



#ifdef _USE_HW_XPT2046_TOUCH

/*** Redefine if necessary ***/

// Warning! Use SPI bus with < 2.5 Mbit speed, better ~650 Kbit to be save.
#define XPT2046_SPI_PORT hspi2
SPI_HandleTypeDef XPT2046_SPI_PORT;

#define XPT2046_IRQ_Pin       T_PEN_Pin
#define XPT2046_IRQ_GPIO_Port T_PEN_GPIO_Port
#define XPT2046_CS_Pin        SPI2_CS_Pin
#define XPT2046_CS_GPIO_Port  SPI2_CS_GPIO_Port


// change depending on screen orientation
#define XPT2046_SCALE_X 240
#define XPT2046_SCALE_Y 320


// to calibrate uncomment line in ili9341_touch.c
#define XPT2046_MIN_RAW_X 2000
#define XPT2046_MAX_RAW_X 30000
#define XPT2046_MIN_RAW_Y 1500
#define XPT2046_MAX_RAW_Y 29000


#define XTP2046_CALI_DIFF	600

// Initializing SPI
void XPT2046_Init(void);

// call before initializing any SPI devices
void XPT2046_TouchUnselect(void);
bool XPT2046_TouchPressed(void);

bool XPT2046_TouchGetCoordinates(uint16_t* x, uint16_t* y);
bool XPT2046_TouchCalibration(void);

#endif /* _USE_HW_XPT2046_TOUCH */
