#include "widget.h"
#include "ui_widget.h"
#include <QImageReader>
#include <QDebug>
#include <QCameraInfo>

Widget::Widget(QWidget *parent) :
    QWidget(parent)
{
    setupUi(this);
    QImage testImage = QIcon("://images/Qt_logo_2016.svg").pixmap(QSize(200,200)).toImage();
    lensPicLabel->setPixmap(QPixmap::fromImage(testImage));
    checkCameraAvailability();
}

Widget::~Widget()
{

}

void Widget::checkCameraAvailability()
{
    if (QCameraInfo::availableCameras().count() > 0)
            qDebug() << QCameraInfo::availableCameras().count() << " cameras available";
        else
            qDebug() << "No cameras available";

}

