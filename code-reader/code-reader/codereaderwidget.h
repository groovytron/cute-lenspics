#ifndef CODEREADERWIDGET_H
#define CODEREADERWIDGET_H

#include <QWidget>
#include <QLabel>
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
    void updateIfRegexMatches(const QRegularExpression* regex, QLabel* outputLabel);
    QString formatDiopter(QString string);
public slots:
    void updateOutputLabel();
    void clearQRCodeInput();
private:
    QRegularExpression* serialNumberRegex;
    QRegularExpression* expirationDateCodeRegex;
    QRegularExpression* diopterRegex;
    static const QString OUTPUT_PLACEHOLDER;
};

#endif // CODEREADERWIDGET_H
