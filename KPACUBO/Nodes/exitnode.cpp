#include "exitnode.h"
#include <QPainter>
#include <QDebug>

void ExitNode::drawOpenGLCube(bool showWired)
{
    float x = m_coord.x();
    float z = m_coord.y();
    float y = 2;
    m_color = {124, 55, 125, 255};
    SimpleVertex vertices[8] =
    {
        {{x, y + 1, z}, m_color},		// 0
        {{x + WALL_LEN, y + 1, z}, m_color},		// 1
        {{x + WALL_LEN, y + m_height + 1, z}, m_color},		// 2
        {{x, y + m_height + 1, z}, m_color},			// 3
        {{x, y + 1, z + WALL_LEN}, m_color},		// 4
        {{x + WALL_LEN, y + 1, z + WALL_LEN}, m_color},	// 5
        {{x + WALL_LEN, y + m_height + 1, z + WALL_LEN}, m_color},		// 6
        {{x, y + m_height + 1, z + WALL_LEN}, m_color},		// 7
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

    const unsigned char faces[6][4] =
    {
        {4, 7, 3, 0},	// грань x<0
        {5, 1, 2, 6},	// грань x>0
        {4, 0, 1, 5},	// грань y<0
        {7, 6, 2, 3},	// грань y>0
        {0, 3, 2, 1},	// грань z<0
        {4, 5, 6, 7},	// грань z>0
    };

    glVertexPointer(3, GL_FLOAT, sizeof(SimpleVertex), &vertices[0].pos);
    glColorPointer(4, GL_UNSIGNED_BYTE, sizeof(SimpleVertex), &vertices[0].color);
    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_COLOR_ARRAY);
    glDrawElements(GL_QUADS, 24, GL_UNSIGNED_BYTE, faces);
    glDisableClientState(GL_COLOR_ARRAY);
    glDisableClientState(GL_VERTEX_ARRAY);
}

ExitNode::ExitNode(SceneNode *parent, QVector2D coord)
    : SceneNode(parent),
      m_coord(coord)
{
    m_height = 3;
}

QVector2D ExitNode::GetCoords() const
{
    return m_coord;
}

void ExitNode::advance(int64_t msec)
{
    (void)msec;
}

void ExitNode::render(QPainter &painter)
{
    (void)painter;
    drawOpenGLCube(false);
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}
