#include "exportwindow.h"
#include "ui_exportwindow.h"

ExportWindow::ExportWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ExportWindow)
{
    ui->setupUi(this);    
}
ExportWindow::ExportWindow(QWidget *parent, DMS *db):
    QWidget(parent),
    ui(new Ui::ExportWindow)
{
     ui->setupUi(this);
     this->db = db;
    vector<Table*> list = db->getTableList();
     for(int i = 0; i < (int)list.size(); i++){
        Table dummy = *list.at(i);
         ui->listWidget->addItem(new QListWidgetItem(QString::fromStdString(dummy.getTableName())));
     }
     ui->TableExportView->setText(QString::fromStdString("<No Contents>"));
}





ExportWindow::~ExportWindow()
{
    delete ui;
}


void ExportWindow::on_listWidget_itemSelectionChanged()
{
    QListWidgetItem * dummy = ui->listWidget->currentItem();
    string table = dummy->text().toStdString();
    string wholeTable = db->getTableHeaders(table) + "\n" + db->getTable(table)->createQuery("Select * from " + table + ";");
    ui->TableContentView->setText(QString::fromStdString(wholeTable));

}

void ExportWindow::on_Preview_clicked()
{
    string columnSelect = ui->ColumnEdit->text().toStdString();
    string condition = ui->ConditionEdit->text().toStdString();

    QListWidgetItem * dummy = ui->listWidget->currentItem();
    string table = dummy->text().toStdString();
    if(!columnSelect.empty() && condition.empty()){
        string dummy = db->getTable(table)->createQuery("Select " + columnSelect + " from " + table);
        ui->TableExportView->setText(QString::fromStdString(dummy));
    }
    else if(!columnSelect.empty() && !condition.empty()){
        string dummy = db->getTable(table)->createQuery("Select " + columnSelect + " from " + table + " where " + condition );
        ui->TableExportView->setText(QString::fromStdString(dummy));
    }
    else{
        ui->TableExportView->setText(QString::fromStdString("Bad Constraints"));
    }
}

void ExportWindow::on_Export_clicked(){
    string columnSelect = ui->ColumnEdit->text().toStdString();
    string condition = ui->ConditionEdit->text().toStdString();
    string filePath = ui->FilePath->text().toStdString();
    if(filePath.empty()){filePath = "export.csv";}
    QListWidgetItem * dummy = ui->listWidget->currentItem();
    string table = dummy->text().toStdString();
    if(!columnSelect.empty()){db->getTable(table)->exp(columnSelect,condition,filePath);}
    else{ui->TableExportView->setText(QString::fromStdString("Bad Constraints"));}
}
