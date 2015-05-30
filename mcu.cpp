//模拟MCU把Qt相关代码隔离掉，具有较好的移植性
#include "mcu.h"
#include "menu.h"
#include "LcdAPI.h"
#include "MenuAPP.h"
#include "key.h"
/*
 * 相当于main到while(1)之间
 */
void MCU_Init(void)
{
    LCD_init();
    KeyInit();
    SetMainPage(&mainPage);
    ShowPage(pPage);
}

u8 tempKey;
/*
 * 相当于while(1){}
 */
void MCU_While(void)
{
    tempKey=GetKey();
    if(tempKey!=KEY_NONE)
    {
        pPage->Function(tempKey);
    }

}
