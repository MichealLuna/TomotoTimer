#include "../inc/recordworkdialog.h"
#include "ui_recordworkdialog.h"

RecordWorkDialog::RecordWorkDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::RecordWorkDialog)
{
    ui->setupUi(this);
}

RecordWorkDialog::~RecordWorkDialog()
{
    delete ui;
}

void RecordWorkDialog::on_buttonBox_accepted()
{
    QString workContext = tr(" ");
    workContext += ui->lineEdit->text();
    workContext += tr("【WorkContext】: ");
    workContext += ui->textEdit->toPlainText();

    emit updateRecord(workContext);
    hide();
    clearContext();
}

void RecordWorkDialog::clearContext(){
    ui->lineEdit->clear();
    ui->textEdit->clear();
}
