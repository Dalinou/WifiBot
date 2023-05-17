#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    robot.doConnect();
    robot.Move(120, 120, false, true);
}

MainWindow::~MainWindow()
{
    robot.disConnect();
    delete ui;
}

