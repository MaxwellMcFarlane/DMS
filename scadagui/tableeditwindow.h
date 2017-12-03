#ifndef TABLEEDITWINDOW_H
#define TABLEEDITWINDOW_H

#include "../DMS/dms.h"
#include "../DMS/table.h"
#include <QWidget>
#include <QMessageBox>
#include <QFileDialog>
#include <QInputDialog>
#include <QProgressBar>
#include <QWidget>
#include <QMessageBox>
#include <QFileDialog>
#include <QInputDialog>
#include <QProgressBar>
#include "../scada/ControlSubSystem/branch.h"
#include "../scada/ControlSubSystem/modemanager.h"
#include "../scada/ControlSubSystem/state.h"
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

    void on_listWidget_itemSelectionChanged();

    void on_Savebutton_clicked();

    void on_Previewbutton_clicked();

private:

    bool checkModeManagerConfigure(string file);
    Ui::tableEditWindow *ui;
    DMS * db;
};

#endif // TABLEEDITWINDOW_H
