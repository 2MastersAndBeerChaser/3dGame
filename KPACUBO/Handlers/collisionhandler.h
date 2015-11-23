#pragma once
#include <vector>
#include <QVector2D>
#include "globals.h"

class CollisionHandler
{
public:
    CollisionHandler();
    void SetMap(std::vector<std::vector<int> > const& map);
    void SetCoord(QVector2D coord);
    bool TryMove(float dx, float dy);
private:
    void FillMap();
    std::vector<std::vector<int> > m_map;
    QVector2D m_playerCoord;
};
