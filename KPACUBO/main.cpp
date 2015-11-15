#include <gameapplication.h>

int main(int argc, char *argv[])
{
    qsrand(QTime::currentTime().msec());
    GameApplication a(argc, argv);
    return a.enterGameLoop();
}
