#include "key.h"
#include "ui_key.h"
#include <QDebug>
Key *key;
static u8 KeyTemp;
void KeyInit(void)
{
    key=new Key;
    key->show();
}

u8 GetKey(void)
{
     u8 temp;
    temp=KeyTemp;
    KeyTemp=KEY_NONE;
    return temp;
}

Key::Key(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Key)
{
    ui->setupUi(this);
}

Key::~Key()
{
    delete ui;
}

void Key::on_button_Up_clicked()
{
    qDebug()<<"key up";
    KeyTemp=KEY_UP;
}

void Key::on_button_Down_clicked()
{
    qDebug()<<"key down";
    KeyTemp=KEY_Down;
}

void Key::on_button_Left_clicked()
{
    qDebug()<<"key left";
    KeyTemp=KEY_Left;
}

void Key::on_button_Right_clicked()
{
    qDebug()<<"key right";
    KeyTemp=KEY_Right;
}

void Key::on_button_Return_clicked()
{
    qDebug()<<"key return";
    KeyTemp=KEY_Return;
}

void Key::on_button_Ok_clicked()
{
    qDebug()<<"key ok";
    KeyTemp=KEY_Ok;
}
