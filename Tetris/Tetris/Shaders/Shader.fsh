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
    //colorVarying.r = 1.0;
    //colorVarying.g = 1.0;
    gl_FragColor = vec4(1.0, 0, 0, 0);//colorVarying;

    //gl_FragColor.r = 1.0;
}
