#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QOpenGLWidget>

extern "C" {
#include "../obj_parcer.h"
}

class Widget : public QOpenGLWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

    void initializeGL();
    void resizeGL(int w, int h);
    void paintGL();
};
#endif // WIDGET_H
