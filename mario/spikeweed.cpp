#include <spikeweed.h>
#include"mary.h"
#include"QDebug"

Spikeweed::Spikeweed(int a) {
    if(a==3)
    {
        Spikeweed_Init3();
    }
}

void Spikeweed::Spikeweed_Init3() {
    m.clear();
    QVector<int> v;
    int arr[11][2] = {{1385, 460},
                      {1415, 460},
                      {1700, 460},
                      {2400, 460},
                      {3200, 460},
                      {3630, 460},
                      {3900, 460},
                      {4550, 460},
                      {4600, 460},
                      {4650, 460},
                      {5000, 320}};
    for (int i = 0; i < 11; i++) {
        v.push_back(arr[i][0]);
        v.push_back(arr[i][1]);
        v1.push_back(v);
        v.clear();
    }
    m.insert(1, v1);
    v1.clear();
}

void Spikeweed::Spikeweed_State(Mary *m) {
    mary = m;
}

void Spikeweed::Spikeweed_collision() {
    for (itm = m.begin()->begin(); itm != m.begin()->end(); itm++) {
        if (*itm->begin() - mary->x > -40 && *(itm->begin()) - mary->x < 800) {
            if (*itm->begin() - mary->x - 300 >= -20&& *itm->begin() - mary->x - 300 <= 20 &&
                *(itm->begin() + 1) > mary->y -15&& *(itm->begin() + 1) < mary->y + 15) {
                if (mary->colour == 1 && !mary->is_invincible) {
                    mary->is_die = true;
                } else if (mary->colour != 1 && !mary->is_invincible) {
                    mary->colour = 1;
                    mary->is_invincible = true;
                }
                return;
            }
        }
    }

}

