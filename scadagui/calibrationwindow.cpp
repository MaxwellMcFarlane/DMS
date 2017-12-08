#include "calibrationwindow.h"
#include "ui_calibrationwindow.h"

calibrationWindow::calibrationWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::calibrationWindow)
{
    ui->setupUi(this);
}

calibrationWindow::~calibrationWindow()
{
    delete ui;
}
