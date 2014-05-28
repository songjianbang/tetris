//
//  render.cpp
//  Tetris
//
//  Created by 建邦 宋 on 14-5-27.
//  Copyright (c) 2014年 rx. All rights reserved.
//

#include "render.h"

const PictureHandle INVALIDATE_PICTURE = 0;

void CRender::DrawPicture(PictureHandle hPic, CRect & dest)
{
    if (m_batches.empty() || m_batches.back().hPic != hPic) {
        Batch b;
        b.hPic = hPic;
        b.vertices.push_back(Vertex());
        b.vertices.push_back(Vertex());
        b.vertices.push_back(Vertex());
        b.vertices.push_back(Vertex());
        
        m_batches.push_back(b);
        return;
    }
    
    if (m_batches.back().hPic == hPic) {
        Batch& b = m_batches.back();
        b.vertices.push_back(Vertex());
        b.vertices.push_back(Vertex());
        b.vertices.push_back(Vertex());
        b.vertices.push_back(Vertex());
        
        return;
    }
}