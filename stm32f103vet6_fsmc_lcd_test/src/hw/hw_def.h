/*
 * hw_def.h
 *
 *  Created on: Mar 14, 2021
 *      Author: sungt
 */

/*hw 폴더 밑에 만들어지는 모듈들이 공통으로 쓰는 하드웨어 관련 정의를 선언합니다.*/

#ifndef SRC_HW_HW_DEF_H_
#define SRC_HW_HW_DEF_H_


#include "def.h"
#include "bsp.h"

//TODO: 컴파일 허용 설정 (2)

#define   _USE_HW_LED
#define        HW_LED_MAX_CH						2

#define   _USE_HW_FSMC

#define   _USE_HW_ILI9341_LCD

#define   _USE_HW_XPT2046_TOUCH

#define   _USE_HW_SPI

#define   _USE_HW_SHOWMESSAGE

#define   _USE_HW_MENU


#endif /* SRC_HW_HW_DEF_H_ */
