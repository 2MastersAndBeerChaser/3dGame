#include "skybox.h"
#include <QPainter>
#include <QDebug>

void SkyBox::Draw()
{

}

SkyBox::SkyBox(SceneNode *parent)
    : SceneNode(parent)
{
}

void SkyBox::advance(int64_t msec)
{
    (void)msec;
}

void SkyBox::render(QPainter &painter)
{
    (void)painter;
    Draw();
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}
