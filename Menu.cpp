#include "Menu.h"

//保存选中的菜单项变量
static u8 SelItem=0;

/**
用于当前LCD列表中显示着哪几项
高4位：最大序号
低4为：最小序号
*/
static u8 ListShow=0x00;

const struct PAGE *pPage;

void SelItemOfList(u8 index);

void SetMainPage(const struct PAGE *pMainPage)
{
    pPage=pMainPage;
}
/**
获得当前选中的菜单项
@return 返回菜单序号
*/
u8 Menu_GetSelItem(void)
{
    return SelItem;
}

/**
获取当前显示列表的范围
@param pOutMin 当前显示的最小序号
@param pOutMax 当前显示的最大序号
*/
void GetShowLst(u8 *pOutMin,u8 *pOutMax)
{
    *pOutMin=ListShow&0x0f;
    *pOutMax=ListShow>>4;
}
void ShowList(u8 min,u8 max)
{
    u8 i=0,index=0;
    #if MENU_DEBUG
        if(max-min>3)
        {
            Lcd_Clr_Scr();
            LCD_Write_Str(0,0,(u8*)"err:ShowList>3");
            while (1);
        }

        if ((pPage->pItem[0].TypeAndIndex & 0x10)==0)///<如果是使用列表方式
        {

                Lcd_Clr_Scr();
                LCD_Write_Str(0,0,(u8*)"不是列表类型不能不能列出");
                while (1);
        }
    #endif

    Lcd_Clr_Scr();
    for (index=min;index<=max;index++)
    {

        LCD_Write_Str(i++,0,pPage->pItem[index].pText);
    }
    ListShow=(max<<4)|min; ///<记录当前显示的Item

}
/**
页显示

1.当这个页有项目(Item)时：显示Item并同时选中Item 0  	\n
2.没有时:会调用该Page的回调函数并传入KEY_Special 参数	\n
@param pPage 指向一个page
*/
void ShowPage( const struct PAGE *pPage)
{
    s8 i;
    ///清屏
    Lcd_Clr_Scr();

    if(pPage->pItem==0)
    {
        pPage->Function(KEY_Special);
        return; ///<如果没有Item项则不显示Item，直接返回
    }

    if (pPage->pItem[0].TypeAndIndex & 0x10)///<如果是使用列表方式
    {
        ShowList(0,3);
        SelItemOfList(0);
        pPage->Function(KEY_Special);
    }
    else
    {
        ///取出page中的Item并显示
        for (i=0;i<pPage->ItemNum;i++)
        {
            if (i<4)
            {
                LCD_Write_Str(i,1,pPage->pItem[i].pText);
            }
            else
            {
                LCD_Write_Str(i-4,5,pPage->pItem[i].pText);
            }

        }
        SelPageItem(0);///<选中Item 0
        pPage->Function(KEY_Special);
    }

};

/**
显示父页(ParentPage)
*/
void ShowParentPage(void)
{
    pPage=pPage->pParent;
    ShowPage(pPage);
}

/**
显示项目(Item)下对应的页(Page)
*/
void ShowItemPage(void)
{
    //如果该项下没有页，这警告或返回
    if (pPage->pItem[Menu_GetSelItem()].pChildrenPage ==0)
    {
        #if MENU_DEBUG
            Lcd_Clr_Scr();
            LCD_Write_Str(0,0,(u8*)"Item Not Set,Stop MCU");
            while (1);
        #else
            return;
        #endif
    }
    pPage=pPage->pItem[Menu_GetSelItem()].pChildrenPage; //获得菜单项(Item)对应的page

    ShowPage(pPage);
}

/**
选择page中的Item项
@param ItemIndex page中Item的索引号 0~7
*/
void SelPageItem(u8 ItemIndex)
{
    ///检查是否有错误调用
#if MENU_DEBUG

    if (ItemIndex>=8)
    {
        LCD_Write_Str(0,0,(u8*)"设置菜单项溢出");
        return;
    }
#endif

///清除上次选中的
   if (SelItem<4)
   {
        LCD_Write_Str(SelItem,0,(u8*)" ");
        //LCD_Write_Str(SelItem,3,(u8*)"  ");

   }
   else
   {
        LCD_Write_Str(SelItem-4,4,(u8*)" ");
        //LCD_Write_Str(SelItem-4,7,(u8*)"  ");
   }
///选中这次要选中的
   if (ItemIndex<4)
   {
        LCD_Write_Str(ItemIndex,0,(u8*)">");
        //LCD_Write_Str(ItemIndex,3,(u8*)"]");
        SelItem=ItemIndex;
   }
   else
   {
        LCD_Write_Str(ItemIndex-4,4,(u8*)">");
       // LCD_Write_Str(ItemIndex-4,7,(u8*)"]");
        SelItem=ItemIndex;
   }
}
void SelItemOfList(u8 index)
{
    u8 max;
    u8 min;

    max=ListShow>>4;
    min=ListShow&0x0f;

    if (index>max) ///<超出最大当前显示的序号
    {

        LCD_Write_Str(Menu_GetSelItem()-min,0,(u8*)" ");

        min+=1;
        max+=1;
        ShowList(min,max);
        ListShow=(max<<4)|min;

        LCD_Write_Str(index-min,0,(u8*)">");

    }
    else if(index>=min)///<在最小和最大序号之间
    {
        LCD_Write_Str(Menu_GetSelItem()-min,0,(u8*)" ");
        LCD_Write_Str(index-min,0,(u8*)">");
    }
    else					///<低于最小当前显示最小序号
    {
        LCD_Write_Str(Menu_GetSelItem()-min,0,(u8*)" ");

        min-=1;
        max-=1;
        ShowList(min,max);
        ListShow=(max<<4)|min;

        LCD_Write_Str(index-min,0,(u8*)">");
    }
    SelItem=index;
}
void KeySelItem(u8 key)
{
    s8 index;
    if (pPage->pItem[0].TypeAndIndex & 0x10)///<如果是使用列表方式
    {
        switch(key)
        {
            case KEY_UP:
                index=Menu_GetSelItem()-1;
                if(index<0) break;

                SelItemOfList(index);
                break;
            case KEY_Down:
                index=Menu_GetSelItem()+1;
                if(index>(pPage->ItemNum-1)) break;;
                SelItemOfList(index);
                break;
        }
        return;
    }
    switch(key)
    {
        case KEY_UP:
            index=Menu_GetSelItem()-1;
            if(index<0) index=pPage->ItemNum-1;
            SelPageItem(index);
            break;
        case KEY_Down:
            index=Menu_GetSelItem()+1;
            if(index>(pPage->ItemNum-1)) index=0;
            SelPageItem(index);
            break;
        case KEY_Left:
        case KEY_Right:
            index=Menu_GetSelItem();
            if (index<4)
            {
                if((index+4)>(pPage->ItemNum-1)) return; //右没有Item项，无法选中右边项；所以返回
                index+=4;								//右边有Item时把index定位到右边的Item
            }
            else	    index-=4;						//因为右边有Item项时，左边一定有Item项；因为是按顺序安排的
            SelPageItem(index);
            break;
    }
}

