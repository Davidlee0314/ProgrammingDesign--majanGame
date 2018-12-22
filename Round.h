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
    int open;
    int playerNow;
    Player** playerList;
    Deck* totals;
    Deck* haidi;
    Round(Player*, Player*, Player*, Player*);
    void initRound(int);
};


#endif //MAJANGAME_ROUND_H
