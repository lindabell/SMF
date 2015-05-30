#include "MenuAPP.h"


void mainPageCallBack(u8 key);
void mainPage_Item1_CallBack(u8 key);

extern const struct PAGE Version_Page;
void Version_CallBack(u8 key);

extern const struct PAGE Setting_Page;
void Setting_CallBack(u8 key);

extern const struct PAGE Time_Page;
void Time_CallBack(u8 key);



/******************************************************************************************************/
//主菜单
//定义Item项             //显示方式&序号  项目的名字    项目指向的页(Page)
const struct Item main_item[]={	0x00,	(u8*)"memu0",			0,
                                0x01,	(u8*)"Set",			&Setting_Page,
                                0x02,	(u8*)"Version",			&Version_Page,
                                0x03,	(u8*)"Time",			&Time_Page,
                                0x04,	(u8*)"memu4",			0,
                                0x05,	(u8*)"memu5",			0,
                                0x06,	(u8*)"memu6",			0,
                                0x07,	(u8*)"memu7",			0
};
//定义一个Page		      父页 该页的回调函数	该页的项          项的个数
const struct PAGE mainPage={0,mainPageCallBack,main_item,sizeof(main_item)/sizeof(struct Item)};
/*********************************************************************************************************/


const struct PAGE Version_Page={&mainPage,Version_CallBack,0,0};
/***************************************************************************************************************/

//定义Item项              //显示方式&序号    项目的名字      项目指向的页(Page)
const struct Item Setting_item[]={	0x10,	(u8*)" 00.set0",			0,
                                    0x11,	(u8*)" 01.set1",			0,
                                    0x12,	(u8*)" 02.set2",			0,
                                    0x13,	(u8*)" 03.set3",			0,
                                    0x14,	(u8*)" 04.set4",			0,
                                    0x15,	(u8*)" 05.set5",			0,
                                    0x16,	(u8*)" 06.set6 hell world",		0,
                                    0x17,	(u8*)" 07.set7",			0,
                                    0x18,	(u8*)" 08.set8",			0,
                                    0x19,	(u8*)" 09.set9",			0,
                                    0x1A,	(u8*)" 10.set10",			0
                                    };
const struct PAGE Setting_Page={&mainPage,Setting_CallBack,Setting_item,sizeof(Setting_item)/sizeof(struct Item)};
/***************************************************************************************************************/

const struct PAGE Time_Page={&mainPage,Time_CallBack,0,0};





/**
主菜单回调函数，对这个页得处理全部放在回调函数里
@param key 按键代码
*/
void mainPageCallBack(u8 key)
{
    switch (key)
    {
        case KEY_UP:
        case KEY_Down:
        case KEY_Left:
        case KEY_Right:
            KeySelItem(key);
            break;

        case KEY_Return:///<主菜单 对返回按键没有处理
            ShowPage(&mainPage);
            break;
        case KEY_Ok:
            ShowItemPage();
            break;
    }
}


void Version_CallBack(u8 key)
{
    LCD_Write_Str(0,0,(u8*)"      Info     ");
    LCD_Write_Str(1,0,(u8*)"Co:80eboy");
    LCD_Write_Str(2,0,(u8*)"Addr:ShenZhen");
    LCD_Write_Str(3,0,(u8*)"Version:V0.4");
    if (key==KEY_Return)
    {
        ShowParentPage();
    }
}


void Setting_CallBack(u8 key)
{
    switch (key)
    {
        case KEY_UP:
        case KEY_Down:
        case KEY_Left:
        case KEY_Right:
            KeySelItem(key);
            break;

        case KEY_Return:///<主菜单 对返回按键没有处理
            ShowParentPage();
            break;
        case KEY_Ok:
            ShowItemPage();
            break;
    }
}


void Time_CallBack(u8 key)
{
    LCD_Write_Str(0,0,(u8*)"Date:2012-7-5");
    LCD_Write_Str(1,0,(u8*)"Time:16:59");
    if (key==KEY_Return)
    {
        ShowParentPage();
    }
}




