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
    int searchMajan(Majan*);

    //檢查胡、碰、槓、吃
    bool checkWin();
    //傳出可以碰的牌的位置(第一張)
    int checkPon(Majan*);
    //傳出可以槓的牌的位置(第一張)
    int checkGan(Majan*);
    //若可以吃，將傳入的陣列填滿，長度 = 可以吃的方式 * 2
    bool checkEat(vector<Majan>&, Majan*);

    //吃
    void eat(Majan, Majan, Majan);
    //碰
    void pon(int, Majan);
    //槓
    void gan(int, Majan);
    //胡
    //算台
};

#endif //MAJANGAME_DECK_H
