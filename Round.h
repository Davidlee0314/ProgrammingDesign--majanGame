//
// Created by User on 2018/12/21.
//
#include "Deck.h"
#include "Player.h"
#include <vector>

#ifndef MAJANGAME_ROUND_H
#define MAJANGAME_ROUND_H

class Round{
private:
    void initTotals();
public:
    //東 南 西 北 0 1 2 3
    int wind;
    //開門方
    int open;
    //現在玩家 0 1 2 3
    int playerNow;
    //拿牌的地方
    int pos;
    int backPos;
    //觸發此玩家的情況是否為吃碰槓
    bool justAction;

    Player** playerList;
    Deck* totals;
    Deck* haidi;
    Round(Player*, Player*, Player*, Player*);
    void initRound(int);
    bool haveWinner();
    int playerNext();
};


#endif //MAJANGAME_ROUND_H
