#pragma once

#include "../GL/scenenode.h"
#include <qopengl.h>
#include <QVector2D>
#include <QKeyEvent>

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
    void SetCoords(QVector2D coord);
    QVector2D GetCoords() const;
    void drawOpenGLCube(bool showWired);
    void advance(int64_t msec) override;
    void render(QPainter &painter) override;

protected:
    virtual void keyPressEvent(QKeyEvent *) ;
    virtual void keyReleaseEvent(QKeyEvent *) ;

private:
    QVector2D m_coord;
    Color4 m_color;
    int m_height;
    const int LEN = 2;
};
