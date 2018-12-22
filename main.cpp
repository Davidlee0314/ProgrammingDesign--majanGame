#include <random>
#include <vector>
#include <iostream>
#include <algorithm>

#include "Majan.h"
#include "Deck.h"
#include "Player.h"
#include "Round.h"
#include "Dice.h"
#include "Option.h"

using namespace std;

/*待完成
 * 1. AI 動作
 * 2. 所有局
 *
 *
 *
*/

int main(){
    Player p1 = Player(), p2 = Player(), p3 = Player(), p4 = Player();
    Dice d1{}, d2{}, d3{};
    Round r = Round(&p1, &p2, &p3, &p4);

    //先指定 P1 當莊家
    r.playerNow = 0;
    p1.host = true;
    p1.multiHost = 1;



    //開始一局
    int diceNum, giveOutIndex, listenIndex;

    //骰色子
    d1.throwDice();
    d2.throwDice();
    d3.throwDice();
    diceNum = d1.num + d2.num + d3.num;
    r.initRound(diceNum);

    while(!r.haveWinner() && r.totals->deck.size() > 16){
        cout << "===============玩家 " << r.playerNow << "摸牌==============" << endl;

        //initRound 造成 host 多一張牌
        //摸牌
        r.totals->print();
        if(r.playerList[r.playerNow]->ownedDeck->deck.size() != 17 && !r.justAction){
            r.playerList[r.playerNow]->ownedDeck->addMajan(r.pos, 1, r.totals);

            //check 是否為花牌，是則補花
            while(r.playerList[r.playerNow]->ownedDeck->deck.back().type == 1){
                r.playerList[r.playerNow]->ownedDeck->putDeckOut(
                        (int)r.playerList[r.playerNow]->ownedDeck->deck.size() - 1, 1);
                r.playerList[r.playerNow]->ownedDeck->addMajanBack(r.backPos, 1, r.totals);
            }

            //檢查暗槓，若可以則要再摸
            int gan = 0;
            if(r.playerNow){
                int pos = r.playerList[r.playerNow]->ownedDeck->checkGan(&r.playerList[r.playerNow]->ownedDeck->deck.back());
                if(pos != -1){
                    cout << "是否要暗槓, 輸入 1 or 0" << endl;
                    cin >> gan;
                    if(gan == 1){
                        r.playerList[r.playerNow]->ownedDeck->darkGan();
                    }
                }
            }

            if(gan == 1){
                r.playerList[r.playerNow]->ownedDeck->addMajan(r.pos, 1, r.totals);
                while(r.playerList[r.playerNow]->ownedDeck->deck.back().type == 1){
                    r.playerList[r.playerNow]->ownedDeck->putDeckOut(
                            (int)r.playerList[r.playerNow]->ownedDeck->deck.size() - 1, 1);
                    r.playerList[r.playerNow]->ownedDeck->addMajanBack(r.backPos, 1, r.totals);
                }
            }
        }

        //更改 justAction 變數
        r.justAction = false;

        //print for testing
        for(int i = 0; i < 4; i++){
            r.playerList[i]->ownedDeck->print();
        }

        //是否為玩家可操縱的 player，是就選擇打哪張
        if(r.playerNow == 0){

            //打什麼
            if(!r.playerList[r.playerNow]->listen){
                //檢查可聽
                if(r.playerList[r.playerNow]->ownedDeck->checkListen()){
                    //印出選項
                    cout << endl;
                    for(int i = 0; i < r.playerList[r.playerNow]->ownedDeck->listenOption.size(); i++){
                        r.playerList[r.playerNow]->ownedDeck->listenOption[i].print();
                    }

                    cin >> giveOutIndex;

                    //確認打牌後有聽
                    for(int i = 0; i < r.playerList[r.playerNow]->ownedDeck->listenOption.size(); i++){
                        if(r.playerList[r.playerNow]->ownedDeck->deck[giveOutIndex] ==
                           r.playerList[r.playerNow]->ownedDeck->listenOption[i].giveOut){
                            r.playerList[r.playerNow]->listen = true;
                            cout << "你聽了" << endl;
                        }
                    }
                }else{
                    cin >> giveOutIndex;
                }
            }else{
                //檢查可胡
                Majan m = {r.playerList[r.playerNow]->ownedDeck->deck.back().type,
                           r.playerList[r.playerNow]->ownedDeck->deck.back().num};
                r.playerList[r.playerNow]->ownedDeck->sort();
                if(r.playerList[r.playerNow]->ownedDeck->checkHoo()){
                    r.playerList[r.playerNow]->win = true;
                }else{
                    giveOutIndex = r.playerList[r.playerNow]->ownedDeck->searchMajan(&m);
                }
            }


        }else{
            giveOutIndex = (int)r.playerList[r.playerNow]->ownedDeck->deck.size() - 1;
        }

        //出牌
        Majan m{};
        if(giveOutIndex < r.playerList[r.playerNow]->ownedDeck->deck.size()){
            m = {r.playerList[r.playerNow]->ownedDeck->deck[giveOutIndex].type,
                       r.playerList[r.playerNow]->ownedDeck->deck[giveOutIndex].num};
            r.playerList[r.playerNow]->ownedDeck->deck.erase(
                    r.playerList[r.playerNow]->ownedDeck->deck.begin() + giveOutIndex,
                    r.playerList[r.playerNow]->ownedDeck->deck.begin() + giveOutIndex + 1);
            r.haidi->deck.push_back(m);
        }

        r.playerList[r.playerNow]->ownedDeck->sort();

        // 可胡
        bool hoo = false;
        for(int i = 0; i < 4; i++){
            if(i != r.playerNow){
                r.playerList[i]->ownedDeck->deck.push_back(m);
                r.playerList[i]->ownedDeck->sort();
                int pos = r.playerList[i]->ownedDeck->searchMajan(&m);

                if(r.playerList[i]->ownedDeck->checkHoo()){
                    r.playerList[i]->win = true;
                    hoo = true;
                }else{
                    r.playerList[i]->ownedDeck->deck.erase(r.playerList[i]->ownedDeck->deck.begin() + pos,
                                                           r.playerList[i]->ownedDeck->deck.begin() + pos + 1);
                }
            }
        }

        if(!hoo){
            // 可碰
            int pon;
            for(int i = 0; i < 4; i++){
                if(i != r.playerNow && !r.playerList[r.playerNow]->listen){
                    int pos = 0;
                    pos = r.playerList[i]->ownedDeck->checkPon(&m);

                    if(i == 0){
                        if(pos != -1){
                            m.print();
                            cout << "碰的位置 " << pos << " 是否要碰, 輸入 1 or 0" << endl;
                            cin >> pon;
                            if(pon == 1){
                                r.playerList[0]->ownedDeck->pon(pos, m);
                                r.haidi->deck.erase(r.haidi->deck.end() - 1, r.haidi->deck.end());
                                r.playerNow = 0;
                                r.justAction = true;
                            }
                        }
                    }
                }
            }

            // 可槓
            int gan;
            for(int i = 0; i < 4; i++){
                if(i != r.playerNow && !r.playerList[r.playerNow]->listen) {
                    int pos = 0;
                    pos = r.playerList[i]->ownedDeck->checkGan(&m);

                    if (i == 0) {
                        if (pos != -1) {
                            m.print();
                            cout << "是否要槓, 輸入 1 or 0" << endl;
                            cin >> gan;
                            if (gan == 1) {
                                r.playerList[0]->ownedDeck->gan(pos, m);
                                r.haidi->deck.erase(r.haidi->deck.end() - 1, r.haidi->deck.end());
                                r.playerNow = 0;
                                r.justAction = true;
                            }
                        }
                    }
                }
            }

            //檢查下家可吃
            if(pon == 0 && gan == 0){
                vector<Majan> eatStore;
                int next = r.playerNext();
                r.playerList[next]->ownedDeck->checkEat(eatStore, &m);
                if(next == 0 && !eatStore.empty() && !r.playerList[0]->listen){
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
                        r.playerList[next]->ownedDeck->eat(m, eatStore[eatIndex * 2], eatStore[eatIndex * 2 + 1]);
                        r.haidi->deck.erase(r.haidi->deck.end() - 1, r.haidi->deck.end());
                        r.playerNow = 0;
                        r.justAction = true;
                    }
                }
                eatStore.clear();
            }
        }

        if(!r.justAction){
            r.playerNow = r.playerNext();
        }

        //print for testing
        cout << "玩家 " << r.playerNow << "打 ";
        m.print();
        cout << endl << "--------- 一輪後 ----------" << endl;
        for(int i = 0; i < 4; i++){
            r.playerList[i]->ownedDeck->print();
        }
    }

//============================
//           Test
//============================

//    int n = 0, type = 0, num = 0, index = 0;
//    Deck a = Deck();
//    cin >> n;
//    while(n != 0){
//        cin >> type >> num;
//        Majan m = {type, num};
//        a.deck.push_back(m);
//        n--;
//        index++;
//    }
//    a.print();
////    cout << a.checkWin();
//    cout << (a.checkListen() ? "聽" : "沒聽");
//    cout << endl;
//    for(int i = 0; i < a.listenOption.size(); i++){
//        a.listenOption[i].print();
//    }
//    return 0;
}