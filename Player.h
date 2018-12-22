//
// Created by User on 2018/12/21.
//
#include "Deck.h"

#ifndef MAJANGAME_PLAYER_H
#define MAJANGAME_PLAYER_H

class Player{
public:
    bool win;
    bool host;
    bool listen;
    int multiHost;
    Deck* ownedDeck;
    Player();
};

#endif //MAJANGAME_PLAYER_H
