//
//  Shader.fsh
//  Tetris
//
//  Created by 建邦 宋 on 14-5-25.
//  Copyright (c) 2014年 rx. All rights reserved.
//

varying lowp vec4 colorVarying;

void main()
{
    gl_FragColor = colorVarying;
}
