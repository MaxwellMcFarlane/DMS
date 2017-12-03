#ifndef CALIBRATIONWINDOW_H
#define CALIBRATIONWINDOW_H

#include <QWidget>

namespace Ui {
class calibrationWindow;
}

class calibrationWindow : public QWidget
{
    Q_OBJECT

public:
    explicit calibrationWindow(QWidget *parent = 0);
    ~calibrationWindow();

private:
    Ui::calibrationWindow *ui;
};

#endif // CALIBRATIONWINDOW_H
