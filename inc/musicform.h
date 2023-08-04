#ifndef MUSICFORM_H
#define MUSICFORM_H

#include <QWidget>
#include "audioplayer.h"

#define UpdateSliderValueInMinMiliSeconds 10

class QString;
class QCloseEvent;

namespace Ui {
class MusicForm;
}

class MusicForm : public QWidget
{
    Q_OBJECT

public:
    explicit MusicForm(QWidget *parent = nullptr);
    ~MusicForm();
private slots:
    void prev();
    void next();
    void play();
    void stop();
    void pause();
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();
    void on_pushButton_4_clicked();
    void on_pushButton_5_clicked();
    void on_pushButton_6_clicked();
    void onCurrentLineLight();
    void currAudio();
    void updateSliderMax(qint64 pos);
    void setSliderVal(int);
    void updateSlider();
    void sliderPressed();
    void sliderMoved(int);
    void sliderReleased();
signals:
    void changedPosition(int);
protected:
    void updateTextBroswer();
    void __updateSlider(int pos);
    void closeEvent(QCloseEvent *event);
private:
    Ui::MusicForm *ui;
    bool m_isPlaying = false;
    AudioPlayer* m_player;
    QString m_specifyPath;
    QTimer m_timer; // use for updating splider
};

#endif // MUSICFORM_H
