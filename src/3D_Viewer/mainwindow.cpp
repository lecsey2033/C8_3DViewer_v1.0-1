#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);
  ui->radioButton_2->setChecked(true);

  screencast = new QTimer(this);
  screencast->setInterval(100);
  connect(screencast, SIGNAL(timeout()), this, SLOT(creategif()));

  settings = new QSettings("dejaneom", "interface", this);
  loadSettings();
}

MainWindow::~MainWindow() {
  saveSettings();
  delete ui;
}

void MainWindow::on_object_activated(int index) {
  initializeWidget();
  this->ui->lineEdit->setText("");

  std::string filename;
  if (index == 0) {
    filename = "../../../../obj_files/cube.obj";
  } else if (index == 1) {
    filename = "../../../../obj_files/guitar.obj";
  } else if (index == 2) {
    filename = "../../../../obj_files/deer.obj";
  } else if (index == 3) {
    filename = "../../../../obj_files/piranha.obj";
  } else if (index == 4) {
    filename = "../../../../obj_files/plane.obj";
  }
  char *c = const_cast<char *>(filename.c_str());
  obj_parcer(c, &this->ui->widget->objdata);
  this->ui->widget->Z = (-2.8) * this->ui->widget->objdata.max;

  filename.erase(0, 13);
  strdata = QString::fromStdString(filename);
  dataTextEdit(strdata, this->ui->widget->objdata.amount_of_vertexes,
               this->ui->widget->objdata.amount_of_facets);
}

void MainWindow::on_color_clicked() {
  initializeWidget();

  strdata = this->ui->lineEdit->text();
  QString filename = "../../../../obj_files/" + strdata;
  QByteArray tmp = filename.toLocal8Bit();
  const char *str = tmp.data();
  char *c = const_cast<char *>(str);
  obj_parcer(c, &this->ui->widget->objdata);
  this->ui->widget->Z = (-2.8) * this->ui->widget->objdata.max;

  dataTextEdit(strdata, this->ui->widget->objdata.amount_of_vertexes,
               this->ui->widget->objdata.amount_of_facets);
}

void MainWindow::on_X_valueChanged(double arg1) { this->ui->widget->X = arg1; }

void MainWindow::on_Y_valueChanged(double arg1) { this->ui->widget->Y = arg1; }

void MainWindow::on_Z_valueChanged(double arg1) {
  this->ui->widget->Z = arg1 * (-1) - 2.8 * this->ui->widget->objdata.max;
}

void MainWindow::on_ScaleX_valueChanged(double arg1) {
  this->ui->widget->ScaleX = arg1;
}

void MainWindow::on_ScaleY_valueChanged(double arg1) {
  this->ui->widget->ScaleY = arg1;
}

void MainWindow::on_ScaleZ_valueChanged(double arg1) {
  this->ui->widget->ScaleZ = arg1;
}

void MainWindow::on_radioButton_clicked(bool checked) {
  if (checked) {
    this->ui->widget->projection = 0;
  }
}

void MainWindow::on_radioButton_2_clicked(bool checked) {
  if (checked) {
    this->ui->widget->projection = 1;
  }
}

void MainWindow::on_type_of_edges_activated(int index) {
  if (index == 0) {
    this->ui->widget->line_stipple = 0;
  } else {
    this->ui->widget->line_stipple = 1;
  }
}

void MainWindow::on_doubleSpinBox_3_valueChanged(double arg1) {
  this->ui->widget->linewidth = arg1;
}

void MainWindow::on_Lred_valueChanged(double arg1) {
  this->ui->widget->Lred = arg1;
}

void MainWindow::on_Lgreen_valueChanged(double arg1) {
  this->ui->widget->Lgreen = arg1;
}

void MainWindow::on_Lblue_valueChanged(double arg1) {
  this->ui->widget->Lblue = arg1;
}

void MainWindow::on_type_of_vertexes_activated(int index) {
  if (index == 0) {
    this->ui->widget->type_of_vertexes = 0;
  } else {
    this->ui->widget->type_of_vertexes = 1;
  }
}

void MainWindow::on_size_of_vertexes_valueChanged(double arg1) {
  this->ui->widget->vertexsize = arg1;
}

void MainWindow::on_Vred_valueChanged(double arg1) {
  this->ui->widget->Vred = arg1;
}

void MainWindow::on_Vgreen_valueChanged(double arg1) {
  this->ui->widget->Vgreen = arg1;
}

void MainWindow::on_Vblue_valueChanged(double arg1) {
  this->ui->widget->Vblue = arg1;
}

void MainWindow::on_BGred_valueChanged(double arg1) {
  this->ui->widget->BGred = arg1;
}

void MainWindow::on_BGgreen_valueChanged(double arg1) {
  this->ui->widget->BGgreen = arg1;
}

void MainWindow::on_BGblue_valueChanged(double arg1) {
  this->ui->widget->BGblue = arg1;
}

void MainWindow::initializeWidget() {
  this->ui->widget->xRot = 0;
  this->ui->widget->yRot = 0;
  this->ui->X->setValue(0.0);
  this->ui->Y->setValue(0.0);
  this->ui->Z->setValue(0.0);
  this->ui->ScaleX->setValue(1.0);
  this->ui->ScaleY->setValue(1.0);
  this->ui->ScaleZ->setValue(1.0);
}

void MainWindow::dataTextEdit(QString strdata, unsigned int vertexes,
                              unsigned int facets) {
  QString vertex = QString::number(vertexes);
  QString facet = QString::number(facets);
  this->ui->textEdit->setText("Название:  " + strdata + "\nКол-во вершин:  " +
                              vertex + "\nКол-во полигонов:  " + facet);
}

void MainWindow::on_image_clicked() {
  QImage image = this->ui->widget->grabFramebuffer();
  strdata.chop(4);
  QString file = QFileDialog::getSaveFileName(this, "Save as...", strdata,
                                              "BMP (*.bmp);; JPEG (*.jpeg)");
  image.save(file);
}

void MainWindow::on_start_clicked() {
  screencast->start();
  QTimer::singleShot(5000, this, SLOT(done()));
}

void MainWindow::creategif() {
  mas_image.push_back(this->ui->widget->grabFramebuffer());
}

void MainWindow::done() {
  QString fileName = QFileDialog::getSaveFileName(
      this, tr("Save screenshot"), "",
      tr("GIF screenshot (*.gif);;GIF screenshot (*.gif)"));
  QGifImage gif(QSize(640, 640));
  QVector<QRgb> ctable;
  ctable << qRgb((int)(this->ui->widget->Vred * 255),
                 (int)(this->ui->widget->Vgreen * 255),
                 (int)(this->ui->widget->Vblue * 255))
         << qRgb((int)(this->ui->widget->Lred * 255),
                 (int)(this->ui->widget->Lgreen * 255),
                 (int)(this->ui->widget->Lblue * 255))
         << qRgb((int)(this->ui->widget->BGred * 255),
                 (int)(this->ui->widget->BGgreen * 255),
                 (int)(this->ui->widget->BGblue * 255));

  gif.setGlobalColorTable(ctable, Qt::black);
  gif.setDefaultTransparentColor(Qt::black);
  gif.setDefaultDelay(100);

  for (QVector<QImage>::Iterator img = mas_image.begin();
       img != mas_image.end(); ++img) {
    gif.addFrame(*img);
  }
  gif.save(fileName);
}

void MainWindow::saveSettings() {
  settings->setValue("object1", this->ui->object->currentIndex());
  settings->setValue("object2", this->ui->lineEdit->text());
  settings->setValue("X", this->ui->X->value());
  settings->setValue("Y", this->ui->Y->value());
  settings->setValue("Z", this->ui->Z->value());
  settings->setValue("ScaleX", this->ui->ScaleX->value());
  settings->setValue("ScaleY", this->ui->ScaleY->value());
  settings->setValue("ScaleZ", this->ui->ScaleZ->value());
  settings->setValue("radiobutton", this->ui->radioButton->isChecked());
  settings->setValue("type_of_edges", this->ui->type_of_edges->currentIndex());
  settings->setValue("doubleSpinBox_3", this->ui->doubleSpinBox_3->value());
  settings->setValue("Lred", this->ui->Lred->value());
  settings->setValue("Lgreen", this->ui->Lgreen->value());
  settings->setValue("Lblue", this->ui->Lblue->value());
  settings->setValue("type_of_vertexes",
                     this->ui->type_of_vertexes->currentIndex());
  settings->setValue("size_of_vertexes", this->ui->size_of_vertexes->value());
  settings->setValue("Vred", this->ui->Vred->value());
  settings->setValue("Vgreen", this->ui->Vgreen->value());
  settings->setValue("Vblue", this->ui->Vblue->value());
  settings->setValue("BGred", this->ui->BGred->value());
  settings->setValue("BGgreen", this->ui->BGgreen->value());
  settings->setValue("BGblue", this->ui->BGblue->value());
  settings->setValue("xRot", this->ui->widget->xRot);
  settings->setValue("yRot", this->ui->widget->yRot);
}

void MainWindow::loadSettings() {
  if (settings->value("object2") == "") {
    this->ui->object->setCurrentIndex(settings->value("object1").toInt());
    on_object_activated(settings->value("object1").toInt());
  } else {
    this->ui->lineEdit->setText(settings->value("object2").toString());
    on_color_clicked();
  }
  this->ui->ScaleX->setValue(settings->value("ScaleX", 1).toDouble());
  this->ui->ScaleY->setValue(settings->value("ScaleY", 1).toDouble());
  this->ui->ScaleZ->setValue(settings->value("ScaleZ", 1).toDouble());
  this->ui->X->setValue(settings->value("X").toDouble());
  this->ui->Y->setValue(settings->value("Y").toDouble());
  this->ui->Z->setValue(settings->value("Z").toDouble());
  this->ui->widget->xRot = settings->value("xRot", 0).toFloat();
  this->ui->widget->yRot = settings->value("yRot", 0).toFloat();
  if (settings->value("radiobutton").toBool()) {
    this->ui->radioButton->setChecked(true);
    on_radioButton_clicked(true);
  }
  this->ui->type_of_edges->setCurrentIndex(
      settings->value("type_of_edges").toInt());
  on_type_of_edges_activated(settings->value("type_of_edges").toInt());
  this->ui->doubleSpinBox_3->setValue(
      settings->value("doubleSpinBox_3").toDouble());
  this->ui->Lred->setValue(settings->value("Lred").toDouble());
  this->ui->Lgreen->setValue(settings->value("Lgreen").toDouble());
  this->ui->Lblue->setValue(settings->value("Lblue", 1).toDouble());
  this->ui->type_of_vertexes->setCurrentIndex(
      settings->value("type_of_vertexes").toInt());
  on_type_of_vertexes_activated(settings->value("type_of_vertexes").toInt());
  this->ui->size_of_vertexes->setValue(
      settings->value("size_of_vertexes").toDouble());
  this->ui->Vred->setValue(settings->value("Vred", 1).toDouble());
  this->ui->Vgreen->setValue(settings->value("Vgreen").toDouble());
  this->ui->Vblue->setValue(settings->value("Vblue").toDouble());
  this->ui->BGred->setValue(settings->value("BGred").toDouble());
  this->ui->BGgreen->setValue(settings->value("BGgreen").toDouble());
  this->ui->BGblue->setValue(settings->value("BGblue").toDouble());
}
