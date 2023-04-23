#include "musicplayer.h"
#include <QMediaPlayer>
#include <global.h>
#include <QDebug>
MusicPlayer::MusicPlayer(QObject *parent) : QObject(parent)
{
    mediaPlayer = new QMediaPlayer;
    backPlayer = new QMediaPlayer;
}

void MusicPlayer::play(QString str)
{
    mediaPlayer->setSource(QUrl::fromLocalFile(str));
    mediaPlayer->play();
    qDebug()<<str<<"音效的状态:"<<mediaPlayer->playbackState();
                                            playerList.append(mediaPlayer);
}

void MusicPlayer::backMusicPlay(QString str)
{
    backPlayer->setSource(QUrl::fromLocalFile(str));
    backPlayer->play();
    qDebug()<<str<<"音效的状态:"<<backPlayer->playbackState();
                                            backplayerList.append(backPlayer);
}

