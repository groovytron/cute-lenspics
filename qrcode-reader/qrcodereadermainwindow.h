#ifndef QRCODEREADERMAINWINDOW_H
#define QRCODEREADERMAINWINDOW_H

#include "QrCodeReaderWidget.h"
#include "lens.h"

#include <QMainWindow>
#include <QAction>
#include <QMenu>
#include <QMenuBar>
#include <QFileDialog>

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = nullptr);
signals:

public slots:
private:
    QrCodeReaderWidget* widget;
    QAction* newSessionAction;
    QAction* saveSessionAction;
    // QAction* loadSessionAction;
    QMenu* fileMenu;
    void createActions();
    void createMenus();
    void resetSession();
    void saveSession();
    void loadSession();
};

#endif // QRCODEREADERMAINWINDOW_H
