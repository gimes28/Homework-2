
#ifndef WHEEL_H
#define WHEEL_H

#include <iostream>
#include <random>
using namespace std;

class Wheel {
private:
    int upBound;
    int lowBound;
    int spinVal;
public:
    Wheel();
    void spin();
    void updateRange(int bound);
    int getSpinVal() const { return spinVal; }
};
#endif
