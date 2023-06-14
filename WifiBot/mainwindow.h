#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "myrobot.h"
#include <QMainWindow>
#include <QWebEngineView>
#include <QWidget>
#include <QKeyEvent>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void displayWebcam();

public slots:
    void onButtonUpClicked();
    void onButtonDownClicked();
    void onButtonRightClicked();
    void onButtonLeftClicked();
    void onButtonSTOPClicked();
    void keyPressEvent(QKeyEvent* event);

private:
    Ui::MainWindow *ui;
    MyRobot robot;
};
#endif // MAINWINDOW_H
