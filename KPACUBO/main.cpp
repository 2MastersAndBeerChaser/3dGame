#include <QApplication>
#include "cavegenerator.h"

int main(int argc, char *argv[])
{
    qsrand(QTime::currentTime().msec());
    //QApplication a(argc, argv);
    CaveGenerator cgen(95, 95, 10);
    std::vector<std::vector<int> > vec = cgen.GetCaveMap();
    return 0;
}
