#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include <colortransformation.h>
#include <noise.h>
#include <morphological.h>
#include <QPixmap>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsPixmapItem>
#include <QApplication>
#include <histogram.h>
#include <QtCharts>
#include <QBarSeries>
#include <QBarSet>
#include <QChartView>

using namespace QtCharts;

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

private:
    Ui::MainWindow *ui;
    ColorTransformation* transform;
    noise* smooth;
    histogram* Histogram;
    QImage image;
    morphological* morpho;
    QGraphicsScene* scene;
    QGraphicsView* view;
    QGraphicsPixmapItem* item;
    QChart *chart = new QChart();
    QBarCategoryAxis *axis = new QBarCategoryAxis();
    QChartView *chartView = new QChartView(chart);
    QMainWindow window;

private slots:
    void on_radioButtonRGBtoHSL_clicked();
    void on_radioButtonRGBtoHSV_clicked();
    void on_pushButtonLoadImage_clicked();
    void on_pushButtonSaveImage_clicked();
    void on_radioButtonMeanFilter_clicked();
    void on_radioButtonMedianFilter_clicked();
    void on_radioButtonGaussianFilter_clicked();
    void on_radioButtonHistogram_clicked();
    void on_radioButtonEqualize_clicked();
    void on_radioButtonIsodata_clicked();
    void on_radioButtonOtsu_clicked();
    void on_radioButtonErosion_clicked();
    void on_radioButtonDilate_clicked();
    void on_radioButtonOpening_clicked();
    void on_radioButtonClosing_clicked();
    void on_radioButtonEquHistogram_clicked();
    void on_radioButtonGSGradient_clicked();
    void on_radioButtonGSTopHat_clicked();
    void on_radioButtonGSErosion_clicked();
    void on_radioButtonGSDilate_clicked();
    void on_radioButtonGSOpening_clicked();
    void on_radioButtonGSClosing_clicked();
};

#endif // MAINWINDOW_H
