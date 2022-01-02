#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QWidget>
#include <QPushButton>
#include "subwidget.h" //子窗口头文件
#include <QLabel>
#include <QTimer>
#include <QDateTime>


class mainWidget : public QWidget
{
    Q_OBJECT

public:
    mainWidget(QWidget *parent = 0);
    ~mainWidget();

    QLabel *lb;
    QLabel *lb1;
    QLabel *lb2;



public:
    SubWidget subWin;
    QPushButton * mainButton;



private slots:
    void tosubSlot();

};

#endif // MAINWIDGET_H

