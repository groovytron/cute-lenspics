#include "codereaderwidget.h"
#include "ui_codereaderwidget.h"

#include <QPlainTextEdit>
#include <QDebug>
#include <QPushButton>

const QString CodeReaderWidget::OUTPUT_PLACEHOLDER("Information not found");

CodeReaderWidget::CodeReaderWidget(QWidget *parent) :
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

CodeReaderWidget::~CodeReaderWidget()
{
}

void CodeReaderWidget::connectEventHandlers()
{
    connect(qrCodeInput, &QPlainTextEdit::textChanged, this, &CodeReaderWidget::updateOutputLabel);
    connect(clearBtn, &QPushButton::clicked, this, &CodeReaderWidget::clearQRCodeInput);
}

void CodeReaderWidget::updateIfRegexMatches(const QRegularExpression* regex, QLabel* outputLabel)
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

QString CodeReaderWidget::formatDiopter(QString string)
{
    return string.remove(0, 1);
}

void CodeReaderWidget::updateOutputLabel()
{
    updateIfRegexMatches(serialNumberRegex, serialNumberOuput);
    updateIfRegexMatches(expirationDateCodeRegex, expirationDateOutput);

    QString match = diopterRegex->match(qrCodeInput->toPlainText()).captured();
    diopterOutput->setText(match != NULL ? match.remove(0, 1) : OUTPUT_PLACEHOLDER);
}

void CodeReaderWidget::clearQRCodeInput()
{
    qrCodeInput->clear();
}
