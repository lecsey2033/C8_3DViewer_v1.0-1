#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "3rdparty/src/gifimage/qgifimage.h"
#include <QFileDialog>
#include <QMainWindow>
#include <QSettings>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
  Q_OBJECT

public:
  MainWindow(QWidget *parent = nullptr);
  ~MainWindow();
  void initializeWidget();
  void dataTextEdit(QString strdata, unsigned int vertexes,
                    unsigned int facets);

  void saveSettings();
  void loadSettings();
  QString strdata;
  QVector<QImage> mas_image;

private slots:
  void on_object_activated(int index);

  void on_X_valueChanged(double arg1);

  void on_Y_valueChanged(double arg1);

  void on_Z_valueChanged(double arg1);

  void on_ScaleX_valueChanged(double arg1);

  void on_ScaleY_valueChanged(double arg1);

  void on_ScaleZ_valueChanged(double arg1);

  void on_radioButton_clicked(bool checked);

  void on_radioButton_2_clicked(bool checked);

  void on_type_of_edges_activated(int index);

  void on_doubleSpinBox_3_valueChanged(double arg1);

  void on_Lred_valueChanged(double arg1);

  void on_Lgreen_valueChanged(double arg1);

  void on_Lblue_valueChanged(double arg1);

  void on_type_of_vertexes_activated(int index);

  void on_size_of_vertexes_valueChanged(double arg1);

  void on_Vred_valueChanged(double arg1);

  void on_Vgreen_valueChanged(double arg1);

  void on_Vblue_valueChanged(double arg1);

  void on_BGred_valueChanged(double arg1);

  void on_BGgreen_valueChanged(double arg1);

  void on_BGblue_valueChanged(double arg1);

  void on_color_clicked();

  void on_image_clicked();

  void on_start_clicked();

  void creategif();

  void done();

private:
  Ui::MainWindow *ui;
  QSettings *settings;
  QTimer *screencast;
};
#endif // MAINWINDOW_H
