#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    transform = new ColorTransformation();
    smooth = new noise();
    deactivateFunctions();
    //connect(ui->pushButtonLoadImage,SIGNAL(released()),this,SLOT(loadImage()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButtonLoadImage_clicked()
{
    QString filename = QFileDialog::getOpenFileName(this,tr("Choose file"),"",tr("images (*.png *.jpg *.jpeg)"));
    if(QString::compare(filename,QString()) != 0){
       bool valid = image.load(filename);
       if(valid){
           QImage copy = image;
           copy = copy.scaledToWidth(ui->labelImage->width(), Qt::SmoothTransformation);
           ui->route->setText(filename);
           ui->labelImage->setPixmap(QPixmap::fromImage(copy));
           activateFunctions();
       }
    }
}

void MainWindow::on_pushButtonSaveImage_clicked()
{
    if(ui->radioButtonRGBtoHSL->isChecked()){
        transform->RGBtoHSL(image);
        QImage imageObject;
        QString imagePath = QFileDialog::getSaveFileName(this,tr("Save file"),"",tr("JPEG (*.jpg *.jpeg);;PNG (*.png)" ));
        imageObject.load(imagePath);
        imageObject = transform->getHSLImage();
        imageObject.save(imagePath);
        showImage(transform->getBlueImage());
        showImage(transform->getGreenImage());
        showImage(transform->getRedImage());
        showImage(imageObject);
    }

    if (ui->radioButtonRGBtoHSV->isChecked()) {
        transform->RGBtoHSV(image);
        QImage imageObject;
        QString imagePath = QFileDialog::getSaveFileName(this,tr("Save file"),"",tr("JPEG (*.jpg *.jpeg);;PNG (*.png)" ));
        imageObject.load(imagePath);
        imageObject = transform->getHSVImage();
        imageObject.save(imagePath);
        showImage(transform->getBlueImage());
        showImage(transform->getGreenImage());
        showImage(transform->getRedImage());
        showImage(imageObject);
    }

    if(ui->radioButtonMeanFilter->isChecked()){
        smooth->smoothing(MEAN,image);
        QImage imageObject;
        QString imagePath = QFileDialog::getSaveFileName(this,tr("Save file"),"",tr("JPEG (*.jpg *.jpeg);;PNG (*.png)" ));
        imageObject.load(imagePath);
        imageObject = smooth->getDenoisingImage();
        imageObject.save(imagePath);
        showImage(imageObject);
    }

    if(ui->radioButtonMedianFilter->isChecked()){
        smooth->smoothing(MEDIAN,image);
        QImage imageObject;
        QString imagePath = QFileDialog::getSaveFileName(this,tr("Save file"),"",tr("JPEG (*.jpg *.jpeg);;PNG (*.png)" ));
        imageObject.load(imagePath);
        imageObject = smooth->getDenoisingImage();
        imageObject.save(imagePath);
        showImage(imageObject);
    }

    if(ui->radioButtonGaussianFilter->isChecked()){
        smooth->smoothing(GAUSSIAN,image);
        QImage imageObject;
        QString imagePath = QFileDialog::getSaveFileName(this,tr("Save file"),"",tr("JPEG (*.jpg *.jpeg);;PNG (*.png)" ));
        imageObject.load(imagePath);
        imageObject = smooth->getDenoisingImage();
        imageObject.save(imagePath);
        showImage(imageObject);
    }
}

void MainWindow::deactivateFunctions(){
    ui->radioButtonRGBtoHSL->setEnabled(false);
    ui->radioButtonRGBtoHSV->setEnabled(false);
    ui->radioButtonMeanFilter->setEnabled(false);
    ui->radioButtonMedianFilter->setEnabled(false);
    ui->radioButtonGaussianFilter->setEnabled(false);
    ui->pushButtonSaveImage->setEnabled(false);
}

void MainWindow::activateFunctions(){
    ui->radioButtonRGBtoHSL->setEnabled(true);
    ui->radioButtonRGBtoHSV->setEnabled(true);
    ui->radioButtonMeanFilter->setEnabled(true);
    ui->radioButtonMedianFilter->setEnabled(true);
    ui->radioButtonGaussianFilter->setEnabled(true);
}

void MainWindow::showImage(QImage ImageToShow){
    scene = new QGraphicsScene();
    view = new QGraphicsView(scene);
    item = new QGraphicsPixmapItem(QPixmap::fromImage(ImageToShow));
    scene->addItem(item);
    view->show();
}

void MainWindow::on_radioButtonRGBtoHSL_clicked()
{
   ui->pushButtonSaveImage->setEnabled(true);
}

void MainWindow::on_radioButtonRGBtoHSV_clicked()
{
    ui->pushButtonSaveImage->setEnabled(true);
}

void MainWindow::on_radioButtonMeanFilter_clicked()
{
    ui->pushButtonSaveImage->setEnabled(true);
}

void MainWindow::on_radioButtonMedianFilter_clicked()
{
    ui->pushButtonSaveImage->setEnabled(true);
}

void MainWindow::on_radioButtonGaussianFilter_clicked()
{
    ui->pushButtonSaveImage->setEnabled(true);
}
