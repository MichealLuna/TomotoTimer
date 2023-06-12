
#include "audiolist.h"

#include<QDir>
#include<QFile>
#include<QString>
#include<QStringList>
#include<QTextStream>
#include<QIODevice>

#define FullPath "./musicList.txt"
#define JustFileName "./musicName.txt"

#define Filter ".mp3"
#define MusicRoot "c:/Users/ego"


AudioList::AudioList():
    m_currAudio(-1),
    m_currSize(0)
{
    m_fileFilter.append(".mp3");
    QFile fullPath(FullPath);
    QFile filename(JustFileName);

    if(!fullPath.exists()){
        //recursive search
        recursiveSearch(MusicRoot,m_audioList,&m_fileFilter);
    }else{
        //read audio list from ./musicList.txt file.
        readAudioInDisk(FullPath,m_audioList);
    }

    m_currAudio = m_audioList.size()>0?0:-1;
    assert(m_currAudio >= 0);

    _fullPath2FileName(m_audioList,m_audioName);

    m_currSize = m_audioName.size();

    fullPath.close();
    filename.close();
}

AudioList::~AudioList(){
    saveAudioInDisk(FullPath,m_audioList);
    saveAudioInDisk(JustFileName,m_audioName);
}

const int& AudioList::currIndex(){
    return m_currAudio;
}

QString& AudioList::prev(){
    assert(m_currAudio >= 0);
    //这里不考虑audioList为空的情况了
    if(m_currAudio == 0){
        m_currAudio = m_currSize-1;
    }else if(m_currAudio > 0){
        --m_currAudio;
    }
    return m_audioList[m_currAudio];
}

QString& AudioList::next(){
    if(m_currAudio == m_currSize - 1){
        m_currAudio = 0;
    }else{
        ++m_currAudio;
    }
    return m_audioList[m_currAudio];
}

QString& AudioList::curr(){
    return m_audioList[m_currAudio];
}

QStringList& AudioList::getAudioList(){
    return m_audioList;
}

void AudioList::addAudio(const QString &audioPath){
    m_audioList.append(audioPath);
}

void AudioList::delAudio(const QString &audioPath){
    int len = m_audioList.size();
    for(int i = 0; i <len; ++i){
        if(m_audioList[i] == audioPath){
            m_audioList.removeAt(i);
            break;
        }
    }
}

QStringList& AudioList::getAudioNameList(){
    return m_audioName;
}

void AudioList::updateList(){
    m_audioList.clear();
    recursiveSearch(MusicRoot,m_audioList,&m_fileFilter);
    _fullPath2FileName(m_audioList,m_audioName);
    m_currAudio = 0;
    m_currSize = m_audioList.size();
}

void AudioList::specifyDirSearch(const QString &path){
    m_audioList.clear();
    recursiveSearch(path,m_audioList,&m_fileFilter);
    _fullPath2FileName(m_audioList,m_audioName);
    m_currAudio = 0;
    m_currSize = m_audioList.size();
}

/*****************************************************************************/
/*
* helper function
*/
/*******************************************************************************/

void recursiveSearch(const QString &path, QStringList &list,QStringList* filter){
    QDir dir(path);
    QFileInfoList fileInfos = dir.entryInfoList(QDir::Files | QDir::Dirs | QDir::NoDotAndDotDot);

    foreach(QFileInfo fileInfo,fileInfos){
        if(fileInfo.isDir()){
            recursiveSearch(fileInfo.absoluteFilePath(),list,filter);
        }else if(fileInfo.isFile()){
            const QString& tmpFileInfo = fileInfo.fileName();
            if(filter == nullptr)
                list.append(fileInfo.absoluteFilePath());
            else{
                foreach(QString type,*filter){
                    if(tmpFileInfo.contains(type)){
                        list.append(fileInfo.absoluteFilePath());
                        break;
                    }
                }
            }
        }
    }
}

void currentDirSearch(const QString &path, QStringList &list,QStringList* filter){
    QDir dir(path);
    QFileInfoList fileInfos = dir.entryInfoList(QDir::Files);

    foreach(QFileInfo fileInfo,fileInfos){
        foreach(QString type,*filter){
            const QString& tmpFileInfo = fileInfo.fileName();
            if(filter == 0){
                list.append(fileInfo.absoluteFilePath());
            }else{
                if(tmpFileInfo.contains(type)){
                    list.append(tmpFileInfo);
                    break;
                }
            }
        }
    }
}

void readAudioInDisk(const QString& path,QStringList& list){
    QFile file(path);
    file.open(QIODevice::ReadOnly|QIODevice::Text);

    QTextStream in(&file);
    while(!in.atEnd()){
        list.append(std::move(in.readLine()));
    }
    file.close();
}
void saveAudioInDisk(const QString& path,QStringList& list){
    QFile file(path);
    file.open(QIODevice::WriteOnly|QIODevice::Text);

    QTextStream out(&file);
    foreach(QString line,list){
        line += "\n";
        out << line;
    }
    file.close();
}

QString fullPath2FileName(const QString &fullpath){
    int begin = -1;
    int end = -1;

    int len = fullpath.size();
    for(int i = 0; i < len ; ++i){
        QChar ch = fullpath[i];
        if(ch == '/' || ch =='\\'){
            begin = i;
        }else if(ch == '.'){
            end = i;
        }
    }
    QString ret;
    ret.reserve(end-begin);
    for(int i = begin+1; i < end; ++i){
        ret += fullpath[i];
    }
    return std::move(ret);
}

void _fullPath2FileName(QStringList& fullPath,QStringList& justName){
    int i = 1;
    justName.clear();
    foreach(QString path,fullPath){
        QString tmp;
        tmp = QString("[%1]:").arg(i++);
        tmp += fullPath2FileName(path);
        justName.append(std::move(tmp));
    }
}
