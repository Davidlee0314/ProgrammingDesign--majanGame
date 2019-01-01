#include <iostream>
using namespace std;
#define SDL_MAIN_HANDLED
#include "Texture.hpp"
#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <string>

//Screen dimension constants
#include "GameMgr.hpp"

//#include <iomanip>



int main(int argc, char* args[])  // int main(int argc, char* args[])
{
    GameMgr game;
    game.mainLoop();
    
    system("pause");
    return 0;
}
