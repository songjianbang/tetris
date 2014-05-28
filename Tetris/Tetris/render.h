//
//  render.h
//  Tetris
//
//  Created by 建邦 宋 on 14-5-27.
//  Copyright (c) 2014年 rx. All rights reserved.
//

#ifndef __Tetris__render__
#define __Tetris__render__

#include <iostream>

#include <vector>

typedef int PictureHandle;
extern const PictureHandle INVALIDATE_PICTURE;

class CPictureManager
{
public:
    CPictureManager();
    ~CPictureManager();
    
    PictureHandle LoadPicture(std::string aPath);
};

struct CPoint
{
    float x,y;
};

struct CRect
{
    float l,r,b,t;
};

struct CColor
{
    float r,g,b,a;
};

struct Vertex
{
    float x,y,z;
    float r,g,b,a;
    float tx,ty;
};

struct Batch
{
    PictureHandle hPic;
    std::vector<Vertex> vertices;
};

class CRender
{
public:
    CRender();
    ~CRender();
    
    struct DrawPictureParameter
    {
        CRect   srcRect;
        CRect   destRect;
        CColor  color;
        float   rotate;
    };
    
    void DrawPicture(PictureHandle hPic, CRect & dest);
    void DrawPicture(PictureHandle hPic, DrawPictureParameter& dpp);
    
private:
    std::vector<Vertex> m_vertexes;
    std::vector<Batch>  m_batches;
};

#endif /* defined(__Tetris__render__) */
