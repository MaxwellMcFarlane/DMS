#ifndef CONFIGURATIONEDITWINDOW_H
#define CONFIGURATIONEDITWINDOW_H

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
#include <QTextStream>
#include "../scada/ControlSubSystem/branch.h"
#include "../scada/ControlSubSystem/modemanager.h"
#include "../scada/ControlSubSystem/state.h"

namespace Ui {
class ConfigurationEditWindow;
}

class ConfigurationEditWindow : public QWidget
{
    Q_OBJECT

public:
    explicit ConfigurationEditWindow(QWidget *parent = 0);    
    explicit ConfigurationEditWindow(QWidget *parent = 0, DMS * db = 0);
    ~ConfigurationEditWindow();

private slots:
    void on_getfileButton_clicked();

    void on_Savebutton_clicked();

    void on_listWidget_itemSelectionChanged();

private:
    Ui::ConfigurationEditWindow *ui;
    bool checkModeManagerConfigure(string file);
    DMS * db;
};

#endif // CONFIGURATIONEDITWINDOW_H
