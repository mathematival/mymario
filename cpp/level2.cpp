#include "level2.h"
#include<musicplayer.h>
#include<QSoundEffect>
#include <QDebug>
#include <global.h>
#include<QPixmap>

level2::level2(QWidget *parent) : QWidget(parent) {
    setWindowTitle("马里奥");//设置标题
    setFixedSize(800, 545);//设置窗口大小
    Game_Init();
    Pause_Init();
    QTimer::singleShot(1000, this, [=]() {
        timer1 = startTimer(15);
        timer3 = startTimer(50);
        game_start = true;
    });
    this->setFocusPolicy(Qt::StrongFocus);
}

void level2::Pause_Init() {
    Pause = new GamePause();//初始化暂停窗口
    MyPushButton *btn_continue = new MyPushButton(":/photo/continueGame.png");//添加继续游戏按钮
    btn_continue->setParent(Pause);
    btn_continue->setFixedSize(150, 75);
    btn_continue->setIconSize(QSize(150, 75));
    btn_continue->move(20, 10);
    connect(btn_continue, &QPushButton::clicked, this, [=]() {
        btn_continue->zoom1();//加载动画
        btn_continue->zoom2();
        QTimer::singleShot(500, this, [=]() {
            timer1 = startTimer(15);
            timer3 = startTimer(40);
            mary->walk_state = 0;//初始化mary的行走状态
            key = "nullptr";
            Pause->close();
            update();
        });
    });
    MyPushButton *initGame = new MyPushButton(":/photo/initGame.png");//添加重新开始按钮
    initGame->setParent(Pause);
    initGame->setFixedSize(150, 75);
    initGame->setIconSize(QSize(150, 75));
    initGame->move(20, 90);
    connect(initGame, &QPushButton::clicked, this, [=]() {
        initGame->zoom1();
        initGame->zoom2();
        QTimer::singleShot(500, this, [=]() {
            Pause_Game_Init();//游戏初始化
            Pause->close();
            QTimer::singleShot(500, this, [=]() {
                timer1 = startTimer(15);
                timer3 = startTimer(50);
                game_start = true;
            });
            update();
        });
    });
    MyPushButton *btn_exit = new MyPushButton(":/photo/start.png");//添加退出游戏按钮
    btn_exit->setParent(Pause);
    btn_exit->setFixedSize(150, 75);
    btn_exit->setIconSize(QSize(150, 75));
    btn_exit->move(20, 170);
    connect(btn_exit, &QPushButton::clicked, this, [=]() {
        btn_exit->zoom1();
        btn_exit->zoom2();
        QTimer::singleShot(500, this, [=]() {
            this->close();
        });
    });
}

void level2::timerEvent(QTimerEvent *event) {
    if (event->timerId() == timer1 && mary->is_die) {
        mary->Mary_die();
        Die_Init();
        update();
        return;
    }
    if (event->timerId() == timer1) {
        mary->Mary_Move(key);
        mary->Jump_And_Down();
        Jump_Collision();
        Move_Collision();
        brick->ShatterState();
        mushroom->Move_state();
        master->Master_Move();
        bullet->Bullet_Move();
        Die_Init();
        Fall_Down(mary->y);
        fire->Fire_state();
        update();
    }

    if (event->timerId() == timer2) {
        mary->Mary_Move(key);
    }

    if (event->timerId() == timer3) {
        time -= 0.05;
        if(time<=0.0){
            Game_Over();
        };
        unknown->Unknown_State();
        unknown->Crash_state();
    }
}

void level2::keyPressEvent(QKeyEvent *event) {
    if (!mary->is_die) {
        switch (event->key()) {
        case Qt::Key_Right:
            mary->direction = key = "right";
            break;
        case Qt::Key_Left:
            mary->direction = key = "left";
            break;
        case Qt::Key_Z:
            timer2 = startTimer(25);
            is_kill_timer2 = false;
            break;
        case Qt::Key_Space:
            mary->is_jump = true;
            break;
        case Qt::Key_B:
            if (game_start) {
                killTimer(timer1);
                if (is_kill_timer2) {
                    killTimer(timer2);
                }
                killTimer(timer3);
                Pause->setParent(this);
                Pause->open();
            }
            break;
        case Qt::Key_C:
            if (mary->life < 8) {
                mary->life++;
            }
        case Qt::Key_X:
            if (!is_press_x && !mary->is_jump && mary->is_jump_end && mary->colour == 3) {
                is_press_x = true;
                fire->Fire_xy();
            }
            break;
        case Qt::Key_W:
            is_press_x = true;
            fire->Fire_xy();
        }
    }
}

void level2::keyReleaseEvent(QKeyEvent *event) {
    if (!mary->is_die) {
        switch (event->key()) {
        case Qt::Key_Right:
            mary->walk_state = 0;
            key = "null";
            break;
        case Qt::Key_Left:
            mary->walk_state = 0;
            key = "null";
            break;
        case Qt::Key_Z:
            is_kill_timer2 = true;
            killTimer(timer2);
            break;
        case Qt::Key_Space:
            mary->is_jump = false;
            mary->is_space_release = true;
            break;
        case Qt::Key_X:
            is_press_x = false;
            break;
        }
    }
}

void level2::paintEvent(QPaintEvent *) {
    QPainter painter(this);
    if(mary->life<=0){
        painter.drawPixmap(0, 0, 800, 545, QPixmap(":/photo/gameover.png"));
        return;
    }
    if (!game_start) {
        painter.drawPixmap(0, 0, 800, 545, QPixmap(":/photo/blackground2.png"));
        painter.drawPixmap(300, 250, 40, 40, QPixmap(":/photo/life.png"));
        painter.setPen(QColor(255, 255, 255));
        QFont font;
        font.setPointSize(35);
        painter.setFont(font);
        painter.drawText(360, 280, "x");
        painter.drawText(80, 38, "times:");
        painter.drawText(220, 38, QString::number(time, 'f', 1));
        painter.drawText(600, 38, "coin:");
        painter.drawText(720, 38, QString::number(unknown->coin));
        font.setPointSize(45);
        painter.setFont(font);
        painter.drawText(400, 287, QString::number(mary->life));
        return;
    }
    painter.drawPixmap(0, 0, 800, 550, QPixmap(":/photo/sky.png"));//画背景
    painter.drawPixmap(230, 10, QPixmap(":/photo/coin.png"), 0, 0, 30, 30);
    painter.drawPixmap(380, 10, 30, 30, QPixmap(":/photo/score.png"));
    painter.setFont(QFont("Times", 45, QFont::Bold));
    painter.drawText(280, 48, QString::number(unknown->coin));
    painter.drawText(430, 48, QString::number(score));
    for (int i = 1; i <= mary->life; i++) {
        painter.drawPixmap(800 - i * 35, 10, 30, 30, QPixmap(":/photo/life.png"));
    }
    painter.drawPixmap(10, 12, 30, 30, QPixmap(":/photo/time.png"));
    painter.drawText(50, 48, QString::number(time, 'f', 1));
    painter.drawPixmap(0, 500, QPixmap(":/photo/ground.png"), mary->ground_state, 0, 800, 45);//画地板
    if (mary->x > 7800) {
        QVector < QVector < int >> ::iterator
            it = castle->m.begin()->begin();
        painter.drawPixmap(*it->begin() - mary->x, *(it->begin() + 1), 200, 200, QPixmap(":/photo/castle.png"));
    }
    if (mushroom->mushroom_state != 0) {
        painter.drawPixmap(mushroom->mushroom_x - mary->x, mushroom->mushroom_y, 40, 40,
                           QPixmap(":/photo/mushroom" + QString::number(mary->colour) + ".png"));
    }
    for (QVector < QVector < int >> ::iterator it = brick->m.begin()->begin(); it != brick->m.begin()->end();
         it++)
    {
        if (*(it->begin()) - mary->x > -50 && *(it->begin()) - mary->x < 800 && *(it->begin() + 2) == 1) {
            painter.drawPixmap(*(it->begin()) - mary->x, *(it->begin() + 1), 50, 40, QPixmap(":/photo/brick1.png"));
        }
    }
    for (QVector < QVector < int >> ::iterator it = flower->m.begin()->begin(); it != flower->m.begin()->end();
         it++)
    {
        if (*(it->begin()) - mary->x > -50 && *(it->begin()) - mary->x < 800 && *(it->begin() + 2) == 1) {
            painter.drawPixmap(*(it->begin()) - mary->x, *(it->begin() + 1), 50, 40, QPixmap(":/photo/flower.png"));
        }
    }
    for (QVector < QVector < int >> ::iterator it = unknown->m.begin()->begin(); it != unknown->m.begin()->end();
         it++)
    {
        if (*(it->begin()) - mary->x > -50 && *(it->begin()) - mary->x < 800 && *(it->begin() + 2) != 0) {
            painter.drawPixmap(*(it->begin()) - mary->x, *(it->begin() + 1), QPixmap(":/photo/unknown.png"),
                               unknown->unknown_state, 0, 50, 40);
        } else if (*(it->begin()) - mary->x > -50 && *(it->begin()) - mary->x < 800 && *(it->begin() + 2) == 0) {
            painter.drawPixmap(*(it->begin()) - mary->x, *(it->begin() + 1), 50, 40,
                               QPixmap(":/photo/unknown_after.png"));
        }
    }
    if (unknown->coin_state > 0) {
        painter.drawPixmap(unknown->coin_x - mary->x, unknown->coin_y, QPixmap(":/photo/coin.png"), unknown->coin_state,
                           0, 30, 33);
    }
    for (QVector < QVector < int >> ::iterator it = pipe->long_m.begin()->begin(); it != pipe->long_m.begin()->end();
         it++)
    {
        if (*(it->begin()) - mary->x > -80 && *(it->begin()) - mary->x < 800) {
            painter.drawPixmap(*(it->begin()) - mary->x, *(it->begin() + 1), 80, 100, QPixmap(":/photo/pipe_long.png"));
        }
    }
    for (QVector < QVector < int >> ::iterator it = pipe->short_m.begin()->begin(); it != pipe->short_m.begin()->end();
         it++)
    {
        if (*(it->begin()) - mary->x > -80 && *(it->begin()) - mary->x < 800) {
            painter.drawPixmap(*(it->begin()) - mary->x, *(it->begin() + 1), 80, 50, QPixmap(":/photo/pipe_short.png"));
        }
    }
    if (brick->shatter_state > 0) {
        painter.drawPixmap(brick->left_shatter_x - mary->x, brick->left_shatter_y - 20, 30, 30,
                           QPixmap(":/photo/brick2.png"));
        painter.drawPixmap(brick->left_shatter_x - mary->x, brick->left_shatter_y + 50, 30, 30,
                           QPixmap(":/photo/brick2.png"));
        painter.drawPixmap(brick->right_shatter_x - mary->x, brick->right_shatter_y - 20, 30, 30,
                           QPixmap(":/photo/brick3.png"));
        painter.drawPixmap(brick->right_shatter_x - mary->x, brick->right_shatter_y + 50, 30, 30,
                           QPixmap(":/photo/brick3.png"));
    }
    for (QVector < QVector < int >> ::iterator it = master->m.begin()->begin(); it != master->m.begin()->end();
         it++)
    {
        if (*(it->begin()) - mary->x > -80 && *(it->begin()) - mary->x < 800 && *(it->begin() + 2) != 0) {
            painter.drawPixmap(*(it->begin()) - mary->x, *(it->begin() + 1), 40, 40,
                               QPixmap(":/photo/master_" + QString::number(*(it->begin() + 3)) + ".png"));
        } else if (*(it->begin()) - mary->x > -80 && *(it->begin()) - mary->x < 800 && *(it->begin() + 2) == 0 &&
                   *(it->begin() + 4) == 1) {
            painter.drawPixmap(*(it->begin()) - mary->x, *(it->begin() + 1) + 20, 40, 20,
                               QPixmap(":/photo/master_" + QString::number(*(it->begin() + 3)) + ".png"));
        }
    }
    for (QVector < QVector < int >> ::iterator it = bullet->m.begin()->begin(); it != bullet->m.begin()->end();
         it++)
    {
        if (*(it->begin()) - mary->x > -80 && *(it->begin()) - mary->x < 800 && *(it->begin() + 2) != 0) {
            painter.drawPixmap(*(it->begin()) - mary->x, *(it->begin() + 1), 40, 40,
                               QPixmap(":/photo/bullet" + QString::number(*(it->begin() + 3)) + ".png"));
        } else if (*(it->begin()) - mary->x > -80 && *(it->begin()) - mary->x < 800 && *(it->begin() + 2) == 0 &&
                   *(it->begin() + 4) == 1) {
            painter.drawPixmap(*(it->begin()) - mary->x, *(it->begin() + 1) + 20, 40, 20,
                               QPixmap(":/photo/bullet" + QString::number(*(it->begin() + 3)) + ".png"));
        }
    }
    if (mary->is_die) {
        painter.drawPixmap(mary->map_x, mary->y, QPixmap(":/photo/mary_die.png"), mary->die_pix_state, 0, 50, 50);//画角色
    }
    if (!mary->is_die && mary->invincible_state % 2 == 0 && !is_win) {
        painter.drawPixmap(mary->map_x, mary->y,
                           QPixmap(":/photo/walk_" + mary->direction + QString::number(mary->colour) + ".png"),
                           mary->walk_state, 0, 45, 45);//画角色
    }
    if (fire->is_have) {
        painter.drawPixmap(fire->x - mary->x, fire->y, 20, 20, QPixmap(":/photo/fire.png"));
    }
    if (fire->is_have1) {
        painter.drawPixmap(fire->x1 - mary->x, fire->y1, 20, 20, QPixmap(":/photo/fire.png"));
    }
    if (fire->is_have2) {
        painter.drawPixmap(fire->x2 - mary->x, fire->y2, 20, 20, QPixmap(":/photo/fire.png"));
    }
}

void level2::Game_Init() {
    mary = new Mary;
    brick = new Brick(2);
    flower = new Flower(2);
    pipe = new class Pipe(2);
    unknown = new Unknown(2);
    mushroom = new MushRoom(2);
    master = new Master(2);
    bullet = new Bullet(2);
    fire = new Fire;
    castle = new Castle;
    key = "nullptr";
    is_press_x = false;
    is_win = false;
    score = 0;
    time =100.0;
    mary->life =this->mary->life;
    is_kill_timer2 = true;
    game_start = false;
    master->Master_State(mary, pipe, brick);
    bullet->Bullet_State(mary, pipe, brick);
    fire->Fire_Move(mary, pipe, brick, master);
}

void level2::Pause_Game_Init() {
    key = "nullptr";
    score = 0;
    time = 100.0;
    is_press_x = false;
    is_kill_timer2 = true;
    game_start = false;
    mary->Mary_Init();
    unknown->Unknown_Init2();
    brick->BrickInit2();
    flower->Flower_Init2();
    mushroom->MushRoom_Init2();
    master->Master_Init2();
    master->Master_State(mary, pipe, brick);
    bullet->Bullet_Init2();
    bullet->Bullet_State(mary, pipe, brick);
}

void level2::Jump_Collision() {
    if (mary->height - mary->distance <= 0) {
        return;
    }
    for (QVector < QVector < int >> ::iterator it = brick->m.begin()->begin(); it != brick->m.begin()->end();
         it++)
    {
        if (*it->begin() - mary->x - 300 >= -30 && *it->begin() - mary->x - 300 <= 30 &&
            *(it->begin() + 1) - mary->y + 40 >= -10 && *(it->begin() + 1) - mary->y + 40 <= 20 &&
            *(it->begin() + 2) == 1) {
            score += 5;
            brick->BrickShatter(it);
            *(it->begin() + 2) = 0;
            mary->y = *(it->begin() + 1) + 40;
            mary->height = mary->distance;
            return;
        }
    }
    for (QVector < QVector < int >> ::iterator it = unknown->m.begin()->begin(); it != unknown->m.begin()->end();
         it++)
    {
        if (*it->begin() - mary->x - 300 >= -30 && *it->begin() - mary->x - 300 <= 30 &&
            *(it->begin() + 1) - mary->y + 40 >= -10 && *(it->begin() + 1) - mary->y + 40 <= 20) {
            if (*(it->begin() + 2) == 1) {
                unknown->coin++;
                score += 10;
                unknown->Unknown_crash(it);
            } else if (*(it->begin() + 2) == 2) {
                mushroom->MushRoom_Move(it, unknown, brick, mary);
            }
            mary->y = *(it->begin() + 1) + 40;
            *(it->begin() + 2) = 0;
            mary->height = mary->distance;
            return;
        }
    }
    for (QVector < QVector < int >> ::iterator it = flower->m.begin()->begin(); it != flower->m.begin()->end();
         it++)
    {
        if (*it->begin() - mary->x - 300 >= -30 && *it->begin() - mary->x - 300 <= 30 &&
            *(it->begin() + 1) - mary->y + 40 >= -10 && *(it->begin() + 1) - mary->y + 40 <= 20 &&
            *(it->begin() + 2) == 1) {
            score += 10;
            mary->colour = 3;
            *(it->begin() + 2) = 0;
            return;
        }
    }
}

void level2::Move_Collision() {

    for (QVector < QVector < int >> ::iterator it = brick->m.begin()->begin(); it != brick->m.begin()->end();
         it++)
    {
        if (*it->begin() - mary->x - 300 >= 35 && *it->begin() - mary->x - 300 <= 40 &&
            *(it->begin() + 1) > mary->y - 35 && *(it->begin() + 1) < mary->y + 35 && mary->direction == "right" &&
            *(it->begin() + 2) == 1) {
            mary->can_move = false;
            return;
        } else if (*it->begin() - mary->x - 300 >= -40 && *it->begin() - mary->x - 300 <= -35 &&
                   *(it->begin() + 1) > mary->y - 35 && *(it->begin() + 1) < mary->y + 35 &&
                   mary->direction == "left" && *(it->begin() + 2) == 1) {
            mary->can_move = false;
            return;
        }
    }
    for (QVector < QVector < int >> ::iterator it = unknown->m.begin()->begin(); it != unknown->m.begin()->end();
         it++)
    {
        if (*it->begin() - mary->x - 300 >= 35 && *it->begin() - mary->x - 300 <= 40 &&
            *(it->begin() + 1) > mary->y - 35 && *(it->begin() + 1) < mary->y + 35 && mary->direction == "right") {
            mary->can_move = false;
            return;
        } else if (*it->begin() - mary->x - 300 >= -40 && *it->begin() - mary->x - 300 <= -35 &&
                   *(it->begin() + 1) > mary->y - 35 && *(it->begin() + 1) < mary->y + 35 &&
                   mary->direction == "left") {
            mary->can_move = false;
            return;
        }
    }
    for (QVector < QVector < int >> ::iterator it = flower->m.begin()->begin(); it != flower->m.begin()->end();
         it++)
    {
        if (*it->begin() - mary->x - 300 >= 36 && *it->begin() - mary->x - 300 <= 39 &&
            *(it->begin() + 1) > mary->y - 35 && *(it->begin() + 1) < mary->y + 35 && mary->direction == "right") {
            mary->colour = 3;
            *(it->begin() + 2) = 0;
            return;
        } else if (*it->begin() - mary->x - 300 >= -39 && *it->begin() - mary->x - 300 <= -36 &&
                   *(it->begin() + 1) > mary->y - 35 && *(it->begin() + 1) < mary->y + 35 &&
                   mary->direction == "left") {
            score += 10;
            mary->colour = 3;
            *(it->begin() + 2) = 0;
            return;
        }
    }
    for (QVector < QVector < int >> ::iterator it = pipe->long_m.begin()->begin(); it != pipe->long_m.begin()->end();
         it++)
    {
        if (*it->begin() - mary->x - 300 >= 30 && *it->begin() - mary->x - 300 <= 35 &&
            *(it->begin() + 1) < mary->y + 45 && mary->direction == "right") {
            mary->can_move = false;
            return;
        } else if (*it->begin() - mary->x - 300 >= -55 && *it->begin() - mary->x - 300 <= -50 &&
                   *(it->begin() + 1) < mary->y + 45 && mary->direction == "left") {
            mary->can_move = false;
            return;
        }
    }
    for (QVector < QVector < int >> ::iterator it = pipe->short_m.begin()->begin(); it != pipe->short_m.begin()->end();
         it++)
    {
        if (*it->begin() - mary->x - 300 >= 30 && *it->begin() - mary->x - 300 <= 35 &&
            *(it->begin() + 1) < mary->y + 45 && mary->direction == "right") {
            mary->can_move = false;
            return;
        } else if (*it->begin() - mary->x - 300 >= -55 && *it->begin() - mary->x - 300 <= -50 &&
                   *(it->begin() + 1) < mary->y + 45 && mary->direction == "left") {
            mary->can_move = false;
            return;
        }
    }
    QVector < QVector < int >> ::iterator
        it = castle->m.begin()->begin();
    if (*it->begin() - mary->x - 300 >= -60 && *it->begin() - mary->x - 300 <= -20 &&
        *(it->begin() + 1) < mary->y - 100 && *(it->begin() + 1) > mary->y - 200) {

        is_win = true;
        Game_Win();
    }
    mary->can_move = true;
}

void level2::Fall_Down(int &y) {
    qDebug() << mary->distance;
    if (mary->height - mary->distance < 0) {
        if (y > 455) {
            y = 455;
            mary->is_jump_end = true;
            mary->distance = 0;
            mary->height = 20;
            return;
        }
        for (QVector < QVector < int >> ::iterator it = brick->m.begin()->begin(); it != brick->m.begin()->end();
             it++)
        {
            if (*it->begin() - mary->x - 300 >= -30 && *it->begin() - mary->x - 300 <= 30 &&
                *(it->begin() + 1) <= y + 50 && *(it->begin() + 1) >= y + 25 && *(it->begin() + 2) == 1) {
                y = *(it->begin() + 1) - 45;
                mary->is_jump_end = true;
                mary->height = mary->distance = 20;
                return;
            }
        }
        for (QVector < QVector < int >> ::iterator it = unknown->m.begin()->begin(); it != unknown->m.begin()->end();
             it++)
        {
            if (*it->begin() - mary->x - 300 >= -30 && *it->begin() - mary->x - 300 <= 30 &&
                *(it->begin() + 1) <= y + 50 && *(it->begin() + 1) >= y + 25) {
                y = *(it->begin() + 1) - 45;
                mary->is_jump_end = true;
                mary->height = mary->distance = 20;
                return;
            }
        }
        for (QVector < QVector < int >> ::iterator it = pipe->long_m.begin()->begin(); it !=
                                                                                 pipe->long_m.begin()->end();
             it++)
        {
            if (*it->begin() - mary->x - 300 >= -50 && *it->begin() - mary->x - 300 <= 30 &&
                *(it->begin() + 1) <= y + 50 && *(it->begin() + 1) >= y + 25) {
                y = *(it->begin() + 1) - 45;
                mary->is_jump_end = true;
                mary->height = mary->distance = 20;
                return;
            }
        }
        for (QVector < QVector < int >> ::iterator it = pipe->short_m.begin()->begin(); it !=
                                                                                  pipe->short_m.begin()->end();
             it++)
        {
            if (*it->begin() - mary->x - 300 >= -50 && *it->begin() - mary->x - 300 <= 30 &&
                *(it->begin() + 1) <= y + 50 && *(it->begin() + 1) >= y + 25) {
                y = *(it->begin() + 1) - 45;
                mary->is_jump_end = true;
                mary->height = mary->distance = 20;
                return;
            }
        }
    }
}

void level2::Die_Init() {
    if (mary->is_die && key != "null") {
        mary->walk_state = 0;
        key = "null";
    }
    if (mary->invincible_state == 100) {
        mary->is_invincible = false;
        mary->invincible_state = 0;
    }
    if (mary->is_invincible) {
        mary->invincible_state += 1;
    }
    if (mary->y > 500) {
        mary->y = 455;
        mary->life--;
        if(mary->life<=0){
            Game_Over();
            return;
        };
        killTimer(timer3);
        killTimer(timer1);
        game_start = false;
        QTimer::singleShot(1500, this, [=]() {
            mary->is_die = false;
            mary->is_invincible = true;
            timer1 = startTimer(15);//开启定时器
            timer3 = startTimer(40);
            game_start = true;
            mary->die_state = 0;
            mary->die_pix_state = -50;
        });
    }
}

void level2::Game_Win() {
    killTimer(timer1);
    killTimer(timer3);
    QTimer::singleShot(1000, this, [=]() {
        game_start = false;
        time = 100.0;
        update();
    });
    QTimer::singleShot(1000, this, [=]() {
        startTimer(timer1);
        startTimer(timer3);
    });
}

void level2::Game_Over(){
    killTimer(timer1);
    killTimer(timer3);
    QTimer::singleShot(1000, this, [=]() {
        game_start = false;
        time = 100.0;
        QTimer::singleShot(1500, this, [=]() {
            this->close();
            emit  this->back();
        });
    });
}


