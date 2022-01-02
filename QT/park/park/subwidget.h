#ifndef SUBWIDGET_H
#define SUBWIDGET_H

#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include <QTimer>
#include <QDateTime>
#include <QTextEdit>
#include <QLineEdit>
#include <QNetworkAccessManager>
#include <QCamera>
#include <QCameraViewfinder>
#include <QCameraImageCapture>
#include <QTextToSpeech>
#include <QTcpSocket>
#include <QMessageBox>
#include "pay.h"

class SubWidget : public QWidget
{
    Q_OBJECT
public:
    explicit SubWidget(QWidget *parent = 0);
    QLabel *lb;
    QLabel *lb1;
    QLabel *lb2;
    QLabel *lb3;
    QLabel *lb_icon;
    QLabel *lb_pix;
    QLabel *lb_gif;
    QLabel *lb_0;
    QTextEdit *text1;
    QLineEdit *le_path;
    //QLineEdit *le_path1;
    QNetworkAccessManager *httpmanager;
    QCamera *camera;
    QCameraViewfinder *vfinder;
    QCameraImageCapture *imageCapture;
    QTextToSpeech *speeker;
    QTcpSocket *mysock;


public slots://申明下面的函数可被信号激发（槽函数）
        void timerUpdate(void);
        void camCaptured(int id, const QImage preview);
        void decode_pix();
        void read_ack(QNetworkReply*);
        void changeSlot();
        void recv_data();
        void send_data();
        void send_1();
        void send_2();
        void send_3();
        void send_4();
        void send_7();



private:
    QPushButton * subButton1;
    QPushButton * subButton2;
    QPushButton * subButton3;
    QPushButton * subButton4;
    QPushButton * subButton5;
    QPushButton * subButton6;
    QPushButton * subButton7;
    QPushButton * btn_decode;
    payWidget payWin;
private slots:
    void topaySlot();
   // void tosubSlot();

};

#endif // SUBWIDGET_H
