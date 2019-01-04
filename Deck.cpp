#include "Deck.hpp"
#include "Option.hpp"
#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

bool getThree(vector<Majan>& a, int remain){
    //    for(int i = 0; i < a.size(); i++){
    //        a[i].print();
    //    }
    //    cout << endl;
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
                if(((a[i].num + 1 == a[i + 1].num && a[i + 1].num + 1 == a[i + 2].num) && a[i].type != 2) ||
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
                    if(a[i].type != 2){
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
            }
            temp.clear();
        }
        temp.clear();
    }
    return false;
};

Deck::Deck(SDL_Renderer* rRTemp) {
    rR = rRTemp;
}

void fillPossMajan(vector<Majan>& a, SDL_Renderer* rR){
    for(int i = 2; i < 6; i++){
        if(i == 2){
            int repeat = 1;
            while(repeat != 0){
                for (int j = 1; j < 8; j++){
                    Majan temp = Majan(i , j, rR);
                    a.push_back(temp);
                }
                repeat--;
            }
        }else{
            int repeat = 1;
            while(repeat != 0){
                for (int j = 1; j < 10; j++){
                    Majan temp = Majan(i , j, rR);
                    a.push_back(temp);
                }
                repeat--;
            }
        }
    }
}

bool Deck::checkListen(){
    listenOption.clear();
    vector<Majan>totals;
    fillPossMajan(totals, rR);
    
    Deck temp = Deck(rR);
    for(int i = 0; i < deck.size(); i++){
        temp.deck.push_back(deck[i]);
    }
    
    int pos = 0;
    Majan m{}, n{};
    for(int i = 0; i < temp.deck.size(); i++){
        Option o = Option(temp.deck[i]);
        m = Majan(temp.deck[i].type, temp.deck[i].num, rR);
        //        m.print();
        temp.deck.erase(temp.deck.begin() + i, temp.deck.begin() + i + 1);
        
        for(int j = 0; j < 34; j++){
            temp.deck.push_back(totals[j]);
            temp.sort();
            //            for(int l = 0; l < temp.deck.size(); l++){
            //                temp.deck[l].print();
            //            }
            //            cout << endl;
            if(temp.checkHoo()){
                //                cout << "上面這副有聽" << endl;
                o.addOption(totals[j]);
            }
            pos = temp.searchMajan(&totals[j]);
            temp.deck.erase(temp.deck.begin() + pos, temp.deck.begin() + pos + 1);
        }
        if(!o.listenTo.empty()){
            bool canAdd = true;
            for(int j = 0; j < listenOption.size(); j++){
                if(o.giveOut == listenOption[j].giveOut){
                    canAdd = false;
                }
            }
            if(canAdd){
                listenOption.push_back(o);
            }
        }
        temp.deck.push_back(m);
        temp.sort();
    }
    temp.deck.clear();
    return !listenOption.empty();
}

void Deck::delMajan(Majan* m, int num){
    int pos = this->searchMajan(m);
    this->deck.erase(this->deck.begin() + pos, this->deck.begin() + pos + num);
}

void Deck::eat(Majan a, Majan b, Majan c){
    this->deckOut.push_back(b);
    this->deckOut.push_back(a);
    this->deckOut.push_back(c);
    this->delMajan(&b, 1);
    this->delMajan(&c, 1);
}

void Deck::gan(int pos, Majan m){
    if(pos != -1){
        this->deckOut.push_back(m);
        this->putDeckOut(pos, 3);
    }
}

void Deck::darkGan(int pos){
    if(pos != -1){
        putDeckOut((int)deck.size() - 1, 1);
        putDeckOut(pos, 3);
    }
}

void Deck::pon(int pos, Majan m){
    if(pos != -1){
        this->deckOut.push_back(m);
        this->putDeckOut(pos, 2);
    }
}

bool Deck::checkEat(vector<int>& eat, Majan* m){
    eat.clear();
    bool canEat = false;
    if(m->type >= 3){
        if(m->num == 1){
            Majan n = Majan(m->type, m->num + 1, rR);
            Majan o = Majan(m->type, m->num + 2, rR);
            if(this->searchMajan(&n) != -1 && this->searchMajan(&o) != -1 ){
                eat.push_back(this->searchMajan(&n));
                eat.push_back(this->searchMajan(&o));
                canEat = true;
            }
        }else if(m->num == 2){
            Majan n = Majan(m->type, m->num - 1, rR);
            Majan o = Majan(m->type, m->num + 1, rR);
            if(this->searchMajan(&n) != -1 && this->searchMajan(&o) != -1 ){
                eat.push_back(this->searchMajan(&n));
                eat.push_back(this->searchMajan(&o));
                canEat = true;
            }
            n = Majan(m->type, m->num + 1, rR);
            o = Majan(m->type, m->num + 2, rR);
            if(this->searchMajan(&n) != -1 && this->searchMajan(&o) != -1 ){
                eat.push_back(this->searchMajan(&n));
                eat.push_back(this->searchMajan(&o));
                canEat = true;
            }
        }else if(m->num >= 3 && m->num <= 7){
            Majan n = Majan(m->type, m->num - 1, rR);
            Majan o = Majan(m->type, m->num - 2, rR);
            if(this->searchMajan(&n) != -1 && this->searchMajan(&o) != -1 ){
                eat.push_back(this->searchMajan(&o));
                eat.push_back(this->searchMajan(&n));
                canEat = true;
            }
            n = Majan(m->type, m->num - 1 ,rR);
            o = Majan(m->type, m->num + 1, rR);
            if(this->searchMajan(&n) != -1 && this->searchMajan(&o) != -1 ){
                eat.push_back(this->searchMajan(&n));
                eat.push_back(this->searchMajan(&o));
                canEat = true;
            }
            n = Majan(m->type, m->num + 1, rR);
            o = Majan(m->type, m->num + 2, rR);
            if(this->searchMajan(&n) != -1 && this->searchMajan(&o) != -1 ){
                eat.push_back(this->searchMajan(&n));
                eat.push_back(this->searchMajan(&o));
                canEat = true;
            }
        }else if(m->num == 8){
            Majan n = Majan(m->type, m->num - 1, rR);
            Majan o = Majan(m->type, m->num - 2, rR);
            if(this->searchMajan(&n) != -1 && this->searchMajan(&o) != -1 ){
                eat.push_back(this->searchMajan(&o));
                eat.push_back(this->searchMajan(&n));
                canEat = true;
            }
            n = Majan(m->type, m->num - 1, rR);
            o = Majan(m->type, m->num + 1, rR);
            if(this->searchMajan(&n) != -1 && this->searchMajan(&o) != -1 ){
                eat.push_back(this->searchMajan(&n));
                eat.push_back(this->searchMajan(&o));
                canEat = true;
            }
        }else if(m->num == 9){
            Majan n = Majan(m->type, m->num - 1, rR);
            Majan o = Majan(m->type, m->num - 2, rR);
            if(this->searchMajan(&n) != -1 && this->searchMajan(&o) != -1 ){
                eat.push_back(this->searchMajan(&o));
                eat.push_back(this->searchMajan(&n));
                canEat = true;
            }
        }
        return canEat;
    }else{
        return canEat;
    }
}

int Deck::checkGan(Majan* a){
    bool canGan = false;
    int pos = this->searchMajan(a);
    if(pos != -1 && pos + 2 < deck.size()){
        if(this->deck[pos + 1].type == a->type && this->deck[pos + 1].num == a->num
           && this->deck[pos + 2].type == a->type && this->deck[pos + 2].num == a->num){
            canGan = true;
        }
    }
    if(canGan){
        return pos;
    }else{
        return -1;
    }
}

bool Deck::samePonMajan(){
    vector<Majan>temp;
    int pos = (int)deck.size() - 1;
    temp.push_back(deck[pos]);
    for(int i = 0; i < deckOut.size(); i++){
        if(deckOut[i] == deck[pos] && deckOut[i + 1] == deck[pos] && deckOut[i + 2] == deck[pos]){
            deck.erase(deck.end() - 1, deck.end());
            deckOut.insert(deckOut.begin() + i, temp.begin(), temp.end());
            temp.clear();
            return true;
        }
    }
    return false;
}

int Deck::checkPon(Majan* a){
    bool canPon = false;
    int pos = this->searchMajan(a);
    if(pos != -1 && pos + 1 < deck.size()){
        if(this->deck[pos + 1].type == a->type && this->deck[pos + 1].num == a->num){
            canPon = true;
        }
    }
    if(canPon){
        return pos;
    }else{
        return -1;
    }
}

int Deck::checkDarkGan() {
    bool canDarkGan = false;
    int pos = searchMajan(&deck[deck.size() - 1]);
    if(pos != -1 && pos + 2 < deck.size() - 1){
        if(this->deck[pos + 1] == this->deck[pos]
           && this->deck[pos + 2] == this->deck[pos]){
            canDarkGan = true;
        }
    }
    if(canDarkGan){
        return pos;
    }else{
        return -1;
    }
}

bool Deck::checkHoo(){
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
            bool win = getThree(word, wordRemain) && getThree(wan, wanRemain)
            && getThree(ton, tonRemain) && getThree(tia, tiaRemain);
            word.clear();
            wan.clear();
            tia.clear();
            ton.clear();
            return win;
        };
    }
}

int Deck::searchMajan(Majan* m){
    int pos = -1;
    for(int i = 0; i < this->deck.size(); i++){
        if(this->deck[i].type == m->type && this->deck[i].num == m->num){
            pos = i;
            return pos;
        }
    }
    return pos;
}

void Deck::addMajan(int& pos, int num, Deck* totals){
    vector<Majan> temp;
    Majan m = Majan(0, 0, rR);
    for(int i = 0; i < num; i++){
        deck.push_back(totals->deck[pos + i]);
        temp.push_back(m);
    }
    totals->deck.erase(totals->deck.begin() + pos, totals->deck.begin() + pos + num);
    totals->deck.insert(totals->deck.begin() + pos, temp.begin(), temp.end());
    temp.clear();
}

void Deck::addMajanBack(int& backPos, int num, Deck* totals) {
    vector<Majan> temp;
    Majan m = Majan(0, 0, rR);
    bool CrossZero = false;
    int end = backPos - num;
    if(end < 0){
        if(end != -1){
            CrossZero = !CrossZero;
        }
        end += 144;
    }
    if(CrossZero){
        vector<Majan> temp2;
        for(int i = 0; i < num; i++) {
            if(backPos - i >= 0){
                this->deck.push_back(totals->deck[backPos - i]);
                temp.push_back(m);
            }else{
                this->deck.push_back(totals->deck[backPos - i + 144]);
                temp2.push_back(m);
            }
        }
        totals->deck.erase(totals->deck.begin(), totals->deck.begin() + backPos + 1);
        totals->deck.insert(totals->deck.begin(), temp.begin(), temp.end());
        totals->deck.erase(totals->deck.begin() + end, totals->deck.end());
        totals->deck.insert(totals->deck.begin() + end, temp2.begin(), temp2.end());
    }else{
        for(int i = 0; i < num; i++) {
            this->deck.push_back(totals->deck[backPos - i]);
            temp.push_back(m);
        }
        if(end == 143){
            totals->deck.erase(totals->deck.begin(), totals->deck.begin() + backPos + 1);
            totals->deck.insert(totals->deck.begin(), temp.begin(), temp.end());
        }else{
            totals->deck.erase(totals->deck.begin() + end + 1, totals->deck.begin() + backPos + 1);
            totals->deck.insert(totals->deck.begin() + end + 1, temp.begin(), temp.end());
        }
        
    }
    backPos = end;
    temp.clear();
}

void Deck::putDeckOut(int pos, int num){
    if(num == 1){
        if(this->deck[pos].type == 1){
            vector<Majan>temp;
            temp.push_back(deck[pos]);
            this->deckOut.insert(deckOut.begin(), temp.begin(), temp.end());
            temp.clear();
        }else{
            this->deckOut.push_back(this->deck[pos]);
        }
    }else{
        for(int i = 0; i < num; i++){
            this->deckOut.push_back(this->deck[pos + i]);
        }
    }
    this->deck.erase(this->deck.begin() + pos, this->deck.begin() + pos + num);
}

void Deck::print(){
    cout << "<手牌>" << endl;
    for(int i = 0; i < this->deck.size(); i++){
        if(i % 36 == 0 && i != 0){
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
              [](const Majan a,const Majan b){
                  bool right = false;
                  if(b.type > a.type){
                      right = true;
                  }else if(b.type == a.type){
                      if(b.num > a.num){
                          right = true;
                      }
                  }
                  return right;});
}
