#pragma once

#include "../GL/scenenode.h"
#include <qopengl.h>
#include "globals.h"

class SkyBox : public SceneNode
{
public:
    SkyBox(SceneNode *parent);
    void Draw();
    void advance(int64_t msec) override;
    void render(QPainter &painter) override;
};
