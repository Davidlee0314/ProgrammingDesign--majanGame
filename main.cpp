#include <random>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

/*
 * Majan
 *   type: 1 for 花
 *         2 for 字
 *         3 for 萬
 *         4 for 筒
 *         5 for 條
 *   num: 萬筒條直接給數字
 *        花:
 *            1 for 春
 *            2 for 夏
 *            3 for 秋
 *            4 for 冬
 *            5 for 梅
 *            6 for 蘭
 *            7 for 竹
 *            8 for 菊
 *        字:
 *            1 for 東
 *            2 for 南
 *            3 for 西
 *            4 for 北
 *            5 for 中
 *            6 for 發
 *            7 for 白
 */
class Majan{
public:
    int type;
    int num;
    bool compare(Majan*);
};
bool Majan::compare(Majan* a){
    bool right = true;
    if(type > a->type){
        right = false;
    }else if(type == a->type){
        if(num > a->num){
            right = false;
        }
    }
    return right;
}

class Deck{
public:
    int numOfMajan;
    vector<Majan> deck;
    vector<Majan> deckOut;
    Deck(int);
    void print();
    void sort();
    //檢查可不可以吃碰槓聽胡
    //吃
    //碰
    //槓
    //聽
    //胡
    //算台
};
Deck::Deck(int n){
    this->numOfMajan = n;
}
void Deck::print(){
    for(int i = 0; i < this->numOfMajan; i++){
        if(i % 16 == 0 && i != 0){
            cout << endl;
        }
        switch (this->deck[i].type){
            case 1:
                switch (this->deck[i].num){
                    case 1:
                        cout << "春 ";
                        break;
                    case 2:
                        cout << "夏 ";
                        break;
                    case 3:
                        cout << "秋 ";
                        break;
                    case 4:
                        cout << "冬 ";
                        break;
                    case 5:
                        cout << "梅 ";
                        break;
                    case 6:
                        cout << "蘭 ";
                        break;
                    case 7:
                        cout << "竹 ";
                        break;
                    case 8:
                        cout << "菊 ";
                        break;
                    default:
                        break;
                }
                break;
            case 2:
                switch (this->deck[i].num){
                    case 1:
                        cout << "東 ";
                        break;
                    case 2:
                        cout << "南 ";
                        break;
                    case 3:
                        cout << "西 ";
                        break;
                    case 4:
                        cout << "北 ";
                        break;
                    case 5:
                        cout << "中 ";
                        break;
                    case 6:
                        cout << "發 ";
                        break;
                    case 7:
                        cout << "白 ";
                        break;
                    default:
                        break;
                }
                break;
            case 3:
                cout << this->deck[i].num << " 萬 ";
                break;
            case 4:
                cout << this->deck[i].num << " 筒 ";
                break;
            case 5:
                cout << this->deck[i].num << " 條 ";
                break;
            default:
                break;
        }
    }
}
void Deck::sort(){
    std::sort(this->deck.begin(), this->deck.end(),
            [](Majan a, Majan b){ return a.compare(&b); });
}

Deck* initTotals(){
    Deck* totals = new Deck(144);
    int now = 0;

    for(int i = 1; i < 6; i++){
        if(i == 1){
            for(int j = 1; j < 9; j++){
                Majan temp = {i, j};
                totals->deck.push_back(temp);
                now++;
            }
        }else if(i == 2){
            int repeat = 4;
            while(repeat != 0){
                for (int j = 1; j < 8; j++){
                    Majan temp = {i, j};
                    totals->deck.push_back(temp);
                    now++;
                }
                repeat--;
            }
        }else{
            int repeat = 4;
            while(repeat != 0){
                for (int j = 1; j < 10; j++){
                    Majan temp = {i, j};
                    totals->deck.push_back(temp);
                    now++;
                }
                repeat--;
            }
        }
    }
    shuffle(&totals->deck[0], &totals->deck[143], std::mt19937(std::random_device()()));
    return totals;
}
void initRound(Deck* totals, Deck* players[], int pos){
    int majanNow = 64, playerNow = 0;
    while(majanNow != 0){
        for(int i = 0; i < 4; i++){
            players[playerNow]->deck.push_back(totals->deck[pos + i]);
        }
        totals->deck.erase(totals->deck.begin() + pos, totals->deck.begin() + pos + 4);
        if(playerNow == 3){
            playerNow = 0;
        }else{
            playerNow += 1;
        }
        majanNow -= 4;
    }
    totals->numOfMajan -= 64;
    for(int i = 0; i < 4; i++){
        players[i]->numOfMajan += 16;
    }
}

int main(){
    Deck* totals = initTotals();
    cout << "現在亂數麻將長這樣：" << endl;
    totals->print();
    Deck* players[4] = {nullptr};
    for(int i = 0; i < 4; i++){
        players[i] = new Deck(0);
    }
    initRound(totals, players, 0);
    cout << endl << endl;
    cout << "玩家開局後亂數麻將長這樣：" << endl;
    totals->print();
    cout << endl << endl;

    cout << "玩家的亂數牌長這樣" << endl;
    for(int i = 0; i < 4; i++){
        players[i]->print();
        cout << endl;
    }

    cout << endl;
    cout << "玩家的牌排好長這樣" << endl;
    for(int i = 0; i < 4; i++){
        players[i]->sort();
        players[i]->print();
        cout << endl;
    }
    return 0;
}