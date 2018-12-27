#include "comdialog.h"
#include "ui_comdialog.h"
#include "comobject.h"
ComDialog::ComDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ComDialog)
{
    ui->setupUi(this);
}

ComDialog::~ComDialog()
{
    delete ui;
}

void ComDialog::on_okBtn_clicked()
{
    ComDriver::name = ui->nameCbx->currentText();
    ComDriver::baud = ui->baudCbx->currentText();
    ComDriver::databit = ui->databitCbx->currentText();
    ComDriver::stopbit = ui->stopbitCbx->currentText();
    ComDriver::parity = ui->parityCbx->currentText();
    accept();
}

void ComDialog::on_cancelBtn_clicked()
{
    reject();
}
