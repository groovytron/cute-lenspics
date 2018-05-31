#ifndef QR_CODE_READER_WIDGET_H
#define QR_CODE_READER_WIDGET_H

#include <QWidget>
#include <QLabel>
#include "ui_QrCodeReaderWidget.h"
#include "LensTableModel.h"

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
    bool regexMatchesInQRInput(const QRegularExpression* regex);
    bool QRInputContainsALens();
    QString formatDiopter(QString string);
    void clearLenses();
    QList<Lens> getLenses();
public slots:
    void updateOutputLabels();
    void clearQRCodeInput();
private:
    QRegularExpression* serialNumberRegex;
    QRegularExpression* expirationDateCodeRegex;
    QRegularExpression* diopterRegex;
    static const QString OUTPUT_PLACEHOLDER;
    LensTableModel* lenses;


};

#endif // CODEREADERWIDGET_H
