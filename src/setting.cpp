#include "../inc/setting.h"
#include "ui_setting.h"
#include<QFileDialog>

Setting::Setting(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Setting)
{
    ui->setupUi(this);
    ui->checkBox->setChecked(false);
    ui->checkBox_2->setChecked(true);

    setWindowTitle("Setting Selection");
    connect(ui->checkBox,SIGNAL(stateChanged(int)),this,SLOT(recordStateChanged(int)));
    connect(ui->checkBox_2,SIGNAL(stateChanged(int)),this,SLOT(saveStateChanged(int)));
}

Setting::~Setting()
{
    delete ui;
}

void Setting::on_pushButton_2_clicked()
{
   QString tomatoTimes =  ui->lineEdit->text();
   emit updateTomato(tomatoTimes.toDouble());
}


void Setting::on_pushButton_3_clicked()
{
   QString happyTimes = ui->lineEdit_2->text();
   emit updateHappy(happyTimes.toDouble());
}

void Setting::recordStateChanged(int val){
    emit updateRecordState(val);
}

void Setting::saveStateChanged(int val){
    emit updateSaveState(val);
}

//void Setting::on_pushButton_clicked()
//{
//    QString fileFullPath =  QFileDialog::getOpenFileName(this,tr("file"),"./",tr("music(*.mp3)"));
//    emit updateMuisc(fileFullPath);
//    ui->textBrowser->setText(fileFullPath);
//}

