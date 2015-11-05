#include <gameapplication.h>
#include <Generators/roomgenerator.h>

int main(int argc, char *argv[])
{
    qsrand(QTime::currentTime().msec());
//    CaveGenerator cgen(95, 95, 10);
//    std::vector<std::vector<int> > vec = cgen.GetCaveMap();
    RoomGenerator rgen(50, 50);
    rgen.GetCaveMap();
    GameApplication a(argc, argv);
    return a.enterGameLoop();
}
