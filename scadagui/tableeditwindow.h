#ifndef TABLEEDITWINDOW_H
#define TABLEEDITWINDOW_H

#include "../DMS/dms.h"
#include "../DMS/table.h"
#include <QWidget>

namespace Ui {
class tableEditWindow;
}

class tableEditWindow : public QWidget
{
    Q_OBJECT

public:
    explicit tableEditWindow(QWidget *parent = 0);
    explicit tableEditWindow(QWidget *parent = 0, DMS * db = 0);
    ~tableEditWindow();

private slots:
    void on_pushButton_clicked();

    void on_listWidget_itemSelectionChanged();

private:
    Ui::tableEditWindow *ui;
    DMS * db;
};

#endif // TABLEEDITWINDOW_H
