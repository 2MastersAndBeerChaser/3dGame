#include "collisionhandler.h"
#include <QDebug>
#include "Box2D/Box2D.h"

CollisionHandler::CollisionHandler()
{

}

void CollisionHandler::SetMap(const std::vector<std::vector<int> > &map)
{
    size_t mapLen = map.size() * WALL_LEN;
    m_map.resize(mapLen);
    for (int i = 0; i < mapLen; i++)
    {
        m_map[i].resize(mapLen);
    }
    for (int i = 0; i < map.size(); i++)
    {
        for (int j = 0; j < map.size(); j++)
        {
            for (int k = 0; k < WALL_LEN; k++)
            {
                for (int l = 0; l < WALL_LEN; l++)
                {
                    m_map[i * WALL_LEN + k][j *WALL_LEN + l] = map[i][j];
                }
            }
        }
    }
}

void CollisionHandler::SetCoord(QVector2D coord)
{
    m_playerCoord = coord;
}

bool CollisionHandler::TryMove(float dx, float dy)
{
    int newX = m_playerCoord.x() + dx;
    int newY = m_playerCoord.y() + dy;
//    QList<QVector2D> vert;
//    vert.append(QVector2D(newX, newY));
//    vert.append(QVector2D(newX + PLAYER_SIZE, newY));
//    vert.append(QVector2D(newX, newY + PLAYER_SIZE));
//    vert.append(QVector2D(newX + PLAYER_SIZE, newY + PLAYER_SIZE));

//    for (int i = 0; i < 4; i++)
//    {
//        if (vert[i].x() < 0 || vert[i].x() >= m_map.size() ||
//                vert[i].y() < 0 || vert[i].y() >= m_map.size())
//        {
//            qDebug() << "COLL";
//            return false;
//        }
//        if (m_map[vert[i].x()][vert[i].x()] == WALL_CELL)
//        {
//            qDebug() << "COLL";
//            return false;
//        }
   // }
        if (newX < 0 || newX >= m_map.size() ||
                newY < 0 || newY >= m_map.size())
        {
            qDebug() << "COLL";
            return false;
        }
        if (m_map[newX][newY] == WALL_CELL)
        {
            qDebug() << "COLL";
            return false;
        }
    m_playerCoord.setX(m_playerCoord.x() + dx);
    m_playerCoord.setY(m_playerCoord.y() + dy);
    return true;

}
