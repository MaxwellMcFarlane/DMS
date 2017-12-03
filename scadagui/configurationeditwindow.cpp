#include "configurationeditwindow.h"
#include "ui_configurationeditwindow.h"

ConfigurationEditWindow::ConfigurationEditWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ConfigurationEditWindow)
{
    ui->setupUi(this);
}

ConfigurationEditWindow::ConfigurationEditWindow(QWidget *parent, DMS *db):
    QWidget(parent),
    ui(new Ui::ConfigurationEditWindow)
{
    ui->setupUi(this);
    this->db = db;
    ui->listWidget->addItem(new QListWidgetItem(QString::fromStdString("ControlState_config.txt")));
    ui->FileEditor->setText(QString::fromStdString("<No Contents>"));
}

ConfigurationEditWindow::~ConfigurationEditWindow()
{
    delete ui;
}

bool ConfigurationEditWindow::checkModeManagerConfigure(string file){
    string stateDeclaration("STATES:");
    string branchDeclaration("BRANCHES:");
    ModeManager m;
    bool state = false;
    bool branch = false;
    if(file.empty()){return false;}
    vector<char*> list;
    char * it;
    it = strtok((char*)file.c_str(), ".\n");
    while(it != NULL){
        if(!isdigit(*it))list.push_back(it);
        it = strtok(NULL, ".\n");
    }

    for(int i = 0; i < (int)list.size(); i++){cout << list.at(i) << endl;}

    for(int i = 0; i < (int)list.size(); i++){
        string line(list.at(i));
        if(line.at(0) == '#'){}
        if(list.size() != 3){return false;}
        else if(strcmp(list.at(i),stateDeclaration.c_str()) == 0){state = true; branch = false;}
        else if(!line.compare(branchDeclaration)){state = false;branch = true;}
        else if (state) {
            vector<string > stateLine= m.split(line,',');
            for(string s: stateLine){
                State tempState(s);
                m.states.push_back(tempState);
            }
        }
        else if (branch) {
                vector<string> branchLine= m.split(line,',');
//                for(int i = 0; i < (int)branchLine.size(); i++){cout << branchLine.at(i) << endl;}
                State from= m.getState(branchLine[0]);
                State to = m.getState(branchLine[1]);
                if(!from.name.compare("NULL")){return false;}
                if(!to.name.compare("NULL")){return false;}
        }
    }
    return true;
}

void ConfigurationEditWindow::on_getfileButton_clicked()
{
    QListWidgetItem * dummy = ui->listWidget->currentItem();
    string configname = dummy->text().toStdString();
    if(true){
        string dummy = db->getTable("ConfigFileTable")->createQuery("Select contents from ConfigFileTable where fileName = '"
                                                                    +configname + "';");
        vector<char*> list;
        char * it;
        it = strtok((char*)dummy.c_str(), "\n");
        while(it != NULL){
            list.push_back(it);
            it = strtok(NULL, "\n");
        }
        string print;
        for(int i = 0; i < (int)list.size(); i++){
            print += to_string(i) + ". " + list[i] + "\n";
        }
        ui->FileEditor->setText(QString::fromStdString(print));
    }
    else{
        ui->FileEditor->setText(QString::fromStdString("Bad Constraints"));
    }
}

void ConfigurationEditWindow::on_Savebutton_clicked()
{
    QListWidgetItem * dummy = ui->listWidget->currentItem();
    string configname = dummy->text().toStdString();

    string edits = ui->FileEditor->toPlainText().toStdString();
    /**
      try{
      mode.configure(txtFile);
}
catch(const std::exception &e){
 e.what();//the error message
}
      **/
    if(!checkModeManagerConfigure(edits)){QMessageBox::about(this,"Error","Error File Corrupt Resolve Error");}
    db->getTable("ConfigFileTable")->updateTable("filename = " + configname,edits);
}

void ConfigurationEditWindow::on_listWidget_itemSelectionChanged()
{
    QListWidgetItem * dummy = ui->listWidget->currentItem();
    string configname = dummy->text().toStdString();
    string wholeTable = db->getTableHeaders("ConfigFileTable")
            + "\n"
            + db->getTable("ConfigFileTable")->createQuery("Select contents from ConfigFileTable where fileName = '"
                                                           +configname + "';");
    ui->FileContentView->setText(QString::fromStdString(wholeTable));
}
