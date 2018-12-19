//
// Created by User on 2018/12/19.
//
#include "Majan.h"
#include <vector>
using namespace std;

#ifndef MAJANGAME_DECK_H
#define MAJANGAME_DECK_H

class Deck{
public:
    bool listen;
    vector<Majan> deck;
    vector<Majan> deckOut;
    void print();
    void sort();
    void addMajan(int, int, Deck*);
    void putDeckOut(int, int);

    //在打牌前檢查是否聽
    bool checkWin();

    //吃
    //碰
    //槓
    //聽
    //胡
    //算台
};

#endif //MAJANGAME_DECK_H
