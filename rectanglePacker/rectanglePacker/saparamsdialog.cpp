#include "saparamsdialog.h"
#include "ui_saparamsdialog.h"

#include <QMessageBox>

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
    int loop = getInnerLoop(0);
    double itemp = getInitTemp(0);
    double ftemp = getFinalTemp(0);
    double alp = getAlpha(0);
    double bta = getBeta(0);
    if(loop < 0 || itemp < 0 || ftemp < 0 || alp <0 || alp >=1 || bta < 0 || bta >=2)
    {
        QMessageBox::warning(this, tr("rectanglePacker"),
                             tr("input params error"), QMessageBox::Ok);
        return;
    }
    this->acc = true;
    this->close();
}

void SAParamsDialog::on_buttonBox_rejected()
{
    this->acc = false;
    this->close();
}
