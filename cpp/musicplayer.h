
#ifndef MUSICPLAYER_H
#define MUSICPLAYER_H

#include <QObject>
#include<QSoundEffect>
#include <QMediaPlayer>
class MusicPlayer : public QObject
{
    Q_OBJECT
public:
    explicit MusicPlayer(QObject *parent = nullptr);
    QMediaPlayer *mediaPlayer;
    QMediaPlayer *backPlayer;
    void play(QString str);
    void backMusicPlay(QString str);
signals:

public slots:
};

#endif // MUSICPLAYER_H
