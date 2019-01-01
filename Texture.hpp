//
//  Texture.hpp
//  PDfinal
//
//  Created by Jonathan Chen on 2018/12/19.
//  Copyright © 2018 farm. All rights reserved.
//

#ifndef Texture_hpp
#define Texture_hpp

#include <stdio.h>
#include <SDL_image.h>
#include <SDL.h>
#include <string>
#include <iostream>
#include <vector>


using namespace std;

class Texture
{
public:
    Texture();
    ~Texture();
    
//    void Draw(SDL_Renderer * rR, int iXOffset, int iYOffset, int iFrame = 0);
//    void Draw(SDL_Renderer * rR, int iXOffset, int iYOffset,int h,int w, int iFrame = 0);
    void Draw(SDL_Renderer * rR, int iXOffset, int iYOffset,int h,int w, int x,int y,int iFrame);

    void LoadImagePNG(string fileName, SDL_Renderer * rR);
    void RotateImage(SDL_Renderer* rR, double angle, int iFrame, SDL_Rect* r);
    void SetImageOpacity(double);

private:
    vector<SDL_Texture*> images;
    SDL_Rect rRect;
    SDL_Rect srcRect;
    
};
#endif /* Texture_hpp */
