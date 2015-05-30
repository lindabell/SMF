#ifndef MENU_H_80eboy
#define MENU_H_80eboy
#include "basetype.h"
#include "Key.h"
#include "LcdAPI.h"

#define KEY_Special 	255	///<这个保留用于特别事件


//菜单调试，在调试时最好定义，可以帮助发现问题；当发布时把其置为0可以加快速度
#define MENU_DEBUG 1



void Menu_Show(void);

#define DISPLAY_MODE_0_COLUMN   (0) //全屏显示
#define DISPLAY_MODE_1_COLUMN   (1) //1列显示
#define DISPLAY_MODE_2_COLUMN   (2) //2列显示

struct PAGE
{
    const struct PAGE *pParent;
    void (*Function)(u8 key);
    const struct Item *pItem;
    const u8 ItemNum;
    const u8 DisplayMode;
};
struct Item
{
    const u8 *pText;
    const struct PAGE *pChildrenPage;
};


extern const struct PAGE *pPage;

void SetMainPage(const struct PAGE *pMainPage);
void ShowMenu(const struct PAGE *pPage);
void ShowPage(const struct PAGE *pPage);
void ShowParentPage(void);
void ShowItemPage(void);
void SelPageItem(u8 ItemIndex);
u8 Menu_GetSelItem(void);

void GetShowLst(u8 *pOutMin,u8 *pOutMax);

void KeySelItem(u8 key);

#endif // MENU_H_80eboy
