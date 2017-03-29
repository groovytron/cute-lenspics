#include "codereaderwidget.h"
#include "ui_codereaderwidget.h"

#include <QPlainTextEdit>
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
    serialNumberOuput->setText(SERIAL_NUMBER_TEXT + SERIAL_NUMBER_PLACEHOLDER);

    setWindowTitle("Lens Serial Number Reader");

    /* Connect signal to slots */
    connectEventHandlers();
}

CodeReaderWidget::~CodeReaderWidget()
{
}

void CodeReaderWidget::connectEventHandlers()
{
    connect(serialNumberInput, &QPlainTextEdit::textChanged, this, &CodeReaderWidget::updateOutputLabel);
}

void CodeReaderWidget::updateOutputLabel()
{
    QString serialNumberMatch = regex->match(serialNumberInput->toPlainText()).captured();

    if ( serialNumberMatch != NULL)
    {
        serialNumberOuput->setText(SERIAL_NUMBER_TEXT + serialNumberMatch);
    }
    else
    {
        serialNumberOuput->setText(SERIAL_NUMBER_TEXT + SERIAL_NUMBER_PLACEHOLDER);
    }
}
