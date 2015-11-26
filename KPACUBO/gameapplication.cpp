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
    connect(&m_window, &Window3D::ExitReached, this, &GameApplication::nextFloor);
    return exec();
}

void GameApplication::loadScene()
{
    disconnect(&m_window, &QWindow::activeChanged, this, &GameApplication::loadScene);
    CaveGenerator cgen(MAP_SIZE, MAP_SIZE, 10);
    m_map = cgen.GetCaveMap();
    ObjectsGenerator ogen(m_map);
    m_map = ogen.GenerateObj();

    std::shared_ptr<BaseScene> scene = std::make_shared<BaseScene>();
    scene->camera().setViewport(m_window.size());

    new ColoredCube(scene.get(), {0, 0, 0}, ColoredCube::WallType::CaveGround);
    new SkyBox(scene.get());

    int x = 0;
    int z = 0;
    for (size_t i = 0; i < MAP_SIZE; i++, z += WALL_LEN)
    {
        x = 0;
        for (size_t j = 0; j < MAP_SIZE; j++, x += WALL_LEN)
        {
            if (m_map[i][j] == WALL_CELL)
            {
                new ColoredCube(scene.get(), {x, 0, z}, ColoredCube::WallType::CaveWall);
            }
            else if (m_map[i][j] == ENTERANCE_CELL)
            {
                m_player = new PlayerNode(scene.get(), QVector2D(x, z));
            }
            else if (m_map[i][j] == SIDE_EXIT_CELL)
            {
                m_exit = new ExitNode(scene.get(), QVector2D(x, z));
            }
            else if (m_map[i][j] == GROUND_EXIT_CELL)
            {

            }
        }
    }

    scene->setPlayer(m_player);
    scene->setExit(m_exit);
    QVector2D pos = m_player->GetCoords();
    //scene->camera().lookAt(QVector3D(pos.x(), CAM_UP, pos.y() - CAM_RANGE), QVector3D(pos.x(), CAM_UP_ANGLE, pos.y()), QVector3D(0, 0, 1));

    CollisionHandler colHandler;
    colHandler.SetMap(m_map);
    colHandler.SetCoord(pos);
    m_window.SetCollisionHandler(colHandler);

    m_window.pushScene(scene);
}

void GameApplication::nextFloor()
{
    //qDebug() << "HOROSHO RABOTAET";
    loadScene();
}
