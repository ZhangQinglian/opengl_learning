//
// Created by zqlxt on 2020/10/2.
//

#ifndef LEARNOPENGL_GLBASERENDER_H
#define LEARNOPENGL_GLBASERENDER_H


#include "../egl/EGLThread.h"

class GLBaseRender {
private:
    const char *vertexShader;
    const char *fragmentShader;
    int windowWidth{0};
    int windowHeight{0};
public:
    GLBaseRender();
    ~GLBaseRender();
    void changeWindowSize(int width,int height);
    virtual void renderInit() = 0;
    virtual void draw() = 0;
    virtual char* getVertexShader() = 0;
    virtual char* getFragmentShader() = 0;
};


#endif //LEARNOPENGL_GLBASERENDER_H
