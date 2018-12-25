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

    //開局
    void initRound(int);

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
    //上一局是否為流局
    bool failToFindWinner;

    Player** playerList;
    Deck* totals;
    Deck* haidi;
    Round(Player*, Player*, Player*, Player*);
    int playerNext();

    //單局暫停條件
    bool haveWinner();
    int posPre16();

    //遊玩需要
    void singleGame();
    void multiGame();
};


#endif //MAJANGAME_ROUND_H
