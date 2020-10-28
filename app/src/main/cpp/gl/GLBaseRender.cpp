//
// Created by zqlxt on 2020/10/2.
//

#include <GLES3/gl3.h>
#include "GLBaseRender.h"

void GLBaseRender::renderInit() {
    glHelper = new GLHelper();
    processShader();
    processProgram();
}

void GLBaseRender::changeWindowSize(int width, int height) {
    windowWidth = width;
    windowHeight = height;
    glViewport(0, 0, width, height);
}

GLBaseRender::GLBaseRender() {

}

GLBaseRender::~GLBaseRender() {
    delete glHelper;
}
