#ifndef ADDRECTDIALOG_H
#define ADDRECTDIALOG_H

#include <QDialog>

namespace Ui {
class AddRectDialog;
}

class AddRectDialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit AddRectDialog(QWidget *parent = 0);
    ~AddRectDialog();
    int getWidth();
    int getHeight();
    bool isAccepted(){return acc;}
    
private slots:
    void on_buttonBox_accepted();

    void on_buttonBox_rejected();

private:
    Ui::AddRectDialog *ui;
    bool acc;
};

#endif // ADDRECTDIALOG_H
