#include "Majan.hpp"
#include <vector>
using namespace std;

#ifndef MAJANGAME_OPTION_HPP
#define MAJANGAME_OPTION_HPP
class Option{
public:
    Majan giveOut;
    vector<Majan> listenTo;
    Option(Majan);
    void addOption(Majan);
    void print();
};
#endif //MAJANGAME_OPTION_H
