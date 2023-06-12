
#include "audioplayer.h"

#include<QAudioOutput>

AudioPlayer::AudioPlayer(QObject* parent):
    QObject(parent)
    ,m_player(new QMediaPlayer)
    ,m_audio(new QAudioOutput)
{
    m_audio->setVolume(20);
    m_player->setAudioOutput(m_audio);
    m_player->setSource(QUrl::fromLocalFile(m_audioList.curr()));
    //m_player->play();

    //connect
    connect(m_player,SIGNAL(playbackStateChanged(QMediaPlayer::PlaybackState)),
            this,SLOT(State(QMediaPlayer::PlaybackState)));
    connect(m_player,SIGNAL(positionChanged(qint64)),this,SLOT(updatePosition(qint64)));
}

AudioPlayer::~AudioPlayer(){
    delete m_audio;
    delete m_player;
}

void AudioPlayer::_updateMaxPosition(){
    emit audioMaxPositionChanged(m_player->duration());
}

void AudioPlayer::prev(){
    //setSource 会产生stopStated，进而触发状态里的next！
    m_isOperation = false;
    m_player->setSource(QUrl::fromLocalFile(m_audioList.prev()));
    _updateMaxPosition();
    m_player->play();
    m_isOperation = true;
}

void AudioPlayer::next(){
    //先暂停更严重，无限递归。
    m_isOperation = false;
    m_player->setSource(QUrl::fromLocalFile(m_audioList.next()));
    _updateMaxPosition();
    m_player->play();
    m_isOperation = true;
}

void AudioPlayer::play(){
    _updateMaxPosition();
    m_player->play();
}

void AudioPlayer::stop(){
    m_player->stop();
}

void AudioPlayer::pause(){
    m_player->pause();
}

void AudioPlayer::State(QMediaPlayer::PlaybackState state){
    switch(state){
    case QMediaPlayer::StoppedState:
        if(m_isOperation == true){
            m_player->setSource(QUrl::fromLocalFile(m_audioList.next()));
            emit updateCurrentAudio();
            _updateMaxPosition();
            m_player->play();
        }
        break;
    case QMediaPlayer::PlayingState:
        //do nothing
        break;
    case QMediaPlayer::PausedState:
        //do nothing
        break;
    }
}

QStringList& AudioPlayer::getAudioList(){
    return m_audioList.getAudioList();
}

QStringList& AudioPlayer::getAudioNameList(){
    return m_audioList.getAudioNameList();
}

QString AudioPlayer::getPlayingAudioName(){
    return m_audioList.getAudioNameList().at(m_audioList.currIndex());
}

void AudioPlayer::upDateList(){
    m_audioList.updateList();
}

void AudioPlayer::specifyDirSearch(const QString &path){
    m_audioList.specifyDirSearch(path);
}

void AudioPlayer::setPosition(int pos){
    m_player->setPosition(static_cast<qint64>(pos));
}

//如果播放长度超过了2^31毫秒有隐患
void AudioPlayer::updatePosition(qint64 pos){
    emit positionChanged(static_cast<int>(pos));
}

qint64 AudioPlayer::getCurentaAudioPosition(){
    return m_player->position();
}
