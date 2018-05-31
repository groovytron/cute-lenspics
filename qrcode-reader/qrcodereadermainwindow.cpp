#include "qrcodereadermainwindow.h"
#include "QrCodeReaderWidget.h"

#include <QDebug>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
    this->createActions();
    this->createMenus();
    this->widget = new QrCodeReaderWidget();
    this->setCentralWidget(this->widget);
}

void MainWindow::createActions()
{
    this->newSessionAction = new QAction(tr("&New Session"), this);
    newSessionAction->setShortcuts(QKeySequence::New);
    newSessionAction->setStatusTip(tr("Create a new scanning session"));
    connect(newSessionAction, &QAction::triggered, this, &MainWindow::resetSession);

    this->saveSessionAction = new QAction(tr("&Save session"), this);
    saveSessionAction->setStatusTip(tr("Save the current scanning session"));
    saveSessionAction->setShortcuts(QKeySequence::Save);
    connect(saveSessionAction, &QAction::triggered, this, &MainWindow::saveSession);

    /*this->loadSessionAction = new QAction(tr("&Load session"), this);
    loadSessionAction->setStatusTip(tr("Load a scanning session"));
    loadSessionAction->setShortcuts(QKeySequence::Open);
    connect(loadSessionAction, &QAction::triggered, this, &MainWindow::loadSession);*/

}

void MainWindow::createMenus()
{
    this->fileMenu = menuBar()->addMenu(tr("&File"));
    this->fileMenu->addAction(this->newSessionAction);
    // this->fileMenu->addAction(this->loadSessionAction);
    this->fileMenu->addAction(this->saveSessionAction);
}

void MainWindow::resetSession()
{
    this->widget->clearLenses();
}

void MainWindow::saveSession()
{
    QString filename = QFileDialog::getSaveFileName(this, "Save a session", "filename.csv", "CSV files (.csv);", 0, 0);
    QFile destinationFile(filename);

    if(destinationFile.open(QFile::WriteOnly | QFile::Truncate))
    {
        QTextStream output(&destinationFile);
        output << "serial_number;diopter;expiration_date\n" ;
        QList<Lens> lenses = this->widget->getLenses();

        foreach (Lens lens, lenses) {
           output << lens.getSerialNumber() << ";" << lens.getDiopter() << ";" << lens.getExpirationDate() << "\n";
        }
    }

    destinationFile.close();
}

void MainWindow::loadSession()
{

}
