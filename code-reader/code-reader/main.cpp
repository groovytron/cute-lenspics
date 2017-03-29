#include "codereaderwidget.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    CodeReaderWidget w;
    w.show();

    return a.exec();
}
