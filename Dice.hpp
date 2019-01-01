#ifndef MAJANGAME_DICE_HPP
#define MAJANGAME_DICE_HPP
#include "Texture.hpp"
#include <SDL.h>

class Dice{
public:
    int num;
    Dice();
    void throwDice();
    void readImage(SDL_Renderer* rR);
    void drawDice(SDL_Renderer* rR, int, int);
    int updateDice(int x, int y, bool mouseL);

    Texture* tDice;
};
#endif //MAJANGAME_DICE_H
