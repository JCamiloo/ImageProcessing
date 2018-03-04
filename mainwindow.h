#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include <colortransformation.h>
#include <noise.h>
#include <QPixmap>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsPixmapItem>
#include <QApplication>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void activateFunctions();
    void deactivateFunctions();
    void showImage(QImage);

private slots:
    void on_radioButtonRGBtoHSL_clicked();
    void on_radioButtonRGBtoHSV_clicked();
    void on_pushButtonLoadImage_clicked();
    void on_pushButtonSaveImage_clicked();
    void on_radioButtonMeanFilter_clicked();
    void on_radioButtonMedianFilter_clicked();
    void on_radioButtonGaussianFilter_clicked();

private:
    Ui::MainWindow *ui;
    ColorTransformation* transform;
    noise* smooth;
    QImage image;
    QGraphicsScene* scene;
    QGraphicsView* view;
    QGraphicsPixmapItem* item;
};

#endif // MAINWINDOW_H
