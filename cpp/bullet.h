
#ifndef BULLET_H
#define BULLET_H

#include<QMap>
#include<QVector>
#include<QString>
#include<mary.h>
#include"pipe.h"
#include"brick.h"
#include"master.h"

class Bullet {
public:
    QString direction;
    int die_state;
    Mary *mary;
    Pipe *pipe;
    Brick *brick;
    Master *master;
    QVector <QVector<int>> v1;
    QMap<int, QVector<QVector < int>>> m;
    QVector<QVector < int>>::
        iterator itm;

    void Bullet_Init2();
    void Bullet_Init3();
    void Bullet_State(Mary *m, Pipe *p, Brick *r);

    void Bullet_Move();

    Bullet(int a);
};

#endif // BULLET_H
