#include "tableeditwindow.h"
#include "ui_tableeditwindow.h"

tableEditWindow::tableEditWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::tableEditWindow)
{
    ui->setupUi(this);
}

tableEditWindow::tableEditWindow(QWidget *parent, DMS *db):
    QWidget(parent),
    ui(new Ui::tableEditWindow)
{
    ui->setupUi(this);
    this->db = db;
    vector<Table*> list = db->getTableList();
    for(int i = 0; i < (int)list.size(); i++){
        Table dummy = *list.at(i);

        if(dummy.getTableName() != "ConfigFileTable"){
            ui->listWidget->addItem(new QListWidgetItem(QString::fromStdString(dummy.getTableName())));
        }
    }
}

tableEditWindow::~tableEditWindow()
{
    delete ui;
}

void tableEditWindow::on_listWidget_itemSelectionChanged()
{
    QListWidgetItem * dummy = ui->listWidget->currentItem();
    string table = dummy->text().toStdString();
    string wholeTable = db->getTableHeaders(table) + "\n" + db->getTable(table)->createQuery("Select * from " + table + ";");
    ui->TableContentView->setText(QString::fromStdString(wholeTable));
}

//void tableEditWindow::on_getTablebutton_clicked()
//{
//    QListWidgetItem * dummy = ui->listWidget->currentItem();
//    string tableName = dummy->text().toStdString();
//    if(true){
//        string dummy = db->getTable(tableName)->createQuery("Select * from " + tableName + ";");
//        vector <char*> list;
//        char * it;
//        it = strtok((char*)dummy.c_str(), "\n");
//        while(it != NULL){
//            list.push_back(it);
//            it = strtok(NULL, "\n");
//        }
//        ui->tableWidget->setRowCount(list.size()+1);
//        ui->tableWidget->setColumnCount(1);
//        for(int i = 0; i < (int)list.size(); i++){
//            ui->tableWidget->setItem(i,1,new QTableWidgetItem(QString::fromStdString(list.at(i))));
//        }
//    }
//}
//void tableEditWindow::on_deletebutton_clicked()
//{
//    QModelIndexList selection = ui->tableWidget->selectionModel()->selectedRows();
//    QListWidgetItem * dummy = ui->listWidget->currentItem();
//    string tableName = dummy->text().toStdString();

//    QModelIndexList select = ui->tableWidget->selectionModel()->selectedRows();

//    for(int i=0; i< select.count(); i++)
//    {
//        db->getTable(tableName)->delRow("rowid",to_string(i+1));
//    }
//    db->resetRowIdTable(tableName);


    //    string edits = ui->FileEditor->toPlainText().toStdString();
    //    if(!checkModeManagerConfigure(edits)){QMessageBox::about(this,"Error","Error File Corrupt Resolve Error");}
    //    db->getTable("ConfigFileTable")->updateTable("filename = " + configname,edits);
//}
