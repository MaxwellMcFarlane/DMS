#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);    
    db = new DMS("/Users/maxwellmcfarlane/scada_repo/scada.db",
                 "/Users/maxwellmcfarlane/scada_repo/configuration_files/deftables_config.txt",
                 "/Users/maxwellmcfarlane/scada_repo/log.txt");    
    ui->SensorArch->setText(QString::fromStdString(db->getTableHeaders("SensorTable")
                                                   + "\n"
                                                   + db->getTable("SensorTable")->createQuery("Select * from SensorTable")));
    ui->StateArch->setText(QString::fromStdString(db->getTableHeaders("StateTable")
                                                  + "\n"
                                                  + db->getTable("StateTable")->createQuery("Select * from StateTable")));
}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::on_actionExport_Table_triggered()
{
    ExportWindow * ex = new ExportWindow(0,db);
    ex->show();

}

void MainWindow::on_actionConfiguration_triggered()
{
    ConfigurationEditWindow * ex = new ConfigurationEditWindow(0,db);
//    tableEditWindow * ex = new tableEditWindow(0,db);
    ex->show();
}

void MainWindow::on_actionEdit_Table_triggered()
{
    tableEditWindow * ex = new tableEditWindow(0,db);
    ex->show();
}
