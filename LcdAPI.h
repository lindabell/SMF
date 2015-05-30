#ifndef _LCDAPI_H_80eboy
#define _LCDAPI_H_80eboy
#include "basetype.h"
#include "lcd.h"

void LCD_init(void);
void Lcd_Clr_Scr(void);
void LCD_Write_Str(u8 line,u8 column,const u8 *pStr);
#endif
