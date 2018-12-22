//
// Created by User on 2018/12/22.
//

#include "Majan.h"
#include "Option.h"
#include <iostream>

Option::Option(Majan a){
    giveOut = {a.type, a.num};
}

void Option::addOption(Majan a) {
    listenTo.push_back(a);
}

void Option::print(){
    cout << "打 ";
    giveOut.print();
    cout << " 聽 ";
    for(int i = 0; i < listenTo.size(); i++){
        listenTo[i].print();
    }
    cout << endl;
}