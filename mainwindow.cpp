#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    transform = new ColorTransformation();
    smooth = new noise();
    Histogram = new histogram();
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
           copy = copy.scaled(ui->labelImage->width(),ui->labelImage->height(), Qt::KeepAspectRatio);
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

    if(ui->radioButtonEqualize->isChecked()){
        Histogram->equalizeHistogram(image);
        QImage imageObject;
        QString imagePath = QFileDialog::getSaveFileName(this,tr("Save file"),"",tr("JPEG (*.jpg *.jpeg);;PNG (*.png)" ));
        imageObject.load(imagePath);
        imageObject = Histogram->getEqualizedImage();
        imageObject.save(imagePath);
        showImage(imageObject);
    }

    if(ui->radioButtonIsodata->isChecked()){
        int thres = Histogram->calculateThreshold(ISODATA,image);
        printf("%d",thres);
        Histogram->thresholding(thres,image);
        QImage imageObject;
        QString imagePath = QFileDialog::getSaveFileName(this,tr("Save file"),"",tr("JPEG (*.jpg *.jpeg);;PNG (*.png)" ));
        imageObject.load(imagePath);
        imageObject = Histogram->getThresholdedImage();
        imageObject.save(imagePath);
        showImage(imageObject);
    }

    if(ui->radioButtonOtsu->isChecked()){
        int thres = Histogram->calculateThreshold(OTSU,image);
        printf("%d",thres);
        Histogram->thresholding(thres,image);
        QImage imageObject;
        QString imagePath = QFileDialog::getSaveFileName(this,tr("Save file"),"",tr("JPEG (*.jpg *.jpeg);;PNG (*.png)" ));
        imageObject.load(imagePath);
        imageObject = Histogram->getThresholdedImage();
        imageObject.save(imagePath);
        showImage(imageObject);
    }
}

void MainWindow::deactivateFunctions(){
    ui->radioButtonRGBtoHSL->setEnabled(false);
    ui->radioButtonRGBtoHSV->setEnabled(false);
    ui->radioButtonMeanFilter->setEnabled(false);
    ui->radioButtonMedianFilter->setEnabled(false);
    ui->radioButtonHistogram->setEnabled(false);
    ui->radioButtonGaussianFilter->setEnabled(false);
    ui->pushButtonSaveImage->setEnabled(false);
    ui->radioButtonEqualize->setEnabled(false);
    ui->radioButtonIsodata->setEnabled(false);
    ui->radioButtonOtsu->setEnabled(false);
}

void MainWindow::activateFunctions(){
    ui->radioButtonRGBtoHSL->setEnabled(true);
    ui->radioButtonRGBtoHSV->setEnabled(true);
    ui->radioButtonMeanFilter->setEnabled(true);
    ui->radioButtonMedianFilter->setEnabled(true);
    ui->radioButtonGaussianFilter->setEnabled(true);
    ui->radioButtonHistogram->setEnabled(true);
    ui->radioButtonEqualize->setEnabled(true);
    ui->radioButtonIsodata->setEnabled(true);
    ui->radioButtonOtsu->setEnabled(true);
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

void MainWindow::on_radioButtonHistogram_clicked()
{
    Histogram->calculateHistogram(image);
    int* histogramImage = Histogram->getHistogram();

    QBarSet* set = new QBarSet("Intensity Pixels");
    QStringList categories;

    for (int i = 0; i < 256; i++) {
        categories.append("" + i);
        set->insert(i,histogramImage[i]);
    }

    QBarSeries *series = new QBarSeries();
    series->append(set);

    chart->addSeries(series);
    chart->setTitle("Histogram");
    chart->setAnimationOptions(QChart::SeriesAnimations);

    axis->append(categories);
    chart->createDefaultAxes();

    chartView->setRenderHint(QPainter::Antialiasing);

    window.setCentralWidget(chartView);
    window.resize(420,300);
    window.show();
}


void MainWindow::on_radioButtonEqualize_clicked()
{
    ui->pushButtonSaveImage->setEnabled(true);
}

void MainWindow::on_radioButtonIsodata_clicked()
{
    ui->pushButtonSaveImage->setEnabled(true);
}

void MainWindow::on_radioButtonOtsu_clicked()
{
    ui->pushButtonSaveImage->setEnabled(true);
}
