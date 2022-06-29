#ifndef PLAYER_H
#define PLAYER_H
#include "wheel.h"

#include <iostream>
using namespace std;
class Player {
private:
    double currAmount;
    double bettingAmount;
    string bet;
public:
    Wheel plyr;
    Player();
    Player(double curr);

    double getCurrAmount() { return currAmount; }
    void setCurrAmount(double a) { currAmount = a; }

    string getBet() { return bet; }
    void setBet(string b) { bet = b; }

    double getBetAmount() { return bettingAmount; }
    void setBetAmount(double ba) { bettingAmount = ba; }
};
#endif#pragma once
