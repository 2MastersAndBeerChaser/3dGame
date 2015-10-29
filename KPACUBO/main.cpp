#include <QApplication>
#include "cavegenerator.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    CaveGenerator cgen(50, 50);
    std::vector<std::vector<int> > vec = cgen.GetCaveMap();
    return a.exec();
}
