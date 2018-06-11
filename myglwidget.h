#ifndef MYGLWIDGET_H
#define MYGLWIDGET_H

#include <QWidget>
#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QOpenGLVertexArrayObject>
#include <QOpenGLShaderProgram>
#include <QElapsedTimer>
#include <QWheelEvent>
#include <cmath>

class MyGLWidget : public QOpenGLWidget, protected QOpenGLFunctions {
    Q_OBJECT

public:
    explicit MyGLWidget(QWidget *parent = 0);

    void initializeGL();
    void paintGL();
    void resizeGL(int width, int height);

    void keyPressEvent(QKeyEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void wheelEvent(QWheelEvent *event);

signals:
    void updateLabelC(QString);
    void updateLabelZoom(QString);
    void updateLabelOffset(QString);

private:
    // Rendering
    GLuint m_vbo;
    QOpenGLVertexArrayObject m_vao;
    QOpenGLShaderProgram *m_program;

    // Interaction
    QPoint m_lastMouse;
    QVector2D m_offset;
    float m_zoom;

    // System Uniforms
    QVector2D m_resolution;
    QElapsedTimer m_timer;
};

#endif // MYGLWIDGET_H
