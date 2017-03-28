#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include "ui_widget.h"

namespace Ui {
class Widget;
}

class Widget : public QWidget, private Ui::Widget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();
    void checkCameraAvailability();

private:
    Ui::Widget *ui;
};

#endif // WIDGET_H
