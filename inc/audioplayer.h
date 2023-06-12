
#ifndef AUDIOPLAYER_H
#define AUDIOPLAYER_H


#include <QObject>
#include <QTimer>
#include<QMediaPlayer>
#include "audiolist.h"

class QAudioOutput;

class AudioPlayer : public QObject
{
    Q_OBJECT
public:

    explicit AudioPlayer(QObject* parent = nullptr);
    ~AudioPlayer();

    void prev();
    void next();
    void play();
    void stop();
    void pause();
    void upDateList();
    void specifyDirSearch(const QString& path);

    qint64 getCurentaAudioPosition();
    QStringList& getAudioList();
    QStringList& getAudioNameList();
    QString getPlayingAudioName();
protected:
    void _updateMaxPosition();
private slots:
    void State(QMediaPlayer::PlaybackState state);
    void setPosition(int);
    void updatePosition(qint64);
signals:
    void updateCurrentAudio();
    void positionChanged(int);
    void audioMaxPositionChanged(qint64);
protected:


public:
    QMediaPlayer* m_player;
private:
    QAudioOutput* m_audio;
    AudioList m_audioList;
    bool m_isOperation = true;
};

#endif // AUDIOPLAYER_H
