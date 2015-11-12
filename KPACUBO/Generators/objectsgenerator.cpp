#include "objectsgenerator.h"

ObjectsGenerator::ObjectsGenerator(std::vector<std::vector<int> > map, Orientation enteranceOrientation)
    : m_map(map),
      m_or(enteranceOrientation)
{

}

std::vector<std::vector<int> > ObjectsGenerator::GenerateObj()
{
    GenEnterance();
    GenTreasure();
    GenExit();
    GenEnemies();
    return m_map;
}

void ObjectsGenerator::GenEnterance()
{
    /*std::vector<Coord> freeSpace;
    switch (m_or)
    {
    case Orientation::Bottom:
        GetFreeSpace(freeSpace, {0, m_map.size() - (m_map.size() / 5)}, {m_map[0].size(), m_map.size()});
        break;
    case Orientation::Top:
        GetFreeSpace(freeSpace, {0, 0}, {m_map[0].size(), m_map.size() / 5});
        break;
    case Orientation::Left:
        GetFreeSpace(freeSpace, {0, 0}, {m_map[0].size() / 5, m_map.size()});
        break;
    case Orientation::Right:
        GetFreeSpace(freeSpace, {m_map[0].size() - m_map[0].size() / 5, 0}, {m_map[0].size(), m_map.size()});
        break;
    case Orientation::Random:
        GetFreeSpace(freeSpace, {0, 0}, {m_map[0].size(), m_map.size()});
        break;
    default:
        break;
    }
    Coord enterance = freeSpace[qrand() % (int)freeSpace.size()];
    m_map[enterance.x][enterance.y] = 2;*/
}

void ObjectsGenerator::GenExit()
{

}

void ObjectsGenerator::GenTreasure()
{

}

void ObjectsGenerator::GenEnemies()
{

}

/*void ObjectsGenerator::GetFreeSpace(std::vector<ObjectsGenerator::Coord> &coords, Coord lt, Coord rb)
{
    for (int i = lt.y; i < rb.y; i++)
    {
        for (int j = lt.x; j < rb.x; j++)
        {
            if (m_map[i][j] == 0)
            {
                coords.push_back({j, i});
            }
        }
    }
}*/
