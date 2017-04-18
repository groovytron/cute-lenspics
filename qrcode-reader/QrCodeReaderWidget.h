#ifndef QR_CODE_READER_WIDGET_H
#define QR_CODE_READER_WIDGET_H

#include <QWidget>
#include <QLabel>
#include "ui_QrCodeReaderWidget.h"

namespace Ui {
class QrCodeReaderWidget;
}

class QrCodeReaderWidget : public QWidget, private Ui::QrCodeReaderWidget
{
    Q_OBJECT

public:
    explicit QrCodeReaderWidget(QWidget *parent = 0);
    ~QrCodeReaderWidget();
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
