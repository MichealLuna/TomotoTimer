#include "../inc/musicform.h"
#include "ui_musicform.h"

#include<QFileDialog>
#include<QDir>

MusicForm::MusicForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MusicForm)
    ,m_player(new AudioPlayer(this))
    ,m_timer(this)
{
    ui->setupUi(this);
    setFixedSize(600,200);
    setWindowTitle("Music Music Music");
    currAudio();

    //init timer
    m_timer.setInterval(UpdateSliderValueInMinMiliSeconds);
    connect(&m_timer,SIGNAL(timeout()),this,SLOT(updateSlider()));
    m_timer.start();

    ui->lcdNumber->setDigitCount(8);
    ui->lcdNumber->setMode(QLCDNumber::Dec);
    ui->lcdNumber->setSegmentStyle(QLCDNumber::Flat);
    ui->lcdNumber->setStyleSheet("border: 1px solid green; color: green; background:silver;");

    updateTextBroswer();
    //
    connect(ui->textBrowser,SIGNAL(cursorPositionChanged()),this,SLOT(onCurrentLineLight()));
    connect(ui->pushButton_2,SIGNAL(clicked(bool)),this,SLOT(currAudio()));
    connect(ui->pushButton,SIGNAL(clicked(bool)),this,SLOT(currAudio()));
    connect(m_player,SIGNAL(updateCurrentAudio()),this,SLOT(currAudio()));

    /*
     * 1、当音乐播放时，需要告知slider随着播放改变位置
     * 2、当拖动slider改变播放位置时，需要告知播放器改变音乐位置
     * 3、触发1、2条件时，除了告诉播放器，也要告诉musicForm窗口
    */
    ui->horizontalSlider->setSingleStep(500);
    ui->horizontalSlider->setMinimum(0);
    connect(m_player,SIGNAL(audioMaxPositionChanged(qint64)),this,SLOT(updateSliderMax(qint64)));
    connect(ui->horizontalSlider,SIGNAL(sliderPressed()),this,SLOT(sliderPressed()));
    connect(ui->horizontalSlider,SIGNAL(sliderMoved(int)),this,SLOT(sliderMoved(int)));
    connect(ui->horizontalSlider,SIGNAL(sliderReleased()),this,SLOT(sliderReleased()));
    connect(this,SIGNAL(changedPosition(int)),m_player,SLOT(setPosition(int)));
}

MusicForm::~MusicForm()
{
    delete ui;
}

void MusicForm::updateTextBroswer(){
    ui->textBrowser->clear();
    foreach(QString line,m_player->getAudioNameList()){
        ui->textBrowser->append(line);
    }
}

void MusicForm::currAudio(){
    ui->label_2->setText(tr("当前播放：") + m_player->getPlayingAudioName());
}

void MusicForm::updateSliderMax(qint64 pos){
    ui->horizontalSlider->setMaximum(static_cast<int>(pos));
}

void MusicForm::onCurrentLineLight(){
    QList<QTextBrowser::ExtraSelection> extraSelection;
    QTextBrowser::ExtraSelection selection;
    QColor color= QColor(Qt::gray).lighter(100);
    selection.format.setBackground(color);
    selection.format.setProperty(QTextFormat::FullWidthSelection,true);
    selection.cursor = ui->textBrowser->textCursor();
    selection.cursor.clearSelection();

    extraSelection.append(selection);
    ui->textBrowser->setExtraSelections(extraSelection);
}

void MusicForm::prev(){
    m_player->prev();
}

void MusicForm::next(){
    m_player->next();
}

void MusicForm::play(){
    m_player->play();
    m_timer.start();
}

void MusicForm::stop(){
    m_player->stop();
    m_timer.stop();
}

void MusicForm::pause(){
    m_player->pause();
    m_timer.stop();
}

void MusicForm::on_pushButton_clicked()
{
    next();
}

void MusicForm::on_pushButton_2_clicked()
{
    prev();
}

//btn play or stop
void MusicForm::on_pushButton_4_clicked()
{
    //正在播放
    if(m_isPlaying){
        ui->pushButton_4->setText(tr("暂停"));
        pause();
        m_isPlaying = false;
    }else{
        ui->pushButton_4->setText(tr("播放"));
        play();
        m_isPlaying = true;
    }
}

void MusicForm::on_pushButton_5_clicked()
{
    m_player->upDateList();
    updateTextBroswer();
}


void MusicForm::on_pushButton_6_clicked()
{
    QString path = QFileDialog::getExistingDirectory();
    m_player->specifyDirSearch(path);
    updateTextBroswer();
}

void MusicForm::setSliderVal(int pos){
    ui->horizontalSlider->setValue(pos);
}

void MusicForm::__updateSlider(int pos){
    int hours = (pos / (1000*60*60) % 24);
    int minute = (pos / (1000*60) % 60);
    int seconds = (pos /(1000) % 60);
    ui->lcdNumber->display(QString("%1:%2:%3").arg(hours).arg(minute).arg(seconds));
    ui->horizontalSlider->setValue(pos);
}

void MusicForm::updateSlider(){
    qint64 curr = m_player->getCurentaAudioPosition();
    __updateSlider(static_cast<int>(curr));
}

void MusicForm::sliderPressed(){
    m_timer.stop();
    int val = ui->horizontalSlider->value();
    __updateSlider(val);
}

void MusicForm::sliderMoved(int pos){
    __updateSlider(pos);
}

void MusicForm::sliderReleased(){
    int val = ui->horizontalSlider->value();
    emit changedPosition(val);
    m_timer.start();
}

//void MusicForm::closeEvent(QCloseEvent *event){
//    (void*)event;
//    hide();
//}
