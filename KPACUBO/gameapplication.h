#pragma once
#include <QGuiApplication>
#include "UI/window3d.h"
#include "GL/scenenode.h"
#include "Nodes/cavewall.h"
#include "Nodes/playernode.h"
#include "Generators/generators.h"
#include "globals.h"
#include "Nodes/exitnode.h"

class GameApplication : public QGuiApplication
{
    Q_OBJECT
public:
    GameApplication(int argc, char *argv[]);

    int enterGameLoop();

private slots:
    void loadScene();
    void nextFloor();

private:
    Window3D m_window;
    std::vector<std::vector<int> > m_map;
    PlayerNode *m_player;
    ExitNode *m_exit;
};
