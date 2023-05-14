
#ifndef LEVEL1_H
#define LEVEL1_H

#include <QWidget>
#include<QPainter>
#include<QDebug>
#include<QString>
#include<QTimer>
#include<QKeyEvent>
#include<QDialog>
#include"mary.h"
#include"brick.h"
#include"unknown.h"
#include"mushroom.h"
#include"master.h"
#include"pipe.h"
#include"gamepause.h"
#include<mypushbutton.h>
#include"fire.h"
#include"castle.h"

class level1 : public QWidget {
    Q_OBJECT

public:
    explicit level1(QWidget *parent = nullptr);
    int timer1;
    int timer2;
    int timer3;
    bool is_kill_timer2;
    bool game_start;
    bool open;
    double time;
    int score;
    bool is_press_x;
    bool is_win;
    QString key;
    Mary *mary;
    Brick *brick;
    Pipe *pipe;
    Unknown *unknown;
    MushRoom *mushroom;
    GamePause *Pause;
    Master *master;
    Fire *fire;
    Castle *castle;

    void paintEvent(QPaintEvent *);//绘图事件
    void keyPressEvent(QKeyEvent *event);//键盘按下
    void keyReleaseEvent(QKeyEvent *event);//键盘抬起
    void timerEvent(QTimerEvent *event);//定时器
    void Game_Init();

    void Die_Init();

    void Pause_Init();

    void Pause_Game_Init();

    void Fall_Down(int &y);

    void Jump_Collision();//角色跳跃碰撞检测
    void Move_Collision();//移动碰撞检测
    bool level1_Win(bool is_win);
    void Game_Over();
signals:
    void back();
private:

};

#endif // LEVEL1_H
