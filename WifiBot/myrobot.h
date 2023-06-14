#ifndef MYROBOT_H
#define MYROBOT_H
#include <QObject>
#include <QTcpSocket>
#include <QAbstractSocket>
#include <QDebug>
#include <QTimer>
#include <QMutex>

class MyRobot : public QObject {
    Q_OBJECT
public:
    explicit MyRobot(QObject *parent = 0);
    void doConnect();
    void disConnect();
    QByteArray DataToSend;
    QByteArray DataReceived;
    QMutex Mutex;
    int captorValues[11];

signals:
    void updateUI(const QByteArray Data);
public slots:
    void connected();
    void disconnected();
    void bytesWritten(qint64 bytes);
    void readyRead();
    void MyTimerSlot();
    void TestConnection();
    short Crc16(unsigned char *Adresse_tab , unsigned char Taille_max);
    void WriteData(unsigned char *Adresse_tab);
    void Move(unsigned short leftSpeed, unsigned short rightSpeed,bool leftForward, bool rightForward);
private:
    QTcpSocket *socket;
    QTimer *TimerEnvoi;
};

#endif // MYROBOT_H
