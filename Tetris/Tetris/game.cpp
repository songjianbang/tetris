//
//  game.cpp
//  Tetris
//
//  Created by 建邦 宋 on 14-5-28.
//  Copyright (c) 2014年 rx. All rights reserved.
//

#include "game.h"

CGame g_game;

CGame::CGame()
{
    
}

CGame::~CGame()
{
    
}

bool CGame::InitGame()
{
    m_rect.l = 0;
    m_rect.r = 500;
    m_rect.b = 0;
    m_rect.t = 300;
    m_render.InitRender();
    return true;
}

void CGame::Tick(float aDelta)
{
    printf("tick: %f\n", aDelta);
}

void CGame::TouchBegin(float x, float y)
{
    m_rect.l = x;
    m_rect.r = m_rect.l + 500;
    
    m_rect.b = y;
    m_rect.t = y + 300;
    
}

void CGame::Render()
{

    m_render.DrawPicture(0, m_rect);
    m_render.BeginRender();
    m_render.EndRender();
}