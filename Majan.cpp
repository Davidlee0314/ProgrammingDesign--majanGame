#include "Majan.hpp"
#include <iostream>
using namespace std;

Majan::Majan() : type(0), num(0), tMajan(nullptr){}
Majan::Majan(int type, int num, SDL_Renderer* rR) {
    this->type = type;
    this->num = num;
    readImage(rR);
}
Majan::~Majan() {
}
void Majan::readImage(SDL_Renderer *rR) {
    tMajan = new Texture;
    if (type == 1){
        if (num == 1){
            tMajan->LoadImagePNG("spring", rR);
        } else if (num == 2){
            tMajan->LoadImagePNG("summer", rR);
        } else if (num == 3){
            tMajan->LoadImagePNG("fall", rR);
        } else if (num == 4){
            tMajan->LoadImagePNG("fall", rR);
        } else if (num == 5){
            tMajan->LoadImagePNG("may", rR);
        } else if (num == 6){
            tMajan->LoadImagePNG("lan", rR);
        } else if (num == 7){
            tMajan->LoadImagePNG("chu", rR);
        } else if (num == 8){
            tMajan->LoadImagePNG("chiu", rR);
        }
    } else if (type == 2){
        if (num == 1){
            tMajan->LoadImagePNG("east", rR);
        } else if (num == 2){
            tMajan->LoadImagePNG("south", rR);
        } else if (num == 3){
            tMajan->LoadImagePNG("west", rR);
        } else if (num == 4){
            tMajan->LoadImagePNG("north", rR);
        } else if (num == 5){
            tMajan->LoadImagePNG("chong", rR);
        } else if (num == 6){
            tMajan->LoadImagePNG("fa", rR);
        } else if (num == 7){
            tMajan->LoadImagePNG("bai", rR);
        }
    } else if (type == 3){
        if (num == 1){
            tMajan->LoadImagePNG("oneOne", rR);
        } else if (num == 2){
            tMajan->LoadImagePNG("twoOne", rR);
        } else if (num == 3){
            tMajan->LoadImagePNG("threeOne", rR);
        } else if (num == 4){
            tMajan->LoadImagePNG("fourOne", rR);
        } else if (num == 5){
            tMajan->LoadImagePNG("fiveOne", rR);
        } else if (num == 6){
            tMajan->LoadImagePNG("sixOne", rR);
        } else if (num == 7){
            tMajan->LoadImagePNG("sevenOne", rR);
        } else if (num == 8){
            tMajan->LoadImagePNG("eightOne", rR);
        } else if (num == 9){
            tMajan->LoadImagePNG("nineOne", rR);
        }
    } else if (type == 4){
        if (num == 1){
            tMajan->LoadImagePNG("oneTon", rR);
        } else if (num == 2){
            tMajan->LoadImagePNG("twoTon", rR);
        } else if (num == 3){
            tMajan->LoadImagePNG("threeTon", rR);
        } else if (num == 4){
            tMajan->LoadImagePNG("fourTon", rR);
        } else if (num == 5){
            tMajan->LoadImagePNG("fiveTon", rR);
        } else if (num == 6){
            tMajan->LoadImagePNG("sixTon", rR);
        } else if (num == 7){
            tMajan->LoadImagePNG("sevenTon", rR);
        } else if (num == 8){
            tMajan->LoadImagePNG("eightTon", rR);
        }else if (num == 9){
            tMajan->LoadImagePNG("nineTon", rR);
        }
    } else if (type == 5){
        if (num == 1){
            tMajan->LoadImagePNG("oneTiaw", rR);
        } else if (num == 2){
            tMajan->LoadImagePNG("twoTiaw", rR);
        } else if (num == 3){
            tMajan->LoadImagePNG("threeTiaw", rR);
        } else if (num == 4){
            tMajan->LoadImagePNG("fourTiaw", rR);
        } else if (num == 5){
            tMajan->LoadImagePNG("fiveTiaw", rR);
        } else if (num == 6){
            tMajan->LoadImagePNG("sixTiaw", rR);
        } else if (num == 7){
            tMajan->LoadImagePNG("sevenTiaw", rR);
        } else if (num == 8){
            tMajan->LoadImagePNG("eightTiaw", rR);
        }else if (num == 9){
            tMajan->LoadImagePNG("nineTiaw", rR);
        }
    }
}

void Majan::drawMajan(SDL_Renderer* rR, int x, int y, int h, int w)
{
    tMajan->Draw(rR, 0, 0, h, w, x, y, 0);
}

void Majan::drawMajanOpacity(SDL_Renderer* rR, int x, int y, int h, int w, double a){
    tMajan->SetImageOpacity(a);
    tMajan->Draw(rR, 0, 0, h, w, x, y, 0);
}


void Majan::drawMajanRotate(SDL_Renderer* rR, int x, int y, int h, int w, double angle) {
    rect.x = x;
    rect.y = y;
    rect.h = h;
    rect.w = w;
    tMajan->RotateImage(rR, angle, 0, &rect);
}


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
        case 0:
            switch (this->num){
                case 0:
                    cout << "<空> ";
                    break;
                default:
                    break;
            }
            break;
        case 1:
            switch (this->num){
                case 1:
                    cout << "春   ";
                    break;
                case 2:
                    cout << "夏   ";
                    break;
                case 3:
                    cout << "秋   ";
                    break;
                case 4:
                    cout << "冬   ";
                    break;
                case 5:
                    cout << "梅   ";
                    break;
                case 6:
                    cout << "蘭   ";
                    break;
                case 7:
                    cout << "竹   ";
                    break;
                case 8:
                    cout << "菊   ";
                    break;
                default:
                    break;
            }
            break;
        case 2:
            switch (this->num){
                case 1:
                    cout << "東   ";
                    break;
                case 2:
                    cout << "南   ";
                    break;
                case 3:
                    cout << "西   ";
                    break;
                case 4:
                    cout << "北   ";
                    break;
                case 5:
                    cout << "中   ";
                    break;
                case 6:
                    cout << "發   ";
                    break;
                case 7:
                    cout << "白   ";
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
