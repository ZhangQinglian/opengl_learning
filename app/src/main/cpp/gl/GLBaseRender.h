//
// Created by zqlxt on 2020/10/2.
//

#ifndef LEARNOPENGL_GLBASERENDER_H
#define LEARNOPENGL_GLBASERENDER_H


#include "../egl/EGLThread.h"
#include "GLHelper.h"

class GLBaseRender {
private:
    //surface 宽度
    int windowWidth{0};
    //surface 高度
    int windowHeight{0};
public:
    GLHelper *glHelper{};
    GLuint glVertexShader{};
    GLuint glFragmentShader{};
    GLuint glShaderProgram{};
    GLBaseRender();
    virtual ~GLBaseRender();
    void changeWindowSize(int width,int height);
    void renderInit();
    virtual void processShader() = 0;
    virtual void processProgram() = 0;
    virtual void draw() = 0;
    virtual void release() = 0;
};


#endif //LEARNOPENGL_GLBASERENDER_H
