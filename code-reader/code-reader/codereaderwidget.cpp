#include "codereaderwidget.h"
#include "ui_codereaderwidget.h"

#include <QLineEdit>
#include <QDebug>

const QString CodeReaderWidget::SERIAL_NUMBER_PLACEHOLDER("Not found");
const QString CodeReaderWidget::SERIAL_NUMBER_TEXT("Serial Number: ");

CodeReaderWidget::CodeReaderWidget(QWidget *parent) :
    QWidget(parent)
{
    /* Load the form */
    setupUi(this);

    /* Attributes setup */
    regex = new QRegularExpression("F[0-9]{8}");
    QValidator *validator = new QRegularExpressionValidator(*regex, this);
    serialNumberInput->setValidator(validator);
    serialNumberOuput->setText(SERIAL_NUMBER_TEXT + SERIAL_NUMBER_PLACEHOLDER);

    /* Connect signal to slots */
    connectEventHandlers();
}

CodeReaderWidget::~CodeReaderWidget()
{
}

void CodeReaderWidget::connectEventHandlers()
{
    connect(serialNumberInput, &QLineEdit::textChanged, this, &CodeReaderWidget::updateOutputLabel);
}

void CodeReaderWidget::updateOutputLabel(const QString &serialNumber)
{
    if (regex->match(serialNumber).captured() != NULL) {
        serialNumberOuput->setText(SERIAL_NUMBER_TEXT + serialNumber);
    }
    else
    {
        serialNumberOuput->setText(SERIAL_NUMBER_TEXT + SERIAL_NUMBER_PLACEHOLDER);
    }
}
