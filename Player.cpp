#include "Player.hpp"
#include <random>
#include <iostream>
#include <algorithm>

Player::Player(SDL_Renderer* rRTemp) {
    win = false;
    host = false;
    listen = false;
    multiHost = 0;
    ownedDeck = new Deck(rRTemp);
    
    //for AI
    threeCount = 0;
    eyeCount = 0;
    howManyTurn = 0;

    rR = rRTemp;
}

Player::~Player(){
    ownedDeck->deck.clear();
    ownedDeck->deckOut.clear();
    left.clear();
    eye.clear();
    throwAble.clear();
    delete ownedDeck;
    ownedDeck = nullptr;
}

void Player::drawPlayer(SDL_Renderer *rR, int playerIndex, int moveIndex) {
    if(!ownedDeck->deck.empty()){
        if(playerIndex == 0){
            int totals = (int)ownedDeck->deck.size();
            for(int i = 0; i < totals; i++){
                if(i == moveIndex){
                    ownedDeck->deck[i].drawMajan(rR, 615 + (i - totals / 2) * 55, 630, 72, 50);
                }else{
                    ownedDeck->deck[i].drawMajan(rR, 615 + (i - totals / 2) * 55, 640, 72, 50);
                }
            }
            for(int i = 0; i < ownedDeck->deckOut.size(); i++){
                ownedDeck->deckOut[i].drawMajan(rR, 110 + i * 55, 555, 72, 50);
            }
        }else if(playerIndex == 1){
            for(int i = 0; i < ownedDeck->deckOut.size(); i++){
                ownedDeck->deckOut[i].drawMajanRotate(rR, 1210, 650 -  i * 52, 72, 50, 270);
            }
        }else if(playerIndex == 2){
            for(int i = 0; i < ownedDeck->deckOut.size(); i++){
                ownedDeck->deckOut[i].drawMajanRotate(rR, 150 + i * 55, 10, 72, 50, 0);
            }
        }else if(playerIndex == 3){
            for(int i = 0; i < ownedDeck->deckOut.size(); i++){
                ownedDeck->deckOut[i].drawMajanRotate(rR, 20, 5 + i * 55, 72, 50, 90);
            }
        }
    }
}

void leftToThree(vector<Majan>& left, int threeCount){
    int i = 0;
    int size = (int)left.size();
    while(i < size - 2) {
        if (left[i].type == left[i + 1].type && left[i + 1].type == left[i + 2].type) {
            if ((left[i].num == left[i + 1].num && left[i + 1].num == left[i + 2].num) ||
                (left[i].num == left[i + 1].num - 1 && left[i + 1].num == left[i + 2].num - 1 && left[i].type != 2)) {
                //                for (int j = 0; j < 3; j++) {
                //                    threeDeck[threeCount].push_back(left[i + j]);
                //                }
                left.erase(left.begin() + i, left.begin() + i + 3);
                threeCount++;
                size = (int) left.size();
            } else if (left[i].type != 2) {
                int plusOne = 0, plusTwo = 0;
                for (int j = i + 1; j < left.size(); j++) {
                    if (left[j].num > left[i].num + 2 || left[j].type != left[i].type) {
                        break;
                    } else {
                        if (plusOne == 0) {
                            if (left[j].num == left[i].num + 1) {
                                plusOne = j;
                            }
                        }
                        if (plusTwo == 0) {
                            if (left[j].num == left[i].num + 2) {
                                plusTwo = j;
                            }
                        }
                    }
                }
                if (plusOne != 0 && plusTwo != 0) {
                    //                    for (int j = 0; j < left.size(); j++) {
                    //                        if (j == i && j == plusOne && j == plusTwo) {
                    //                            threeDeck[threeCount].push_back(left[j]);
                    //                        }
                    //                    }
                    threeCount++;
                    left.erase(left.begin() + plusTwo, left.begin() + plusTwo + 1);
                    left.erase(left.begin() + plusOne, left.begin() + plusOne + 1);
                    left.erase(left.begin() + i, left.begin() + i + 1);
                    size = (int) left.size();
                } else {
                    i++;
                }
            } else {
                i++;
            }
        } else {
            i++;
        }
    }
}

void sort(vector<Majan>& a){
    std::sort(a.begin(), a.end(),
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

void Player::firstTime(){
    left.clear();
    for(int i = 0; i < ownedDeck->deck.size(); i++){ //copy ownedDeck
        left.push_back(ownedDeck->deck[i]);
    }
    leftToThree(left, threeCount);
}

void Player::refresh(){
    howManyTurn++;
    left.push_back(ownedDeck->deck[ownedDeck->deck.size() - 1]);
    sort(left);
//    cout << "******** Left驗證 ***********" <<endl;
//    for(int i = 0; i < left.size(); i++){
//        left[i].print();
//    }
//    cout << endl;
    leftToThree(left, threeCount);
    if(howManyTurn > 4 && eyeCount == 0){
        for(int j = 0; j < left.size() - 1; j++){
            if (left[j] == left[j + 1]) {
                eye.push_back(left[j]);
                eye.push_back(left[j + 1]);
                left.erase(left.begin() + j, left.begin() + j + 2);
                eyeCount = 1;
                break;
            }
        }
    }
}

bool Player::searchMajan(int type, int num, int pos){
    for(int i = 0; i < left.size(); i++)
        if(i != pos && left[i].type == type && left[i].num == num)
            return true;
    return false;
}

bool Player::searchMajanFriend(int type, int num, int pos){
    if(type == 2){
        if(searchMajan(2, num, pos)){
            return true;
        }
    }else{
        int searchStart = -2;
        int searchEnd = 2;
        if(num == 1)  //一萬
            searchStart = 0;
        else if(num == 2) //二萬
            searchStart = -1;
        else if(num == 8) //八萬
            searchEnd = 1;
        else if(num == 9) // 九萬
            searchEnd = 0;
        for(int i = searchStart; i <= searchEnd; i++) //比如說現在被要找朋友的是五萬，那就去找三四五六七萬
        {
            if(searchMajan(type, num + i, pos))   //只要這幾張存在，就回傳有朋友
                return true;
        }
    }
    return false;
}

Majan* Player::throwAway(){
    throwAble.clear();
    for(int i = 0; i < left.size(); i++){
        if(!searchMajanFriend(left[i].type, left[i].num, i)){
            throwAble.push_back(left[i]);  //如果沒朋友，裝進 left裡面
        }
    }
    
    if(throwAble.empty()){
        return &left[rand() % left.size()];  //隨便丟一張
    }
    else{
        for(int i = 0; i < throwAble.size(); i++){
            if(throwAble[i].type == 2)
                return &throwAble[i];  //優先丟單張字
        }
        return &throwAble[rand() % throwAble.size()];  //從可以丟得裡面隨便丟一張
    }
}
