//
// Created by User on 2018/12/19.
//
#include "Deck.h"
#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

bool getThree(vector<Majan>& a, int remain){
    if(remain == 0 && a.empty()){
        return true;
    }else if(remain == 2 && a.size() == 2){
        if(a[0] == a[1]){
            return true;
        }
    }else if(a.size() >= 3){
        vector<Majan>temp;
        bool win;
        for(int i = 0; i <= a.size() - 3; i++){
            if(a[i].type == a[i + 1].type && a[i + 1].type == a[i + 2].type){
                if((a[i].num + 1 == a[i + 1].num && a[i + 1].num + 1 == a[i + 2].num) ||
                   (a[i].num == a[i + 1].num && a[i + 1].num == a[i + 2].num)){
                    for(int j = 0; j < a.size(); j++){
                        if(j != i && j != i + 1 && j != i + 2){
                            temp.push_back(a[j]);
                        }
                    }
                    win = getThree(temp, remain);
                    if(win){
                        return true;
                    }
                }else{
                    int plusOne = 0, plusTwo = 0;
                    for(int j = i + 1; j < a.size(); j++){
                        if(a[j].num > a[i].num + 2 || a[j].type != a[i].type){
                            break;
                        }else{
                            if(plusOne == 0){
                                if(a[j].num == a[i].num + 1){
                                    plusOne = j;
                                }
                            }
                            if(plusTwo == 0){
                                if(a[j].num == a[i].num + 2){
                                    plusTwo = j;
                                }
                            }
                        }
                    }
                    if(plusOne != 0 && plusTwo != 0){
                        for(int j = 0; j < a.size(); j++){
                            if(j != i && j != plusOne && j != plusTwo){
                                temp.push_back(a[j]);
                            }
                        }
                        win = getThree(temp, remain);
                        if(win){
                            return true;
                        }
                    }
                }
            }
            temp.clear();
        }
        temp.clear();
    }
    return false;
};

bool Deck::checkWin(){
    vector<Majan> word;
    vector<Majan> wan;
    vector<Majan> ton;
    vector<Majan> tia;
    for(int i = 0; i < (int)this->deck.size(); i++){
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
    }else{
        int wordRemain = (int)word.size() % 3;
        int wanRemain = (int)wan.size() % 3;
        int tonRemain = (int)ton.size() % 3;
        int tiaRemain = (int)tia.size() % 3;
        if(wordRemain + wanRemain + tonRemain + tiaRemain > 2){
            return false;
        }else{
//            cout << getThree(word, wordRemain) << getThree(wan, wanRemain) <<
//            getThree(ton, tonRemain) << getThree(tia, tiaRemain);

            return getThree(word, wordRemain) && getThree(wan, wanRemain)
                   && getThree(ton, tonRemain) && getThree(tia, tiaRemain);
        };
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
    for(auto i = 0; i < this->deckOut.size(); i++){
        this->deckOut[i].print();
    }
    cout << endl;
}
void Deck::sort(){
    std::sort(this->deck.begin(), this->deck.end(),
              [](Majan a, Majan b){ return a.compare(&b); });
}


