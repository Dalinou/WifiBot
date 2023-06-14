#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //robot.doConnect();
    setFocusPolicy(Qt::StrongFocus); // Permettre à la fenêtre de recevoir le focus clavier
    setFocus(); // Définir le focus clavier sur la fenêtre principale

    //robot.Move(120, 120, false, true);
    //Pour gérer les boutons directionnels
    connect(ui->pushButtonUp, &QPushButton::clicked, this, &MainWindow::onButtonUpClicked); //bouton UP
    connect(ui->pushButton_Down, &QPushButton::clicked, this, &MainWindow::onButtonDownClicked); //bouton DOWN
    connect(ui->pushButton_Right, &QPushButton::clicked, this, &MainWindow::onButtonRightClicked); //bouton RIGHT
    connect(ui->pushButton_Left, &QPushButton::clicked, this, &MainWindow::onButtonLeftClicked); //bouton LEFT
    connect(ui->pushButton_STOP, &QPushButton::clicked, this, &MainWindow::onButtonSTOPClicked); //bouton STOP
    //Gestion boutons connexion et deconnexion
    connect(ui->Connexion, &QPushButton::clicked, this, &MainWindow::connexion);
    connect(ui->Deconnexion, &QPushButton::clicked, this, &MainWindow::deconnexion);


    //Pour afficher la Webcam
    displayWebcam();
    //Timer for actualising the captor display captor values
    TimerCaptor = new QTimer();
    // setup signal and slot
    connect(TimerCaptor, SIGNAL(timeout()), this, SLOT(updateCaptorValues())); //Update display

    TimerCaptor->start(250);
}

MainWindow::~MainWindow()
{
    TimerCaptor->stop();
    delete ui;
}

//Gestion des mouvements du robot
//Avec les boutons de l'interface
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

void MainWindow::onButtonSTOPClicked()
{
    // Code à exécuter lorsque le bouton STOP est cliqué
    robot.Move(1, 1, true, true);
}

//Avec les touches du clavier
void MainWindow::keyPressEvent(QKeyEvent* event)
{
    // Récupérer le code de la touche pressée
    int key = event->key();

    // Effectuer des actions en fonction de la touche pressée
    if (key == Qt::Key_Up)
    {
        //lorsque la touche Up est pressée
        robot.Move(120, 120, true, true);
    }
    else if (key == Qt::Key_Down)
    {
        //lorsque la touche Down est pressée
        robot.Move(120, 120, false, false);
    }
    else if (key == Qt::Key_Right)
    {
        //lorsque la touche Right est pressée
         robot.Move(120, 120, true, false);
    }
    else if (key == Qt::Key_Left)
    {
        //lorsque la touche Left est pressée
         robot.Move(120, 120, false, true);
    }
    else if (key == Qt::Key_Space)
    {
        //lorsque la touche Space est pressée
         robot.Move(1, 1, true, true);
    }

    // Passer l'événement au gestionnaire parent
    QMainWindow::keyPressEvent(event);
}

void MainWindow::displayWebcam() //Pour gérer l'affichage de la webcam sur l'interface
{
    QWebEngineView *webView = new QWebEngineView(ui->videoWidget); //Création de l'objet lié au widget videoWidget sur l'interface
    webView->setMinimumSize(341,311); //taille minimum de l'affichage de la Webcam
    webView->load(QUrl("http://192.168.1.106:8080/?action=stream")); // lien du stream de la webcam
}

void MainWindow::updateCaptorValues(){
    ui->lcdNumber_Odometrie1->display(robot.captorValues[3]); //Affichage odométrie gauche
    ui->lcdNumber_Odometrie2->display(robot.captorValues[7]); //Affichage odométrie droite
    ui->lcdNumber_vitesse_gauche->display(robot.captorValues[0]); //Affichage vitesse gauche
    ui->lcdNumber_vitesse_droite->display(robot.captorValues[4]); //Affichage vitesse droite
    ui->progressBarBatterie->setValue(abs(robot.captorValues[8])); //Affichage batterie
    ui->lcdNumberIR_LEFT->display(robot.captorValues[1]); //Affichage IR1 Left
    ui->lcdNumberIR_RIGHT->display(robot.captorValues[5]); //Affichage IR1 Right
}

void MainWindow::connexion(){
    robot.doConnect();
}

void MainWindow::deconnexion(){
    robot.disConnect();
}
