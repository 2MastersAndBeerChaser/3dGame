#include "collisionhandler.h"
#include <cmath>

CollisionHandler::CollisionHandler()
{

}

void CollisionHandler::SetMap(const std::vector<std::vector<int> > &map)
{
    size_t mapLen = map.size() * WALL_LEN;
    m_map.resize(mapLen);
    for (size_t i = 0; i < mapLen; i++)
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

QVector2D CollisionHandler::TryMove(float dx, float dy)
{
    float newX = floor(m_playerCoord.x() + dx);
    float newY = floor(m_playerCoord.y() + dy);
    std::vector<QVector2D> vert;
    vert.push_back(QVector2D(newX, newY)); //br
    vert.push_back(QVector2D(newX + PLAYER_SIZE, newY)); //bl
    vert.push_back(QVector2D(newX, newY + PLAYER_SIZE)); //tr
    vert.push_back(QVector2D(newX + PLAYER_SIZE, newY + PLAYER_SIZE)); //tl
	//-----------------------
    if (newX < 0 || newX >= m_map.size() ||	  //
            newY < 0 || newY >= m_map.size()) // Этот фрагмент коллайдера будет не нужным после переделки генератора!!!
    {
        return QVector2D(0, 0);
    }
	//-----------------------
	//QVector2D movingVector = QVector2D(dx, dy);
	//if (m_map[m_playerCoord.x()][vert[0].y()] == WALL_CELL || // y-axis move
	//	m_map[m_playerCoord.x()][vert[1].y()] == WALL_CELL ||
	//	m_map[m_playerCoord.x()][vert[2].y()] == WALL_CELL ||
	//	m_map[m_playerCoord.x()][vert[3].y()] == WALL_CELL)
	//{
	//	movingVector -= QVector2D(0, dy);
	//}
	//if (m_map[vert[0].x()][m_playerCoord.y()] == WALL_CELL || // x-axis move
	//	m_map[vert[1].x()][m_playerCoord.y()] == WALL_CELL ||
	//	m_map[vert[2].x()][m_playerCoord.y()] == WALL_CELL ||
	//	m_map[vert[3].x()][m_playerCoord.y()] == WALL_CELL)
	//{
	//	movingVector -= QVector2D(dx, 0);
	//}

	QVector2D movingVector = QVector2D(0, 0);
	if (dx > 0) // left
	{
		if (m_map[vert[1].x()][m_playerCoord.y()] != WALL_CELL &&
			m_map[vert[3].x()][m_playerCoord.y()] != WALL_CELL) // left verticles
		{
			movingVector += QVector2D(dx, 0);
		}
	}
	else // right
	{
		if (m_map[vert[0].x()][m_playerCoord.y()] != WALL_CELL &&
			m_map[vert[2].x()][m_playerCoord.y()] != WALL_CELL) // right verticles
		{
			movingVector += QVector2D(dx, 0);
		}
	}
	if (dy > 0) // top
	{
		if (m_map[m_playerCoord.x()][vert[2].y()] != WALL_CELL &&
			m_map[m_playerCoord.x()][vert[3].y()] != WALL_CELL) // top verticles
		{
			movingVector += QVector2D(0, dy);
		}
	}
	else // bottom
	{
		if (m_map[m_playerCoord.x()][vert[0].y()] != WALL_CELL &&
			m_map[m_playerCoord.x()][vert[1].y()] != WALL_CELL) // bottom verticles
		{
			movingVector += QVector2D(0, dy);
		}
	}

	m_playerCoord.setX(m_playerCoord.x() + movingVector.x());
	m_playerCoord.setY(m_playerCoord.y() + movingVector.y());
	return movingVector;
}

std::vector<std::vector<int> > CollisionHandler::GetMap() const
{
    return m_map;
}
