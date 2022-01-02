#include "subwidget.h"
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QTime>
#include <QDateTime>
#include <QCameraInfo>
#include <QBuffer>
#include <QFileDialog>
#include <QNetworkRequest>
#include <QFile>
#include <QNetworkReply>
#include <QUrl>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QHostAddress>
#include <QGridLayout>
#include <QCameraInfo>
#include <QBuffer>
#include <QMovie>
#include <QFont>


SubWidget::SubWidget(QWidget *parent) : QWidget(parent)
{
     //1. 构造所有需要的控件
     this->setWindowTitle("长江智星智能停车管理系统");
     this->setWindowState(Qt::WindowMaximized);//窗口大小
     this->setWindowFlags(Qt::FramelessWindowHint);//设置窗体无边框
     //this->setWindowOpacity(0.7);

     //设置子窗体背景
     QPalette palette;
     QPixmap pixmap("D:/code/Qt/park/photo/0.png");
     this->setAutoFillBackground(true);
     palette.setBrush(QPalette::Window, QBrush(pixmap));
     this->setPalette(palette);
     //设置按钮
     subButton1 = new QPushButton("停车");
     subButton2 = new QPushButton("取车");
     subButton3 = new QPushButton("查询");
     subButton4 = new QPushButton("返回");
     subButton5 = new QPushButton("退出");
     subButton6 = new QPushButton("发送");
     subButton7 = new QPushButton("缴费");
     subButton1->setFixedSize(175,70);
     subButton2->setFixedSize(175,70);
     subButton3->setFixedSize(175,70);
     subButton4->setFixedSize(175,70);
     subButton5->setFixedSize(175,70);
     subButton6->setFixedSize(175,70);
     subButton7->setFixedSize(175,70);
     subButton1->setIcon(QIcon("D:/code/Qt/park/photo/2.png"));
     subButton1->setIconSize(QSize(60,60));
     subButton2->setIcon(QIcon("D:/code/Qt/park/photo/3.png"));
     subButton2->setIconSize(QSize(60,60));
     subButton3->setIcon(QIcon("D:/code/Qt/park/photo/4.png"));
     subButton3->setIconSize(QSize(60,60));
     subButton4->setIcon(QIcon("D:/code/Qt/park/photo/5.png"));
     subButton4->setIconSize(QSize(60,60));
     subButton5->setIcon(QIcon("D:/code/Qt/park/photo/6.png"));
     subButton5->setIconSize(QSize(60,60));
     subButton6->setIcon(QIcon("D:/code/Qt/park/photo/8.png"));
     subButton6->setIconSize(QSize(60,60));
     subButton7->setIcon(QIcon("D:/code/Qt/park/photo/8.png"));
     subButton7->setIconSize(QSize(60,60));

     btn_decode = new QPushButton("识别");
     btn_decode->setFixedSize(175,70);
     btn_decode->setIcon(QIcon("D:/code/Qt/park/photo/7.png"));
     btn_decode->setIconSize(QSize(60,60));
     //设置label
     lb = new QLabel("长江智星智能停车管理系统");
     lb->setScaledContents(true);
     QFont font = lb->font();
     font.setFamily("KaiTi");//楷体
     lb->setFont(font);

     lb1 = new QLabel("第六组");
     lb1->setScaledContents(true);


     QLabel *lb_gif = new QLabel();  //主页动图
     lb_gif->setScaledContents(true);

     lb_gif->setFixedSize(160,160);
     QMovie *m = new QMovie("D:/code/Qt/park/photo/3.gif");
     m->start();
     lb_gif->setMovie(m);

     lb2 = new QLabel;//时间
     lb2->setScaledContents(true);

     lb_pix = new QLabel;//公司图标
     lb_pix->setFixedSize(600,200);
     lb_pix->setScaledContents(true);
     lb_pix->setPixmap(QPixmap("D:/code/Qt/park/photo/1.png"));

     lb_0 = new QLabel;//空lb
     lb_0->setScaledContents(true);

     text1 = new QTextEdit;//显示屏
     text1->setFixedSize(800,630);
     text1->setReadOnly(true);

     mysock = new QTcpSocket;//套接字
     mysock->connectToHost(QHostAddress("192.168.1.222"), 8888);

     //设置输入框
     le_path = new QLineEdit;
     //le_path1 = new QLineEdit;
     le_path->setPlaceholderText("请输入车牌:");
     //le_path1->setPlaceholderText(":");
     le_path->setFixedSize(800,70);
     //le_path1->setFixedSize(700,70);

     //定时器
     QTimer *timer = new QTimer(this);
     connect(timer,SIGNAL(timeout()),this,SLOT(timerUpdate()));
     timer->start(1000);

     //构造摄像头对象
     QList<QCameraInfo> cameras = QCameraInfo::availableCameras();
        foreach (const QCameraInfo &cameraInfo, cameras) {
               qDebug()<<cameraInfo.description();
              // le_path1->setText(cameraInfo.description());
               camera = new QCamera(this);
           }

     //构造取景器
     vfinder = new QCameraViewfinder(this);
     vfinder->setFixedSize(960, 540);
     //vfinder->setMaximumSize(960, 540);
     //vfinder->setGeometry(10, 10, 320, 240);


     //构造抓取器
     imageCapture = new QCameraImageCapture(camera);
     connect(imageCapture, SIGNAL(imageCaptured(int,QImage)), this, SLOT(camCaptured(int,QImage)));

     //给摄像头配取景器
     camera->setViewfinder(vfinder);
     camera->start();

     httpmanager = new QNetworkAccessManager;
     connect(httpmanager, SIGNAL(finished(QNetworkReply*)), this, SLOT(read_ack(QNetworkReply*)));

     speeker = new QTextToSpeech;

     //2. 排版
     QHBoxLayout *box1 = new QHBoxLayout;
     box1->addWidget(lb_pix,0,Qt::AlignLeft | Qt::AlignTop);
     box1->addWidget(lb,0,Qt::AlignCenter | Qt::AlignCenter);
     box1->addWidget(lb2,0,Qt::AlignRight | Qt::AlignTop);

     QHBoxLayout *box2 = new QHBoxLayout;
     box2->addWidget(vfinder,0,Qt::AlignCenter | Qt::AlignTop);
     box2->addWidget(text1,0,Qt::AlignCenter | Qt::AlignCenter);

     QHBoxLayout *box3 = new QHBoxLayout;
     box3->addWidget(lb1,0,Qt::AlignLeft | Qt::AlignBottom);

     box3->addStretch();
     box3->setSpacing(50);
     box3->addWidget(lb_gif);
     box3->addWidget(btn_decode);
     box3->addWidget(subButton1);
     box3->addWidget(subButton2);
     box3->addWidget(subButton3);
     box3->addWidget(subButton7);
     box3->addWidget(subButton4);
     box3->addWidget(subButton5);

     QHBoxLayout *box4 = new QHBoxLayout;
     box4->addWidget(le_path,0,Qt::AlignCenter | Qt::AlignTop);
     box4->addWidget(subButton6,0,Qt::AlignLeft | Qt::AlignTop);
     box4->addWidget(lb_0,0,Qt::AlignCenter | Qt::AlignTop);

     QVBoxLayout *mainbox = new QVBoxLayout;
     mainbox->addLayout(box1);
     mainbox->addLayout(box2);
     mainbox->addLayout(box4);
     mainbox->addLayout(box3);
     setLayout(mainbox);

     //3.前后台挂接
     connect(btn_decode, SIGNAL(clicked(bool)), this, SLOT(decode_pix()));
     connect(subButton1, SIGNAL(clicked(bool)), this, SLOT(send_1()));
     connect(subButton2, SIGNAL(clicked(bool)), this, SLOT(send_2()));
     connect(subButton3, SIGNAL(clicked(bool)), this, SLOT(send_3()));
     connect(subButton4, SIGNAL(clicked(bool)), this, SLOT(send_4()));
     connect(subButton7, SIGNAL(clicked(bool)), this, SLOT(send_7()));
     connect(subButton5,SIGNAL(clicked()),this,SLOT(changeSlot()));
     connect(&payWin,SIGNAL(mySignal()),this,SLOT(tosubSlot()));
     connect(subButton7,SIGNAL(clicked()),this,SLOT(topaySlot()));
     connect(subButton6, SIGNAL(clicked(bool)), this, SLOT(send_data()));
     connect(mysock, SIGNAL(readyRead()), this, SLOT(recv_data()));

     //4. 美化
     lb->setStyleSheet("color:white;font-weight:bold;font-size:50px;");
     lb1->setStyleSheet("color:white;font-weight:bold;font-size:40px;");
     lb2->setStyleSheet("color:white;font-weight:bold;font-size:40px;");
     text1->setStyleSheet("background:rgba(46, 134, 222,0.6);color:white;font-weight:bold;font-size:30px;border-radius: 50px;");
     le_path->setStyleSheet("background:rgba(45, 152, 218,0.8);color:white;font-weight:bold;font-size:30px;border-radius: 20px;");
     //le_path1->setStyleSheet("background:rgba(45, 152, 218,0.8);color:white;font-weight:bold;font-size:30px;border-radius: 20px;");

     subButton1->setStyleSheet("QPushButton{"
                               "background: qlineargradient(x1:0, y1:0, x2:1, y2:1, stop:0 white, stop: 0.3 #96e0f6, stop:1 #02154f);"
                               "border-radius: 35px;"
                               "color: white;"
                               "font-weight:bold;"
                               "font-size:30px;}"
                               "QPushButton:hover{"
                               "background: qlineargradient(x1:0, y1:0, x2:1, y2:1, stop:0 white, stop: 0.3 #96e0f6, stop:1 #02154f);"
                               "border-radius: 35px;"
                               "color: white;"
                               "font-weight:bold;"
                               "font-size:33px;}"
                               "QPushButton:pressed{"
                               "background: qlineargradient(x1:0, y1:0, x2:1, y2:1, stop:0 white, stop: 0.3 #96e0f6, stop:1 #02154f);"
                               "border-radius: 35px;"
                               "color: white;"
                               "font-weight:bold;"
                               "font-size:33px;"
                               "padding-left:4px;"
                               "padding-top:4px;}");
     subButton2->setStyleSheet("QPushButton{"
                               "background: qlineargradient(x1:0, y1:0, x2:1, y2:1, stop:0 white, stop: 0.3 #96e0f6, stop:1 #02154f);"
                               "border-radius: 35px;"
                               "color: white;"
                               "font-weight:bold;"
                               "font-size:30px;}"
                               "QPushButton:hover{"
                               "background: qlineargradient(x1:0, y1:0, x2:1, y2:1, stop:0 white, stop: 0.3 #96e0f6, stop:1 #02154f);"
                               "border-radius: 35px;"
                               "color: white;"
                               "font-weight:bold;"
                               "font-size:33px;}"
                               "QPushButton:pressed{"
                               "background: qlineargradient(x1:0, y1:0, x2:1, y2:1, stop:0 white, stop: 0.3 #96e0f6, stop:1 #02154f);"
                               "border-radius: 35px;"
                               "color: white;"
                               "font-weight:bold;"
                               "font-size:33px;"
                               "padding-left:4px;"
                               "padding-top:4px;}");
     subButton3->setStyleSheet("QPushButton{"
                               "background: qlineargradient(x1:0, y1:0, x2:1, y2:1, stop:0 white, stop: 0.3 #96e0f6, stop:1 #02154f);"
                               "border-radius: 35px;"
                               "color: white;"
                               "font-weight:bold;"
                               "font-size:30px;}"
                               "QPushButton:hover{"
                               "background: qlineargradient(x1:0, y1:0, x2:1, y2:1, stop:0 white, stop: 0.3 #96e0f6, stop:1 #02154f);"
                               "border-radius: 35px;"
                               "color: white;"
                               "font-weight:bold;"
                               "font-size:33px;}"
                               "QPushButton:pressed{"
                               "background: qlineargradient(x1:0, y1:0, x2:1, y2:1, stop:0 white, stop: 0.3 #96e0f6, stop:1 #02154f);"
                               "border-radius: 35px;"
                               "color: white;"
                               "font-weight:bold;"
                               "font-size:33px;"
                               "padding-left:4px;"
                               "padding-top:4px;}");
     subButton4->setStyleSheet("QPushButton{"
                               "background: qlineargradient(x1:0, y1:0, x2:1, y2:1, stop:0 white, stop: 0.3 #96e0f6, stop:1 #02154f);"
                               "border-radius: 35px;"
                               "color: white;"
                               "font-weight:bold;"
                               "font-size:30px;}"
                               "QPushButton:hover{"
                               "background: qlineargradient(x1:0, y1:0, x2:1, y2:1, stop:0 white, stop: 0.3 #96e0f6, stop:1 #02154f);"
                               "border-radius: 35px;"
                               "color: white;"
                               "font-weight:bold;"
                               "font-size:33px;}"
                               "QPushButton:pressed{"
                               "background: qlineargradient(x1:0, y1:0, x2:1, y2:1, stop:0 white, stop: 0.3 #96e0f6, stop:1 #02154f);"
                               "border-radius: 35px;"
                               "color: white;"
                               "font-weight:bold;"
                               "font-size:33px;"
                               "padding-left:4px;"
                               "padding-top:4px;}");
     subButton5->setStyleSheet("QPushButton{"
                               "background: qlineargradient(x1:0, y1:0, x2:1, y2:1, stop:0 white, stop: 0.3 #96e0f6, stop:1 #02154f);"
                               "border-radius: 35px;"
                               "color: white;"
                               "font-weight:bold;"
                               "font-size:30px;}"
                               "QPushButton:hover{"
                               "background: qlineargradient(x1:0, y1:0, x2:1, y2:1, stop:0 white, stop: 0.3 #96e0f6, stop:1 #02154f);"
                               "border-radius: 35px;"
                               "color: white;"
                               "font-weight:bold;"
                               "font-size:33px;}"
                               "QPushButton:pressed{"
                               "background: qlineargradient(x1:0, y1:0, x2:1, y2:1, stop:0 white, stop: 0.3 #96e0f6, stop:1 #02154f);"
                               "border-radius: 35px;"
                               "color: white;"
                               "font-weight:bold;"
                               "font-size:33px;"
                               "padding-left:4px;"
                               "padding-top:4px;}");
     subButton6->setStyleSheet("QPushButton{"
                               "background: qlineargradient(x1:0, y1:0, x2:1, y2:1, stop:0 white, stop: 0.3 #96e0f6, stop:1 #02154f);"
                               "border-radius: 35px;"
                               "color: white;"
                               "font-weight:bold;"
                               "font-size:30px;}"
                               "QPushButton:hover{"
                               "background: qlineargradient(x1:0, y1:0, x2:1, y2:1, stop:0 white, stop: 0.3 #96e0f6, stop:1 #02154f);"
                               "border-radius: 35px;"
                               "color: white;"
                               "font-weight:bold;"
                               "font-size:33px;}"
                               "QPushButton:pressed{"
                               "background: qlineargradient(x1:0, y1:0, x2:1, y2:1, stop:0 white, stop: 0.3 #96e0f6, stop:1 #02154f);"
                               "border-radius: 35px;"
                               "color: white;"
                               "font-weight:bold;"
                               "font-size:33px;"
                               "padding-left:4px;"
                               "padding-top:4px;}");
     subButton7->setStyleSheet("QPushButton{"
                               "background: qlineargradient(x1:0, y1:0, x2:1, y2:1, stop:0 white, stop: 0.3 #96e0f6, stop:1 #02154f);"
                               "border-radius: 35px;"
                               "color: white;"
                               "font-weight:bold;"
                               "font-size:30px;}"
                               "QPushButton:hover{"
                               "background: qlineargradient(x1:0, y1:0, x2:1, y2:1, stop:0 white, stop: 0.3 #96e0f6, stop:1 #02154f);"
                               "border-radius: 35px;"
                               "color: white;"
                               "font-weight:bold;"
                               "font-size:33px;}"
                               "QPushButton:pressed{"
                               "background: qlineargradient(x1:0, y1:0, x2:1, y2:1, stop:0 white, stop: 0.3 #96e0f6, stop:1 #02154f);"
                               "border-radius: 35px;"
                               "color: white;"
                               "font-weight:bold;"
                               "font-size:33px;"
                               "padding-left:4px;"
                               "padding-top:4px;}");
     btn_decode->setStyleSheet("QPushButton{"
                               "background: qlineargradient(x1:0, y1:0, x2:1, y2:1, stop:0 white, stop: 0.3 #96e0f6, stop:1 #02154f);"
                               "border-radius: 35px;"
                               "color: white;"
                               "font-weight:bold;"
                               "font-size:30px;}"
                               "QPushButton:hover{"
                               "background: qlineargradient(x1:0, y1:0, x2:1, y2:1, stop:0 white, stop: 0.3 #96e0f6, stop:1 #02154f);"
                               "border-radius: 35px;"
                               "color: white;"
                               "font-weight:bold;"
                               "font-size:33px;}"
                               "QPushButton:pressed{"
                               "background: qlineargradient(x1:0, y1:0, x2:1, y2:1, stop:0 white, stop: 0.3 #96e0f6, stop:1 #02154f);"
                               "border-radius: 35px;"
                               "color: white;"
                               "font-weight:bold;"
                               "font-size:33px;"
                               "padding-left:4px;"
                               "padding-top:4px;}");


 }

void SubWidget::camCaptured(int id, const QImage pix)
{
    //向百度发送一个二维码识别请求（HTTP）
    QNetworkRequest myrequset;// = new QNetworkRequest;
    //填充请求url
    myrequset.setUrl(QUrl("https://aip.baidubce.com/rest/2.0/ocr/v1/license_plate?"
                          "access_token=24.15d8c083b61f1498f408254cc217f0eb.2592000.1619248166.282335-23862092"));
    //填充header
    myrequset.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");

    //填充请求的body
    //1.挖出照片内容!!!!!!!照片源自于拍到的！！！！！！！！！！！
//    QFile file(le_path->text());
//    file.open(QIODevice::ReadOnly);
//    QByteArray buf = file.readAll();
    QByteArray buf;
    QBuffer buffer(&buf);
    buffer.open(QIODevice::WriteOnly);
    pix.save(&buffer,"png");

    //2.转成base64及urlcode
    QByteArray buf64 = buf.toBase64().toPercentEncoding();
    QByteArray body = "image="+buf64;
    //发送完整的一次识别请求

    httpmanager->post(myrequset, body);

}


void SubWidget::decode_pix()
{
    //拍照
    imageCapture->capture();

}
//结果解析
void SubWidget::read_ack(QNetworkReply* r)
{
    //提取json格式的返回
    QByteArray buf = r->readAll();
    qDebug() << buf;

    //提取json中的感兴趣的内容
    QJsonDocument myjson = QJsonDocument::fromJson(buf);
    QJsonObject node = myjson.object();
    QJsonObject arr = node.value("words_result").toObject();
    QString text = arr.value("number").toString();
     qDebug() << arr;
    qDebug() << text;
    le_path->setText(text);
   speeker->say("您好"+text);
}

void SubWidget::recv_data() //接受到显示屏
{
//    QMessageBox message(QMessageBox::Information,"Tip","<font size='5'>Send success!</font>");
//    message.exec();
    QByteArray buf = mysock->readAll();
    text1->append(buf);
}

void SubWidget::send_data()  //发送
{
     qDebug()<<"send: "<<le_path->text();
     mysock->write(le_path->text().toStdString().c_str());
     le_path->clear();
}
void SubWidget::timerUpdate(void)  //时间
{
    QDateTime time = QDateTime::currentDateTime();
    QString str = time.toString("yyyy-MM-dd hh:mm:ss dddd");
    lb2->setText(str);
}

void SubWidget::changeSlot() //关闭窗口
{

        QPushButton *okbtn = new QPushButton(QString::fromLocal8Bit("Ok"));
        QPushButton *cancelbtn = new QPushButton(QString::fromLocal8Bit("Cancel"));
        QMessageBox *mymsgbox = new QMessageBox;

        mymsgbox->setIcon(QMessageBox::Warning);
        mymsgbox->setWindowTitle(QString::fromLocal8Bit("Tip"));
        mymsgbox->setText(QString::fromLocal8Bit("Are you sure to quit?"));
        mymsgbox->addButton(okbtn, QMessageBox::AcceptRole);
        mymsgbox->addButton(cancelbtn, QMessageBox::RejectRole);
        mymsgbox->show();

        mymsgbox->exec();//阻塞等待用户输入
        if (mymsgbox->clickedButton()==okbtn)//点击了OK按钮
        {
            this->close();QWidget:close();
        }
        else{

        }
    //QWidget:close();

}

void SubWidget::send_1()  //停车按钮发送命令
{

     qDebug()<<"send: 停车";
     mysock->write("1");
//     QMessageBox message(QMessageBox::Information,"Tip","<font size='5'>Stop success!</font>");
//     message.exec();
}

void SubWidget::send_2()  //取车按钮发送命令
{

     qDebug()<<"send: 取车";
     mysock->write("2");
//     QMessageBox message(QMessageBox::Information,"Tip","<font size='5'>Leave success!</font>");
//     message.exec();
}

void SubWidget::send_3()  //查询按钮发送命令
{

     qDebug()<<"send: 查询";
     mysock->write("show");
//     QMessageBox message(QMessageBox::Information,"Tip","<font size='5'>Select success!</font>");
//     message.exec();
}

void SubWidget::send_4()  //返回按钮发送命令
{

     qDebug()<<"send: 返回";
     mysock->write("0");

}

void SubWidget::send_7()  //缴费按钮发送命令
{

     qDebug()<<"send: 缴费";
     mysock->write("6");
}


void SubWidget::topaySlot()
{
    //this->hide();
    payWin.show();
}

