#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "../DMS/dms.h"
#include "../DMS/table.h"
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

private:
    Ui::MainWindow *ui;
    DMS *db;
};

#endif // MAINWINDOW_H
