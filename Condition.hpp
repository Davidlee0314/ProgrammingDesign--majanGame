//
//  Condition.hpp
//  PDfinal
//
//  Created by Jonathan Chen on 2018/12/21.
//  Copyright © 2018 farm. All rights reserved.
//

#ifndef Condition_hpp
#define Condition_hpp

#include <stdio.h>
#include <string.h>
#include "Texture.hpp"
//#include "Music.hpp"

class Condition{
private:
    Texture* frame;
    Texture* number;
    
    bool bigornot;
//    Music* muCondition;
    
public:
    int money;
    int experience;
    int level;
    
    Condition();
    Condition(SDL_Renderer* rR);
    Condition(SDL_Renderer* rR,int money,int experience,int level);
    void drawCondition(SDL_Renderer* rR);
    
    int updateCondtion(int x, int y, bool mouseL);
    
    void addExp(int exp);
    
    
    
    
    
};
#endif /* Condition_hpp */
