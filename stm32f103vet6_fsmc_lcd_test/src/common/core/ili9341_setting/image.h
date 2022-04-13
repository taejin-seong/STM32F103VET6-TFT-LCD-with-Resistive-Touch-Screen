/*
 * image.h
 *
 *  Created on: 2022. 4. 8.
 *      Author: sungt
 */

#ifndef SRC_COMMON_CORE_ILI9341_SETTING_IMAGE_H_
#define SRC_COMMON_CORE_ILI9341_SETTING_IMAGE_H_

#ifdef _cpluscplus
extern "C"{
#endif


#include "def.h"


typedef struct _tImage
{
  uint16_t 					xSize;
  uint16_t 					ySize;
  uint16_t 					bytesPerLine;
  uint8_t					bitsPerPixel;
  const unsigned char* 		pData;
} sImage;

#define GUI_BITMAP			sImage
#define GUI_CONST_STORAGE	const

extern GUI_CONST_STORAGE GUI_BITMAP bmSTLogo;




#ifdef __cpluscplus
}
#endif

#endif /* SRC_COMMON_CORE_ILI9341_SETTING_IMAGE_H_ */
