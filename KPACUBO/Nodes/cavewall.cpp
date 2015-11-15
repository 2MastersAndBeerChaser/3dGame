#include "cavewall.h"
#include <QPainter>

void ColoredCube::drawOpenGLCube(bool showWired)
{
    /*

       Y
       |
       |
       |
       +---X
      /
     /
    Z
       3----2
      /    /|
     /    / |
    7----6  |
    |  0 |  1
    |    | /
    |    |/
    4----5
    */
    // Массив координат вершин
    int x = m_coord.x;
    int y = m_coord.y;
    int z = m_coord.z;
    SimpleVertex vertices[8] =
    {
        {{x, y, z}, m_color},		// 0
        {{x + m_len, y, z}, m_color},		// 1
        {{x + m_len, y + m_height, z}, m_color},		// 2
        {{x, y + m_height, z}, m_color},			// 3
        {{x, y, z + m_len}, m_color},		// 4
        {{x + m_len, y, z + m_len}, m_color},	// 5
        {{x + m_len, y + m_height, z + m_len}, m_color},		// 6
        {{x, y + m_height, z + m_len}, m_color},		// 7
    };

    if (showWired) {
        for (SimpleVertex &vert : vertices) {
            vert.pos.x *= 1.01;
            vert.pos.y *= 1.01;
            vert.pos.z *= 1.01;
            vert.color.r = 0;
            vert.color.g = 0;
            vert.color.b = 0;
        }
    }

    // Массив граней, а точнее, индексов составляющих их вершин.
    // Индексы вершин граней перечисляются в порядке их обхода
    // против часовой стрелки (если смотреть на грань снаружи)
    const unsigned char faces[6][4] =
    {
        {4, 7, 3, 0},	// грань x<0
        {5, 1, 2, 6},	// грань x>0
        {4, 0, 1, 5},	// грань y<0
        {7, 6, 2, 3},	// грань y>0
        {0, 3, 2, 1},	// грань z<0
        {4, 5, 6, 7},	// грань z>0
    };

    // Передаем информацию о массиве вершин
    glVertexPointer(3, GL_FLOAT, sizeof(SimpleVertex), &vertices[0].pos);

    // и массиве цветов
    glColorPointer(4, GL_UNSIGNED_BYTE, sizeof(SimpleVertex), &vertices[0].color);

    // Разрешаем использование массива координат вершин и цветов
    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_COLOR_ARRAY);

    glDrawElements(GL_QUADS, 24, GL_UNSIGNED_BYTE, faces);

    // Выключаем использовнием массива цветов
    glDisableClientState(GL_COLOR_ARRAY);
    // Выключаем использование массива координат вершин
    glDisableClientState(GL_VERTEX_ARRAY);
}

ColoredCube::ColoredCube(SceneNode *parent, Vec3 coord, WallType wallType)
    : SceneNode(parent),
      m_coord(coord),
      m_len(WALL_LEN)
{
    switch (wallType)
    {
    case WallType::CaveGround:
        m_color = {128, 128, 128, 255};
        m_height = 0;
        m_len = MAP_SIZE * WALL_LEN;


        break;
    case WallType::CaveWall:
        m_color = {128, 5, 5, 255};
        m_height = WALL_LEN;
        break;
    case WallType::RoomGround:
        m_color = {128, 5, 128, 255};
        m_height = 0;
        break;
    case WallType::RoomWall:
        m_color = {8, 5, 125, 255};
        m_height = 4;
        break;
    default:
        break;
    }

}

void ColoredCube::advance(int64_t msec)
{
    (void)msec;
}

void ColoredCube::render(QPainter &painter)
{
    (void)painter;

    drawOpenGLCube(false);
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}
