// myrobot.cpp

#include "myrobot.h"
#include <QThread>

MyRobot::MyRobot(QObject *parent) : QObject(parent) {
    DataToSend.resize(9);
    DataToSend[0] = 0xFF;
    DataToSend[1] = 0x07;
    DataToSend[2] = 0x0;
    DataToSend[3] = 0x0;
    DataToSend[4] = 0x0;
    DataToSend[5] = 0x0;
    DataToSend[6] = 0x0;
    DataToSend[7] = 0x0;
    DataToSend[8] = 0x0;
    DataReceived.resize(21);
    TimerEnvoi = new QTimer();
    // setup signal and slot
    connect(TimerEnvoi, SIGNAL(timeout()), this, SLOT(MyTimerSlot())); //Send data to wifibot timer
}


void MyRobot::doConnect() {
    socket = new QTcpSocket(this); // socket creation
    connect(socket, SIGNAL(connected()),this, SLOT(connected()));
    connect(socket, SIGNAL(disconnected()),this, SLOT(disconnected()));
    connect(socket, SIGNAL(bytesWritten(qint64)),this, SLOT(bytesWritten(qint64)));
    connect(socket, SIGNAL(readyRead()),this, SLOT(readyRead()));
    qDebug() << "connecting..."; // this is not blocking call
    //socket->connectToHost("LOCALHOST", 15020);
    socket->connectToHost("192.168.1.106", 15020); // connection to wifibot
    // we need to wait...
    if(!socket->waitForConnected(5000)) {
        qDebug() << "Error: " << socket->errorString();
        return;
    }
    TimerEnvoi->start(75);
}

void MyRobot::disConnect() {
    TimerEnvoi->stop();
    socket->close();
}

void MyRobot::connected() {
    qDebug() << "connected..."; // Hey server, tell me about you.
}

void MyRobot::disconnected() {
    qDebug() << "disconnected...";
}

void MyRobot::bytesWritten(qint64 bytes) {
    qDebug() << bytes << " bytes written...";
}

void MyRobot::readyRead() {
    QThread::sleep(1);
    qDebug() << "reading..."; // read the data from the socket
    DataReceived = socket->readAll();
    emit updateUI(DataReceived);
    qDebug() << DataReceived;
    //Left
    int SpeedFront=(int)((DataReceived[1] << 8) + DataReceived[0]);
    if (SpeedFront > 32767) SpeedFront-=65536;
    int BatLevel=DataReceived[2];
    int IR=DataReceived[3];
    int IR2=DataReceived[4];
    int odometry=((((long)DataReceived[8] << 24))+(((long)DataReceived[7] << 16))+(((long)DataReceived[6] << 8))+((long)DataReceived[5]));
    qDebug() << "Left speed:" << SpeedFront << "\tIR:" << IR << "\tIR2:" << IR2 << "\todométrie:" << odometry;
    //Right
    SpeedFront=(int)(DataReceived[10] << 8) + DataReceived[9];
    if (SpeedFront > 32767) SpeedFront=SpeedFront-65536;
    IR=DataReceived[11];
    IR2=DataReceived[12];
    odometry=((((long)DataReceived[16] << 24))+(((long)DataReceived[15] << 16))+(((long)DataReceived[14] << 8))+((long)DataReceived[13]));
    qDebug() << "Right speed:" << SpeedFront << "\tIR:" << IR << "\tIR2:" << IR2 << "\todométrie:" << odometry;
    int Current=DataReceived[17];
    int Version=DataReceived[18];
    qDebug() << "bat : " << BatLevel << "\tCurrent:" << Current << "\tVersion:" << Version;



}

void MyRobot::MyTimerSlot() {
    qDebug() << "Timer...";
    while(Mutex.tryLock());
    socket->write(DataToSend);
    Mutex.unlock();
}

void MyRobot::TestConnection(){
    qDebug() << "writting...";
    DataToSend = "init";
    socket->write(DataToSend);
    qDebug() << "reading..."; // read the data from the socket
    DataReceived = socket->readAll();
    qDebug() << DataReceived;
    DataReceived = socket->readAll();
    qDebug() << DataReceived;
}
short MyRobot::Crc16(unsigned char *Adresse_tab , unsigned char Taille_max)
{
    unsigned int Crc = 0xFFFF;
    unsigned int Polynome = 0xA001;
    unsigned int CptOctet = 0;
    unsigned int CptBit = 0;
    unsigned int Parity= 0;
    Crc = 0xFFFF;
    Polynome = 0xA001;
    for ( CptOctet= 1 ; CptOctet < Taille_max ; CptOctet++)
    {
        Crc ^= *( Adresse_tab + CptOctet);
        for ( CptBit = 0; CptBit <= 7 ; CptBit++)
        {
            Parity= Crc;
            Crc >>= 1;
            if (Parity%2 == true) Crc ^= Polynome;
        }
    }
    return(Crc);
}

void MyRobot::WriteData(unsigned char *Adresse_tab){
    for (int i=0;i<9;i++){
        DataToSend[i] = Adresse_tab[i];
    }
}
void MyRobot::Move(unsigned short leftSpeed, unsigned short rightSpeed, bool leftForward, bool rightForward){
    unsigned char sbuf[9];
    sbuf[0]=0xFF;
    sbuf[1]=0x07;
    sbuf[6]=0;
    if (leftSpeed!=0){
        sbuf[2]=(char)leftSpeed;
        sbuf[3]=(char)(leftSpeed>>8);
        if (leftForward){
            sbuf[6] += 64;
        }
    }
    if (rightSpeed!=0){
        sbuf[4]=(char)rightSpeed;
        sbuf[5]=(char)(rightSpeed>>8);
        if (rightForward){
            sbuf[6] += 16;
        }
    }

    unsigned short crc = Crc16(sbuf,7);
    qDebug() << crc;
    sbuf[7]=(char)crc;
    sbuf[8]=(char)(crc>>8);

    WriteData(sbuf);
}
