#include "collisionhandler.h"

CollisionHandler::CollisionHandler()
{

}

void CollisionHandler::SetMap(const std::vector<std::vector<int> > &map)
{
    m_mapLen = map.size() * WALL_LEN;
    m_map.resize(m_mapLen);
    for (int i = 0; i < m_mapLen; i++)
    {
        m_map[i].resize(m_mapLen);
    }
    for (int i = 0; i < map.size(); i++)
    {
        for (int j = 0; j < map.size(); j++)
        {

        }
    }
}

void CollisionHandler::SetCoord(QVector2D coord)
{
    m_playerCoord = coord;
}

void CollisionHandler::SetDiffMove(float dx, float dy)
{
    if (m_map[m_playerCoord.x() + dx, m_playerCoord.y() + dy] == 1)
    {
        emit Collided();
    }
    else
    {
        m_playerCoord.setX(m_playerCoord.x() + dx);
        m_playerCoord.setY(m_playerCoord.y() + dy);
    }
}

