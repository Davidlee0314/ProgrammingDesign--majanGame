//
//  GameMgr.hpp
//  PDfinal
//
//  Created by Jonathan Chen on 2018/12/19.
//  Copyright © 2018 farm. All rights reserved.
//

#ifndef GameMgr_hpp
#define GameMgr_hpp

#include <stdio.h>
#include <iostream>
#include <SDL.h>
#include "Texture.hpp"
#include "Condition.hpp"
#include "Majan.hpp"
#include "Player.hpp"
#include "Dice.hpp"
#include "Round.hpp"


enum gStats
{
    INIT,
    MENU,
    DICE,
    INITROUND,
    PLAYER,
    TAI
};

class GameMgr
{
public:
    GameMgr();
    ~GameMgr();
    
    bool quitGame;
    
    //init
    void initLoadIMG();
    
    // Loop
    void mainLoop();
    void Update();
    void Draw();
    
    static int COMPUTER_SETTING;
    static int TIME_SETTING;
    
private:
    // ----- SDL -----
    SDL_Window * window;
    SDL_Renderer* rR;
    SDL_Event* mainEvent;
    Texture* gmTexture;


    //-----Status for Drawing-------------
    bool mouseEnterStart;
    bool biggerAgain;
    int ctrl;

    //for Dice
    int changeDice;
    int diceNum;
    int taiNum;
    int winner;


    
    // ------Data Structure pointer--------
    Condition* aCondition;
    Majan* aMajan;
    Round* aRound;
    Dice* aDice[3];
    
    // ----- FPS -----
    long frameTime;
    size_t frameCounter;
    static const int MIN_FRAME_TIME = 16;
    
    // ----- Keyboard & Mouse INPUT -----
    bool keyUp, keyDown, keyLeft, keyRight, keySpace, keySpaceTrigger;  // player1 control
    bool keyW, keyS, keyA, keyD, keyLShift, keyLShiftTrigger;           // player2 control
    unsigned inKey;
    unsigned KEY_UP, KEY_DOWN, KEY_LEFT, KEY_RIGHT, KEY_SPACE;
    unsigned KEY_w, KEY_s, KEY_a, KEY_d, KEY_LSHIFT;
    
    bool mouseLeftPressed, mouseRightPressed, mouseLeftTrigger, mouseRightTrigger;
    int mouseX, mouseY;
    
    void MouseInput();
    
    // ----- Game Data -----
    gStats NowStat;
};
#endif /* GameMgr_hpp */
