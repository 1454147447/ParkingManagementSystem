#include "pay.h"
#include <QVBoxLayout>
#include <QPixmap>

payWidget::payWidget(QWidget *parent) : QWidget(parent)
{
     this->setWindowTitle("长江智星智能停车管理系统");
     this->setFixedSize(540, 540);
     this->setStyleSheet("background-color:#96e0f6");

    mainButton = new QPushButton(this);
    mainButton->setText("关闭");
    mainButton->setFixedSize(150,60);
    mainButton->setIcon(QIcon("D:/code/Qt/park/photo/5.png"));
    mainButton->setIconSize(QSize(60,60));

    //mysock = new QTcpSocket;//套接字


     lb = new QLabel;//二维码
     lb->setFixedSize(400,400);
     lb->setScaledContents(true);
     lb->setPixmap(QPixmap("D:/code/Qt/park/photo/pay.png"));

     //排版
     QVBoxLayout *vbox = new QVBoxLayout;
     vbox->addWidget(lb,0,Qt::AlignCenter | Qt::AlignCenter);
     vbox->addWidget(mainButton,0,Qt::AlignCenter | Qt::AlignCenter);
     setLayout(vbox);

     //连接
     //connect(mainButton, SIGNAL(clicked(bool)), this, SLOT(send()));
     connect(mainButton,SIGNAL(clicked()),this,SLOT(changeSlot()));


     //美化

     mainButton->setStyleSheet("QPushButton{"
                               "background: qlineargradient(x1:0, y1:0, x2:1, y2:1, stop:0 white, stop: 0.3 #96e0f6, stop:1 #02154f);"
                               "border-radius: 30px;"
                               "color: white;"
                               "font-weight:bold;"
                               "font-size:25px;}"
                               "QPushButton:hover{"
                               "background: qlineargradient(x1:0, y1:0, x2:1, y2:1, stop:0 white, stop: 0.3 #96e0f6, stop:1 #02154f);"
                               "border-radius: 30px;"
                               "color: white;"
                               "font-weight:bold;"
                               "font-size:28px;}"
                               "QPushButton:pressed{"
                               "background: qlineargradient(x1:0, y1:0, x2:1, y2:1, stop:0 white, stop: 0.3 #96e0f6, stop:1 #02154f);"
                               "border-radius: 30px;"
                               "color: white;"
                               "font-weight:bold;"
                               "font-size:28px;"
                               "padding-left:4px;"
                               "padding-top:4px;}");

}

void payWidget::changeSlot()
{
    this->close();
}

//void payWidget::send()
//{
//    mysock->write("6");
//}
