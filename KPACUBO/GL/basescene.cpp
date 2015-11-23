#include "basescene.h"
#include <QColor>
#include <qopengl.h>
#include "glhelper.h"
#include <QPainter>

static float Z_NEAR = 0.02f;
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
    glShadeModel(GL_FLAT);
    glShadeModel(GL_SMOOTH);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glEnable(GL_MULTISAMPLE);
    glCullFace(GL_BACK);
    glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
    glLineWidth(2);
    glEnable(GL_LINE_SMOOTH);
    glEnable(GL_NORMALIZE);

    GLfloat light0_diffuse[] = {0.5f, 0.5f, 0.5f, 1.0f};
    GLfloat light0_direction[] = {0.0f, 100.0f, 100.0f, 0.0f};
    GLfloat light_ambient[] = {0.1f, 0.1f, 0.1f, 1.0f};
    //glEnable(GL_LIGHT1);
    glLightfv (GL_LIGHT0, GL_AMBIENT, light_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light0_diffuse);
    glLightfv(GL_LIGHT0, GL_POSITION, light0_direction);
    glEnable(GL_COLOR_MATERIAL);
    glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    //glDisable(GL_LIGHT0);
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
