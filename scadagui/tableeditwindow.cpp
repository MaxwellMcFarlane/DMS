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
    ui->listWidget->addItem(new QListWidgetItem(QString::fromStdString("table_config.txt")));
    ui->listWidget->addItem(new QListWidgetItem(QString::fromStdString("ControlState_config.txt")));
    ui->listWidget->addItem(new QListWidgetItem(QString::fromStdString("deftables_config.txt")));
    ui->listWidget->addItem(new QListWidgetItem(QString::fromStdString("ConditionTable")));
    ui->FileEditor->setText(QString::fromStdString("<No Contents>"));
}

tableEditWindow::~tableEditWindow()
{
    delete ui;
}

void tableEditWindow::on_pushButton_clicked()
{

}

void tableEditWindow::on_listWidget_itemSelectionChanged()
{
    QListWidgetItem * dummy = ui->listWidget->currentItem();
    string configname = dummy->text().toStdString();
    cout << configname << endl;
    string wholeTable = db->getTableHeaders("ConfigFileTable")
            + "\n"
            + db->getTable("ConfigFileTable")->createQuery("Select contents from ConfigFileTable where fileName = '"
                                                           +configname + "';");
    ui->FileContentView->setText(QString::fromStdString(wholeTable));
}
