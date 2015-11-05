#include "gameapplication.h"
#include "GL/scenenode.h"
#include "Nodes/cavewall.h"

const QSize FIXED_WINDOW_SIZE(1366, 768);

GameApplication::GameApplication(int argc, char *argv[])
    : QGuiApplication(argc, argv)
{
}

int GameApplication::enterGameLoop()
{
    m_window.setFixedSize(FIXED_WINDOW_SIZE);
    m_window.show();
    connect(&m_window, SIGNAL(activeChanged()), this, SLOT(loadScene()));

    return exec();
}

void GameApplication::loadScene()
{
    disconnect(&m_window, SIGNAL(activeChanged()), this, SLOT(loadScene()));
    CaveGenerator cgen(50, 50, 10);
    m_map = cgen.GetCaveMap();

    auto scene = std::make_shared<BaseScene>();
    scene->camera().setViewport(m_window.size());
    scene->camera().lookAt(QVector3D(0, 30, -5), QVector3D(0, 0, 0), QVector3D(0, 0, 1));

    int x = 0;
    int z = 0;
    for (size_t i = 0; i < m_map.size(); i++, z += 2)
    {
        x = 0;
        for (size_t j = 0; j < m_map[0].size(); j++, x += 2)
        {
            if (m_map[i][j] == 0)
            {
                new ColoredCube(scene.get(), {x, 0, z}, ColoredCube::CaveGround);
            }
            else
            {
                new ColoredCube(scene.get(), {x, 0, z}, ColoredCube::CaveWall);
            }
        }
    }

    m_window.pushScene(scene);
}

