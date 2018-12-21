#include <random>
#include <vector>
#include <iostream>
#include <algorithm>

#include "Majan.h"
#include "Deck.h"

using namespace std;
Deck* initTotals();
void printPlayers(Deck** players);
void initRound(Deck* totals, Deck* players[], int pos, int playerNow);
int nextPlayer(int);

Deck* initTotals(){
    Deck* totals = new Deck();
    int now = 0;

    for(int i = 1; i < 6; i++){
        if(i == 1){
            for(int j = 1; j < 9; j++){
                Majan temp = {i, j};
                totals->deck.push_back(temp);
                now++;
            }
        }else if(i == 2){
            int repeat = 4;
            while(repeat != 0){
                for (int j = 1; j < 8; j++){
                    Majan temp = {i, j};
                    totals->deck.push_back(temp);
                    now++;
                }
                repeat--;
            }
        }else{
            int repeat = 4;
            while(repeat != 0){
                for (int j = 1; j < 10; j++){
                    Majan temp = {i, j};
                    totals->deck.push_back(temp);
                    now++;
                }
                repeat--;
            }
        }
    }
    shuffle(&totals->deck[0], &totals->deck[143], std::mt19937(std::random_device()()));
    return totals;
}
void initRound(Deck* totals, Deck* players[], int pos, int playerNow){
    int majanNow = 64;
    while(majanNow != 0){
        players[playerNow]->addMajan(pos, 4, totals);
        playerNow = nextPlayer(playerNow);
        majanNow -= 4;
    }
    printPlayers(players);

    //開門、排列
    players[playerNow]->addMajan(pos, 1, totals);
    for(int i = 0; i < 4; i++){
        players[i]->sort();
    }

    //補花
    bool flower[4] = {false};
    bool allFlower = false;
    int flowerNum = 0;
    while(!allFlower){
        for(int i = 0; i < 8; i++){
            if(players[playerNow]->deck[i].type == 2){
                break;
            }else{
                flowerNum ++;
            }
        }
        if(flowerNum == 0){
            flower[playerNow] = true;
        }else{
            players[playerNow]->putDeckOut(0, flowerNum);
            players[playerNow]->addMajan((int)totals->deck.size() - flowerNum, flowerNum, totals);
        }
        flowerNum = 0;
        players[playerNow]->sort();
        allFlower = flower[0] && flower[1] && flower[2] && flower[3];
        if(!allFlower){
            playerNow = nextPlayer(playerNow);
            while(flower[playerNow]){
                playerNow = nextPlayer(playerNow);
            }
        }
    }
}
void printPlayers(Deck** players){
    for(int i = 0; i < 4; i++){
        cout << "=======================================" << endl;
        cout << "                玩家 " << i + 1 << endl;
        cout << "=======================================" << endl;
        players[i]->print();
    }
}
int nextPlayer(int now){
    if(now == 3){
        now = 0;
    }else{
        now += 1;
    }
    return now;
}



int main(){
//    Deck* totals = initTotals();
//    cout << "現在亂數麻將長這樣：" << endl;
//    totals->print();
//    Deck* players[4] = {nullptr};
//    for(int i = 0; i < 4; i++){
//        players[i] = new Deck();
//    }
//
//    int playerNow = 0;
//    initRound(totals, players, 0, playerNow);
//    cout << "玩家開局後亂數麻將長這樣：" << endl;
//    totals->print();
//    printPlayers(players);

    int n = 0, type = 0, num = 0, index = 0;
    Deck a = Deck();
    cin >> n;
    while(n != 1){
        cin >> type >> num;
        Majan m = {type, num};
        a.deck.push_back(m);
        n--;
        index++;
    }
    cin >> type >> num;
    vector<Majan>eat;
    Majan m = {type, num};
    a.print();
    cout << "這張牌被打出來：";
    m.print();
    cout << endl;
    cout << (a.checkEat(eat, &m) ? "可以吃" : "吃") << endl;
    cout << "這些牌可以吃，兩個兩個一組" << endl;
    for(int i = 0; i < eat.size(); i++){
        eat[i].print();
    }
    a.eat(m, eat[0], eat[1]);
    cout << endl;
    a.print();
    return 0;
}