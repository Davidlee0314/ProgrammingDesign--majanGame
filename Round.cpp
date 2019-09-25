#include <algorithm>
#include <random>
#include <iostream>
#include "Player.hpp"
#include "Round.hpp"
#include "Dice.hpp"
#include <thread>
#include <chrono>
#include <SDL.h>
#include <vector>

//int throwDice(){
//    random_device rd;
//    default_random_engine generator = default_random_engine(rd());
//    uniform_int_distribution<int> distribution(1,6);
//    int dice1 = distribution(generator);
//    int dice2 = distribution(generator);
//    int dice3 = distribution(generator);
//    return dice1 + dice2 + dice3;
//}

Round::~Round() {
    for(int i = 0; i < 4; i++){
        delete playerList[i];
        playerList[i] = nullptr;
    }
    totals->deck.clear();
    delete totals;
    totals = nullptr;
    haidi->deck.clear();
    delete haidi;
    haidi = nullptr;
}

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
    if(remain == 1){
        return 2 * diceNum;
    }else if(remain == 2){
        return 108 + 2 * diceNum;
    }else if(remain == 3){
        return 72 + 2 * diceNum;
    }else{
        return 36 + 2 * diceNum;
    }
}

Round::Round(SDL_Renderer* rRTemp){
    //設為東風
    wind = 0;
    rR = rRTemp;
    totals = new Deck(rRTemp);
    haidi = new Deck(rRTemp);
    initTotals();
    playerNow = 0;
    moveIndex = -1;

    justAction = false;
    justGan = false;
    failToFindWinner = false;
    allFlower = false;
    for(int i = 0; i < 4; i++){
        flower[i] = false;
    }
    tRound = new Texture;
    takeMajan = false;
    readImage();
    giveOutMajan = false;
    finishEat = true;
    finishListen = true;
//    Majan m = Majan(1,1,rR);
//    for(int i = 0; i < 80; i++){
//        haidi->deck.push_back(m);
//    }
}
void Round::readImage(){
    tRound->LoadImagePNG("eat", rR);            //0
    tRound->LoadImagePNG("eatClick", rR);       //1
    tRound->LoadImagePNG("pon", rR);            //2
    tRound->LoadImagePNG("ponClick", rR);       //3
    tRound->LoadImagePNG("gang", rR);           //4
    tRound->LoadImagePNG("gangClick", rR);      //5
    tRound->LoadImagePNG("ting", rR);           //6
    tRound->LoadImagePNG("tingClick", rR);      //7
    tRound->LoadImagePNG("hu", rR);             //8
    tRound->LoadImagePNG("huClick", rR);        //9
    tRound->LoadImagePNG("error", rR);          //10
    tRound->LoadImagePNG("button", rR);         //11

    tRound->LoadImagePNG("num_0", rR);         //12
    tRound->LoadImagePNG("num_1", rR);         //13
    tRound->LoadImagePNG("num_2", rR);         //14
    tRound->LoadImagePNG("num_3", rR);         //15
    tRound->LoadImagePNG("num_4", rR);         //16
    tRound->LoadImagePNG("num_5", rR);         //17
    tRound->LoadImagePNG("num_6", rR);         //18
    tRound->LoadImagePNG("num_7", rR);         //19
    tRound->LoadImagePNG("num_8", rR);         //20
    tRound->LoadImagePNG("num_9", rR);         //21

    tRound->LoadImagePNG("blackBoard", rR);    //22
    tRound->LoadImagePNG("restart", rR);       //23
    tRound->LoadImagePNG("restartClick", rR);   //24

    tRound->LoadImagePNG("taiMeet0", rR);      //25
    tRound->LoadImagePNG("taiMeet1", rR);      //26
    tRound->LoadImagePNG("taiMeet2", rR);      //27
    tRound->LoadImagePNG("taiMeet3", rR);      //28
    tRound->LoadImagePNG("taiMeet4", rR);      //29
    tRound->LoadImagePNG("taiMeet5", rR);      //30
    tRound->LoadImagePNG("taiMeet6", rR);      //31
    tRound->LoadImagePNG("taiMeet7", rR);      //32
    tRound->LoadImagePNG("taiMeet8", rR);      //33
    tRound->LoadImagePNG("taiMeet9", rR);      //34
    tRound->LoadImagePNG("taiMeet10", rR);      //35
    tRound->LoadImagePNG("taiMeet11", rR);      //36
    tRound->LoadImagePNG("taiMeet12", rR);      //37
    tRound->LoadImagePNG("taiMeet13", rR);      //38
    tRound->LoadImagePNG("taiMeet14", rR);      //39
    tRound->LoadImagePNG("taiMeet15", rR);      //40
    tRound->LoadImagePNG("taiMeet16", rR);      //41
    tRound->LoadImagePNG("taiMeet17", rR);      //42
    tRound->LoadImagePNG("player", rR);      //43
    tRound->LoadImagePNG("again", rR);      //44
}
void Round::drawOption(int x, int y, int h, int w, int index){
    tRound->Draw(rR, 0 ,0, h, w, x ,y, index);
}

void Round::drawRoundRotate(int x, int y, int h, int w, double angle){
    rect.x = x;
    rect.y = y;
    rect.h = h;
    rect.w = w;
    tRound->RotateImage(rR, angle, 11, &rect);
}

void Round::initTotals() {
    majanNow = 64;
    for(int i = 1; i < 6; i++){
        if(i == 1){
            for(int j = 1; j < 9; j++){
                Majan temp = Majan(i, j ,rR);
                this->totals->deck.push_back(temp);
            }
        }else if(i == 2){
            int repeat = 4;
            while(repeat != 0){
                for (int j = 1; j < 8; j++){
                    Majan temp = Majan(i, j ,rR);
                    this->totals->deck.push_back(temp);
                }
                repeat--;
            }
        }else{
            int repeat = 4;
            while(repeat != 0){
                for (int j = 1; j < 10; j++){
                    Majan temp = Majan(i, j ,rR);
                    this->totals->deck.push_back(temp);
                }
                repeat--;
            }
        }
    }
    shuffle(&totals->deck[0], &totals->deck[143], std::mt19937(std::random_device()()));
}

bool Round::haveWinner(){
    bool haveWinner = false;
    for(int i = 0; i < 4; i++){
        if(playerList[i]->win){
            haveWinner = true;
        }
    }
    return haveWinner;
}

int Round::playerNext() {
    int next = playerNow;
    if(playerNow == 3){
        next = 0;
    }else{
        next += 1;
    }
    return next;
}

void Round::updateInitRound(int diceNum){
    pos = calcPos(diceNum) + 64 - majanNow;
    if(pos > 143){
        pos -= 144;
    }
    if(majanNow == 64){
        backPos = pos - 1;
        open = pos % 4;
    }
    if(pos == 142){
        playerList[playerNow]->ownedDeck->addMajan(pos, 2, totals);
        pos = 0;
        playerList[playerNow]->ownedDeck->addMajan(pos, 2, totals);
    }else{
        playerList[playerNow]->ownedDeck->addMajan(pos, 4, totals);
    }
//    playerList[playerNow]->ownedDeck->print();
    playerNow = nextPlayer(playerNow);
    majanNow -= 4;
    if(majanNow == 0){
        playerNow = 0;
        pos += 4;
        if(pos > 143){
            pos -= 144;
        }
        playerList[playerNow]->ownedDeck->addMajan(pos, 1, totals);
        pos += 1;
        if(pos > 143){
            pos -= 144;
        }
    }
}

int Round::updateFlower(){
    int flowerNum = 0;
    if(!allFlower){
        for(int i = 0; i < 8; i++){
            if(playerList[playerNow]->ownedDeck->deck[i].type != 1){
                break;
            }else{
                flowerNum ++;
            }
        }
        if(flowerNum == 0){
            flower[playerNow] = true;
        }else{
            playerList[playerNow]->ownedDeck->putDeckOut(0, flowerNum);
            playerList[playerNow]->ownedDeck->addMajanBack(backPos, flowerNum, totals);
        }
        playerList[playerNow]->ownedDeck->sort();
        allFlower = flower[0] && flower[1] && flower[2] && flower[3];
        if(!allFlower){
            playerNow = nextPlayer(playerNow);
            while(flower[playerNow]){
                playerNow = nextPlayer(playerNow);
            }
            return 0;
        }else{
            return 1;
        }
    }
    return 0;
}

int Round::updatePlayer(int x, int y, bool mouseL) {
    int giveOutIndex = -1;
    int totalsIndex = (int)playerList[0]->ownedDeck->deck.size();
    bool giveOut = false;
    justAction = false;
    giveOutMajan = false;

    if(y > 645 && y < 717){
        if(x > 615 + (0 - totalsIndex / 2) * 55 && x < 615 + (totalsIndex - 1 - totalsIndex / 2) * 55 + 50){
            giveOut = true;
        }
    }else if(y > 550 && y < 600){
        choose.clear();
        if(x > 850 && x < 900 && mouseL){
            choose.push_back(1);
        }else if(x > 900 && x < 950 && mouseL){
            choose.push_back(2);
        }else if(x > 950 && x < 1000 && mouseL){
            choose.push_back(3);
        }else if(x > 1000 && x < 1050 && mouseL){
            choose.push_back(4);
        }else if(x > 1050 && x < 1100 && mouseL){
            choose.push_back(5);
        }
    }

    if(!haveWinner() && !failToFindWinner) {
        action.clear();

        if(!takeMajan){
            if (playerList[playerNow]->ownedDeck->deck.size() != 17 && !justAction) {
                playerList[playerNow]->ownedDeck->addMajan(pos, 1, totals);
                pos += 1;
                if(pos > 143){
                    pos -= 144;
                }
                //check 是否為花牌，是則補花
                while (playerList[playerNow]->ownedDeck->deck.back().type == 1) {
                    playerList[playerNow]->ownedDeck->putDeckOut(
                            (int) playerList[playerNow]->ownedDeck->deck.size() - 1, 1);
                    playerList[playerNow]->ownedDeck->addMajanBack(backPos, 1, totals);
                }

                //檢查是否自動槓牌
                if(playerList[playerNow]->ownedDeck->samePonMajan()){
                    playerList[playerNow]->ownedDeck->addMajanBack(backPos, 1, totals);
                    while(playerList[playerNow]->ownedDeck->deck.back().type == 1){
                        playerList[playerNow]->ownedDeck->putDeckOut(
                                (int)playerList[playerNow]->ownedDeck->deck.size() - 1, 1);
                        playerList[playerNow]->ownedDeck->addMajanBack(backPos, 1, totals);
                    }
                }
            }else{
                if(justGan){
                    justGan = false;
                    playerList[playerNow]->ownedDeck->addMajanBack(backPos, 1, totals);
                    while(playerList[playerNow]->ownedDeck->deck.back().type == 1){
                        playerList[playerNow]->ownedDeck->putDeckOut(
                                (int)playerList[playerNow]->ownedDeck->deck.size() - 1, 1);
                        playerList[playerNow]->ownedDeck->addMajanBack(backPos, 1, totals);
                    }
                }
            }
            takeMajan = true;
        }

        //檢查暗槓，若可以則要再摸
        int pos = playerList[playerNow]->ownedDeck->checkDarkGan();
        if (pos != -1){
            action.push_back(3);
            if(choose[0] == 3) {
                playerList[playerNow]->ownedDeck->darkGan(pos);
                playerList[playerNow]->ownedDeck->addMajanBack(backPos, 1, totals);
                while(playerList[playerNow]->ownedDeck->deck.back().type == 1){
                    playerList[playerNow]->ownedDeck->putDeckOut(
                            (int)playerList[playerNow]->ownedDeck->deck.size() - 1, 1);
                    playerList[playerNow]->ownedDeck->addMajanBack(backPos, 1, totals);
                }
            }
        }

        //打什麼
        if (!playerList[playerNow]->listen) {
            //檢查可聽
            if (playerList[playerNow]->ownedDeck->checkListen()) {
                //印出選項
                action.push_back(4);
                if(choose[0] == 4){
                    finishListen = false;
                }
//                cout << "player0 聽了" << endl;
            } else {
                for (int i = 0; i < totalsIndex; i++) {
                    if (y > 645 && y < 717) {
                        if (x > 615 + (i - totalsIndex / 2) * 55 && x < 615 + (i - totalsIndex / 2) * 55 + 50) {
                            if (mouseL) {
                                giveOutIndex = i;
                            }
                        }
                    }
                }
            }
        } else {
            //檢查可胡
            Majan n = Majan(playerList[playerNow]->ownedDeck->deck.back().type,
                            playerList[playerNow]->ownedDeck->deck.back().num, rR);
            playerList[playerNow]->ownedDeck->sort();

            if (playerList[playerNow]->ownedDeck->checkHoo()) {
                action.push_back(5);
                if(choose[0] == 5){
                    playerList[playerNow]->win = true;
                }
            } else {
                giveOutIndex = playerList[playerNow]->ownedDeck->searchMajan(&n);
                m = new Majan(playerList[playerNow]->ownedDeck->deck[giveOutIndex].type,
                              playerList[playerNow]->ownedDeck->deck[giveOutIndex].num, rR);
                playerList[playerNow]->ownedDeck->deck.erase(
                        playerList[playerNow]->ownedDeck->deck.begin() + giveOutIndex,
                        playerList[playerNow]->ownedDeck->deck.begin() + giveOutIndex + 1);
                haidi->deck.push_back(*m);
                playerList[playerNow]->ownedDeck->sort();
                giveOutMajan = true;
            }
        }


        if(!finishListen){
            moveListenIndex = -1;
            for (int i = 0; i < totalsIndex; i++) {
                if (y > 645 && y < 717) {
                    if (x > 615 + (i - totalsIndex / 2) * 55 && x < 615 + (i - totalsIndex / 2) * 55 + 50) {
                        moveListenIndex = i;
                        if (mouseL) {
                            giveOutIndex = i;

                            //確認打牌後有聽
                            for(int j = 0; j < playerList[playerNow]->ownedDeck->listenOption.size(); j++){
                                if(playerList[playerNow]->ownedDeck->deck[giveOutIndex] ==
                                   playerList[playerNow]->ownedDeck->listenOption[j].giveOut){
                                    playerList[playerNow]->listen = true;
                                }
                            }
                            finishListen = true;
                        }
                    }
                }
            }
        }

        //出牌
        if (mouseL && giveOut) {
            giveOutMajan = true;
            if (!haveWinner()) {
                if (giveOutIndex < playerList[playerNow]->ownedDeck->deck.size()) {
                    m = new Majan(playerList[playerNow]->ownedDeck->deck[giveOutIndex].type,
                              playerList[playerNow]->ownedDeck->deck[giveOutIndex].num, rR);
                    playerList[playerNow]->ownedDeck->deck.erase(
                            playerList[playerNow]->ownedDeck->deck.begin() + giveOutIndex,
                            playerList[playerNow]->ownedDeck->deck.begin() + giveOutIndex + 1);
                    haidi->deck.push_back(*m);
                }
                playerList[playerNow]->ownedDeck->sort();
            }

            if (totals->deck[posPre16()].type == 0) {
                failToFindWinner = true;
            }
        }

    }

    if(giveOutIndex == -1){
        for(int i = 0; i < totalsIndex; i++){
            if(y > 645 && y < 717){
                if(x > 615 + (i - totalsIndex / 2) * 55 && x < 615 + (i - totalsIndex / 2) * 55 + 50){
                    return i;
                }
            }
        }
    }else{
        return -1;
    }
    return 0;
}

bool Round::updatePlayerHu(int x, int y, bool mouseL) {
    choose.clear();
    action.clear();

    if(y > 550 && y < 600){
        if(x > 1050 && x < 1100 && mouseL){
            choose.push_back(5);
        }else if(x > 800 && x < 850 && mouseL){
            choose.push_back(6);
        }
    }

    if(!haveWinner() && !failToFindWinner){
        playerList[0]->ownedDeck->deck.push_back(*m);
        playerList[0]->ownedDeck->sort();
        int posHu = playerList[0]->ownedDeck->searchMajan(m);

        if(playerList[0]->ownedDeck->checkHoo()){
//            cout << "player 1 win" << endl;
            action.push_back(5);
            if(!choose.empty()){
                if(choose[0] == 5){
                    playerList[0]->win = true;
                }
            }else{
                playerList[0]->ownedDeck->deck.erase(
                    playerList[0]->ownedDeck->deck.begin() + posHu,
                    playerList[0]->ownedDeck->deck.begin() + posHu + 1);
            }
            return true;
        }else{
//            cout << "清麻將" << posHu << endl;
            playerList[0]->ownedDeck->deck.erase(
                    playerList[0]->ownedDeck->deck.begin() + posHu,
                    playerList[0]->ownedDeck->deck.begin() + posHu + 1);
            return false;
        }
    }
    return 0;
}

void Round::updatePlayerAction(int x, int y, bool mouseL){
    choose.clear();
    action.clear();

    if(y > 550 && y < 600){
        if(x > 850 && x < 900 && mouseL){
            choose.push_back(1);
        }else if(x > 900 && x < 950 && mouseL){
            choose.push_back(2);
        }else if(x > 950 && x < 1000 && mouseL){
            choose.push_back(3);
        }else if(x > 1000 && x < 1050 && mouseL){
            choose.push_back(4);
        }else if(x > 800 && x < 850 && mouseL){
            choose.push_back(6);
        }
    }

    if(!finishEat) {
        moveEatIndex = -1;
        int totalsInt = (int)playerList[0]->ownedDeck->deck.size();
        for(int i = 0; i < totalsInt; i++){
            if(x > 615 + (i - totalsInt / 2) * 55 && x < 615 + (i - totalsInt / 2 ) * 55 + 50){
                if(y > 630 && y < 702){
                    moveEatIndex = i;
                    if(mouseL){
                        int index1 = -1, index2 = -1;
                        for(int j = 0; j < eatIndex.size(); j++){
                            if(eatIndex[j] == i){
                                if(j % 2 == 0){
                                    index1 = eatIndex[j];
                                    index2 = eatIndex[j + 1];
                                }else{
                                    index1 = eatIndex[j - 1];
                                    index2 = eatIndex[j];
                                }
                            }
                        }
                        if(index1 != -1 && index2 != -1){
                            playerList[0]->ownedDeck->eat(*m, playerList[0]->ownedDeck->deck[index1],
                                                          playerList[0]->ownedDeck->deck[index2]);
                            haidi->deck.erase(haidi->deck.end() - 1, haidi->deck.end());
                            playerNow = 0;
                            justAction = true;
                            finishEat = true;
                            eatIndex.clear();
                        }
                    }
                }
            }
        }
    }

    if(!haveWinner() && !failToFindWinner){

        if(!playerList[0]->listen){
            // 可碰
            int pon = 0;
            if(!playerList[0]->listen){
                int posPon = playerList[0]->ownedDeck->checkPon(m);
                if(posPon != -1){
                    action.push_back(2);
                    if(!choose.empty()){
                        if(choose[0] == 2){
                            pon = 1;
                            playerList[0]->ownedDeck->pon(posPon, *m);
                            haidi->deck.erase(haidi->deck.end() - 1, haidi->deck.end());
                            playerNow = 0;
                            justAction = true;
                        }
                    }
                }
            }

            // 可槓
            int gan = 0;
            if(!playerList[0]->listen && playerNow != 3){
                int posGan = playerList[0]->ownedDeck->checkGan(m);
                if (posGan != -1) {
                    action.push_back(3);
                    if(!choose.empty()){
                        if (choose[0] == 3) {
                            gan = 1;
                            playerList[0]->ownedDeck->gan(posGan, *m);
                            haidi->deck.erase(haidi->deck.end() - 1, haidi->deck.end());
                            playerNow = 0;
                            justAction = true;
                            justGan = true;
                            takeMajan = false;
                        }
                    }
                }
            }

            //檢查下家可吃
            if(pon == 0 && gan == 0 && playerNow == 3){
                playerList[0]->ownedDeck->checkEat(eatIndex, m);
                if(!eatIndex.empty() && !playerList[0]->listen){
                    action.push_back(1);
                    if(!choose.empty()){
                        if(choose[0] == 1){
                            if(eatIndex.size() == 2){
                                playerList[0]->ownedDeck->eat(*m, playerList[0]->ownedDeck->deck[eatIndex[0]],
                                                              playerList[0]->ownedDeck->deck[eatIndex[1]]);
                                haidi->deck.erase(haidi->deck.end() - 1, haidi->deck.end());
                                playerNow = 0;
                                justAction = true;
                                finishEat = true;
                                eatIndex.clear();
                            }else{
                                finishEat = false;
                            }
                        }
                    }
                }
            }
        }
    }
}

void Round::updateAI() {
    int giveOutIndex = -1;

    if(!haveWinner() && !failToFindWinner){
        if(playerList[playerNow]->ownedDeck->deck.size() != 17 && !justAction) {
//            cout << "抓牌： " << pos << endl;
            playerList[playerNow]->ownedDeck->addMajan(pos, 1, totals);
            pos += 1;
            if(pos > 143){
                pos -= 144;
            }

            //check 是否為花牌，是則補花
            while (playerList[playerNow]->ownedDeck->deck.back().type == 1) {
                playerList[playerNow]->ownedDeck->putDeckOut(
                        (int) playerList[playerNow]->ownedDeck->deck.size() - 1, 1);
                playerList[playerNow]->ownedDeck->addMajanBack(backPos, 1, totals);
            }

            int pos = playerList[playerNow]->ownedDeck->checkDarkGan();
            if (pos != -1){
                playerList[playerNow]->ownedDeck->darkGan(pos);
                playerList[playerNow]->firstTime();
            }

            if(playerList[playerNow]->ownedDeck->samePonMajan()){
                playerList[playerNow]->ownedDeck->addMajanBack(backPos, 1, totals);
                while(playerList[playerNow]->ownedDeck->deck.back().type == 1){
                    playerList[playerNow]->ownedDeck->putDeckOut(
                            (int)playerList[playerNow]->ownedDeck->deck.size() - 1, 1);
                    playerList[playerNow]->ownedDeck->addMajanBack(backPos, 1, totals);
                }
            }
        }

        if(!playerList[playerNow]->listen){
            //檢查可聽
            if(playerList[playerNow]->ownedDeck->checkListen()){
                if(!justAction){
                    playerList[playerNow]->refresh();
                }
                //印出選項
                int most = 0, mostIndex = 0;
                for(int i = 0; i < playerList[playerNow]->ownedDeck->listenOption.size(); i++){
                    if(playerList[playerNow]->ownedDeck->listenOption[i].listenTo.size() > most){
                        mostIndex = i;
                    }
                }
                giveOutIndex = playerList[playerNow]->ownedDeck->searchMajan(
                        &playerList[playerNow]->ownedDeck->listenOption[mostIndex].giveOut);
                playerList[playerNow]->listen = true;
            }else{
                if(!justAction){
                    playerList[playerNow]->refresh();
                }
                Majan* n = playerList[playerNow]->throwAway();
//                cout << "要丟的麻將: ";
//                n->print();
//                cout << endl;
                giveOutIndex = playerList[playerNow]->ownedDeck->searchMajan(n);
            }
        }else{
            if(!justAction){
                playerList[playerNow]->refresh();
            }

            //檢查可胡
            Majan m = Majan(playerList[playerNow]->ownedDeck->deck[playerList[playerNow]->ownedDeck->deck.size() - 1].type,
                playerList[playerNow]->ownedDeck->deck[playerList[playerNow]->ownedDeck->deck.size() - 1].num, rR);
            playerList[playerNow]->ownedDeck->sort();
            if(playerList[playerNow]->ownedDeck->checkHoo()){
                playerList[playerNow]->win = true;
            }else{
                giveOutIndex = playerList[playerNow]->ownedDeck->searchMajan(&m);
            }
        }
        justAction = false;
//        cout << endl;
//        cout << "********** 摸牌 ***********" << endl;
//        playerList[playerNow]->ownedDeck->print();
//        cout << endl << " ------------left---------------" << endl;
//        for(int j = 0; j < playerList[playerNow]->left.size(); j++){
//            playerList[playerNow]->left[j].print();
//        }
//        cout << "問題 2: player" << playerNow + 1 << " -- 聽了: " << playerList[playerNow]->listen<< endl;
//        cout << "giveOutIndex = " << giveOutIndex << endl;
//        cout << "***************************" << endl;
//        cout << endl;

        //出牌
        if(!haveWinner()){
            if(giveOutIndex < playerList[playerNow]->ownedDeck->deck.size()){
                m = new Majan(playerList[playerNow]->ownedDeck->deck[giveOutIndex].type,
                    playerList[playerNow]->ownedDeck->deck[giveOutIndex].num, rR);
                playerList[playerNow]->ownedDeck->deck.erase(
                        playerList[playerNow]->ownedDeck->deck.begin() + giveOutIndex,
                        playerList[playerNow]->ownedDeck->deck.begin() + giveOutIndex + 1);

                //清 left
                int pos = 0;
                for(int i = 0; i < playerList[playerNow]->left.size(); i++){
                    if(*m == playerList[playerNow]->left[i]){
                        pos = i;
                        break;
                    }
                }
                playerList[playerNow]->left.erase(playerList[playerNow]->left.begin() + pos,
                                                  playerList[playerNow]->left.begin() + pos + 1);
                haidi->deck.push_back(*m);
//                cout <<"Player " << playerNow + 1<<  " 出牌" << endl;
//                m->print();
            }
            playerList[playerNow]->ownedDeck->sort();
//            cout << "<<問題可能點>> sorting" << endl;
//            playerList[playerNow]->ownedDeck->print();
//            cout << endl;
        }

        if(totals->deck[posPre16()].type == 0){
            failToFindWinner = true;
        }
    }
}

int Round::updateAIPonHu() {
    if(!haveWinner() && !failToFindWinner){
        // 可胡
        for(int i = 0; i < 4; i++){
            if(i != playerNow && i != 0){
                playerList[i]->ownedDeck->deck.push_back(*m);
                playerList[i]->ownedDeck->sort();
                int pos = playerList[i]->ownedDeck->searchMajan(m);

                if(playerList[i]->ownedDeck->checkHoo()){
//                    cout << i + 1<< " win" << endl;
                    playerList[i]->win = true;
                    justAction = true;
                    return 2;
                }else{
                    playerList[i]->ownedDeck->deck.erase(playerList[i]->ownedDeck->deck.begin() + pos,
                                                         playerList[i]->ownedDeck->deck.begin() + pos + 1);
                }
            }
        }

        // 可碰
        for(int i = 0; i < 4; i++){
            if(i != playerNow && i != 0 && !playerList[i]->listen){
                int pos = 0;
                pos = playerList[i]->ownedDeck->checkPon(m);
                if(pos != -1){
                    playerList[i]->ownedDeck->pon(pos, *m);
                    haidi->deck.erase(haidi->deck.end() - 1, haidi->deck.end());
                    playerNow = i;
                    justAction = true;
                    playerList[playerNow]->firstTime();
                    return 1;
                }
            }
        }
    }
    return 0;
}

void Round::updateAIAction(int pon){

    if(!haveWinner() && !failToFindWinner){

        //檢查下家可吃
        if(pon == 0){
            vector<int> eatStore;
            int next = playerNext();
            playerList[next]->ownedDeck->checkEat(eatStore, m);
            if(next != 0 && !eatStore.empty() && !playerList[next]->listen){
                playerList[next]->ownedDeck->eat(*m,
                        playerList[next]->ownedDeck->deck[eatStore[0]],
                        playerList[next]->ownedDeck->deck[eatStore[1]]);
                haidi->deck.erase(haidi->deck.end() - 1, haidi->deck.end());
                playerNow = next;
                justAction = true;
                playerList[playerNow]->firstTime();
            }
            eatStore.clear();
        }
    }

}

void Round::drawRound() {
    if(finishEat && finishListen){
        for(int i = 0; i < 4; i++) {
            playerList[i]->drawPlayer(rR, i, moveIndex);
        }
    }else if(!finishEat){
        vector<Majan>temp;
        for(int i = 1; i < 4; i++) {
            playerList[i]->drawPlayer(rR, i, moveIndex);
        }
        for(int i = 0; i < playerList[0]->ownedDeck->deck.size(); i++){
            Majan m = Majan(playerList[0]->ownedDeck->deck[i].type,
                                playerList[0]->ownedDeck->deck[i].num,
                                rR);
            temp.push_back(m);
        }
        int move2Index = -1;
        for(int i = 0; i < eatIndex.size(); i++){
            if(moveEatIndex == eatIndex[i]){
                if(i % 2 == 0){
                    move2Index = eatIndex[i + 1];
                }else{
                    move2Index = eatIndex[i - 1];
                }
            }
        }
        for(int i = 0; i < temp.size(); i++){
            bool canEat = false;
            for(int j = 0; j < eatIndex.size(); j++){
                if(i == eatIndex[j]){
                    canEat = true;
                }
            }
            if(canEat && (i == moveEatIndex || i == move2Index)){
                temp[i].drawMajan(rR, 615 + (i - (int)temp.size() / 2) * 55, 630, 72, 50);
            }else if(canEat){
                temp[i].drawMajan(rR, 615 + (i - (int)temp.size() / 2) * 55, 640, 72, 50);
            }else{
                temp[i].drawMajanOpacity(rR, 615 + (i - (int)temp.size() / 2) * 55, 640, 72, 50, 128);
            }
        }
        temp.clear();
    }else if(!finishListen){
        vector<Majan>temp;
        for(int i = 1; i < 4; i++) {
            playerList[i]->drawPlayer(rR, i, moveIndex);
        }
        for(int i = 0; i < playerList[0]->ownedDeck->deck.size(); i++){
            Majan m = Majan(playerList[0]->ownedDeck->deck[i].type,
                            playerList[0]->ownedDeck->deck[i].num,
                            rR);
            temp.push_back(m);
        }

        for(int i = 0; i < temp.size(); i++){
            bool canListen = false;
            for(int j = 0; j < playerList[0]->ownedDeck->listenOption.size(); j++){
                if(temp[i] == playerList[0]->ownedDeck->listenOption[j].giveOut){
                    canListen = true;
                }
            }
            if(canListen && i == moveListenIndex){
                temp[i].drawMajan(rR, 615 + (i - (int)temp.size() / 2) * 55, 630, 72, 50);
            }else if(canListen){
                temp[i].drawMajan(rR, 615 + (i - (int)temp.size() / 2) * 55, 640, 72, 50);
            }else{
                temp[i].drawMajanOpacity(rR, 615 + (i - (int)temp.size() / 2) * 55, 640, 72, 50, 128);
            }
        }
        temp.clear();
    }


    int xOffset = 175, yOffset = 150;
    for(int i = 0; i < haidi->deck.size(); i++){
        int remain = i % 17;
        int index = (int)floor(i / 17);
        haidi->deck[i].drawMajan(rR, xOffset + 55 * remain, yOffset + 80 * index, 72, 50);
    }

    if(!action.empty()){
        drawOption(800 , 550, 50 ,50, 10);
        for(int i = 0; i < action.size(); i++){
            if(action[i] != -1){
                drawOption(850 + 50 * (action[i] - 1), 550, 50 ,50, (action[i] - 1) * 2 + 1);
            }
        }
    }

    if(allFlower){
        if(playerNow == 0){
            drawRoundRotate(605, 450, 70, 70, 90);
        }else if(playerNow == 1){
            drawRoundRotate(1110, 325, 70, 70, 0);
        }else if(playerNow == 2){
            drawRoundRotate(605, 70, 70, 70, 270);
        }else{
            drawRoundRotate(100, 325, 70, 70, 180);
        }
    }
}


int Round::posPre16() {
    return (backPos - 15 < 0) ? (backPos - 15 + 144) : (backPos - 15);
}

int Round::countTai(int winner, int loser, bool selfTouch)
{
    wind += 1;
    // 18 types of hoo
    for (int i = 0; i < 18; i++) {
        taiMeet[i] = false;
        // reset
    }
    // ADDED BY HSIEN
    /*  =============
     *  taiMeet index
     *  =============
     *  0   風圈      一台         9    全求人 一台
     *  1   自摸      一台         10   五暗刻 八台
     *  2   門清      一台         11   大三元 八台
     *  3   自摸又門清 一台         12   小三元 四台
     *  4   贏家莊家   一台         13   大四喜 十六台
     *  5   輸家莊家   一台         14   小四喜 八台
     *  6   八仙過海   八台         15   字一色 十六台
     *  7   花槓      兩台         16   清一色 十六台
     *  8   碰碰胡     四台         17   混一色 十六台
     */


    int taiCount = 0;
    int deckCount = (int)playerList[winner]->ownedDeck->deck.size();
    int deckOutCount = (int)playerList[winner]->ownedDeck->deckOut.size();
    vector<Majan> myMajan;
    vector<Majan> myFlower;
    for(int i = 0; i < deckCount; i++)
        myMajan.push_back(playerList[winner]->ownedDeck->deck[i]);
    for(int i = 0; i < deckOutCount; i++)
        if(playerList[winner]->ownedDeck->deckOut[i].type == 1)
            myFlower.push_back(playerList[winner]->ownedDeck->deckOut[i]);
        else
            myMajan.push_back(playerList[winner]->ownedDeck->deckOut[i]);

    //風圈
    for(int i = 0; i < myMajan.size() - 3; i++)
        if(myMajan[i].type == 2 and myMajan[i].num == wind and myMajan[i + 1].type == 2 and myMajan[i].num == wind and myMajan[i + 2].type == 2 and myMajan[i + 2].num == wind
           and (myMajan[i + 3].type != 2 or (myMajan[i + 3].type == 2 and myMajan[i + 3].num != wind)))
        {
            taiCount++;
//            cout << "風圈  一台";
            taiMeet[0] = true;
        }
    //自摸
    if(selfTouch)
    {
        taiCount++;
//        cout << "自摸  一台";
        taiMeet[1] = true;
    }
    //門清
    if(playerList[winner]->ownedDeck->deckOut.empty())
    {
        taiCount ++;
//        cout << "門清  一台";
        taiMeet[2] = true;
    }
    //自摸門清
    if(selfTouch and playerList[winner]->ownedDeck->deckOut.empty())
    {
        taiCount++;
//        cout << "自摸又門清　一台";
        taiMeet[3] = true;
    }
    //莊家
    if((playerList[winner]->host or playerList[loser]->host) and !selfTouch)
    {
        taiCount ++;
//        cout << "贏家莊家　一台";
        taiMeet[4] = true;
    }
    else if(playerList[winner]->host and selfTouch)
    {
        taiCount ++;
//        cout << "輸家莊家　一台";
        taiMeet[5] = true;
    }
    //碰碰胡
    if(myMajan.size() == 17)
    {
        int i = 0;
        int eye = 0;
        bool allPon = true;
        while(i < 15 and allPon)  //最後才讀到眼睛　Ｉ：１４　ｅｌｓｅ　Ｉ：１３
        {
            if(eye > 1)
                allPon = false;
            if(myMajan[i] == myMajan[i + 1] and myMajan[i + 1] == myMajan[i + 2])
                i += 3;
            else if(myMajan[i] == myMajan[i + 1] and myMajan[i + 1].type != myMajan[i + 2].type && myMajan[i + 1].num != myMajan[i + 2].num)
            {
                eye++;
                i += 2;
            }
            else
                allPon = false;
        }
        if(allPon)
        {
            taiCount += 4;
//            cout << "碰碰胡　四台";
            taiMeet[8] = true;
        }
    }
    //全球人
    if(playerList[winner]->ownedDeck->deck.size() == 2 and !selfTouch)
    {
        taiCount += 2;
//        cout << "全求人　一台";
        taiMeet[9] = true;
    }
    //五暗刻
    if(playerList[winner]->ownedDeck->deck.size() == 17)
    {
        int i = 0;
        int eye = 0;
        bool allPon = true;
        while(i < 15 and allPon)  //最後才讀到眼睛　Ｉ：１４　ｅｌｓｅ　Ｉ：１３
        {
            if(eye > 1)
                allPon = false;
            if(playerList[winner]->ownedDeck->deck[i] == playerList[winner]->ownedDeck->deck[i + 1] and playerList[winner]->ownedDeck->deck[i + 1] == playerList[winner]->ownedDeck->deck[i + 2])
                i += 3;
            else if(playerList[winner]->ownedDeck->deck[i] == playerList[winner]->ownedDeck->deck[i + 1] and playerList[winner]->ownedDeck->deck[i + 1].type != playerList[winner]->ownedDeck->deck[i + 2].type &&
                    playerList[winner]->ownedDeck->deck[i + 1].num != playerList[winner]->ownedDeck->deck[i + 2].num)
            {
                eye++;
                i += 2;
            }
            else
                allPon = false;
        }
        if(allPon)
        {
            taiCount += 8;
//            cout << "五暗刻　八台";
            taiMeet[10] = true;
        }
    }
    //大三元
    for(int i = 0; i < myMajan.size() - 8; i++)
    {
        if(myMajan[i].type == 2 and myMajan[i].num == 5)  //找到中
            if(myMajan[i + 5].type == 2 and myMajan[i + 5].num == 6 and myMajan[i + 8].type == 2 and myMajan[i + 8].num == 7)
            {
                taiCount += 8;
//                cout << "大三元　八台";
                taiMeet[11] = true;
                break;
            }
    }
    //大四喜
    for(int i = 0; i < myMajan.size() - 2; i++)
    {
        if(myMajan[i].type == 2 and myMajan[i].num == 1) //找到東
            if(myMajan[i + 5].type == 2 and myMajan[i + 5].num == 2 and myMajan[i + 8].type == 2 and myMajan[i + 8].num == 3 and myMajan[i + 11].type == 2 and myMajan[i + 11].num == 4)
            {
                taiCount += 16;
//                cout << "大四喜　十六台";
                taiMeet[13] = true;
                break;
            }
    }
    //小四喜
    if(!playerList[winner]->eye.empty()){
        if(playerList[winner]->eye[0].type == 2 and (playerList[winner]->eye[0].num == 1 or playerList[winner]->eye[0].num == 2 or playerList[winner]->eye[0].num == 3 or playerList[winner]->eye[0].num == 4))
        {
            int east = 0;
            int west = 0;
            int south = 0;
            int north = 0;
            for(int i = 0; i < myMajan.size() - 2; i++)
                if(myMajan[i].type == 2 and myMajan[i].num == 1)
                    east ++;
                else if(myMajan[i].type == 2 and myMajan[i].num == 2) //發
                    west ++;
                else if(myMajan[i].type == 2 and myMajan[i].num == 3)
                    south++;
                else if(myMajan[i].type == 2 and myMajan[i].num == 4)
                    north++;
            if(east + west + south == 9 or east + west + north == 9 or east + north + south == 9 or west + north + south == 9)
            {
                taiCount += 8;
//                cout << "小四喜　八台";
                taiMeet[14] = true;
            }
        }
        //小三元
        if(playerList[winner]->eye[0].type == 2 and (playerList[winner]->eye[0].num == 5 or playerList[winner]->eye[0].num == 6 or playerList[winner]->eye[0].num == 7))
        {
            int jong = 0;
            int fa = 0;
            int white = 0;
            for(int i = 0; i < myMajan.size() - 2; i++)
                if(myMajan[i].type == 2 and myMajan[i].num == 5) //中
                    jong ++;
                else if(myMajan[i].type == 2 and myMajan[i].num == 6) //發
                    fa ++;
                else if(myMajan[i].type == 2 and myMajan[i].num == 7)
                    white++;
            if(jong + fa == 6 or jong + white == 6 or fa + white == 6)
            {
                taiCount += 4;
//                cout << "小三元　四台";
                taiMeet[12] = true;
            }
        }
    }

    //字一色
    bool allWord = true;
    for(int i = 0; i < myMajan.size(); i++)
        if(myMajan[i].type != 2)
        {
            allWord = false;
            break;
        }
    if(allWord)
    {
        taiCount += 16;
//        cout << "字一色　十六台";
        taiMeet[15] = true;
    }
    //清一色
    int sameType = myMajan[0].type;
    if(sameType != 2)
    {
        bool allSame = true;
        for(int i = 1; i < myMajan.size(); i++)
            if(myMajan[i].type != sameType)
            {
                allSame = false;
                break;
            }
        if(allSame)
        {
            taiCount += 8;
//            cout << "清一色　十六台";
            taiMeet[16] = true;
        }
    }
    //混一色
    int anotherType = myMajan.back().type;
    if(myMajan[0].type == 2)
    {
        bool twoType = true;
        for(int i = 1;i < myMajan.size(); i++)
            if(myMajan[i].type != 2 or myMajan[i].type != anotherType)
            {
                twoType = false;
                break;
            }
        if(twoType)
        {
            taiCount += 4;
//            cout << "混一色　十六台";
            taiMeet[17] = true;
        }
    }
    //八仙過海
    if(myFlower.size() == 8)
    {
        taiCount += 8;
//        cout << "八仙過海　八台";
        taiMeet[6] = true;
    }
    //花槓
    if(myFlower.size() >= 4 and myFlower.size() != 8)
    {
        bool season = false;
        for(int i = 1; i <= 4; i++)
        {
            for(int j = 0; j < myFlower.size(); j++)
                if(myFlower[j].num == i)
                {
                    season = true;
                    break;
                }
                else
                    season = false;
            if(!season)
                break;
        }
        if(season)
        {
            taiCount += 2;
//            cout << "花槓　二台";
            taiMeet[7] = true;
        }
        bool plant = false;
        for(int i = 5; i <= 8; i++)
        {
            for(int j = 0; j < myFlower.size(); j++)
                if(myFlower[j].num == i)
                {
                    plant = true;
                    break;
                }
                else
                    plant = false;
            if(!plant)
                break;
        }
        if(plant)
        {
            taiCount += 2;
//            cout << "花槓　二台";
        }
    }

    //結算
    if(!selfTouch)
    {
        taiList[winner] += taiCount;
        taiList[loser] -= taiCount;
    }
    else
    {
        taiList[winner] += taiCount * 3;
        for(int i = 0; i < 4; i++)
            if(i != winner)
                taiList[i] -= taiCount;
    }
//    cout << endl << "台數: " << taiCount << endl;
    return taiCount;
}

void Round::drawTai(SDL_Renderer* rR, int x, int y, int h, int w, int finalTai)
{
    tRound->Draw(rR, 0, 0, h, w, 0, 0, 22);   // blackBoard
    int cnt = 0;
    for(int i = 0; i < 18; i++){
        if(taiMeet[i]){
            if(i % 3 == 1){
                tRound->Draw(rR, 0, 0, 80, 200, 50, 400 + 80 * (int)floor(i / 3), 25 + i);
            }else if(i % 3 == 2){
                tRound->Draw(rR, 0, 0, 80, 200, 250, 400 + 80 * (int)floor(i / 3), 25 + i);
            }else{
                tRound->Draw(rR, 0, 0, 80, 200, 450, 400 + 80 * (int)floor(i / 3), 25 + i);
            }
               //taiMeet
            cnt++;
        }
    }

    if (finalTai < 10){
//        string num = to_string(finalTai);
        tRound->Draw(rR, 0, 0, 100, 100, 1000, 200, 12 + finalTai);    //taiNum
    } else{
//        string num1 = to_string(finalTai)[0];
//        string num2 = to_string(finalTai)[1];
        tRound->Draw(rR, 0, 0, 100, 100, 1000, 200, 12 + finalTai / 10);    //taiNum
        tRound->Draw(rR, 0, 0, 100, 100, 1000, 200, 12 + finalTai % 10);    //taiNum
    }
}
