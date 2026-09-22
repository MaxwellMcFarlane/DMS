#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "../src/dms.h"
#include "../src/table.h"
#include "exportwindow.h"
#include "tableeditwindow.h"
#include "configurationeditwindow.h"
#include <QMainWindow>
#include <QKeyEvent>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_actionExport_Table_triggered();

    void on_actionConfiguration_triggered();    

    void on_actionView_Table_triggered();

private:
    Ui::MainWindow *ui;
    DMS *db;
    ModeManager * m;
};

#endif // MAINWINDOW_H
