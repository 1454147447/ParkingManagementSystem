#include "mainwidget.h"
#include <QPushButton>
#include <QHBoxLayout>
#include <QTime>
#include <QDateTime>
#include <QMovie>
#include <QString>
#include <QFont>


mainWidget::mainWidget(QWidget *parent)
    : QWidget(parent)
{
    //1.构造控件
    this->setWindowTitle("长江智星智能停车管理系统");
    mainButton = new QPushButton(this);
    mainButton->setText("进入系统");
    mainButton->setFixedSize(300,100);
    mainButton->setIcon(QIcon("D:/code/Qt/park/photo/5.png"));
    mainButton->setIconSize(QSize(70,70));

    //1. 构造所有需要的控件
    lb = new QLabel("长江智星智能停车管理系统");
    lb->setScaledContents(true);
    QFont font = lb->font();
    font.setFamily("KaiTi");//楷体
    lb->setFont(font);
//    lb1 = new QLabel();
//    lb1->setScaledContents(true);

    QLabel *lb_gif = new QLabel();  //主页动图拳头
    lb_gif->setScaledContents(true);
    QMovie *m = new QMovie("D:/code/Qt/park/photo/1.gif");
    m->start();
    lb_gif->setMovie(m);

    QLabel *lb_gif1 = new QLabel();  //主页动图车
    lb_gif1->setScaledContents(true);
    QMovie *m1 = new QMovie("D:/code/Qt/park/photo/10.gif");
    m1->start();
    lb_gif1->setMovie(m1);

    QLabel *lb_gif2 = new QLabel();  //主页动图月球
    lb_gif2->setScaledContents(true);
    lb_gif2->setFixedSize(400,309);
    QMovie *m2 = new QMovie("D:/code/Qt/park/photo/2.gif");
    m2->start();
    lb_gif2->setMovie(m2);

    QLabel *lb_gif3 = new QLabel();  //主页动图地图
    lb_gif3->setScaledContents(true);
    //lb_gif3->setFixedSize(400,309);
    QMovie *m3 = new QMovie("D:/code/Qt/park/photo/7.gif");
    m3->start();
    lb_gif3->setMovie(m3);

    QLabel *lb_gif4 = new QLabel();  //主页动图车
    lb_gif4->setScaledContents(true);
    //lb_gif4->setFixedSize(400,309);
    QMovie *m4 = new QMovie("D:/code/Qt/park/photo/9.gif");
    m4->start();
    lb_gif4->setMovie(m4);

    //2.排版
    QHBoxLayout *first = new QHBoxLayout;
    first->addWidget(lb_gif1,0,Qt::AlignLeft| Qt::AlignCenter);
    first->addWidget(lb,0,Qt::AlignCenter | Qt::AlignCenter);
    first->addWidget(lb_gif2,0,Qt::AlignRight | Qt::AlignCenter);

    QHBoxLayout *second = new QHBoxLayout;
    second->addWidget(lb_gif3,0,Qt::AlignLeft| Qt::AlignBottom);
    second->addWidget(lb_gif,0,Qt::AlignCenter | Qt::AlignCenter);
    second->addWidget(lb_gif4,0,Qt::AlignRight | Qt::AlignBottom);

    QVBoxLayout *hbox = new QVBoxLayout;
    hbox->addLayout(first);
    hbox->addWidget(mainButton,0,Qt::AlignCenter | Qt::AlignBottom);
    hbox->addLayout(second);

    setLayout(hbox);

    //3.前后台挂接
    connect(mainButton,SIGNAL(clicked(bool)),this,SLOT(tosubSlot()));

    //4. 美化
    lb->setStyleSheet("color:white;font-weight:bold;font-size:70px;");
    mainButton->setStyleSheet("QPushButton{"
                              "background: qlineargradient(x1:0, y1:0, x2:1, y2:1, stop:0 white, stop: 0.3 #96e0f6, stop:1 #02154f);"
                               "border-radius: 50px;""color: white;"
                               "font-weight:bold;""font-size:40px;}"
                               "QPushButton:hover{"
                               "background: qlineargradient(x1:0, y1:0, x2:1, y2:1, stop:0 white, stop: 0.3 #96e0f6, stop:1 #02154f);"
                               "border-radius: 50px;""color: white;"
                               "font-weight:bold;""font-size:43px;}"
                             "QPushButton:pressed{"
                             "background: qlineargradient(x1:0, y1:0, x2:1, y2:1, stop:0 white, stop: 0.3 #96e0f6, stop:1 #02154f);"
                             "border-radius: 50px;""color: white;"
                             "font-weight:bold;""font-size:43px;"
                             "padding-left:4px;""padding-top:4px;}");



}



mainWidget::~mainWidget()
{

}

void mainWidget::tosubSlot()
{
    this->hide();
    subWin.show();
}


