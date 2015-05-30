#ifndef MENU_H_80eboy
#define MENU_H_80eboy
#include "basetype.h"
#include "Key.h"
#include "LcdAPI.h"

#define KEY_Special 	255	///<这个保留用于特别事件


//菜单调试，在调试时最好定义，可以帮助发现问题；当发布时把其置为0可以加快速度
#define MENU_DEBUG 1



void Menu_Show(void);



struct PAGE
{
    const struct PAGE *pParent;
    void (*Function)(u8 key);
    const struct Item *pItem;
    const u8 ItemNum;
};
struct Item
{
    /**
    高4位作为特殊用途（bit4=1表示列表显示否则两列显示），低4位用于标记Item的序号  \n
    如果为列表模式时*pText的格式为：" xx.string",最前面保留一个空格用于个光标(>)使用，xx.为两位序号不要"."一定要有，string是要显示的文字，最多能显示6个汉字  \n
    如果是两列显示则pText，即为要显示的文本（最多2个汉字）
    */
    const u8 TypeAndIndex;
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
