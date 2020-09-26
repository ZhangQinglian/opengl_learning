//
// Created by 番茄沙司 on 2020/9/24.
//

#ifndef LEARNOPENGL_EGLHELPER_H
#define LEARNOPENGL_EGLHELPER_H

#include "EGL/egl.h"

class EGLHelper {

public :
    EGLDisplay mEGLDisplay;
    EGLSurface mEGLSurface;
    EGLConfig mEGLConfig;
    EGLContext mEGLContext;

    EGLHelper();

    ~EGLHelper();

    int initEGL(EGLNativeWindowType windowType);

    int swapBuffers();

    void destroyEGL();
};


#endif //LEARNOPENGL_EGLHELPER_H
