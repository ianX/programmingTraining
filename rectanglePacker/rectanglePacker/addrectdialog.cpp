#include "addrectdialog.h"
#include "ui_addrectdialog.h"

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
    acc = true;
    close();
}

void AddRectDialog::on_buttonBox_rejected()
{
    acc = false;
    close();
}
