#pragma once

#include "../GL/scenenode.h"
#include <qopengl.h>
#include "globals.h"

class ColoredCube : public SceneNode
{
public:
    struct Vec3
    {
        GLfloat x, y, z;
    };

    struct Color4
    {
        GLubyte r, g, b, a;
    };

    struct SimpleVertex
    {
        Vec3 pos;
        Color4 color;
    };

    enum WallType
    {
        CaveWall,
        CaveGround,
        RoomWall,
        RoomGround
    };

    ColoredCube(SceneNode *parent, Vec3 coord, WallType wallType);
    void drawOpenGLCube(bool showWired);
    void advance(int64_t msec) override;
    void render(QPainter &painter) override;
private:
    Vec3 m_coord;
    Color4 m_color;
    int m_height;
    int m_len;
};
