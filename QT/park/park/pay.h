#ifndef PAY_H
#define PAY_H

#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include <QTcpSocket>
#include <QHostAddress>

class payWidget : public QWidget
{
    Q_OBJECT

public:
    payWidget(QWidget *parent = 0);


    QLabel *lb;
    QTcpSocket *mysock;


public:

    QPushButton * mainButton;

public slots:
    void changeSlot();
    //void send();


};

#endif // PAY_H
