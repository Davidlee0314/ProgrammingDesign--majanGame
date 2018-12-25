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
 * 1. AI 動作 V
 * 2. 單局 V
 * 3. 流局條件 V
 * 4. 所有局 V
 * 5. AI 整合 V
 * 6. 搶碰 V
 * 7. 完整局 V
 * 8. 算台
 * 9. 讓 AI 槓
*/

int main(){
    Player p1 = Player(), p2 = Player(), p3 = Player(), p4 = Player();
    Round r = Round(&p1, &p2, &p3, &p4);
    r.multiGame();


//============================
//       Test for AI
//============================

//    int n = 0, type = 0, num = 0, index = 0;
//    Player a = Player();
//    cin >> n;
//    while(n != 0){
//        cin >> type >> num;
//        Majan m = {type, num};
//        a.ownedDeck->deck.push_back(m);
//        n--;
//        index++;
//    }
//    a.firstTime();
//    cin >> type >> num;
//    Majan m = {type, num};
//    a.ownedDeck->deck.push_back(m);
//    a.refresh();
//    Majan* x = a.throwAway();
//    for(int i = 0; i < a.left.size(); i++){
//        a.left[i].print();
//    }
//    cout << "打   "<< endl;
//    x->print();
//    cout << endl;


//    for(int i = 0; i < 5; i++){
//        for(int j = 0; j < a.threeDeck[i].size(); i++){
//            a.threeDeck[i][j].print();
//        }
//        cout << endl;
//    }
//    cout << endl;
    return 0;


//============================
//   Test for CheckCondition
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