#include "saparamsdialog.h"
#include "ui_saparamsdialog.h"

SAParamsDialog::SAParamsDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SAParamsDialog)
{
    ui->setupUi(this);
}

SAParamsDialog::~SAParamsDialog()
{
    delete ui;
}

int SAParamsDialog::getInnerLoop(int d)
{
    int ret = ui->innerLoop->text().toInt();
    return ret == 0? d:ret;
}

double SAParamsDialog::getInitTemp(double d)
{
    double ret =ui->initTemp->text().toDouble();
    return  ret == 0? d:ret;
}

double SAParamsDialog::getFinalTemp(double d)
{
    double ret  =  ui->finalTemp->text().toDouble();
    return ret== 0? d:ret;
}

double SAParamsDialog::getAlpha(double d)
{
    double ret  = ui->alpha->text().toDouble();
    return ret== 0? d:ret;
}

double SAParamsDialog::getBeta(double d)
{
    double ret = ui->beta->text().toDouble();
    return ret== 0? d:ret;
}

void SAParamsDialog::on_buttonBox_accepted()
{
    this->acc = true;
    this->close();
}

void SAParamsDialog::on_buttonBox_rejected()
{
    this->acc = false;
    this->close();
}
