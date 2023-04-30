
#ifndef FLAG_H
#define FLAG_H

class Flag
{
public:
    Flag();
    bool update(int y);
    double prex;//处理下降的时候，乱飞，x变化
    double prey;//处理下到砖块上面即不能在动
    double flagY;
};

#endif // FLAG_H
