//
//  render.cpp
//  Tetris
//
//  Created by 建邦 宋 on 14-5-27.
//  Copyright (c) 2014年 rx. All rights reserved.
//

#include "render.h"
#include <assert.h>

const PictureHandle INVALIDATE_PICTURE = 0;

const char* g_vertex_shader = "\
attribute vec4 position;\
attribute vec4 color;\
attribute vec2 tex;\
\
varying lowp vec4 colorVarying;\
\
uniform mat4 modelViewProjMat;\
void main()\
{\
colorVarying = position;\
gl_Position = vec4(position.x / 320.0 - 1.0, position.y / 568.0 - 1.0, 0, position.w);\
}\
";


const char* g_pixel_shader = "\
varying lowp vec4 colorVarying;\
void main()\
{\
if(colorVarying.x < 100.0)\
gl_FragColor = vec4(1.0, 0, 0, 0);\
else if(colorVarying.x > 600.0)\
gl_FragColor = vec4(0, 1.0, 0, 0);\
else \
gl_FragColor = vec4(colorVarying.x/640.0, colorVarying.y/1136.0, 0, 0);\
}\
";

CTechnique::CTechnique()
{
    
}

CTechnique::~CTechnique()
{
    
}

void CTechnique::UseTechnique()
{
    glUseProgram(m_hProgram);
}

bool CTechnique::InitTechnique(const char* vertexShader, const char* pixelShader)
{
    m_hProgram = glCreateProgram();
    m_hV = glCreateShader(GL_VERTEX_SHADER);
    m_hF = glCreateShader(GL_FRAGMENT_SHADER);
    
    if (CompileShader(m_hV, vertexShader) == false) {
        assert(false);
        return false;
    }
    
    if (CompileShader(m_hF, pixelShader) == false) {
        assert(false);
        return false;
    }
    
    GLint vp[4];
    glGetIntegerv(GL_VIEWPORT, vp);
    glAttachShader(m_hProgram, m_hV);
    glAttachShader(m_hProgram, m_hF);
    

    GLint status;
    glLinkProgram(m_hProgram);
    
//#if defined(DEBUG)
    GLint logLength;
    glGetProgramiv(m_hProgram, GL_INFO_LOG_LENGTH, &logLength);
    if (logLength > 0) {
        GLchar *log = (GLchar *)malloc(logLength);
        glGetProgramInfoLog(m_hProgram, logLength, &logLength, log);
        //NSLog(@"Program link log:\n%s", log);
        printf(log);
        free(log);
    }
//#endif
    
    glGetProgramiv(m_hProgram, GL_LINK_STATUS, &status);
    if (status == 0) {
        return false;
    }
    
    return true;
}

bool CTechnique::CompileShader(GLuint shader, const char* strShader)
{
    glShaderSource(shader, 1, &strShader, NULL);
    glCompileShader(shader);
    
//#if defined(DEBUG)
    GLint logLength;
    glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &logLength);
    if (logLength > 0) {
        GLchar *log = (GLchar *)malloc(logLength);
        glGetShaderInfoLog(shader, logLength, &logLength, log);
        printf("shader compile log: %s\n", log);
        free(log);
    }
//#endif
    
    GLint status;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
    if (status == 0) {
        assert(false);
        printf("fail to compile shader\n");
        glDeleteShader(shader);
        return false;
    }

    return true;
}

CRender::CRender()
{
    
}

CRender::~CRender()
{
    
}

bool CRender::InitRender()
{
    GLint vp[4];
    glGetIntegerv(GL_VIEWPORT, vp);
    m_technique.InitTechnique(g_vertex_shader, g_pixel_shader);
    
    glGenBuffers(1, &m_hvb);
    return true;
}

void CRender::DrawPicture(PictureHandle hPic, CRect & dest)
{
    if (m_batches.empty() || m_batches.back().hPic != hPic) {
        Batch b;
        b.hPic = hPic;
        //lt      rt
        //lb      rb
        b.vertices.push_back(Vertex(dest.l, dest.b, 0));
        b.vertices.push_back(Vertex(dest.l, dest.t, 0));
        b.vertices.push_back(Vertex(dest.r, dest.t, 0));
        
        b.vertices.push_back(Vertex(dest.l, dest.b, 0));
        b.vertices.push_back(Vertex(dest.r, dest.t, 0));
        b.vertices.push_back(Vertex(dest.r, dest.b, 0));
        
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

void CRender::DrawPicture(PictureHandle hPic, CRender::DrawPictureParameter& dpp)
{
    
}

void CRender::BeginRender()
{
    GLint vp[4];
    glGetIntegerv(GL_VIEWPORT, vp);
    m_technique.UseTechnique();
    
//    glViewport(100, 130, 500, 700);
    CRect rectt;
    rectt.l = 0;
    rectt.r = 300;
    rectt.b = 0;
    rectt.t = 500;
    DrawPicture(0, rectt);
    
    glBindBuffer(GL_ARRAY_BUFFER, m_hvb);
//    static float rect[] =
//    {0.f, 0.f, 0.f,   //1.f, 1.f, 0.f,
//        640.f, 960.f, 0.f, //r1.f, 1.f, 0.f,
//        0.f, 960.f, 0.f//, 1.f, 1.f, 0.f
//    };
//    glBufferData(GL_ARRAY_BUFFER, sizeof(rect), rect, GL_STREAM_DRAW);
//    
//    glEnableVertexAttribArray(0);
//    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 12, (char*)0);

//    glEnableVertexAttribArray(1);
//    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 24, (char*)12);
    
    for (unsigned int i = 0; i < m_batches.size(); ++i) {
        //m_batches[i].vertices;
        glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex)*m_batches[i].vertices.size(), &m_batches[i].vertices[0], GL_STREAM_DRAW);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);
        glDrawArrays(GL_TRIANGLES, 0, m_batches[i].vertices.size());
    }
    
    
    glDrawArrays(GL_TRIANGLES, 0, 3);
    
    m_batches.clear();
}

void CRender::EndRender()
{
    
}
