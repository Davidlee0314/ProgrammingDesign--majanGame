//
// Created by User on 2018/12/19.
//
#include "Deck.h"
#include <iostream>
#include <algorithm>
using namespace std;

bool threeInspect(vector<Majan>& a){

};

bool twoRemainInspect(vector<Majan>& a){

};

bool Deck::checkWin(){
    vector<Majan> word;
    vector<Majan> wan;
    vector<Majan> ton;
    vector<Majan> tia;
    for(int i = 0; i < (int)this->deck.size() - 1; i++){
        if(this->deck[i].type == 2){
            word.push_back(this->deck[i]);
        }else if(this->deck[i].type == 3){
            wan.push_back(this->deck[i]);
        }else if(this->deck[i].type == 4){
            ton.push_back(this->deck[i]);
        }else if(this->deck[i].type == 5){
            tia.push_back(this->deck[i]);
        }
    }

    //確認數量
    if(word.size() % 3 == 1 || wan.size() % 3 == 1 || ton.size() % 3 == 1 || tia.size() % 3 == 1){
        return false;
    }else if(word.size() % 3 == 2 && wan.size() % 3 == 0
    && ton.size() % 3 == 0 && tia.size() % 3 == 0){

    }else if(word.size() % 3 == 0 && wan.size() % 3 == 2
    && ton.size() % 3 == 0 && tia.size() % 3 == 0){

    }else if(word.size() % 3 == 0 && wan.size() % 3 == 0
    && ton.size() % 3 == 2 && tia.size() % 3 == 0){

    }else if(word.size() % 3 == 0 && wan.size() % 3 == 0
             && ton.size() % 3 == 0 && tia.size() % 3 == 2){

    }else if(word.size() % 3 == 0 && wan.size() % 3 == 0
             && ton.size() % 3 == 0 && tia.size() % 3 == 0){

    }else{
        return false;
    }
}

void Deck::addMajan(int pos, int num, Deck* totals){
    for(int i = 0; i < num; i++){
        this->deck.push_back(totals->deck[pos + i]);
    }
    totals->deck.erase(totals->deck.begin() + pos, totals->deck.begin() + pos + num);
}

void Deck::putDeckOut(int pos, int num){
    for(int i = 0; i < num; i++){
        this->deckOut.push_back(this->deck[pos + i]);
    }
    this->deck.erase(this->deck.begin() + pos, this->deck.begin() + pos + num);
}

void Deck::print(){
    cout << "<手牌>" << endl;
    for(int i = 0; i < this->deck.size(); i++){
        if(i % 16 == 0 && i != 0){
            cout << endl;
        }
        this->deck[i].print();
    }
    cout << endl << "<牌面>" << endl;
    for(int i = 0; i < this->deckOut.size(); i++){
        this->deckOut[i].print();
    }
    cout << endl;
}
void Deck::sort(){
    std::sort(this->deck.begin(), this->deck.end(),
              [](Majan a, Majan b){ return a.compare(&b); });
}


