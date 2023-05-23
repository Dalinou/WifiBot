#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    robot.doConnect();
    //robot.Move(120, 120, false, true);
    //Pour gérer les boutons
    connect(ui->pushButtonUp, &QPushButton::clicked, this, &MainWindow::onButtonUpClicked); //bouton UP
    connect(ui->pushButton_Down, &QPushButton::clicked, this, &MainWindow::onButtonDownClicked); //bouton DOWN
    connect(ui->pushButton_Right, &QPushButton::clicked, this, &MainWindow::onButtonRightClicked); //bouton RIGHT
    connect(ui->pushButton_Left, &QPushButton::clicked, this, &MainWindow::onButtonLeftClicked); //bouton LEFT
    //Pour gérer la
    QWebEngineView *webView = new QWebEngineView(ui->videoWidget);
    webView->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);// Créer une politique de taille pour l'expansion horizontale et verticale
    webView->setMinimumSize(341,311); //taille minimum de l'affichage de la Webcam
    webView->load(QUrl("http://192.168.1.106:8080/?action=stream"));
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

