//
// Created by User on 2018/12/21.
//
#include <algorithm>
#include <random>
#include <iostream>

#include "Round.h"

//int throwDice(){
//    random_device rd;
//    default_random_engine generator = default_random_engine(rd());
//    uniform_int_distribution<int> distribution(1,6);
//    int dice1 = distribution(generator);
//    int dice2 = distribution(generator);
//    int dice3 = distribution(generator);
//    return dice1 + dice2 + dice3;
//}

int nextPlayer(int now){
    if(now == 3){
        now = 0;
    }else{
        now += 1;
    }
    return now;
}

int calcPos(int diceNum){
    int remain = diceNum % 4;
    cout << "Dice " << diceNum << endl;
    if(remain == 1){
        return 2 * diceNum;
    }else if(remain == 2){
        return 108 + 2 * diceNum;
    }else if(remain == 3){
        return 72 + 2 * diceNum;
    }else if(remain == 0){
        return 36 + 2 * diceNum;
    }
}

Round::Round(Player* p1, Player* p2, Player* p3, Player* p4){
    //設為東風
    wind = 0;
    totals = new Deck();
    haidi = new Deck();
    playerList = new Player* [4];
    playerList[0] = p1;
    playerList[1] = p2;
    playerList[2] = p3;
    playerList[3] = p4;
}

void Round::initTotals() {
    for(int i = 1; i < 6; i++){
        if(i == 1){
            for(int j = 1; j < 9; j++){
                Majan temp = {i, j};
                this->totals->deck.push_back(temp);
            }
        }else if(i == 2){
            int repeat = 4;
            while(repeat != 0){
                for (int j = 1; j < 8; j++){
                    Majan temp = {i, j};
                    this->totals->deck.push_back(temp);
                }
                repeat--;
            }
        }else{
            int repeat = 4;
            while(repeat != 0){
                for (int j = 1; j < 10; j++){
                    Majan temp = {i, j};
                    this->totals->deck.push_back(temp);
                }
                repeat--;
            }
        }
    }
    shuffle(&totals->deck[0], &totals->deck[143], std::mt19937(std::random_device()()));
}

void Round::initRound(int diceNum){
    initTotals();
    int majanNow = 64;
    int pos = calcPos(diceNum);
    open = pos;
    cout << "Pos " << pos << endl;

    for(int i = 0; i < 4; i++){
        if(playerList[i]->host){
            playerNow = i;
        }
    }

    totals->print();

    while(majanNow != 0){
        bool oneCircle = false;
        if(pos == totals->deck.size()){
            pos = 0;
        }else if(pos == totals->deck.size() - 2){
            oneCircle = !oneCircle;
        }
        if(!oneCircle){
            playerList[playerNow]->ownedDeck->addMajan(pos, 4, totals);
        }else{
            playerList[playerNow]->ownedDeck->addMajan(pos, 2, totals);
            pos = 0;
            playerList[playerNow]->ownedDeck->addMajan(pos, 2, totals);
        }
        playerNow = nextPlayer(playerNow);
        majanNow -= 4;
        cout << totals->deck.size() << endl;
        totals->print();
    }

    totals->print();

    //開門、排列
    playerList[playerNow]->ownedDeck->addMajan(pos, 1, totals);
    for(int i = 0; i < 4; i++){
        playerList[i]->ownedDeck->sort();
    }

    //補花
    bool flower[4] = {false};
    bool allFlower = false;
    int flowerNum = 0;
    while(!allFlower){
        for(int i = 0; i < 8; i++){
            if(playerList[playerNow]->ownedDeck->deck[i].type == 2){
                break;
            }else{
                flowerNum ++;
            }
        }
        if(flowerNum == 0){
            flower[playerNow] = true;
        }else{
            playerList[playerNow]->ownedDeck->putDeckOut(0, flowerNum);
            playerList[playerNow]->ownedDeck->addMajan((int)totals->deck.size() - flowerNum, flowerNum, totals);
        }
        flowerNum = 0;
        playerList[playerNow]->ownedDeck->sort();
        allFlower = flower[0] && flower[1] && flower[2] && flower[3];
        if(!allFlower){
            playerNow = nextPlayer(playerNow);
            while(flower[playerNow]){
                playerNow = nextPlayer(playerNow);
            }
        }
    }
    for(int i = 0; i < 4; i++){
        playerList[i]->ownedDeck->print();
    }
}