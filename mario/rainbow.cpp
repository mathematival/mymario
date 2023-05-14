#include "rainbow.h"
#include<iostream>

Rainbow::Rainbow(int a) {
    if(a==2)
    {
        Rainbow_Init2();
    }
    if(a==3)
    {
        Rainbow_Init3();
    }
}

void Rainbow::Rainbow_Init2() {
    m.clear();
    int arr[1][2] = {{6100, 180}};
    for (int i = 0; i < 1; i++) {
        v.push_back(arr[i][0]);
        v.push_back(arr[i][1]);
        v.push_back(1);
        v2.push_back(v);
        v.clear();
    }
    m.insert(1, v2);
}

void Rainbow::Rainbow_Init3() {
    m.clear();
    int arr[1][2] = {{4550, 180}};
    for (int i = 0; i < 1; i++) {
        v.push_back(arr[i][0]);
        v.push_back(arr[i][1]);
        v.push_back(1);
        v2.push_back(v);
        v.clear();
    }
    m.insert(1, v2);
}


