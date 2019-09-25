//
//  Texture.cpp
//  PDfinal
//
//  Created by Jonathan Chen on 2018/12/19.
//  Copyright © 2018 farm. All rights reserved.
//

#include "Texture.hpp"
#include <SDL.h>

//#ifdef _LIBCPP_VERSION
//template const char* std::string::c_str() const;
//#endif

Texture::Texture()
{
}

Texture::~Texture()
{
    for (int i = 0, n = (int)images.size(); i < n; ++i) {
        SDL_DestroyTexture(images[i]);
    }
}
void
Texture::Draw(SDL_Renderer * rR, int iXOffset, int iYOffset,int h,int w, int x,int y,int iFrame)
{
    srcRect.x = iXOffset;
    srcRect.y = iYOffset;
    srcRect.h = h;
    srcRect.w = w;
    rRect.x = x;
    rRect.y = y;
    rRect.h = h;
    rRect.w = w;
    
    SDL_RenderCopy(rR, images[iFrame], &srcRect, &rRect);
}

//void
//Texture::Draw(SDL_Renderer * rR, int iXOffset, int iYOffset,int h,int w, int iFrame)
//{
//    rRect.x = iXOffset;
//    rRect.y = iYOffset;
//    rRect.h = h;
//    rRect.w = w;
//
//    SDL_RenderCopy(rR, images[iFrame], &rRect, &rRect);
//}
//
//void
//Texture::Draw(SDL_Renderer * rR, int iXOffset, int iYOffset, int iFrame)
//{
//    rRect.x = iXOffset;
//    rRect.y = iYOffset;
//
//    SDL_RenderCopy(rR, images[iFrame], nullptr, &rRect);
//}

void Texture::LoadImagePNG(string fileName, SDL_Renderer* rR)
{
//    cout << "load" << fileName << "\n";
    fileName = "/Users/davidlee/C++/majanGame/Image/" + fileName + ".png";
    SDL_Surface* loadedSurface = IMG_Load(fileName.c_str());
    
    if(loadedSurface==nullptr)
        cout<<"error\n";
    
    SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, 255, 0, 255));
    
    SDL_Texture* tIMG = SDL_CreateTextureFromSurface(rR, loadedSurface);
    int iWidth, iHeight;
    
    SDL_QueryTexture(tIMG, nullptr, nullptr, &iWidth, &iHeight);
    
    rRect.x  = 0;
    rRect.y = 0;
    rRect.w = iWidth;
    rRect.h = iHeight;
    SDL_FreeSurface(loadedSurface);
    
    images.push_back(tIMG);
}

void Texture::RotateImage(SDL_Renderer * rR, double angle, int iFrame, SDL_Rect* r){
    SDL_RenderCopyEx(rR, images[iFrame], nullptr, r, angle, nullptr, SDL_FLIP_NONE);
}

void Texture::SetImageOpacity(double a){
    SDL_SetTextureAlphaMod(images[0], a);
}
