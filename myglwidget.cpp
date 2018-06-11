#include "myglwidget.h"
#include <iostream>

MyGLWidget::MyGLWidget(QWidget *parent) : QOpenGLWidget(parent) {
    m_offset = QVector2D(0.0, 0.0);
    m_lastMouse = QPoint(0.0, 0.0);
    m_zoom = 1.0;
}

void MyGLWidget::initializeGL() {
    initializeOpenGLFunctions();
    glClearColor(0.25, 0.25, 0.25, 1.0);

    float vertex_data[] = {
        -1.0, -1.0,     // bottom left
        1.0, -1.0,      // bottom right
        1.0, 1.0,       // top right
        1.0, 1.0,       // top right
        -1.0, 1.0,      // top left
        -1.0, -1.0      // bottom left
    };

    m_program = new QOpenGLShaderProgram;
    m_program->addShaderFromSourceFile(QOpenGLShader::Vertex, ":/default.vert");
    m_program->addShaderFromSourceFile(QOpenGLShader::Fragment, ":/julia.frag");
    m_program->link();

    m_program->bind();

    m_vao.create();
    m_vao.bind();
    glGenBuffers(1, &m_vbo);
    glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertex_data), vertex_data, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    m_program->release();

    m_timer.start();
}

void MyGLWidget::resizeGL(int width, int height) {
    m_resolution = QVector2D(width, height);
}

void MyGLWidget::paintGL() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_CULL_FACE);

    //float delta_t = m_timer.restart();
    QVector2D c = (QVector2D(m_lastMouse) / m_resolution) * 2.0 - QVector2D(1.0, 1.0);
    emit updateLabelC("c = " + QString::number(c.x()) + " + " + QString::number(c.y()) + "i");

    m_vao.bind();
    m_program->bind();

    m_program->setUniformValue("u_resolution", m_resolution);
    m_program->setUniformValue("u_c", c);
    m_program->setUniformValue("u_offset", m_offset/pow(m_zoom, 1.5));
    m_program->setUniformValue("u_zoom", (float)(1.0 / pow(m_zoom, 1.5)));
    m_program->setUniformValue("u_iterations", 200);

    glDrawArrays(GL_TRIANGLES, 0, 6);

    m_program->release();

    update();
}

// Input & Interaction
void MyGLWidget::keyPressEvent(QKeyEvent *event) {
    if (event->key() == Qt::Key_W || event->key() == Qt::Key_Up)
        m_offset.setY(m_offset.y() + 0.01);
    if (event->key() == Qt::Key_S || event->key() == Qt::Key_Down)
        m_offset.setY(m_offset.y() - 0.01);
    if (event->key() == Qt::Key_A || event->key() == Qt::Key_Left)
        m_offset.setX(m_offset.x() - 0.01);
    if (event->key() == Qt::Key_D || event->key() == Qt::Key_Right)
        m_offset.setX(m_offset.x() + 0.01);

    if (event->key() == Qt::Key_R) {
        m_lastMouse = QPoint(0.0, 0.0);
        m_offset = QVector2D(0.0, 0.0);
        m_zoom = 1.0;
    }

    event->accept();
}

void MyGLWidget::wheelEvent(QWheelEvent *event) {
    m_zoom += event->delta() / 120;
    m_zoom = std::max(m_zoom, (float)1.0);

    emit updateLabelZoom("Zoom: " + QString::number(m_zoom));

    event->accept();
}


void MyGLWidget::mousePressEvent(QMouseEvent *event) {
    if (event->buttons() & Qt::LeftButton) {
        m_lastMouse = event->pos();
    }

    event->accept();
}

void MyGLWidget::mouseMoveEvent(QMouseEvent *event) {
    if (event->buttons() & Qt::LeftButton) {
        m_lastMouse = event->pos();
    }

    event->accept();
}


