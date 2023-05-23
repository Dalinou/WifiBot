#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    robot.doConnect();
    robot.Move(120, 120, false, true);
    connect(ui->pushButtonUp, &QPushButton::clicked, this, &MainWindow::onButtonUpClicked); //bouton UP
    connect(ui->pushButton_Down, &QPushButton::clicked, this, &MainWindow::onButtonDownClicked); //bouton DOWN
    connect(ui->pushButton_Right, &QPushButton::clicked, this, &MainWindow::onButtonRightClicked); //bouton RIGHT
    connect(ui->pushButton_Left, &QPushButton::clicked, this, &MainWindow::onButtonLeftClicked); //bouton LEFT
}

MainWindow::~MainWindow()
{
    robot.disConnect();
    delete ui;
}

void MainWindow::onButtonUpClicked()
{
    // Code à exécuter lorsque le bouton Up est cliqué
    robot.Move(120, 120, true, true);
}

void MainWindow::onButtonDownClicked()
{
    // Code à exécuter lorsque le bouton Down est cliqué
    robot.Move(120, 120, false, false);
}

void MainWindow::onButtonRightClicked()
{
    // Code à exécuter lorsque le bouton Right est cliqué
    robot.Move(120, 120, true, false);
}

void MainWindow::onButtonLeftClicked()
{
    // Code à exécuter lorsque le bouton Left est cliqué
    robot.Move(120, 120, false, true);
}

