#include <gameapplication.h>
#include <QDebug>

#pragma comment(lib, "DevIL.lib")
#pragma comment(lib, "ILU.lib")
#pragma comment(lib, "ILUT.lib")

int main(int argc, char *argv[])
{
    qDebug() << "in main";
    qsrand(QTime::currentTime().msec());
    GameApplication a(argc, argv);
    return a.enterGameLoop();
}
