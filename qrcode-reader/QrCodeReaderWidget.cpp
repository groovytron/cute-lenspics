#include "QrCodeReaderWidget.h"
#include "ui_QrCodeReaderWidget.h"
#include "LensTableModel.h"

#include <QPlainTextEdit>
#include <QDebug>
#include <QPushButton>
#include <QDebug>
#include <QMessageBox>

const QString QrCodeReaderWidget::OUTPUT_PLACEHOLDER("Information not found");

QrCodeReaderWidget::QrCodeReaderWidget(QWidget *parent) :
    QWidget(parent)
{
    /* Load the form */
    setupUi(this);

    /* Table wiget */

    /* Table View model variant */
    lenses = new LensTableModel(0);
    tableView->setModel(lenses);
    tableView->horizontalHeader()->setStretchLastSection(true);
    tableView->verticalHeader()->setFixedWidth(20);

    /* DEBUG: deactivate output labels at the moment */
    label->hide();
    label_2->hide();
    label_3->hide();
    serialNumberOuput->hide();
    diopterOutput->hide();
    expirationDateOutput->hide();

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

    /* Connect signal to slots */
    connectEventHandlers();

    qrCodeInput->setFocus();
}

QrCodeReaderWidget::~QrCodeReaderWidget()
{
}

void QrCodeReaderWidget::connectEventHandlers()
{
    connect(qrCodeInput, &QPlainTextEdit::textChanged, this, &QrCodeReaderWidget::updateOutputLabels);
    connect(clearBtn, &QPushButton::clicked, this, &QrCodeReaderWidget::clearQRCodeInput);
}

bool QrCodeReaderWidget::regexMatchesInQRInput(const QRegularExpression* regex)
{
    const QString input = qrCodeInput->toPlainText();
    return regex->match(input).captured() != NULL;
}

bool QrCodeReaderWidget::QRInputContainsALens()
{
    return regexMatchesInQRInput(serialNumberRegex) && regexMatchesInQRInput(expirationDateCodeRegex) && regexMatchesInQRInput(diopterRegex);
}

QString QrCodeReaderWidget::formatDiopter(QString string)
{
    return string.remove(0, 1);
}

void QrCodeReaderWidget::updateOutputLabels()
{
    if (QRInputContainsALens()) {
        QString serialNumber = serialNumberRegex->match(qrCodeInput->toPlainText()).captured();
        QString expirationDate = expirationDateCodeRegex->match(qrCodeInput->toPlainText()).captured();
        QString diopter = diopterRegex->match(qrCodeInput->toPlainText()).captured();

        Lens lens = Lens(serialNumber, diopter, expirationDate);

        if (!this->lenses->addLens(lens)) {
            QMessageBox messageBox;
            messageBox.setText("Lens already exists.");
            QString message = "Lens " + serialNumber + " is already in your list";
            messageBox.setInformativeText(message);
            messageBox.setStandardButtons(QMessageBox::Ok);
            messageBox.exec();
        }
        else {
            this->qrCodeInput->clear();
            this->qrCodeInput->setFocus();
        }
    }
}

void QrCodeReaderWidget::clearQRCodeInput()
{
    qrCodeInput->clear();
}

void QrCodeReaderWidget::clearLenses()
{
    this->lenses->clearLenses();
}

QList<Lens> QrCodeReaderWidget::getLenses()
{
    return this->lenses->getLenses();
}
