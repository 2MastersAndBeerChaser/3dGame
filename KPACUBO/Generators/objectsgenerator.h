#pragma once
#include <vector>
#include <QTime>

class ObjectsGenerator
{
public:
    enum Orientation
    {
        Bottom,
        Top,
        Right,
        Left,
        Random
    };

    ObjectsGenerator(std::vector<std::vector<int> > map, Orientation enteranceOrientation = Orientation::Random);
    std::vector<std::vector<int> > GenerateObj();
private:
    struct Coord
    {
        int x;
        int y;
    };

    void GenEnterance();
    void GenExit();
    void GenTreasure();
    void GenEnemies();
    void GFreeSpace(std::vector<Coord> & coords, Coord lt, Coord rb);

    std::vector<std::vector<int> > m_map;
    Orientation m_or;
};
