#ifndef CODEREADERWIDGET_H
#define CODEREADERWIDGET_H

#include <QWidget>
#include "ui_codereaderwidget.h"

namespace Ui {
class CodeReaderWidget;
}

class CodeReaderWidget : public QWidget, private Ui::CodeReaderWidget
{
    Q_OBJECT

public:
    explicit CodeReaderWidget(QWidget *parent = 0);
    ~CodeReaderWidget();
    void connectEventHandlers();
    void updateOutputLabel();

private:
    QRegularExpression* regex;
    static const QString SERIAL_NUMBER_PLACEHOLDER;
    static const QString SERIAL_NUMBER_TEXT;
};

#endif // CODEREADERWIDGET_H
