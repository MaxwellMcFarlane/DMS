#ifndef EXPORTWINDOW_H
#define EXPORTWINDOW_H
#include "../src/dms.h"
#include "../src/table.h"
#include <QWidget>
#include <QKeyEvent>
#include <QFileDialog>

namespace Ui {
class ExportWindow;
}

class ExportWindow : public QWidget
{
    Q_OBJECT

public:
    explicit ExportWindow(QWidget *parent = 0);
    explicit ExportWindow(QWidget *parent = 0,DMS * db = 0);
    ~ExportWindow();

private slots:
    void on_listWidget_itemSelectionChanged();

    void on_Preview_clicked();

    void on_Export_clicked();

private:

    void printExportTable();

    Ui::ExportWindow *ui;
    DMS *db;    
};

#endif // EXPORTWINDOW_H
