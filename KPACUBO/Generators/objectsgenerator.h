#pragma once
#include <vector>
#include <QTime>
#include "globals.h"

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
        size_t x;
        size_t y;
    };

    void GenEnterance();
    void GenExit();
    void GenTreasure();
    void GenEnemies();
    void GetFreeCells(Coord lt, Coord rb);
	void FillBorders();

    std::vector<std::vector<int> > m_map;
    Orientation m_or;
    std::vector<Coord> m_freeCells;
};
