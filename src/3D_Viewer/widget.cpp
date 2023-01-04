#include "widget.h"

Widget::Widget(QWidget *parent)
    : QOpenGLWidget(parent)
{
}

Widget::~Widget()
{
}

void Widget::initializeGL()
{
    setWindowTitle("Cube");
    setGeometry(400, 200, 800, 600);
}

void Widget::resizeGL(int w, int h)
{
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
//    glOrtho(-1, 1, -1, 1, 1, 2);
    glFrustum(-1, 1, -1, 1, 1, 2);
}

double arr[] = {0, 0, -1.5, 1, 0, -1.5, 0, 1, -1.5};

void Widget::paintGL()
{
    glClearColor(0, 1, 0, 0);
    glClear(GL_COLOR_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glVertexPointer(3, GL_DOUBLE, 0, &arr);
    glEnableClientState(GL_VERTEX_ARRAY);
    glColor3d(1, 0, 0);
    glDrawArrays(GL_TRIANGLES, 0, 3);
    glDisableClientState(GL_VERTEX_ARRAY);
}
