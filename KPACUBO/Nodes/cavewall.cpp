#include "cavewall.h"
#include <QPainter>
#include "../GL/texturecache.h"
#include <QDebug>

void ColoredCube::drawOpenGLCube()
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
     /    / |`
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

    if (m_isWall)
    {
        const TexCoordVertex texCoords[24] = {
            {1.0f, 0.0f},
            {1.0f, 1.0f},
            {0.0f, 1.0f},
            {0.0f, 0.0f},

            {0.0f, 0.0f},
            {1.0f, 0.0f},
            {1.0f, 1.0f},
            {0.0f, 1.0f},

            {1.0f, 0.0f},
            {1.0f, 1.0f},
            {0.0f, 1.0f},
            {0.0f, 0.0f},

            {0.0f, 0.0f},
            {1.0f, 0.0f},
            {1.0f, 1.0f},
            {0.0f, 1.0f},

            {1.0f, 0.0f},
            {1.0f, 1.0f},
            {0.0f, 1.0f},
            {0.0f, 0.0f},

            {0.0f, 0.0f},
            {1.0f, 0.0f},
            {1.0f, 1.0f},
            {0.0f, 1.0f}
        };

        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, TextureCache::GetWallTexture());
        //glBegin(GL_QUADS);

        glVertexPointer(3, GL_FLOAT, sizeof(SimpleVertex), &vertices[0].pos);
        glTexCoordPointer(2, GL_FLOAT, sizeof(TexCoordVertex), &texCoords[0].texWidth);

        glEnableClientState(GL_VERTEX_ARRAY);
        glEnableClientState(GL_TEXTURE_COORD_ARRAY);

        glDrawElements(GL_QUADS, 24, GL_UNSIGNED_BYTE, faces);

        glDisableClientState(GL_VERTEX_ARRAY);
        glDisableClientState(GL_TEXTURE_COORD_ARRAY);

//        glTexCoord2f(0.0f, 0.0f); glVertex3f(x, y, z + m_len);	// Низ лево
//        glTexCoord2f(1.0f, 0.0f); glVertex3f( x + m_len, y, z + m_len);	// Низ право
//        glTexCoord2f(1.0f, 1.0f); glVertex3f( x + m_len, y + m_height, z + m_len);	// Верх право
//        glTexCoord2f(0.0f, 1.0f); glVertex3f(x, y + m_height, z + m_len);	// Верх лево

//                        // Задняя грань
//        glTexCoord2f(1.0f, 0.0f); glVertex3f(x, y, z);	// Низ право
//        glTexCoord2f(1.0f, 1.0f); glVertex3f(x, y + m_height, z);	// Верх право
//        glTexCoord2f(0.0f, 1.0f); glVertex3f(x + m_len, y + m_height, z);	// Верх лево
//        glTexCoord2f(0.0f, 0.0f); glVertex3f(x + m_len, y, z);	// Низ лево

//                        // Верхняя грань
//        glTexCoord2f(0.0f, 1.0f); glVertex3f(x, y + m_height, z + m_len);	// Верх лево
//        glTexCoord2f(0.0f, 0.0f); glVertex3f(x + m_len, y + m_height, z + m_len);	// Низ лево
//        glTexCoord2f(1.0f, 0.0f); glVertex3f(x + m_len, y + m_height, z);	// Низ право
//        glTexCoord2f(1.0f, 1.0f); glVertex3f(x, y + m_height, z);	// Верх право

//                        // Нижняя грань
//        glTexCoord2f(1.0f, 1.0f); glVertex3f(x, y, z + m_len);	// Верх право
//        glTexCoord2f(0.0f, 1.0f); glVertex3f( x, y, z);	// Верх лево
//        glTexCoord2f(0.0f, 0.0f); glVertex3f(x + m_len, y, z);	// Низ лево
//        glTexCoord2f(1.0f, 0.0f); glVertex3f(x + m_len, y, z + m_len);	// Низ право

//                        // Правая грань
//        glTexCoord2f(1.0f, 0.0f); glVertex3f(x + m_len, y, z + m_len);	// Низ право
//        glTexCoord2f(1.0f, 1.0f); glVertex3f(x + m_len, y, z);	// Верх право
//        glTexCoord2f(0.0f, 1.0f); glVertex3f(x + m_len, y + m_height, z);	// Верх лево
//        glTexCoord2f(0.0f, 0.0f); glVertex3f(x + m_len, y + m_height, z + m_len);	// Низ лево

//                        // Левая грань
//        glTexCoord2f(0.0f, 0.0f); glVertex3f(x, y, z + m_len);	// Низ лево
//        glTexCoord2f(1.0f, 0.0f); glVertex3f(x, y + m_height, z + m_len);	// Низ право
//        glTexCoord2f(1.0f, 1.0f); glVertex3f(x, y + m_height, z);	// Верх право
//        glTexCoord2f(0.0f, 1.0f); glVertex3f(x, y, z);	// Верх лево

//        glEnd();
        glDisable(GL_TEXTURE_2D);

        return;
    }

    glVertexPointer(3, GL_FLOAT, sizeof(SimpleVertex), &vertices[0].pos);
    glColorPointer(4, GL_UNSIGNED_BYTE, sizeof(SimpleVertex), &vertices[0].color);

    // Разрешаем использование массива координат вершин и цветов
    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_COLOR_ARRAY);

    glDrawElements(GL_QUADS, 24, GL_UNSIGNED_BYTE, faces);

    glDisableClientState(GL_COLOR_ARRAY);
    glDisableClientState(GL_VERTEX_ARRAY);
}

ColoredCube::ColoredCube(SceneNode *parent, Vec3 coord, WallType wallType)
    : SceneNode(parent),
      m_coord(coord),
      m_len(WALL_LEN),
      m_isWall(false)
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
        m_isWall = true;
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

    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); //для отладки поставить это и убрать след.строку
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    drawOpenGLCube();
}
