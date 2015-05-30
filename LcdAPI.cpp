#include "LcdAPI.h"
static Lcd *lcd;
void LCD_init(void)
{
    lcd=new Lcd;
    lcd->move(100,100);
    lcd->show();
}
void Lcd_Clr_Scr(void)
{
    lcd->LcdClear();
}

void LCD_Write_Str(u8 line,u8 column,const u8 *pStr)
{
    lcd->LcdTextOut(column*6*3,line*13,pStr);
}
