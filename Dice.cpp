//
// Created by User on 2018/12/21.
//

#include <random>
#include "Dice.h"
using namespace std;

void Dice::throwDice() {
    random_device rd;
    default_random_engine generator = default_random_engine(rd());
    uniform_int_distribution<int> distribution(1,6);
    num = distribution(generator);
}