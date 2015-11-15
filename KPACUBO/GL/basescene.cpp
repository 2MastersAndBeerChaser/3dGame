#include "basescene.h"
#include <QColor>
#include <qopengl.h>
#include "glhelper.h"
#include <QPainter>

static float Z_NEAR = 0.02;
static float Z_FAR = 1000.0;

BaseScene::BaseScene(QSize viewportSize)
    : SceneNode()
    , m_camera(viewportSize)
    , m_clearColor(Qt::black)
    , m_player(nullptr)
    , m_exit(nullptr)
{
}

BaseScene::~BaseScene()
{
}

QColor BaseScene::clearColor()
{
    return m_clearColor;
}

void BaseScene::setClearColor(QColor const& clearColor)
{
    m_clearColor = clearColor;
}

void BaseScene::setViewport(QSize viewport)
{
    glViewport(0, 0, viewport.width(), viewport.height());

    QMatrix4x4 proj;
    proj.perspective(90, float(viewport.width()) / viewport.height(), Z_NEAR, Z_FAR);
    GLHelper::setProjectionMatrix(proj);

    m_camera.setViewport(viewport);
    GLHelper::dumpIfError();
}

void BaseScene::setPlayer(PlayerNode *player)
{
    m_player = player;
}

void BaseScene::setExit(ExitNode *exit)
{
    m_exit = exit;
}

void BaseScene::advance(int64_t msec)
{
    (void)msec;
}

void BaseScene::render(QPainter &painter)
{
    (void)painter;
    glClearColor(m_clearColor.redF(), m_clearColor.greenF(), m_clearColor.blueF(), m_clearColor.alphaF());
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glEnable(GL_LIGHT0);
    glCullFace(GL_BACK);
    glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
    glLightModelf(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);
    glLineWidth(2);
    glEnable(GL_LINE_SMOOTH);
    glEnable(GL_NORMALIZE);

    GLfloat light0_diffuse[] = {1, 1, 100, 1};
    GLfloat light0_direction[] = {50.0, 0.0, 0.0, 0.0};
    glEnable(GL_LIGHT0);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light0_diffuse);
    glLightfv(GL_LIGHT0, GL_POSITION, light0_direction);
    GLHelper::dumpIfError();
}

void BaseScene::onPush()
{
    visit([](SceneNode &node) {
        node.onExitScene();
    });
}

void BaseScene::onPop()
{
    visit([](SceneNode &node) {
        node.onExitScene();
    });
}

SceneCamera &BaseScene::camera()
{
    return m_camera;
}

const SceneCamera &BaseScene::camera() const
{
    return m_camera;
}

PlayerNode *BaseScene::player() const
{
    return m_player;
}

ExitNode *BaseScene::exit() const
{
    return m_exit;
}
