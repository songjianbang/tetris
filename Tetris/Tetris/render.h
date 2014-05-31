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
#include <OpenGLES/ES2/gl.h>
#include <OpenGLES/ES2/glext.h>

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
    Vertex(float aX = 0, float aY = 0, float aZ = 0):x(aX), y(aY), z(aZ){}
};

struct Batch
{
    PictureHandle hPic;
    std::vector<Vertex> vertices;
};

class CTechnique
{
public:
    CTechnique();
    ~CTechnique();
    
    bool InitTechnique(const char* vertexShader, const char* pixelShader);
    void UseTechnique();
    
private:
    
    bool CompileShader(GLuint shader, const char* strShader);
    GLuint m_hV;
    GLuint m_hF;
    GLuint m_hProgram;

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
    
    bool InitRender();
    
    void DrawPicture(PictureHandle hPic, CRect & dest);
    void DrawPicture(PictureHandle hPic, DrawPictureParameter& dpp);
    
    void BeginRender();
    void EndRender();
private:
    std::vector<Vertex> m_vertexes;
    std::vector<Batch>  m_batches;
    CTechnique          m_technique;
    GLuint              m_hvb;
};

#endif /* defined(__Tetris__render__) */
