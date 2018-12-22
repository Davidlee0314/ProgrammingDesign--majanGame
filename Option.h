//
// Created by User on 2018/12/22.
//

#include "Majan.h"
#include <vector>
using namespace std;

#ifndef MAJANGAME_OPTION_H
#define MAJANGAME_OPTION_H
class Option{
public:
    Majan giveOut;
    vector<Majan> listenTo;
    Option(Majan);
    void addOption(Majan);
    void print();
};
#endif //MAJANGAME_OPTION_H
