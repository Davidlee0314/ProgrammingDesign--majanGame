//
//  GameMgr.cpp
//  PDfinal
//
//  Created by Jonathan Chen on 2018/12/19.
//  Copyright © 2018 farm. All rights reserved.
//
#include <thread>
#include <chrono>
#include "windows.h"
#include "GameMgr.hpp"
#include "Texture.hpp"
#include "Round.hpp"

using namespace std;

int GameMgr::COMPUTER_SETTING = 1;
int GameMgr::TIME_SETTING = 2;

#define  GAME_WIDTH  1280
#define  GAME_HEIGHT 720
#define  UNIT_PIXEL  32

GameMgr::GameMgr()
{
    // Game Stat
    NowStat = INIT;
    this->quitGame = false;
    changeDice = -1;
    frameCounter = 0;
    
    // SDL
    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER | SDL_INIT_AUDIO);
    
    window = SDL_CreateWindow("MAJAN", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, GAME_WIDTH, GAME_HEIGHT, SDL_WINDOW_SHOWN);
    
    if (window == nullptr) {
        quitGame = true;
    }
    
    rR = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    
    mainEvent = new SDL_Event();
    
    // image
    initLoadIMG();
    // construction
    aCondition = new Condition(rR, 5000, 0, 1);

}


GameMgr::~GameMgr()
{
    delete mainEvent;
    SDL_DestroyRenderer(rR);
    SDL_DestroyWindow(window);
}

// init
void
GameMgr::initLoadIMG()
{
    gmTexture = new Texture[8];
    gmTexture->LoadImagePNG("startBg", rR);
    gmTexture->LoadImagePNG("startDown", rR);
    gmTexture->LoadImagePNG("startUp", rR);
    gmTexture->LoadImagePNG("tableBg", rR);
}
// Loop

void
GameMgr::mainLoop()
{
    
    while (!quitGame && mainEvent->type != SDL_QUIT)
    {
        frameTime = SDL_GetTicks(); // 2@?i //  =  second/1000
        // for debug test
        
        SDL_PollEvent(mainEvent);
        SDL_RenderClear(rR);
        SDL_RenderFillRect(rR, nullptr);
        
        MouseInput();
        Update();
        Draw();
        
        SDL_RenderPresent(rR);
        ++frameCounter;
    }
}


void
GameMgr::Update()
{
    cout << NowStat << endl;
    switch (NowStat)
    {
        case INIT:
        {
            // init
            aRound = new Round(rR);
            for(int i = 0; i < 4; i++){
                aRound->playerList[i] = new Player(rR);
            }
            for(int i = 0; i < 3; i++){
                aDice[i] = new Dice();
            }
            NowStat = MENU; // MENU;

            break;
        }
        case MENU:
        {
            //START

            if((490 < mouseX) && (790 > mouseX) && (420 < mouseY) && (520 > mouseY))
            {
                mouseEnterStart = true;
                //STARTdown
                if(mouseLeftTrigger){
                    NowStat = DICE;
                }
            }else{
                mouseEnterStart = false;
            }
            break;
        }
        case DICE:
        {
// stat還要分成新建遊戲、遊戲中、輸了，輸了要改NowStat=endGame，遊戲中繼續遊戲，
            ctrl = aCondition->updateCondtion(mouseX, mouseY, mouseLeftTrigger);
            switch (ctrl) {
                case 1:
                    NowStat = INIT;
                    break;
                default:
                    break;
            }
            if(changeDice == 1){
                SDL_Delay(1500);
                NowStat = INITROUND;
            }
            for(int i = 0; i < 3; i++){
                changeDice = aDice[i]->updateDice(mouseX, mouseY, mouseLeftTrigger);
            }
            diceNum = 0;
            for(int i = 0; i < 3; i++){
                diceNum += aDice[i]->num;
            }
            break;
        }
        case INITROUND:
        {
            ctrl = aCondition->updateCondtion(mouseX, mouseY, mouseLeftTrigger);
            switch (ctrl) {
                case 1:
                    NowStat = INIT;
                    break;
                default:
                    break;
            }

            int flowerFinish = 0;
            if(aRound->majanNow > 0){
                SDL_Delay(150);
                aRound->updateInitRound(diceNum);
            }else{
                SDL_Delay(150);
                for(int i = 0; i < 4; i++){
                    aRound->playerList[i]->ownedDeck->sort();
                }
                flowerFinish = aRound->updateFlower();
            }
            if(flowerFinish == 1){
                NowStat = PLAYER;
                for(int i = 1; i < 4; i++){
                    aRound->playerList[i]->firstTime();
                }
                aRound->playerNow = 0;
            }
            break;
        }
        case PLAYER:
        {
            for(int i = 0; i < 4; i ++){
                cout << endl;
                cout << "============Player " << i + 1 << " =================" << endl;
                aRound->playerList[i]->ownedDeck->print();
                cout << endl << " ------------left---------------" << endl;
                for(int j = 0; j < aRound->playerList[i]->left.size(); j++){
                    aRound->playerList[i]->left[j].print();
                }
                cout << endl << "=====================================" << endl;
                cout << endl;
            }
            ctrl = aCondition->updateCondtion(mouseX, mouseY, mouseLeftTrigger);
            switch (ctrl) {
                case 1:
                    NowStat = INIT;
                    break;
                default:
                    break;
            }

            if(aRound->playerNow == 0){
                if(aRound->playerList[0]->listen){
                    SDL_Delay(1000);
                }
                aRound->moveIndex = aRound->updatePlayer(mouseX, mouseY, mouseLeftTrigger);
                if(aRound->giveOutMajan){
                    aRound->giveOutMajan = false;
                    aRound->updateAIAction();
                    if(!aRound->justAction && !aRound->justGan){
                        aRound->playerNow += 1;
                        if(aRound->playerNow == 4){
                            aRound->playerNow = 0;
                        }
                    }
                }
            }else{
                if((aRound->action.empty() || !aRound->choose.empty()) && aRound->finishEat && aRound->finishListen){
                    SDL_Delay(1000);
                    aRound->updateAI();
                }
                aRound->updatePlayerAction(mouseX, mouseY, mouseLeftTrigger);
                if((aRound->action.empty() || !aRound->choose.empty()) && aRound->finishEat && aRound->finishListen){
                    if(!aRound->justAction) {
                        aRound->updateAIAction();
                    }
                    if(!aRound->justAction){
                        aRound->playerNow += 1;
                        if(aRound->playerNow == 4){
                            aRound->playerNow = 0;
                            aRound->takeMajan = false;
                        }
                    }
                }
            }
            if(aRound->haveWinner()){
                NowStat = TAI;
            }
            if(aRound->failToFindWinner){
                cout << "流局" << endl;
            }
            break;
        }
        case TAI:
        {
            int winner = 0;
            for(int i = 0; i < 4; i++){
                if(aRound->playerList[i]->win){
                    winner = i;
                }
            }
            cout << " 算台 " << winner << endl;
            bool selfTouch = false;
            if(aRound->playerNow == winner){
                selfTouch = true;
            }
            taiNum = aRound->countTai(winner, aRound->playerNow, selfTouch);
            break;
        }
        default:
            break;
    }
}

void
GameMgr::Draw()
{
    // game mode
    if (NowStat == INIT)
    {
    
    }
    else if (NowStat == MENU)
    {

        gmTexture->Draw(rR, 0, 0, 720, 1280, 0, 0, 0);
        gmTexture->Draw(rR, 0, 0, 100, 300,490,420, 1);

        if(mouseEnterStart){
            gmTexture->Draw(rR, 0, 0, 100, 300,490,420, 2);
        }else{
            gmTexture->Draw(rR, 0, 0, 100, 300,490,420, 1);
        }
    }
    else if (NowStat == DICE)
    {
        gmTexture->Draw(rR, 0, 0, 720, 1280, 0, 0, 3);
        aCondition->drawCondition(rR);
        for(int i = 0; i < 3; i++){
            aDice[i]->drawDice(rR, i + 1, changeDice);
        }
    }
    else if (NowStat == INITROUND)
    {
        gmTexture->Draw(rR, 0, 0, 720, 1280, 0, 0, 3);
        aCondition->drawCondition(rR);
        aRound->drawRound();
    }
    else if(NowStat == PLAYER)
    {
        gmTexture->Draw(rR, 0, 0, 720, 1280, 0, 0, 3);
        aCondition->drawCondition(rR);
        aRound->drawRound();
    }
    else if(NowStat == TAI){
        aRound->drawTai(rR, 0, 0, 720, 1280, taiNum);
    }
}

void
GameMgr::MouseInput()
{
    mouseLeftTrigger = false;
    mouseRightTrigger = false;
    if (mainEvent->type == SDL_MOUSEBUTTONDOWN)
    {
        if (mainEvent->button.button == SDL_BUTTON_LEFT && !mouseLeftPressed) { mouseLeftPressed = true;}
        else if (mainEvent->button.button == SDL_BUTTON_RIGHT && !mouseRightPressed) { mouseRightPressed = true;  }
    }
    else if (mainEvent->type == SDL_MOUSEBUTTONUP)
    {
        if (mainEvent->button.button == SDL_BUTTON_LEFT && mouseLeftPressed) { mouseLeftPressed = false; mouseLeftTrigger = true; }
        else if (mainEvent->button.button == SDL_BUTTON_RIGHT && mouseRightPressed) { mouseRightPressed = false; mouseRightTrigger = false; }
    }
    else if (mainEvent->type == SDL_MOUSEMOTION)
    {
        int x = mouseX, y = mouseY;
        SDL_GetMouseState(&mouseX, &mouseY);
    }
}
