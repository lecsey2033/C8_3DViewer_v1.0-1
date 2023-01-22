#ifndef OPENGLWIDGET_H
#define OPENGLWIDGET_H

#include <QtOpenGLWidgets/QOpenGLWidget>
#include <QTimer>
#include <QMouseEvent>

extern "C" {
#include "../obj_parcer.h"
}

class OpenGLWidget : public QOpenGLWidget
{
    Q_OBJECT
public:
    explicit OpenGLWidget(QWidget *parent = 0);

    void initializeGL();
    void paintGL();
    void resizeGL(int w, int h);
    void drawCube();
    void mousePressEvent(QMouseEvent*) override;
    void mouseMoveEvent(QMouseEvent*) override;

    float xRot, yRot, zRot;
    double ScaleX, ScaleY, ScaleZ;
    double X, Y, Z;
    int projection;
    int line_stipple, type_of_vertexes;
    float linewidth, vertexsize;
    double Lred, Lgreen, Lblue;
    double Vred, Vgreen, Vblue;
    double BGred, BGgreen, BGblue;
    QPoint mPos;
    obj_data objdata;
private:
    QTimer timer;
};

#endif // OPENGLWIDGET_H
