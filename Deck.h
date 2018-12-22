//
// Created by User on 2018/12/19.
//
#include "Majan.h"
#include <vector>
using namespace std;

#ifndef MAJANGAME_DECK_H
#define MAJANGAME_DECK_H

class Deck{
private:
    void delMajan(Majan*, int);
public:
    vector<Majan> deck;
    vector<Majan> deckOut;
    void print();
    void sort();
    void addMajan(int, int, Deck*);
    void putDeckOut(int, int);
    int searchMajan(Majan*);

    //檢查胡，必須把打出來或摸到的牌傳入
    bool checkWin();
    //檢查碰，傳出可以碰的牌的位置(第一張)
    int checkPon(Majan*);
    //檢查槓，傳出可以槓的牌的位置(第一張)
    int checkGan(Majan*);
    //檢查吃，若可以吃，將傳入的陣列填滿，長度 = 可以吃的方式 * 2
    bool checkEat(vector<Majan>&, Majan*);
    //檢查聽，必須把打出來或摸到的牌傳入
    bool checkListen(vector<Majan>&);

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
