
#ifndef SPIKEWEED_H
#define SPIKEWEED_H

#include<QMap>
#include<QVector>
#include<mary.h>

class Spikeweed {
public:
    Mary *mary;
    QVector <QVector<int>> v1;
    QMap<int, QVector<QVector < int>>> m;
    QVector<QVector < int>>::iterator itm;
    void Spikeweed_Init3();
    void Spikeweed_State(Mary *m);
    void Spikeweed_collision();
    Spikeweed(int a);
};

#endif // SPIKEWEED_H
