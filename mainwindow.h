#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include <colortransformation.h>

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

private slots:
    void on_radioButtonRGBtoHSL_clicked();
    void on_radioButtonRGBtoHSV_clicked();
    void on_pushButtonLoadImage_clicked();
    void on_pushButtonSaveImage_clicked();


    void on_radioButton_3_clicked();

    void on_radioButton_4_clicked();

private:
    Ui::MainWindow *ui;
    ColorTransformation* transform;
    QImage image;



};

#endif // MAINWINDOW_H
