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
uniform mat4 modelViewProjMat;\
void main()\
{\
gl_Position = position;\
}\
";

const char* g_pixel_shader = "\
void main()\
{\
gl_FragColor = vec4(1.0, 0, 0, 0);\
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
    m_technique.InitTechnique(g_vertex_shader, g_pixel_shader);
    return true;
}

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

void CRender::DrawPicture(PictureHandle hPic, CRender::DrawPictureParameter& dpp)
{
    
}

void CRender::BeginRender()
{
    m_technique.UseTechnique();
}

void CRender::EndRender()
{
    
}
