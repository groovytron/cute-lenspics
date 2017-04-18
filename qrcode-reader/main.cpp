#include "QrCodeReaderWidget.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QrCodeReaderWidget w;
    w.show();

    return a.exec();
}
