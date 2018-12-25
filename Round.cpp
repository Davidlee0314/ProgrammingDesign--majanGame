//
// Created by User on 2018/12/21.
//
#include <algorithm>
#include <random>
#include <iostream>

#include "Round.h"
#include "Dice.h"

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
    int host = playerNow;
    pos = calcPos(diceNum);
    backPos = pos - 1;
    open = pos % 4;

    cout << "Dice " << diceNum << endl;
    cout << "Pos " << pos << endl;

    for(int i = 0; i < 4; i++){
        if(playerList[i]->host){
            playerNow = i;
        }
    }

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
    }

    //開門、排列
    playerList[playerNow]->ownedDeck->addMajan(pos, 1, totals);
    for(int i = 0; i < 4; i++){
        playerList[i]->ownedDeck->sort();
    }

    //print
//    totals->print();
//    for(int i = 0; i < 4; i++){
//        playerList[i]->ownedDeck->print();
//    }

    //補花
    bool flower[4] = {false};
    bool allFlower = false;
    int flowerNum = 0;
    while(!allFlower){
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
    playerNow = host;

    //print
//    totals->print();
//    for(int i = 0; i < 4; i++){
//        playerList[i]->ownedDeck->print();
//    }
}

bool Round::haveWinner(){
    bool haveWinner = false;
    for(int i = 0; i < 4; i++){
        if(playerList[i]->win){
            haveWinner = true;
        };
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

void Round::singleGame() {
    Dice d1{}, d2{}, d3{};

    int diceNum, giveOutIndex = 0;

    //初始 for test
    //先指定 P1 當莊家
//    playerNow = 0;
//    playerList[0]->host = true;
//    playerList[0]->multiHost = 0;

    //骰色子
    d1.throwDice();
    d2.throwDice();
    d3.throwDice();
    diceNum = d1.num + d2.num + d3.num;
    initRound(diceNum);


    //整理 AI 的牌
    for(int i = 1; i < 4; i++){
        if(i != 0){
            playerList[i]->firstTime();
        }
//        cout << "player " << i << endl;
//        playerList[i]->ownedDeck->print();
//        cout << "-----left" <<endl;
//        for(int j = 0; j < playerList[i]->left.size(); j++){
//            playerList[i]->left[j].print();
//        }
//        cout << endl;
    }

    //動作變數初始
    bool justAction = false;
    failToFindWinner = false;

    while(!haveWinner() && !failToFindWinner){
        cout << "===============玩家 " << playerNow << "摸牌==============" << endl;
        haidi->print();

        //initRound 造成 host 多一張牌
        //摸牌
        totals->print();
        if(playerList[playerNow]->ownedDeck->deck.size() != 17 && !justAction){
            playerList[playerNow]->ownedDeck->addMajan(pos, 1, totals);

            //check 是否為花牌，是則補花
            while(playerList[playerNow]->ownedDeck->deck.back().type == 1){
                playerList[playerNow]->ownedDeck->putDeckOut(
                        (int)playerList[playerNow]->ownedDeck->deck.size() - 1, 1);
                playerList[playerNow]->ownedDeck->addMajanBack(backPos, 1, totals);
            }

            //若為AI，則加上最後一張
//            if(playerNow != 0){
//                playerList[playerNow]->left.push_back(
//                        playerList[playerNow]->ownedDeck->deck[playerList[playerNow]->ownedDeck->deck.size() - 1]);
//            }

            //檢查暗槓，若可以則要再摸
            int gan = 0;
            int pos = playerList[playerNow]->ownedDeck->checkDarkGan();
            if (pos != -1){
                if(playerNow == 0) {
                    cout << "是否要暗槓, 輸入 1 or 0" << endl;
                    cin >> gan;
                    if (gan == 1) {
                        playerList[playerNow]->ownedDeck->darkGan(pos);
                    }
                }else{
                    playerList[playerNow]->ownedDeck->darkGan(pos);
                    playerList[playerNow]->firstTime();
                }
            }

            if(gan == 1){
                playerList[playerNow]->ownedDeck->addMajanBack(backPos, 1, totals);
                while(playerList[playerNow]->ownedDeck->deck.back().type == 1){
                    playerList[playerNow]->ownedDeck->putDeckOut(
                            (int)playerList[playerNow]->ownedDeck->deck.size() - 1, 1);
                    playerList[playerNow]->ownedDeck->addMajanBack(backPos, 1, totals);
                }

                //若為AI，則加上最後一張
//                if(playerNow != 0){
//                    playerList[playerNow]->left.push_back(
//                            playerList[playerNow]->ownedDeck->deck[playerList[playerNow]->ownedDeck->deck.size() - 1]);
//                }
            }
        }

        //print for testing
        for(int i = 0; i < 4; i++){
            playerList[i]->ownedDeck->print();
        }

        //是否為玩家可操縱的 player，是就選擇打哪張
        if(playerNow == 0){

            //打什麼
            if(!playerList[playerNow]->listen){
                //檢查可聽
                if(playerList[playerNow]->ownedDeck->checkListen()){
                    //印出選項
                    cout << endl;
                    for(int i = 0; i < playerList[playerNow]->ownedDeck->listenOption.size(); i++){
                        playerList[playerNow]->ownedDeck->listenOption[i].print();
                    }

                    cin >> giveOutIndex;

                    //確認打牌後有聽
                    for(int i = 0; i < playerList[playerNow]->ownedDeck->listenOption.size(); i++){
                        if(playerList[playerNow]->ownedDeck->deck[giveOutIndex] ==
                           playerList[playerNow]->ownedDeck->listenOption[i].giveOut){
                            playerList[playerNow]->listen = true;
                            cout << "你聽了" << endl;
                        }
                    }
                }else{
                    cin >> giveOutIndex;
                }
            }else{
                //檢查可胡
                Majan m = {playerList[playerNow]->ownedDeck->deck.back().type,
                           playerList[playerNow]->ownedDeck->deck.back().num};
                playerList[playerNow]->ownedDeck->sort();
                if(playerList[playerNow]->ownedDeck->checkHoo()){
                    playerList[playerNow]->win = true;
                }else{
                    giveOutIndex = playerList[playerNow]->ownedDeck->searchMajan(&m);
                }
            }
        }else{
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
                    cout << "player " << playerNow <<" 聽了" << endl;
                }else{
                    if(!justAction){
                        playerList[playerNow]->refresh();
                    }
                    Majan* m = playerList[playerNow]->throwAway();
                    m->print();
                    giveOutIndex = playerList[playerNow]->ownedDeck->searchMajan(m);
                }
            }else{
                if(!justAction){
                    playerList[playerNow]->refresh();
                }

                //檢查可胡
                Majan m = {playerList[playerNow]->ownedDeck->deck[playerList[playerNow]->ownedDeck->deck.size() - 1].type,
                           playerList[playerNow]->ownedDeck->deck[playerList[playerNow]->ownedDeck->deck.size() - 1].num};
                cout << "聽沒胡 打這張 ";
                m.print();
                playerList[playerNow]->ownedDeck->sort();
                if(playerList[playerNow]->ownedDeck->checkHoo()){
                    playerList[playerNow]->win = true;
                }else{
                    giveOutIndex = playerList[playerNow]->ownedDeck->searchMajan(&m);
                }
            }
        }

        //更改 justAction 變數
        justAction = false;

        cout << endl << "打牌的 Index" << giveOutIndex <<endl;

        //出牌
        if(!haveWinner()){

            Majan m{};
            if(giveOutIndex < playerList[playerNow]->ownedDeck->deck.size()){
                m = {playerList[playerNow]->ownedDeck->deck[giveOutIndex].type,
                     playerList[playerNow]->ownedDeck->deck[giveOutIndex].num};
                playerList[playerNow]->ownedDeck->deck.erase(
                        playerList[playerNow]->ownedDeck->deck.begin() + giveOutIndex,
                        playerList[playerNow]->ownedDeck->deck.begin() + giveOutIndex + 1);

                //清 left
                if(playerNow != 0){
                    int pos = 0;
                    for(int i = 0; i < playerList[playerNow]->left.size(); i++){
                        if(m == playerList[playerNow]->left[i]){
                            pos = i;
                            break;
                        }
                    }
                    playerList[playerNow]->left.erase(playerList[playerNow]->left.begin() + pos,
                                                      playerList[playerNow]->left.begin() + pos + 1);
                }
                haidi->deck.push_back(m);
            }
            playerList[playerNow]->ownedDeck->sort();

            //print for testing
            cout << "玩家 " << playerNow << "打 ";
            m.print();

            // 可胡
            bool hoo = false;
            for(int i = 0; i < 4; i++){
                if(i != playerNow){
                    playerList[i]->ownedDeck->deck.push_back(m);
                    playerList[i]->ownedDeck->sort();
                    int pos = playerList[i]->ownedDeck->searchMajan(&m);

                    if(playerList[i]->ownedDeck->checkHoo()){
                        playerList[i]->win = true;
                        hoo = true;
                    }else{
                        playerList[i]->ownedDeck->deck.erase(playerList[i]->ownedDeck->deck.begin() + pos,
                                                             playerList[i]->ownedDeck->deck.begin() + pos + 1);
                    }
                }
            }

            if(!hoo){
                // 可碰
                int pon = 0;
                for(int i = 0; i < 4; i++){
                    if(i != playerNow && !playerList[i]->listen){
                        int pos = 0;
                        pos = playerList[i]->ownedDeck->checkPon(&m);

                        if(i == 0){
                            if(pos != -1){
                                m.print();
                                cout << "碰的位置 " << pos << " 是否要碰, 輸入 1 or 0" << endl;
                                cin >> pon;
                                if(pon == 1){
                                    playerList[0]->ownedDeck->pon(pos, m);
                                    haidi->deck.erase(haidi->deck.end() - 1, haidi->deck.end());
                                    playerNow = 0;
                                    justAction = true;
                                }
                            }
                        }else{
                            if(pos != -1){
                                playerList[i]->ownedDeck->pon(pos, m);
                                haidi->deck.erase(haidi->deck.end() - 1, haidi->deck.end());
                                playerNow = i;
                                justAction = true;
                                playerList[playerNow]->firstTime();
                                pon = 1;
                            }
                        }
                    }
                }

                // 可槓
                int gan = 0;
                for(int i = 0; i < 4; i++){
                    if(i != playerNow && !playerList[i]->listen) {
                        int pos = 0;
                        pos = playerList[i]->ownedDeck->checkGan(&m);
                        if (i == 0) {
                            if (pos != -1) {
                                m.print();
                                cout << "是否要槓, 輸入 1 or 0" << endl;
                                cin >> gan;
                                if (gan == 1) {
                                    playerList[0]->ownedDeck->gan(pos, m);
                                    haidi->deck.erase(haidi->deck.end() - 1, haidi->deck.end());
                                    playerNow = 0;
                                    justAction = true;
                                }
                            }
                        }
                    }
                }

                //檢查下家可吃
                if(pon == 0 && gan == 0){
                    vector<Majan> eatStore;
                    int next = playerNext();
                    playerList[next]->ownedDeck->checkEat(eatStore, &m);
                    if(next == 0 && !eatStore.empty() && !playerList[0]->listen){
                        int eatIndex = 0;
                        m.print();
                        cout << "吃哪一組, 輸入 0, 1, 2 ..., -1 則不吃";
                        for(int i = 0; i < eatStore.size(); i+=2){
                            eatStore[i].print();
                            eatStore[i + 1].print();
                            cout << endl;
                        }
                        cin >> eatIndex;
                        if(eatIndex != -1){
                            playerList[next]->ownedDeck->eat(m, eatStore[eatIndex * 2], eatStore[eatIndex * 2 + 1]);
                            haidi->deck.erase(haidi->deck.end() - 1, haidi->deck.end());
                            playerNow = 0;
                            justAction = true;
                        }
                    }else if(next != 0 && !eatStore.empty() && !playerList[next]->listen){
                        playerList[next]->ownedDeck->eat(m, eatStore[0], eatStore[1]);
                        haidi->deck.erase(haidi->deck.end() - 1, haidi->deck.end());
                        playerNow = next;
                        justAction = true;
                        playerList[playerNow]->firstTime();
                    }
                    eatStore.clear();
                }
            }
        }

        if(!justAction){
            playerNow = playerNext();
        }

        //print for testing
        cout << endl << "--------- 一輪後 ----------" << endl;
        for(int i = 0; i < 4; i++){
            playerList[i]->ownedDeck->print();
            if(i != 0){
                cout << endl << "left" << endl;
                for(int j = 0; j < playerList[i]->left.size(); j++){
                    playerList[i]->left[j].print();
                }
                cout << endl;
            }
        }

        if(totals->deck[posPre16()].type == 0){
            failToFindWinner = true;
        }
    }
}

void Round::multiGame(){
    //初始
    //先指定 P1 當莊家
    playerNow = 0;
    playerList[0]->host = true;
    playerList[0]->multiHost = 0;

    //風初始
    wind = 0;

    bool stopGame = true;
    int host = 0;
    while(stopGame){
        cout << wind;
        cout << " 風" << endl;
        cout << " PlayerHost " << host << endl;
        cout << " PlayerNow " << playerNow << endl;

        singleGame();

        for(int i = 0; i < 4; i++){
            if(playerList[i]->win){
                cout << "Player " << i << " win" << endl;
            }
        }

        //清 Round 資料
        totals->deck.clear();
        haidi->deck.clear();

        //如果流局
        if(failToFindWinner){
            for(int i = 0; i < 4; i++){
                if(playerList[i]->host){
                    playerList[i]->multiHost += 1;
                    playerNow = i;
                }
            }
            failToFindWinner = false;
        }

        //清 Player 資料、連莊、莊家處理
        for(int i = 0; i < 4; i++){

            //清資料
            playerList[i]->ownedDeck->deck.clear();
            playerList[i]->ownedDeck->deckOut.clear();
            playerList[i]->ownedDeck->listenOption.clear();
            playerList[i]->left.clear();
            playerList[i]->throwAble.clear();
            playerList[i]->eye.clear();
            playerList[i]->threeCount = 0;
            playerList[i]->howManyTurn = 0;
            playerList[i]->eyeCount = 0;
            playerList[i]->listen = false;

            //看是否連莊
            if(playerList[i]->win){
                if(playerList[i]->host){
                    playerList[i]->multiHost += 1;
                    playerNow = i;
                }else{
                    //選擇莊家
                    for(int j = 0; j < 4; j++){
                        if(playerList[j]->host){
                            playerList[j]->host = false;
                            playerList[j]->multiHost = 0;

                            int next = nextPlayer(j);
                            playerList[next]->host = true;
                            playerList[next]->multiHost = 0;
                            playerNow = next;

                            break;
                        }
                    }
                }
                playerList[i]->win = false;
            }
        }

        //風處理
        for(int i = 0; i < 4; i++){
            if(playerList[i]->host){
                host = i;
                if(i == 0 && playerList[i]->multiHost == 0){
                    wind += 1;
                }
            }
        }
        if(wind > 3){
            stopGame = false;
        }
    }
}

int Round::posPre16() {
    return (backPos - 15 < 0) ? (backPos - 15 + 144) : (backPos - 15);
}