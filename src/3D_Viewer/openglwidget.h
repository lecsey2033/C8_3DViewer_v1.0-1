#ifndef OPENGLWIDGET_H
#define OPENGLWIDGET_H

#include <QMouseEvent>
#include <QOpenGLWidget>
#include <QTimer>

extern "C" {
#include "../obj_parcer.h"
}

class OpenGLWidget : public QOpenGLWidget {
  Q_OBJECT
public:
  explicit OpenGLWidget(QWidget *parent = 0);

  void initializeGL() override;
  void paintGL() override;
  void resizeGL(int w, int h) override;
  void drawCube();
  void mousePressEvent(QMouseEvent *mo) override;
  void mouseMoveEvent(QMouseEvent *mo) override;

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
