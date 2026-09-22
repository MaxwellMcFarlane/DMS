#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    db = new DMS("../scada.db",
                 "../configuration_files/deftables_config.txt",
                 "../log.txt");
    db->loadConfigTable("control.config.txt","../configuration_files/control_config.txt");
    ui->SensorArch->setText(QString::fromStdString(db->getTableHeaders("SensorTable")
                                                   + "\n"
                                                   + db->getTable("SensorTable")->createQuery("Select * from SensorTable")));

    string info = db->getTable("StateTable")->createQuery("Select * from StateTable");
    vector<char*> list;
    char * it;
    it = strtok((char*)info.c_str(), "\n");
    while(it != NULL){
        list.push_back(it);
        it = strtok(NULL, "\n");
    }
    try{m = new ModeManager("../configuration_files/control_config.txt",db);m->configure();}
    catch(const std::exception &e){cout << e.what() << endl;}
    for(int i = 0; i < (int)list.size();i++){
//        if(db->currentState = ){}
//        else{}
    }
    ui->StateArch->setText(QString::fromStdString(db->getTableHeaders("StateTable")
                                                  + "\n"
                                                  + db->getTable("StateTable")->createQuery("Select * from StateTable")));
//    m->configure();
//    db->setCurrentState();

}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::on_actionExport_Table_triggered()
{
    ExportWindow * ex = new ExportWindow(0,db);    
    ex->show();
    m->configure();
}

void MainWindow::on_actionConfiguration_triggered()
{
    ConfigurationEditWindow * ex = new ConfigurationEditWindow(0,db);
    ex->show();    
//    m->configure();
}

void MainWindow::on_actionView_Table_triggered()
{
    tableEditWindow * ex = new tableEditWindow(0,db);    
    ex->show();
    m->configure();
}
