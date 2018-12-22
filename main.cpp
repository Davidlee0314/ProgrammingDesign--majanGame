#include <random>
#include <vector>
#include <iostream>
#include <algorithm>

#include "Majan.h"
#include "Deck.h"
#include "Player.h"
#include "Round.h"
#include "Dice.h"

using namespace std;

int main(){
//    Player p1 = Player(), p2 = Player(), p3 = Player(), p4 = Player();
//    Dice d1{}, d2{}, d3{};
//    Round r = Round(&p1, &p2, &p3, &p4);
//
//    //先指定 P1 當莊家
//    r.playerNow = 0;
//    p1.host = true;
//    p1.multiHost = 1;
//
//    //開始一局
//    d1.throwDice();
//    d2.throwDice();
//    d3.throwDice();
//    int diceNum = d1.num + d2.num + d3.num;
//    r.initRound(diceNum);

//============================
//           Test
//============================

    int n = 0, type = 0, num = 0, index = 0;
    Deck a = Deck();
    vector<Majan>temp;
    cin >> n;
    while(n != 0){
        cin >> type >> num;
        Majan m = {type, num};
        a.deck.push_back(m);
        n--;
        index++;
    }
    a.print();
//    cout << a.checkWin();
    cout << (a.checkListen(temp) ? "聽" : "沒聽");
    cout << endl;
    for(int i = 0; i < temp.size(); i++){
        temp[i].print();
        cout << temp[i].type2 << " " << temp[i].num1 << endl;
    }
    return 0;
}