/*
 * font.h
 *
 *  Created on: 2022. 4. 8.
 *      Author: sungt
 */

#ifndef SRC_COMMON_CORE_QBUFFER_H_
#define SRC_COMMON_CORE_QBUFFER_H_

#ifdef _cpluscplus
extern "C"{
#endif


#include "def.h"


#define LINE(x) ((x) * (((sFONT *)lcdGetTextFont())->Height))


typedef struct _tFont
{
  const uint8_t *table;
  uint16_t Width;
  uint16_t Height;

} sFONT;

extern sFONT Font24;
extern sFONT Font20;
extern sFONT Font16;
extern sFONT Font12;
extern sFONT Font8;







#ifdef __cpluscplus
}
#endif

#endif /* SRC_COMMON_CORE_QBUFFER_H_ */
