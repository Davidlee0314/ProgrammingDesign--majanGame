#include <random>
#include "Dice.hpp"
using namespace std;

Dice::Dice() : num(1), tDice(nullptr){}

void Dice::readImage(SDL_Renderer* rR) {
    tDice = new Texture;
    if(num == 1){
        tDice->LoadImagePNG("diceOne", rR);
    }else if(num == 2){
        tDice->LoadImagePNG("diceTwo", rR);
    }else if(num == 3){
        tDice->LoadImagePNG("diceThree", rR);
    }else if(num == 4){
        tDice->LoadImagePNG("diceFour", rR);
    }else if(num == 5){
        tDice->LoadImagePNG("diceFive", rR);
    }else if(num == 6){
        tDice->LoadImagePNG("diceSix", rR);
    }
}

void Dice::throwDice() {
    random_device rd;
    default_random_engine generator = default_random_engine(rd());
    uniform_int_distribution<int> distribution(1,6);
    num = distribution(generator);
}

int Dice::updateDice(int x, int y, bool mouseL){
    if(x < 690 && x > 580 && y > 300 && y < 410){
        if(mouseL){
            throwDice();
            return 1;
        }else{
            return 0;
        }
    }else{
        return -1;
    }
}

void Dice::drawDice(SDL_Renderer* rR, int index, int condition) {
    readImage(rR);
    int x = 0, y = 0;
    if(index == 1){
        x = 610;
        y = 300;
    }else if(index == 2){
        x = 580;
        y = 360;
    } else if(index == 3){
        x = 640;
        y = 360;
    }
    if(condition == 0){
        tDice->Draw(rR, 0, 0, 55, 55, x - 2, y - 2, 0);
    }else{
        tDice->Draw(rR, 0, 0, 50, 50, x, y, 0);
    }

}
