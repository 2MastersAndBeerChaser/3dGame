#include "cavewall.h"
#include <QPainter>
#include <QtOpenGL/QGLWidget>

#define ILUT_USE_OPENGL
#include <IL/il.h>
#include <IL/ilu.h>
#include <IL/ilut.h>

#include <QDebug>

GLuint ColoredCube::m_caveWallTexture = 0;
//Нужно поменять способы загрузки - в идеале есть класс, у которого есть статические методы получения определнной текстуры
//Сейчас же каждый раз все загружается, поэтому очень тормозит
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
        //qDebug() << "Start use texture";
        //здесь могут быть косяки с гранями
        glEnable(GL_TEXTURE_2D);
        //glColor3d(1,1,1);
        glBindTexture(GL_TEXTURE_2D, m_caveWallTexture);
        glBegin(GL_QUADS);

        glTexCoord2f(0.0f, 0.0f); glVertex3f(x, y, z + m_len);	// Низ лево
        glTexCoord2f(1.0f, 0.0f); glVertex3f( x + m_len, y, z + m_len);	// Низ право
        glTexCoord2f(1.0f, 1.0f); glVertex3f( x + m_len, y + m_height, z + m_len);	// Верх право
        glTexCoord2f(0.0f, 1.0f); glVertex3f(x, y + m_height, z + m_len);	// Верх лево

                        // Задняя грань
        glTexCoord2f(1.0f, 0.0f); glVertex3f(x, y, z);	// Низ право
        glTexCoord2f(1.0f, 1.0f); glVertex3f(x, y + m_height, z);	// Верх право
        glTexCoord2f(0.0f, 1.0f); glVertex3f(x + m_len, y + m_height, z);	// Верх лево
        glTexCoord2f(0.0f, 0.0f); glVertex3f(x + m_len, y, z);	// Низ лево

                        // Верхняя грань
        glTexCoord2f(0.0f, 1.0f); glVertex3f(x, y + m_height, z + m_len);	// Верх лево
        glTexCoord2f(0.0f, 0.0f); glVertex3f(x + m_len, y + m_height, z + m_len);	// Низ лево
        glTexCoord2f(1.0f, 0.0f); glVertex3f(x + m_len, y + m_height, z);	// Низ право
        glTexCoord2f(1.0f, 1.0f); glVertex3f(x, y + m_height, z);	// Верх право

                        // Нижняя грань
        glTexCoord2f(1.0f, 1.0f); glVertex3f(x, y, z + m_len);	// Верх право
        glTexCoord2f(0.0f, 1.0f); glVertex3f( x, y, z);	// Верх лево
        glTexCoord2f(0.0f, 0.0f); glVertex3f(x + m_len, y, z);	// Низ лево
        glTexCoord2f(1.0f, 0.0f); glVertex3f(x + m_len, y, z + m_len);	// Низ право

                        // Правая грань
        glTexCoord2f(1.0f, 0.0f); glVertex3f(x + m_len, y, z + m_len);	// Низ право
        glTexCoord2f(1.0f, 1.0f); glVertex3f(x + m_len, y, z);	// Верх право
        glTexCoord2f(0.0f, 1.0f); glVertex3f(x + m_len, y + m_height, z);	// Верх лево
        glTexCoord2f(0.0f, 0.0f); glVertex3f(x + m_len, y + m_height, z + m_len);	// Низ лево

                        // Левая грань
        glTexCoord2f(0.0f, 0.0f); glVertex3f(x, y, z + m_len);	// Низ лево
        glTexCoord2f(1.0f, 0.0f); glVertex3f(x, y + m_height, z + m_len);	// Низ право
        glTexCoord2f(1.0f, 1.0f); glVertex3f(x, y + m_height, z);	// Верх право
        glTexCoord2f(0.0f, 1.0f); glVertex3f(x, y, z);	// Верх лево
        glEnd();
        glDisable(GL_TEXTURE_2D);
        //glDisable(GL_BLEND);

        return;
    }

    // Передаем информацию о массиве вершин
    glVertexPointer(3, GL_FLOAT, sizeof(SimpleVertex), &vertices[0].pos);

    // и массиве цветов
    glColorPointer(4, GL_UNSIGNED_BYTE, sizeof(SimpleVertex), &vertices[0].color);

    //glBindTexture(GL_TEXTURE_2D, DiffuseTexture);

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
      m_len(WALL_LEN),
      m_isWall(false)
      //m_caveWallTexture(0)
{
    switch (wallType)
    {
    case WallType::CaveGround:
        m_color = {128, 128, 128, 255};
        m_isWall = false;
        m_height = 0;
        m_len = MAP_SIZE * WALL_LEN;

        break;
    case WallType::CaveWall:
        m_color = {128, 5, 5, 255};
        if (m_caveWallTexture == 0)
            m_caveWallTexture = CreateTexture();
        m_isWall = true;
         //для ПещераСтена
        m_height = WALL_LEN;
        break;
    case WallType::RoomGround:
        m_color = {128, 5, 128, 255};
        m_isWall = false;
        m_height = 0;
        break;
    case WallType::RoomWall:
        m_color = {8, 5, 125, 255};
        m_isWall = false;
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

    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    drawOpenGLCube();
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); //надо ли тут это делать ???
    //glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}

GLuint ColoredCube::CreateTexture()
{
    GLuint textureID;
    QImage texture;
    texture.load("D:/STUD/V/CG/3dGame/KPACUBO/Textures/lava_texture.png");
    texture = QGLWidget::convertToGLFormat(texture);
    glBindTexture(GL_TEXTURE_2D, textureID);
    glTexImage2D(GL_TEXTURE_2D, 0, 3, (GLsizei)texture.width(), (GLsizei)texture.height(), 0, GL_RGBA, GL_UNSIGNED_BYTE, texture.bits());
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);

    return textureID;
//    //qDebug() << "in create texture";
//    ILuint imageID;

//    GLuint textureID;

//    ILboolean success;

//    ILenum error;

//    ilGenImages(1, &imageID);

//    ilBindImage(imageID);
//   // qDebug() << "in create texture";
//    success = ilLoadImage("D:/STUD/V/CG/3dGame/KPACUBO/Textures/lava_texture.png"); // тут нужно написать норм путь
//  //  qDebug() << "stop";
//    if (success)
//    {
//        ILinfo ImageInfo;
//        iluGetImageInfo(&ImageInfo);
//        if (ImageInfo.Origin == IL_ORIGIN_UPPER_LEFT)
//        {
//            iluFlipImage();
//        }

//        success = ilConvertImage(IL_RGBA, IL_UNSIGNED_BYTE);

//        if (!success)
//        {
//            error = ilGetError();
//            qDebug() << "error " << error;
//            return 0;
//        }

//        glGenTextures(1, &textureID);

//        glBindTexture(GL_TEXTURE_2D, textureID);

//        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
//        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);

//        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
//        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

//        glTexImage2D(GL_TEXTURE_2D,
//                     0,
//                     ilGetInteger(IL_IMAGE_FORMAT),
//                     ilGetInteger(IL_IMAGE_WIDTH),
//                     ilGetInteger(IL_IMAGE_HEIGHT),
//                     0,
//                     ilGetInteger(IL_IMAGE_FORMAT),
//                     GL_UNSIGNED_BYTE,
//                     ilGetData());
//    }
//    else
//    {
//        error = ilGetError();
//        qDebug() << "error " << error;
//        return 0;
//    }

//    //ilDeleteImages(1, &imageID);
//    //qDebug() << "OK " << textureID;
//    return textureID;
}
