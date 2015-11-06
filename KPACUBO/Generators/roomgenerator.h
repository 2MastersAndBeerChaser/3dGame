#pragma once
#include <vector>
#include <QTime>
#include <qdebug.h>

class RoomGenerator
{
public:
    RoomGenerator(int width, int height, int roomsCount = 5,
                  int minRoomSize = 4, int maxRoomSize = 100);
    std::vector<std::vector<int> > GetCaveMap();
private:
    struct Room{
        int x;
        int y;
        int w;
        int h;
        bool reachable;
    };

    void CreateRooms();
    bool IsIntersect(Room room);
    void CreateCorridors();
    void ToDebug();
    int Rand(int low, int high);

    std::vector<std::vector<int> > m_map;
    int m_width;
    int m_height;
    int m_roomsCount;
    int m_maxRoomSize;
    int m_minRoomSize;
    std::vector<Room> m_rooms;
};
