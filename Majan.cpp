//
// Created by User on 2018/12/19.
//
#include "Majan.h"
#include <iostream>
using namespace std;

bool Majan::operator==(Majan a) {
    return this->type == a.type && this->num == a.num;
}

bool Majan::operator>=(Majan a) {
    return this->type == a.type && this->num == a.num + 1;
}

bool Majan::operator<=(Majan a) {
    return this->type == a.type && this->num == a.num - 1;
}

void Majan::print(){
    switch (this->type){
        case 1:
            switch (this->num){
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
            switch (this->num){
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
            cout << this->num << " 萬 ";
            break;
        case 4:
            cout << this->num << " 筒 ";
            break;
        case 5:
            cout << this->num << " 條 ";
            break;
        default:
            break;
    }
}

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

