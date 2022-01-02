#include "mainwidget.h"
#include <QApplication>
#include <QIcon>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    mainWidget w;
    w.setWindowState(Qt::WindowMaximized);
    w.setWindowFlags(Qt::FramelessWindowHint);//设置窗体无边框
   // w.setWindowOpacity(0.7);

    QPalette palette;
    QPixmap pixmap("D:/code/Qt/park/photo/0.png");
    w.setAutoFillBackground(true);
    palette.setBrush(QPalette::Window, QBrush(pixmap));
    w.setPalette(palette);
    w.show();

    QIcon icon("src/1.png");
    w.setWindowIcon(icon);

    return a.exec();
}
