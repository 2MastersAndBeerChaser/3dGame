#include "roomgenerator.h"

RoomGenerator::RoomGenerator(int width, int height, int roomsCount, int minRoomSize, int maxRoomSize)
    : m_width(width),
      m_height(height),
      m_roomsCount(roomsCount),
      m_maxRoomSize(maxRoomSize),
      m_minRoomSize(minRoomSize)
{
    m_map.resize(m_width);
    for (int i = 0; i < m_width; i++)
    {
        m_map[i].resize(m_height);
        for (int j = 0; j < m_height; j++)
        {
            m_map[i][j] = 1;
        }
    }
}

std::vector<std::vector<int> > RoomGenerator::GetCaveMap()
{
    CreateRooms();
    CreateCorridors();
    ToDebug();
    return m_map;
}

void RoomGenerator::CreateRooms()
/*
 * @ todo:
 * Сделать адекватную генерацию ширины-высоты
 */
{
    for (int i = 0; i < m_roomsCount; i++)
    {
        Room room;
        do
        {
            room.x = Rand(0, m_width - 2);
            room.y = Rand(0, m_height - 2);
            int size = Rand(m_minRoomSize, m_maxRoomSize);
            room.w = Rand(2, size / 2);
            room.w = room.x + room.w >= m_width ? m_width - room.x : room.w;
            room.h = size / room.w;
            room.h = room.y + room.h >= m_height ? m_height - room.y : room.h;
            if (room.h * room.w < m_minRoomSize)
            {
                continue;
            }
            room.reachable = false;
        } while (IsIntersect(room));

        m_rooms.push_back(room);
        for (int x = room.x; x < room.x + room.w; x++)
        {
            for (int y = room.y; y < room.y + room.h; y++)
            {
                m_map[x][y] = 0;
            }
        }
    }
}

bool RoomGenerator::IsIntersect(Room room)
{
    for (size_t i = 0; i < m_rooms.size(); i++)
    {
        if (room.x <= m_rooms[i].x + m_rooms[i].w
                && room.x + room.w >= m_rooms[i].x
                && room.y <= m_rooms[i].y + m_rooms[i].h
                && room.y + room.h >= m_rooms[i].y)
        {
            return true;
        }
    }
    return false;
}

void RoomGenerator::CreateCorridors()
{

}

void RoomGenerator::ToDebug()
{
    for (int i = 0; i < m_width; i++)
    {
        QString s = "";
        for (int j = 0; j < m_height; j++)
        {
            s += QString::number(m_map[i][j]);
        }
        qDebug() << s;
    }
}

int RoomGenerator::Rand(int low, int high)
{
    return qrand() % ((high + 1) - low) + low;
}
