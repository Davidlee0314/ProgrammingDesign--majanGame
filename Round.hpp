#include "Deck.hpp"
#include "Player.hpp"
#include <vector>

#ifndef MAJANGAME_ROUND_H
#define MAJANGAME_ROUND_H

class Round{
private:


    //開局
    void initRound();


    
public:
    //for optionChoose
    vector<int>choose;
    vector<int>action;

    void initTotals();
    //東 南 西 北 0 1 2 3
    int wind;
    //開門方
    int open;
    //現在玩家 0 1 2 3
    int playerNow;
    //拿牌的地方
    int pos;
    int backPos;
    //上一局是否為流局
    bool failToFindWinner;
    bool justAction;
    bool takeMajan;

    //for render
    int moveIndex;
    bool flower[4];
    bool allFlower;
    
    Player* playerList[4];
    Deck* totals;
    Deck* haidi;
    Majan* m;
    Round(SDL_Renderer*);
    int playerNext();
    
    //單局暫停條件
    bool haveWinner();
    int posPre16();
    
    //遊玩需要
//    void singleGame();
//    void multiGame();
    void updateInitRound(int);
    int updateFlower();
    int updatePlayer(int x, int y, bool mouseL);
    void updatePlayerAction(int x, int y, bool mouseL);
    void updateAI();
    int updateAIPonHu();
    void updateAIAction(int);

    void drawRound();
    SDL_Renderer* rR;
    int majanNow;
    ~Round();
    Texture* tRound;
    void readImage();
    void drawOption(int x, int y, int h, int w, int index);

    SDL_Rect rect;
    void drawRoundRotate(int x, int y, int h, int w, double angle);
    bool giveOutMajan;
    bool justGan;
    bool finishEat;
    bool finishListen;
    vector<int>eatIndex;
    int moveEatIndex;
    int moveListenIndex;

    //
    int taiList[4];
    bool taiMeet[18];
    int countTai(int winner, int loser, bool selfTouch);
    void drawTai(SDL_Renderer* rR, int x, int y, int h, int w, int finalTai);
};


#endif //MAJANGAME_ROUND_H
