#include "openglwidget.h"

OpenGLWidget::OpenGLWidget(QWidget *parent) :
    QOpenGLWidget(parent)
{
    this->ScaleX = 1;
    this->ScaleY = 1;
    this->ScaleZ = 1;
    this->projection = 1;
    this->line_stipple = 0;
    this->linewidth = 0;
    this->Lred = 0;
    this->Lgreen = 0;
    this->Lblue = 1;
    this->vertexsize = 0;
    this->Vred = 1;
    this->Vgreen = 0;
    this->Vblue = 0;
    this->type_of_vertexes = 0;
    this->BGred = 0;
    this->BGgreen = 0;
    this->BGblue = 0;

    char c[24] = "../obj_files/cube.obj";
    obj_parcer(c, &this->objdata);

    this->X = 0;
    this->Y = 0;
    this->Z = (-2.8) * objdata.max;

    connect(&timer, SIGNAL(timeout()), this, SLOT(update()));
    timer.start(16);
}

void OpenGLWidget::initializeGL()
{
    glEnable(GL_DEPTH_TEST);
}

void OpenGLWidget::paintGL()
{
    glClearColor(BGred, BGgreen, BGblue, 1);
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    if (!projection) {
        glOrtho(-objdata.max, objdata.max, -objdata.max, objdata.max, objdata.max, 5 * objdata.max);
    } else {
        glFrustum(-objdata.max, objdata.max, -objdata.max, objdata.max, objdata.max, 5 * objdata.max);
    }

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glScaled(ScaleX, ScaleY, ScaleZ);
    glTranslated(X, Y, Z);
    glRotated(xRot, 1, 0, 0);
    glRotated(yRot, 0, 1, 0);

    drawCube();
}

void OpenGLWidget::resizeGL(int w, int h)
{
    glViewport(0, 0, w, h);
}

void OpenGLWidget::drawCube()
{

    glVertexPointer(3, GL_DOUBLE, 0, objdata.vertexes_array);
    glEnableClientState(GL_VERTEX_ARRAY);

    if (type_of_vertexes) {
        glEnable(GL_POINT_SMOOTH);
    }
        glColor3d(Vred, Vgreen, Vblue);
        glDrawArrays(GL_POINTS, 0, objdata.amount_of_vertexes);
        glPointSize(vertexsize);
    glDisable(GL_POINT_SMOOTH);

    if (line_stipple == 1) {
        glEnable(GL_LINE_STIPPLE);
        glLineStipple(2,0X00FF);
    }
        glColor3d(Lred, Lgreen, Lblue);
        glDrawElements(GL_LINES, objdata.count_of_vertexes_in_facets, GL_UNSIGNED_INT, objdata.indexes_array);
        glLineWidth(linewidth);
    glDisable(GL_LINE_STIPPLE);

    glDisableClientState(GL_VERTEX_ARRAY);
}

void OpenGLWidget::mousePressEvent(QMouseEvent* mo)
{
    mPos = mo->pos();
}

void OpenGLWidget::mouseMoveEvent(QMouseEvent* mo)
{
    xRot += 1/M_PI*(mo->pos().y() - mPos.y());
    yRot += 1/M_PI*(mo->pos().x() - mPos.x());
    mPos = mo->pos();
    update();
}
