#include "gameapplication.h"

const QSize FIXED_WINDOW_SIZE(1366, 768);

GameApplication::GameApplication(int argc, char *argv[])
    : QGuiApplication(argc, argv)
{
}

int GameApplication::enterGameLoop()
{
    m_window.setFixedSize(FIXED_WINDOW_SIZE);
    m_window.show();
    connect(&m_window, &QWindow::activeChanged, this, &GameApplication::loadScene);
//    m_window.popScene();
//    auto scene = std::make_shared<BaseScene>();
//    m_player->SetCoords(QVector2D(0, 0));
//    new PlayerNode(scene.get(), QVector2D(0, 0));
//    m_window.pushScene(scene);
    return exec();
}

void GameApplication::loadScene()
{
    disconnect(&m_window, &QWindow::activeChanged, this, &GameApplication::loadScene);
    CaveGenerator cgen(50, 50, 10);
    m_map = cgen.GetCaveMap();
    ObjectsGenerator ogen(m_map);
    m_map = ogen.GenerateObj();

    auto scene = std::make_shared<BaseScene>();
    scene->camera().setViewport(m_window.size());
    scene->camera().lookAt(QVector3D(0, 300, -10), QVector3D(0, 0, 0), QVector3D(0, 0, 1));

    new ColoredCube(scene.get(), {0, 0, 0}, ColoredCube::WallType::CaveGround);

    int x = 0;
    int z = 0;
    for (size_t i = 0; i < m_map.size(); i++, z += 20)
    {
        x = 0;
        for (size_t j = 0; j < m_map[0].size(); j++, x += 20)
        {
            if (m_map[i][j] == 1)
            {
                new ColoredCube(scene.get(), {x, 0, z}, ColoredCube::WallType::CaveWall);
            }
            else if (m_map[i][j] == 2)
            {
                m_player = new PlayerNode(scene.get(), QVector2D(x, z));
            }
        }
    }

    m_window.pushScene(scene);
}
