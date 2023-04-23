#ifndef GLOBAL_CPP
#define GLOBAL_CPP
#include "global.h"
#include <QDebug>
QString LEVEL_NAME = "";
QVector<QSoundEffect*>playerList;
QVector<QSoundEffect*>backplayerList;
MusicPlayer *musicPlayer = new MusicPlayer;

//音效区
QString course_clear = ":/music/course_clear.wav";
QString Death = ":/music/death.wav";
QString FlagPoleMusic = ":/music/flagpole.wav";
QString GameOver = ":/music/game_over.mp3";
QString Invincible = ":/music/invincible.mp3";
QString MainTheme = ":/music/main_theme.mp3";
QString MainTheme_spedup = ":/music/main_theme_sped_up.mp3";
QString OutOfTime = ":/music/out_of_time.wav";
QString StageClear = ":/music/stage_clear.wav";
QString Start = ":/music/start.mp3";
QString World_clear = ":/music/world_clear.wav";
QString Begin = ":/sound/begin.wav";
QString BigJump = ":/sound/big_jump.mp3";
QString BrickSmash = ":/sound/brick_smash.mp3";
QString Bump = ":/sound/bump.mp3";
QString CoinMusic = ":/sound/coin.mp3";
QString count_down = ":/sound/count_down.mp3";
QString FireBall = ":/sound/fireball.mp3";
QString Kick = ":/sound/kick.mp3";
QString MainTheme_sped_up_instance = ":/sound/main_theme_sped_up - instance.mp3";
QString MainTheme_sped_up = ":/sound/main_theme_sped_up - instance.mp3";
QString OneUp = ":/sound/one_up.mp3";
QString Pipe = ":/sound/pipe.mp3";
QString PowerUp = ":/sound/powerup.mp3";
QString PowerUpAppers = ":/sound/powerup_appears.mp3";
QString SmallJump = ":/sound/small_jump.mp3";
QString Stomp = ":/sound/stomp.mp3";
void deleteMusic()
{

    for(int i=0;i<playerList.size();i++)
    {
        QSoundEffect *m = playerList[i];
        m->stop();
        playerList.remove(i);
    }
}
void stopAllMusic()
{
    for(int i=0;i<playerList.size();i++)
    {
        QSoundEffect *m = playerList[i];
        m->stop();
        playerList.remove(i);
    }
}

void deleteBackMusic()
{
    for(int i=0;i<backplayerList.size();i++)
    {
        QSoundEffect *m = backplayerList[i];
        m->stop();
        backplayerList.remove(i);
    }
}

void stopAllBackMusic()
{
    for(int i=0;i<backplayerList.size();i++)
    {
        QSoundEffect *m = backplayerList[i];
        m->stop();
        backplayerList.remove(i);
    }
}
#endif // GLOBAL_CPP
