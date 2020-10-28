//
// Created by zqlxt on 2020/10/2.
//

#include <GLES3/gl3.h>
#include "GLBaseRender.h"
#include "../log/LogUtil.h"
void GLBaseRender::renderInit() {
    LOGI("[render]:    render init");
    glHelper = new GLHelper();
    processShader();
    processProgram();
}

void GLBaseRender::changeWindowSize(int width, int height) {
    LOGI("[render]:    changeWindowSize width = %d, height = %d",width,height);
    windowWidth = width;
    windowHeight = height;
    glViewport(0, 0, windowWidth, windowHeight);
}

GLBaseRender::GLBaseRender() {
    LOGI("[render]:    GLBaseRender constructor");
}

GLBaseRender::~GLBaseRender() {
    LOGI("[render]:    GLBaseRender destructor");
    delete glHelper;
}
