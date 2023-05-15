#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QCamera>
#include <QCameraImageCapture>
#include <QCameraViewfinder>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    camera = new QCamera(this);
    cameraView = new QCameraViewfinder(this);
    camera->setViewfinder(cameraView);
    camera->start();
}

MainWindow::~MainWindow()
{
    delete ui;
}

