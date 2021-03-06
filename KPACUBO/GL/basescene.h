#pragma once

#include "scenenode.h"
#include "scenecamera.h"
#include "../Nodes/playernode.h"
#include "../Nodes/exitnode.h"
#include <QColor>
//#include "glut.h"

class BaseScene : public SceneNode
{
    Q_OBJECT
    Q_DISABLE_COPY(BaseScene)
public:
    BaseScene(QSize viewportSize = QSize(0, 0));
    ~BaseScene();

    QColor clearColor();
    void setClearColor(const QColor &clearColor);

    void setViewport(QSize viewport);
    void setPlayer(PlayerNode *player);
    void setExit(ExitNode *exit);
    void advance(int64_t msec) override;
    void render(QPainter &painter) override;
    void onPush();
    void onPop();

    SceneCamera &camera();
    SceneCamera const& camera() const;
    PlayerNode* player() const;
    ExitNode* exit() const;

private:
    SceneCamera m_camera;
    QColor m_clearColor;
    PlayerNode *m_player;
    ExitNode *m_exit;
};
