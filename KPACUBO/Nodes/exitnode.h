#pragma once

#include "../GL/scenenode.h"
#include <qopengl.h>
#include <QVector2D>
#include "globals.h"

class ExitNode : public SceneNode
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

    ExitNode(SceneNode *parent, QVector2D coord);
    QVector2D GetCoords() const;
    void drawOpenGLCube();
    void advance(int64_t msec) override;
    void render(QPainter &painter) override;

private:
    QVector2D m_coord;
    Color4 m_color;
    int m_height;
};
