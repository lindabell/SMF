#ifndef KEY_H
#define KEY_H

#include <QWidget>
#include "basetype.h"
///根据通用键盘代码分配
#define KEY_NONE	0
#define KEY_UP		38
#define KEY_Down	40
#define KEY_Left	37
#define KEY_Right	39
#define KEY_Return	27
#define KEY_Ok 		13

void KeyInit(void);
u8 GetKey(void);

namespace Ui {
class Key;
}

class Key : public QWidget
{
    Q_OBJECT

public:
    explicit Key(QWidget *parent = 0);
    ~Key();
private slots:
    void on_button_Up_clicked();

    void on_button_Down_clicked();

    void on_button_Left_clicked();

    void on_button_Right_clicked();

    void on_button_Return_clicked();

    void on_button_Ok_clicked();

private:
    Ui::Key *ui;
};

#endif // KEY_H
