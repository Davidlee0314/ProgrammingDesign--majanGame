#include "Majan.hpp"
#include "Option.hpp"
#include <vector>
using namespace std;

#ifndef MAJANGAME_DECK_HPP
#define MAJANGAME_DECK_HPP

class Deck{
private:
    void delMajan(Majan*, int);
public:
    Deck(SDL_Renderer*);
    SDL_Renderer* rR;
    vector<Majan> deck;
    vector<Majan> deckOut;
    vector<Option> listenOption;
    void print();
    void sort();
    void addMajan(int&, int, Deck*);
    void addMajanBack(int&, int, Deck*);
    void putDeckOut(int, int);
    int searchMajan(Majan*);
    
    //檢查胡，必須把打出來或摸到的牌傳入
    bool checkHoo();
    //檢查碰，傳出可以碰的牌的位置(第一張)
    int checkPon(Majan*);
    //檢查明槓，傳出可以槓的牌的位置(第一張)
    int checkGan(Majan*);
    //檢查暗槓，傳出可以槓的牌的位置
    int checkDarkGan();
    //檢查吃，若可以吃，將傳入的陣列填滿，長度 = 可以吃的方式 * 2
    bool checkEat(vector<int>&, Majan*);
    //檢查聽，必須把打出來或摸到的牌傳入
    bool checkListen();
    bool samePonMajan();
    
    //吃
    void eat(Majan, Majan, Majan);
    //碰
    void pon(int, Majan);
    //槓
    void gan(int, Majan);
    void darkGan(int);
    //胡
    //算台
};

#endif //MAJANGAME_DECK_HPP
