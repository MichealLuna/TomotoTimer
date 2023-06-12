
#ifndef AUDIOLIST_H
#define AUDIOLIST_H

#include<QStringList>

class QString;

class AudioList
{
public:
    AudioList();
    ~AudioList();
    QString& prev();
    QString& next();
    QString& curr();
    void updateList();
    void specifyDirSearch(const QString& path);
    const int& currIndex();
    QStringList& getAudioList();
    QStringList& getAudioNameList();
public:
    void addAudio(const QString& audioPath);
    void delAudio(const QString& audioPath);
private:
    int m_currAudio;
    int m_currSize;
    QStringList m_fileFilter;
    QStringList m_audioList;
    QStringList m_audioName;
};

void recursiveSearch(const QString& path,QStringList& list,QStringList* filter = nullptr);
void currentDirSearch(const QString& path,QStringList& list,QStringList* filter = nullptr);

void readAudioInDisk(const QString& path,QStringList& list);
void saveAudioInDisk(const QString& path,QStringList& list);

QString fullPath2FileName(const QString& fullpath);
void _fullPath2FileName(QStringList &fullPath, QStringList &justName);

#endif // AUDIOLIST_H
