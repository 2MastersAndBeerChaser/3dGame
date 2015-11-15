#pragma once

#include <QWindow>
#include <QOpenGLPaintDevice>
#include <QTime>
#include <memory>
#include <QMouseEvent>
#include "../GL/basescene.h"
#include <QSet>

class Window3D : public QWindow
{
    Q_OBJECT
    Q_DISABLE_COPY(Window3D)

public:
    explicit Window3D(QWindow *parent = 0);
    void setFixedSize(QSize size);
    void pushScene(std::shared_ptr<BaseScene> scene);
    void popScene();

    bool event(QEvent *) override;

signals:
    void ExitReached();

protected:
    void exposeEvent(QExposeEvent *event) override;
    void resizeEvent(QResizeEvent *event) override;
    void showEvent(QShowEvent *event) override;
    virtual void keyPressEvent(QKeyEvent *) override;
    virtual void mouseMoveEvent(QMouseEvent *) override;
    virtual void keyReleaseEvent(QKeyEvent *) override;

private slots:
    void deferRender();
    void render();
    void stopRendering();
    void initRendering();
    void updateScene(BaseScene &scene);
    void HandleMutliKeyPress();

private:
    QTime m_updateTime;
    bool m_canRender = false;
    bool m_updatePending = false;
    std::vector<std::shared_ptr<BaseScene>> m_sceneStack;
    QOpenGLContext *m_pContext = nullptr;
    QSet<Qt::Key> m_pressedKeys;
};
