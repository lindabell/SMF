#ifndef LCD_H
#define LCD_H

#include <QWidget>

#define lcd_Xenlarge 2              //横向放大倍数
#define lcd_Yenlarge 2              //纵向放大倍数

#define lcd_x (128)                 //支持任意大小
#define lcd_y (64)                  //支持任意8倍大小

#define start_x 0
#define start_y 0

namespace Ui {
class Lcd;
}

class Lcd : public QWidget
{
    Q_OBJECT

public:
    explicit Lcd(QWidget *parent = 0);
    ~Lcd();
    void LcdClear (void);
    void LcdDrawBitMap (const unsigned char *Bitmap, int xpos, int ypos, int BmWidth, int BmHigh);
    void LcdTextOut (int xpos, int ypos, const unsigned char *Str);

private:
    Ui::Lcd *ui;
    void paintEvent(QPaintEvent *);
    void drawPointByEnlarge (QPainter *painter, int x, int y, int xenlarge, int yenlarge);
    void ClearBuffAnyByte_bits (unsigned char *p, unsigned char comb, int len);
    void byteCombine (unsigned char *des, const unsigned char *src1, unsigned char RSbits, const unsigned char *src2, unsigned char LSbits, int len);
    void AccordingLcdRamDisplay (int start_xpos, int end_xpos, int displayline);
    unsigned long GetChinesePositon (unsigned char msb, unsigned char lsb);
    void LcdGetChineseDot (unsigned char *buff, unsigned long pos);
};

#endif // LCD_H
