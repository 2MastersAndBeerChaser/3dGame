#pragma once

#include "../GL/scenenode.h"
#include <qopengl.h>
#include <QVector2D>

class PlayerNode : public SceneNode
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

    PlayerNode(SceneNode *parent, QVector2D coord);
    PlayerNode();
    void SetMove(float dx, float dy);
    QVector2D GetCoords() const;
    void SetSpeed(QVector2D vecSpeed);
    void drawOpenGLCube(bool showWired);
    void advance(int64_t msec) override;
    void render(QPainter &painter) override;

private:
    QVector2D m_coord;
    Color4 m_color;
    int m_height;
    const int LEN = 2;
    QVector2D m_speed;
};
