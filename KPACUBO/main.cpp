#include <gameapplication.h>

#pragma comment(lib, "DevIL.lib")
#pragma comment(lib, "ILU.lib")
#pragma comment(lib, "ILUT.lib")

int main(int argc, char *argv[])
{
    qsrand(QTime::currentTime().msec());
    GameApplication a(argc, argv);
    return a.enterGameLoop();
}
