#include <iostream>
#include <time.h>
#include <random>
#include "player.h"
#include "wheel.h"
using namespace std;

int main() {
    srand(time(NULL));

    bool cashOut = false;
    bool hasMoney = true;

    Player person;
    double betVal;
    string wager;
    char val;

    int option;
    cout << "Press 1 to set starting amount, otherwise press 2 to continue with default $100: " << endl;
    cin >> option;

    if (option == 1) {
        int startAmt;
        cout << "Enter your starting amount: " << endl;
        cin >> startAmt;
        person.setCurrAmount(startAmt);
    }

    while (cashOut == false && hasMoney == true) {
        int upperVal = 10;
        cout << "Current amount: " << person.getCurrAmount() << endl;
        cout << "Betting amount: " << endl;
        cin >> betVal;
        while (betVal > person.getCurrAmount()) {
            cout << "Betting amount is over current value" << endl;
            cout << "You have $" << person.getCurrAmount() << ", try again" << endl;
            cin >> betVal;
        }
        person.setBetAmount(betVal);
        cout << "Do you want to change the range values? (Y or N)" << endl;
        cin >> val;

        while (val != 'Y' && val != 'N') {
            cout << "Invalid Input" << endl;
            cout << "Do you want to change the range values? (Y or N)" << endl;
            cin >> val;
        }

        if (val == 'Y' || val == 'y') {
            cout << "Enter Upper bound(between 6 & 20): " << endl;
            cin >> upperVal;
            while (upperVal < 6 || upperVal > 20) {
                cout << "Invalid Input" << endl;
                cout << "Enter Upper bound(between 6 & 20): " << endl;
                cin >> upperVal;
            }
        }
        person.plyr.updateRange(upperVal);

        //Start Playing Game
        person.plyr.spin();
        int playerValue = person.plyr.getSpinVal();
        cout << "Player spin: " << playerValue << endl;

        cout << "Change wager? (Keep, Double, Halve): " << endl;
        cin >> wager;
        while (!(wager == "Halve" || wager == "Double" || wager == "Keep")) {
            cout << "Invalid Input, try again" << endl;
            cout << "Change wager? (Keep, Double, Halve): " << endl;
            cin >> wager;
        }
        int tempBet = betVal * 2;
        while (tempBet > person.getCurrAmount() && wager == "Double" && wager != "Keep" && wager != "Halve") {
            cout << "Betting amount is over current value, you cannot double" << endl;
            cout << "You can keep or halve your wager" << endl;
            cin >> wager;
            while (!(wager == "Halve" || wager == "Double" || wager == "Keep")) {
                cout << "Invalid Input, try again" << endl;
                cout << "Change wager? (Keep, Double, Halve): " << endl;
                cin >> wager;
            }
        }
        person.setBet(wager);
        if (wager == "Double" || wager == "Halve") {
            Wheel* house1 = new Wheel();
            Wheel* house2 = new Wheel();
            house1->updateRange(upperVal);
            house2->updateRange(upperVal);
            house1->spin();
            house2->spin();
            int value1 = house1->getSpinVal();
            int value2 = house2->getSpinVal();
            if (wager == "Double") {
                betVal *= 2;
                person.setBetAmount(betVal);
                if (value1 >= playerValue || value2 >= playerValue) {
                    person.setCurrAmount(person.getCurrAmount() - betVal);
                }
                else {
                    person.setCurrAmount(person.getCurrAmount() + betVal);
                }
            }
            else if (wager == "Halve") {
                betVal /= 2;
                person.setBetAmount(betVal);
                if (value1 >= playerValue || value2 >= playerValue) {
                    person.setCurrAmount(person.getCurrAmount() - betVal);
                }
                else {
                    person.setCurrAmount(person.getCurrAmount() + betVal);
                }
            }
            if (value1 >= playerValue) {
                cout << "House Spin: " << value1 << endl;
                cout << "House wins" << endl;
            }
            else if (value2 >= playerValue) {
                cout << "House Spin: " << value2 << endl;
                cout << "House wins" << endl;
            }
            else {
                cout << "House Spin: " << "Try 1 - " << value1 << " Try 2 - " << value2 << endl;
                cout << "You win!" << endl;
            }
        }
        else if (wager == "Keep") {
            Wheel* house = new Wheel();
            house->updateRange(upperVal);
            house->spin();
            int value = house->getSpinVal();
            if (value >= playerValue) {
                cout << "House Spin: " << value << endl;
                cout << "House wins" << endl;
                person.setCurrAmount(person.getCurrAmount() - betVal);
            }
            else {
                cout << "House Spin: " << value << endl;
                cout << "You win!" << endl;
                person.setCurrAmount(person.getCurrAmount() + betVal);
            }
        }

        //Result of Game
        if (person.getCurrAmount() <= 0) {
            cout << "You are out of money" << endl;
            hasMoney = false;
        }
        else {
            cout << "Would you like to Cash Out (Y or N)" << endl;
            cin >> val;
            if (val == 'Y') {
                cashOut = true;
            }
            while (val != 'Y' && val != 'N') {
                cout << "Invalid Input, try again" << endl;
                cout << "Would you like to Cash Out (Y or N)" << endl;
                cin >> val;
            }
        }
    }
    if (hasMoney != false) {
        cout << "Cash out successful" << endl;
        cout << "You take home: $" << person.getCurrAmount() << endl;
    }
}