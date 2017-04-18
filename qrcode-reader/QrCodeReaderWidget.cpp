#include "QrCodeReaderWidget.h"
#include "ui_QrCodeReaderWidget.h"

#include <QPlainTextEdit>
#include <QDebug>
#include <QPushButton>

const QString QrCodeReaderWidget::OUTPUT_PLACEHOLDER("Information not found");

QrCodeReaderWidget::QrCodeReaderWidget(QWidget *parent) :
    QWidget(parent)
{
    /* Load the form */
    setupUi(this);

    /* Attributes setup */
    serialNumberRegex = new QRegularExpression("F\\d{8}");
    expirationDateCodeRegex = new QRegularExpression("\\d{4}-\\d{2}");
    diopterRegex = new QRegularExpression("\\+\\d{2}\\.\\d");

    /* Placeholders */
    serialNumberOuput->setText(OUTPUT_PLACEHOLDER);
    expirationDateOutput->setText(OUTPUT_PLACEHOLDER);
    diopterOutput->setText(OUTPUT_PLACEHOLDER);

    /* Selectable UI elements */
    serialNumberOuput->setTextInteractionFlags(Qt::TextSelectableByMouse);
    expirationDateOutput->setTextInteractionFlags(Qt::TextSelectableByMouse);
    diopterOutput->setTextInteractionFlags(Qt::TextSelectableByMouse);

    setWindowTitle("Lens Serial Number Reader");

    /* Connect signal to slots */
    connectEventHandlers();

    qrCodeInput->setFocus();
}

QrCodeReaderWidget::~QrCodeReaderWidget()
{
}

void QrCodeReaderWidget::connectEventHandlers()
{
    connect(qrCodeInput, &QPlainTextEdit::textChanged, this, &QrCodeReaderWidget::updateOutputLabel);
    connect(clearBtn, &QPushButton::clicked, this, &QrCodeReaderWidget::clearQRCodeInput);
}

void QrCodeReaderWidget::updateIfRegexMatches(const QRegularExpression* regex, QLabel* outputLabel)
{
    const QString input = qrCodeInput->toPlainText();
    QString match = regex->match(input).captured();

    if (match != NULL)
    {
        outputLabel->setText(match);
    }
    else
    {
        outputLabel->setText(OUTPUT_PLACEHOLDER);
    }
}

QString QrCodeReaderWidget::formatDiopter(QString string)
{
    return string.remove(0, 1);
}

void QrCodeReaderWidget::updateOutputLabel()
{
    updateIfRegexMatches(serialNumberRegex, serialNumberOuput);
    updateIfRegexMatches(expirationDateCodeRegex, expirationDateOutput);

    QString match = diopterRegex->match(qrCodeInput->toPlainText()).captured();
    diopterOutput->setText(match != NULL ? match.remove(0, 1) : OUTPUT_PLACEHOLDER);
}

void QrCodeReaderWidget::clearQRCodeInput()
{
    qrCodeInput->clear();
}
