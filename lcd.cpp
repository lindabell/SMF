#include "lcd.h"
#include "ui_lcd.h"
#include <QPainter>

#define AsciiCodeWidth	6
#define AsciiCodeHigh	12

#define ChineseCodeWidth	12
#define ChineseCodeHigh		12

unsigned char lcdram[lcd_y / 8][lcd_x] = {0};

Lcd::Lcd (QWidget *parent) :
    QWidget (parent),
    ui (new Ui::Lcd)
{
    ui->setupUi (this);

    const unsigned int addx = 0;
    const unsigned int addy = 0;

    unsigned int width = lcd_x * lcd_Xenlarge;
    unsigned int height = lcd_y * lcd_Yenlarge;

    this->setGeometry (start_x, start_y, start_x + width + addx, start_y + height + addy);
    this->setMinimumSize (start_x + width + addx, start_y + height + addy);
    this->setMaximumSize (start_x + width + addx, start_y + height + addy);

    //set to no border
    //setWindowFlags (Qt::FramelessWindowHint);

    LcdClear();

    char title[128] = {0};
    sprintf(title, "lcd %dx%d simulator, one point is %dx%d pixel", lcd_x, lcd_y, lcd_Xenlarge, lcd_Yenlarge);
    this->setWindowTitle(title);
}

Lcd::~Lcd()
{
    delete ui;
}

void Lcd::paintEvent (QPaintEvent *)
{
    QPainter painter (this);

    painter.fillRect (QRect (start_x, start_y, lcd_x * lcd_Xenlarge, lcd_y * lcd_Yenlarge), QBrush (QColor(153,204,0,255), Qt::SolidPattern) );

    int x = 0, y = 0, yv = 0;

    for (y = 0; y < lcd_y / 8; y++)
    {
        for (x = 0; x < lcd_x; x++)
        {
            yv = 0;

            //printf("x=%d, y=%d\r\n", x, y);

            if ( (lcdram[y][x] & (0x01) ) == (0x01) ) drawPointByEnlarge (&painter, x, y * 8 + yv, lcd_Xenlarge, lcd_Yenlarge);

            yv++;

            if ( (lcdram[y][x] & (0x02) ) == (0x02) ) drawPointByEnlarge (&painter, x, y * 8 + yv, lcd_Xenlarge, lcd_Yenlarge);

            yv++;

            if ( (lcdram[y][x] & (0x04) ) == (0x04) ) drawPointByEnlarge (&painter, x, y * 8 + yv, lcd_Xenlarge, lcd_Yenlarge);

            yv++;

            if ( (lcdram[y][x] & (0x08) ) == (0x08) ) drawPointByEnlarge (&painter, x, y * 8 + yv, lcd_Xenlarge, lcd_Yenlarge);

            yv++;

            if ( (lcdram[y][x] & (0x10) ) == (0x10) ) drawPointByEnlarge (&painter, x, y * 8 + yv, lcd_Xenlarge, lcd_Yenlarge);

            yv++;

            if ( (lcdram[y][x] & (0x20) ) == (0x20) ) drawPointByEnlarge (&painter, x, y * 8 + yv, lcd_Xenlarge, lcd_Yenlarge);

            yv++;

            if ( (lcdram[y][x] & (0x40) ) == (0x40) ) drawPointByEnlarge (&painter, x, y * 8 + yv, lcd_Xenlarge, lcd_Yenlarge);

            yv++;

            if ( (lcdram[y][x] & (0x80) ) == (0x80) ) drawPointByEnlarge (&painter, x, y * 8 + yv, lcd_Xenlarge, lcd_Yenlarge);

            yv++;

        }

    }
}

void Lcd::drawPointByEnlarge (QPainter *painter, int x, int y, int xenlarge, int yenlarge)
{
    int i = 0, j = 0;


    x *= xenlarge;
    y *= yenlarge;


    painter->setPen (Qt::black);

    for (i = y; i < y + yenlarge; i++)
    {
        for (j = x; j < x + xenlarge; j++)
        {
            painter->drawPoint (j + start_x, i + start_y);
        }
    }
}

void Lcd::AccordingLcdRamDisplay (int start_xpos, int end_xpos, int displayline)
{
    start_xpos = start_xpos;
    end_xpos = end_xpos;
    displayline = displayline;

    this->update();//RAM -> UI
}

void Lcd::LcdClear (void)
{
    int x = 0, y = 0;

    for (y = 0; y < lcd_y / 8; y++)
    {
        for (x = 0; x < lcd_x; x++)
        {
            lcdram[y][x] = 0x00;
        }

        AccordingLcdRamDisplay (0, lcd_x, y);
    }
}

void Lcd::byteCombine (unsigned char *des, const unsigned char *src1, unsigned char RSbits, const unsigned char *src2, unsigned char LSbits, int len)
{
    const unsigned char comb[9] = {0x00, 0x01, 0x03, 0x07, 0x0f, 0x1f, 0x3f, 0x7f, 0xff};
    unsigned char R, L;

    R = comb[8 - RSbits];
    L = ~comb[LSbits];

    for (; len != 0; len--)
    {
        *des = (*src1 >> RSbits & R) | (*src2 << LSbits & L);
        des++;
        src1++;
        src2++;
    }
}

void Lcd::ClearBuffAnyByte_bits (unsigned char *p, unsigned char comb, int len)
{
    for (; len != 0; len--)
    {
        *p &= comb;
        p++;
    }
}

void Lcd::LcdDrawBitMap (const unsigned char *Bitmap, int xpos, int ypos, int BmWidth, int BmHigh)
{
    const unsigned char comb[9] = {0x00, 0x01, 0x03, 0x07, 0x0f, 0x1f, 0x3f, 0x7f, 0xff};
    int i;
    int displayline;
    int totalline;
    int startdotline = 0;
    int totalbyte;
    unsigned char *p;
    int clearbits;
    int filldot;
    int temp;
    int fillWidth;

    displayline = ypos / 8;

    if (displayline >= (lcd_y/8)) return;
    if (xpos > lcd_x) return;

    if (BmWidth <= lcd_x - xpos) fillWidth = BmWidth;
    else fillWidth = lcd_x - xpos;

    startdotline = ypos % 8;

    if (BmHigh < 8 - startdotline) totalline = 1;
    else
    {
        if (startdotline == 0)
        {
            totalline = BmHigh / 8;

            if (BmHigh % 8 != 0) totalline++;
        }
        else
        {
            totalline = (BmHigh - (8 - startdotline) ) / 8 + 1;

            if ( (BmHigh - (8 - startdotline) ) % 8 != 0) totalline++;
        }
    }

    totalbyte = BmHigh / 8;

    if (BmHigh % 8 != 0) totalbyte++;

    for (i = 0; i < totalline; i++)
    {
        if (i == 0)
        {
            p = &lcdram[displayline][xpos];
            clearbits = comb[startdotline];

            if ( (BmHigh + startdotline) < 8) clearbits |= ~comb[BmHigh + startdotline];

            ClearBuffAnyByte_bits (p, clearbits, fillWidth);

            byteCombine (p, p, 0, Bitmap, startdotline, fillWidth);
            filldot = 8 - startdotline;

            if (filldot >= 8)
            {
                Bitmap += BmWidth;
                filldot = 0;
            }
        }
        else if (i == totalline - 1)
        {
            p = &lcdram[displayline][xpos];

            temp = (BmHigh - (8 - startdotline) ) % 8;

            if (temp == 0) temp = 8;

            clearbits = ~comb[temp];

            ClearBuffAnyByte_bits (p, clearbits, fillWidth);

            if (temp <= BmHigh % 8)
            {
                byteCombine (p, Bitmap, BmHigh % 8 - temp, p, 0, fillWidth);
            }
            else
            {
                byteCombine (p, Bitmap, filldot, p, 0, BmWidth);
                byteCombine (p, p, 0, Bitmap + BmWidth, 8 - filldot, fillWidth);
            }
        }
        else
        {
            p = &lcdram[displayline][xpos];

            byteCombine (p, Bitmap, filldot, Bitmap + BmWidth, 8 - filldot, fillWidth);
            Bitmap += BmWidth;
        }

        AccordingLcdRamDisplay (xpos, xpos + BmWidth, displayline);
        displayline++;
    }
}

#include "ascii.h"

unsigned long Lcd::GetChinesePositon (unsigned char msb, unsigned char lsb)
{
    unsigned long pos = 0;

    if (msb >= 0xa1 && msb <= 0xa9)  		//GB2312 符号区
    {
        //0xa1 0xfe
        pos = (msb - 0xa1) * (0xfe - 0xa1 + 1) + (lsb - 0xa1);
        pos *= 24;	// 1个GB2312 有24byte
    }
    else if (msb >= 0xb0 && msb <= 0xf7)  		//GB2312 汉字区
    {
        //0xa1 0xfe
        pos = (msb - 0xb0) * (0xfe - 0xa1 + 1) + (lsb - 0xa1);
        pos += 846;	//GB2312 符号区846个
        pos *= 24;	// 1个GB2312 有24byte
    }

    return pos;
}

void Lcd::LcdGetChineseDot (unsigned char *buff, unsigned long pos)
{
    //外部Flash字库，起始地址为0x80000

    pos += 0x80000;

    static FILE *fp = NULL;

    if(fp == NULL)
    {
        fp = ::fopen("lcd.bin", "r");
        if(fp == NULL)
        {
            memset(buff, 0xFF, 24);
            printf("%s | fopen error!\r\n", __func__);
            return ;
        }
    }

    ::fseek(fp, pos, 0);
    ::fread(buff, 24, 1, fp);

}

void Lcd::LcdTextOut (int xpos, int ypos, const unsigned char *Str)
{
    int x=0;
    unsigned long pos = 0;
    unsigned char buff[128]={0};

    x = xpos;

    while (*Str != 0)
    {
        if (*Str < 0x80)  	//ascii
        {
            LcdDrawBitMap (&asccii_6x12[*Str * 12], x, ypos, AsciiCodeWidth, AsciiCodeHigh);
            x += AsciiCodeWidth;

            if (x >= lcd_x) break;

            Str++;
        }
        else 	//Chinese
        {
            if (0)
            {

            }
            else
            {
                pos = GetChinesePositon (*Str, * (Str + 1) );
                LcdGetChineseDot (buff, pos);

                LcdDrawBitMap (buff, x, ypos, ChineseCodeWidth, ChineseCodeHigh);
            }


            x += ChineseCodeWidth;

            if (x >= lcd_x) break;

            Str++;

            if (*Str == 0) break;

            Str++;
        }
    }
}
