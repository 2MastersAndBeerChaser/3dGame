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
    switch (m_or)
    {
    case Orientation::Bottom:
        GetFreeCells({0, MAP_SIZE - (MAP_SIZE / 5)}, {MAP_SIZE, MAP_SIZE});
        break;
    case Orientation::Top:
        GetFreeCells({0, 0}, {MAP_SIZE, MAP_SIZE / 5});
        break;
    case Orientation::Left:
        GetFreeCells({0, 0}, {MAP_SIZE / 5, MAP_SIZE});
        break;
    case Orientation::Right:
        GetFreeCells({MAP_SIZE - MAP_SIZE / 5, 0}, {MAP_SIZE, MAP_SIZE});
        break;
    case Orientation::Random:
        GetFreeCells({0, 0}, {MAP_SIZE, MAP_SIZE});
        break;
    default:
        break;
    }
    Coord enterance = m_freeCells[qrand() % (int)m_freeCells.size()];
    m_map[enterance.x][enterance.y] = ENTERANCE_CELL;
}

void ObjectsGenerator::GenExit()
{
    m_freeCells.clear();
    for (size_t i = 0; i < MAP_SIZE; i++)
    {
        if (m_map[0][i] == 0)
        {
            m_freeCells.push_back({0, i});
        }
        if (m_map[MAP_SIZE - 1][i] == 0)
        {
            m_freeCells.push_back({MAP_SIZE - 1, i});
        }
    }
    for (size_t j = 0; j < MAP_SIZE; j++)
    {
        if (m_map[j][0] == 0)
        {
            m_freeCells.push_back({j, 0});
        }
        if (m_map[j][MAP_SIZE - 1] == 0)
        {
            m_freeCells.push_back({j, MAP_SIZE - 1});
        }
    }
    if (m_freeCells.size() > 0)
    {
        Coord exit = m_freeCells[qrand() % (int)m_freeCells.size()];
        m_map[exit.x][exit.y] = SIDE_EXIT_CELL;
    }
    else
    {
        GetFreeCells({0, 0}, {MAP_SIZE, MAP_SIZE});
        Coord exit = m_freeCells[qrand() % (int)m_freeCells.size()];
        m_map[exit.x][exit.y] = GROUND_EXIT_CELL;
    }
}

void ObjectsGenerator::GenTreasure()
{

}

void ObjectsGenerator::GenEnemies()
{

}

void ObjectsGenerator::GetFreeCells(Coord lt, Coord rb)
{
    for (size_t i = lt.y; i < rb.y; i++)
    {
        for (size_t j = lt.x; j < rb.x; j++)
        {
            if (m_map[i][j] == 0)
            {
                m_freeCells.push_back({j, i});
            }
        }
    }
}
