
#ifndef RAINBOW_H
#define RAINBOW_H

#include<QVector>
#include<QMap>

class Rainbow
{
public:
    QVector<int> v;
    QVector <QVector<int>> v2;
    QMap<int, QVector<QVector < int>>> m;
    Rainbow(int a);
    void Rainbow_Init2();
    void Rainbow_Init3();
};

#endif // RAINBOW_H
