#include <QApplication>
#include <QThread>

#include "mcu.h"
class SimulateMCU : public QThread
{
protected:
    void run();
};

SimulateMCU MCU;

void SimulateMCU::run()
{
    while (1)
    {
        MCU_While();
        QThread::msleep(100);
    }


}


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    MCU_Init();
    MCU.start();

    return a.exec();
}
