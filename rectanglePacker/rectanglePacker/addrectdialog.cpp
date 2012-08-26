#include "addrectdialog.h"
#include "ui_addrectdialog.h"

#include <QMessageBox>

AddRectDialog::AddRectDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddRectDialog)
{
    ui->setupUi(this);
}

AddRectDialog::~AddRectDialog()
{
    delete ui;
}

int AddRectDialog::getWidth()
{
    return ui->width->text().toInt();
}

int AddRectDialog::getHeight()
{
    return ui->height->text().toInt();
}

void AddRectDialog::on_buttonBox_accepted()
{
    int w = getWidth();
    int h = getHeight();
    if(w <= 0 || h <= 0)
    {
        acc = false;
        QMessageBox::warning(this, tr("rectanglePacker"),
                             tr("input params error"), QMessageBox::Ok);
        return;
    }
    acc = true;
    close();
}

void AddRectDialog::on_buttonBox_rejected()
{
    acc = false;
    close();
}
