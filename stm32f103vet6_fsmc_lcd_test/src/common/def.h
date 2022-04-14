/*
 * def.h
 *
 *  Created on: Mar 14, 2021
 *      Author: sungt
 */

/* 공통으로 포함시켜야할 헤더파일을 작성합니다.*/


#ifndef SRC_COMMON_DEF_H_
#define SRC_COMMON_DEF_H_

//TODO: 공용헤더 및 모듈 채널 설정 (4)

#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdarg.h>
#include <stdlib.h>



/*                            CH NUM
 -------------------------------------------*/
#define _DEF_LED1			  0
#define _DEF_LED2			  1




/*                            PIN & PORT
 -------------------------------------------*/
/* LCD Backlight Contorl Pin & Port */
#define LCD_BL_Pin 			  GPIO_PIN_0
#define LCD_BL_GPIO_Port	  GPIOB

/* SPI2 CS(NSS) Pin & Port	*/
#define SPI2_CS_Pin 		 GPIO_PIN_12
#define SPI2_CS_GPIO_Port 	 GPIOB

/* SPI2 CS(NSS) Pin & Port	*/
#define T_PEN_Pin 			 GPIO_PIN_8
#define T_PEN_GPIO_Port 	 GPIOA
#define T_PEN_EXTI_IRQn 	 EXTI9_5_IRQn




//TODO: 테스트 함수 선택 (5)

/*
 *  @ 테스트 할 함수 범위 결정
 * - #define TEST_SELECT 주석 해제 시 menu를 사용하지 않는 테스트 함수 활성
 * - #define TEST_SELECT 주석 설정 시 menu를 사용하는 테스트 함수 활성
 *
 */
#define TEST_SELECT


#ifdef  TEST_SELECT
/* 활성화 되었다면 테스트할 함수의 주석을 해제하세요 */

#define BOARD_LED_TEST
//#define LCD_DEMO_TEST
//#define LCD_TOUCH_ROTATION_TEST

#endif /* TEST_SELECT */


#ifndef TEST_SELECT
/* 활성화 되었다면 테스트할 함수의 주석을 해제하세요 */

//#define LCD_TOUCH_MENU_TEST
//#define LCD_TOUCH_BOARD_LED_TEST

#endif /* TEST_SELECT */





#endif /* SRC_COMMON_DEF_H_ */
