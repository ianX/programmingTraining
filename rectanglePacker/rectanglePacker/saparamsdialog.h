#ifndef SAPARAMSDIALOG_H
#define SAPARAMSDIALOG_H

#include <QDialog>

namespace Ui {
class SAParamsDialog;
}

class SAParamsDialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit SAParamsDialog(QWidget *parent = 0);
    ~SAParamsDialog();

    int getInnerLoop(int);
    double getInitTemp(double);
    double getFinalTemp(double);
    double getAlpha(double);
    double getBeta(double);
    bool isAccepted(){return acc;}

private slots:
    void on_buttonBox_accepted();

    void on_buttonBox_rejected();

private:
    Ui::SAParamsDialog *ui;
    bool acc;
};

#endif // SAPARAMSDIALOG_H
