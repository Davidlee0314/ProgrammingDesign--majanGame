#include "Majan.hpp"
#include "Option.hpp"
#include <iostream>

Option::Option(Majan a){
    giveOut.type = a.type;
    giveOut.num = a.num;
}

void Option::addOption(Majan a) {
    listenTo.push_back(a);
}

void Option::print(){
//    cout << "打 ";
//    giveOut.print();
//    cout << " 聽 ";
//    for(int i = 0; i < listenTo.size(); i++){
//        listenTo[i].print();
//    }
//    cout << endl;
}
