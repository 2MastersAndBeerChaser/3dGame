#include "window3d.h"
#include <QResizeEvent>
#include <QPainter>
#include <QGuiApplication>
#include "globals.h"

Window3D::Window3D(QWindow *parent)
    : QWindow(parent)
{
    setSurfaceType(QWindow::OpenGLSurface);
    setFlags(Qt::WindowMinimizeButtonHint | Qt::WindowCloseButtonHint);
}

void Window3D::setFixedSize(QSize size)
{
    setMinimumSize(size);
    setMaximumSize(size);
}

void Window3D::pushScene(std::shared_ptr<BaseScene> scene)
{
    m_sceneStack.push_back(scene);
    scene->onPush();
}

void Window3D::popScene()
{
    if (!m_sceneStack.empty())
    {
        m_sceneStack.back()->onPop();
        m_sceneStack.pop_back();
    }
}

bool Window3D::event(QEvent *event)
{
    switch (event->type())
    {
    case QEvent::UpdateRequest:
        m_updatePending = false;
        render();
        return true;
    case QEvent::Close:
        if (m_canRender)
        {
            stopRendering();
        }
        return QWindow::event(event);
    default:
        return QWindow::event(event);
    }
}

void Window3D::SetCollisionHandler(CollisionHandler colHandler)
{
    m_collisionHandler = colHandler;
}

void Window3D::exposeEvent(QExposeEvent *event)
{
    QWindow::exposeEvent(event);
    if (isExposed())
        render();
}

void Window3D::resizeEvent(QResizeEvent *event)
{
    QWindow::resizeEvent(event);
    if (!m_canRender)
    {
        initRendering();
    }
}

void Window3D::showEvent(QShowEvent *event)
{
    QWindow::showEvent(event);
}

void Window3D::deferRender()
{
    if (!m_updatePending) {
        m_updatePending = true;
        QGuiApplication::postEvent(this, new QEvent(QEvent::UpdateRequest));
    }
}

void Window3D::render()
{
    HandleMutliKeyPress();
    if (!m_canRender)
    {
        return;
    }

    m_pContext->makeCurrent(this);
    if (!m_sceneStack.empty())
    {
        updateScene(*m_sceneStack.back());
    }
    else
    {
        glClearColor(1, 1, 1, 0);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
    }

    m_pContext->swapBuffers(this);
    deferRender();
}

void Window3D::stopRendering()
{
    while (!m_sceneStack.empty())
    {
        popScene();
    }
    m_canRender = false;
}

void Window3D::initRendering()
{
    if (!m_pContext) {
        m_pContext = new QOpenGLContext(this);
        m_pContext->setFormat(requestedFormat());
        m_pContext->create();
    }
    m_canRender = true;
    m_updateTime.start();
}

void Window3D::updateScene(BaseScene &scene)
{
    scene.setViewport(size());

    int msec = m_updateTime.elapsed();
    m_updateTime.restart();
    scene.visit([&](SceneNode & node) {
        node.advance(msec);
    });
    scene.camera().advance(msec);

    QOpenGLPaintDevice device(size());
    QPainter painter(&device);
    scene.camera().loadMatrix();
    scene.render(painter);
    scene.visit([&](SceneNode & node) {
        node.render(painter);
    });
}

void Window3D::HandleMutliKeyPress()
{
    if (!m_sceneStack.empty())
    {
        BaseScene &scene = (*m_sceneStack.back());
        QVector2D pos = scene.player()->GetCoords();
        float dx = 0;
        float dy = 0;
        if (m_pressedKeys.contains(Qt::Key_W))
        {
            dy += MOVE_SPEED;
        }
        if (m_pressedKeys.contains(Qt::Key_S))
        {
            dy -= MOVE_SPEED;
        }
        if (m_pressedKeys.contains(Qt::Key_A))
        {
            dx += MOVE_SPEED;
        }
        if (m_pressedKeys.contains(Qt::Key_D))
        {
            dx -= MOVE_SPEED;
        }
//        if (m_collisionHandler.TryMove(dx, dy))
//        {
//            scene.player()->SetMove(dx, dy);
//        }
//        else if (m_collisionHandler.TryMove(dx, 0))
//        {
//            scene.player()->SetMove(dx, 0);
//        }
//        else if (m_collisionHandler.TryMove(0, dy))
//        {
//            scene.player()->SetMove(0, dy);
//        }
        scene.player()->SetMove(dx, dy);
        pos = scene.player()->GetCoords();
        QVector2D posExit = scene.exit()->GetCoords();
        if (pos.y() >= posExit.y() && pos.y() <= posExit.y() + WALL_LEN
                && pos.x() >= posExit.x() && pos.x() <= posExit.x() + WALL_LEN)
        {
            emit Window3D::ExitReached();
        }
        scene.camera().lookAt(QVector3D(pos.x(), CAM_UP, pos.y() - CAM_RANGE), QVector3D(pos.x(), CAM_UP_ANGLE, pos.y()), QVector3D(0, 0, 1));
    }
}

void Window3D::mouseMoveEvent(QMouseEvent *)
{
//    if (!m_sceneStack.empty())
//    {
//        auto &scene = (*m_sceneStack.back());
//        auto q = scene.camera().eye();
//        scene.camera().lookAt(scene.camera().eye(),
//                              scene.camera().eye() + QVector3D(event->y() / 1000.0f, event->x() / 1000.f, 0),
//                              QVector3D(0, 0, 1));
//        auto w = scene.camera().eye();
//        int u = 3;
    //    }
}

void Window3D::keyReleaseEvent(QKeyEvent *event)
{
    m_pressedKeys.remove((Qt::Key)event->key());
}

void Window3D::keyPressEvent(QKeyEvent *event)
{
    m_pressedKeys.insert((Qt::Key)event->key());
}
