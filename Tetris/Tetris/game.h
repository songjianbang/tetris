//
//  game.h
//  Tetris
//
//  Created by 建邦 宋 on 14-5-28.
//  Copyright (c) 2014年 rx. All rights reserved.
//

#ifndef __Tetris__game__
#define __Tetris__game__

#include <iostream>

#include "render.h"

class CGame
{
public:
    CGame();
    ~CGame();
    
    bool InitGame();
    
    void TouchBegin(float x, float y);
    
    void Tick(float aDelta);
    void Render();
    
    CRect m_rect;
private:
    CRender m_render;
};

extern CGame g_game;

#endif /* defined(__Tetris__game__) */
