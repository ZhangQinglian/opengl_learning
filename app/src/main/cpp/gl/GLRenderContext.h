//
// Created by zqlxt on 2020/10/2.
//

#ifndef LEARNOPENGL_GLRENDERCONTEXT_H
#define LEARNOPENGL_GLRENDERCONTEXT_H

#include <EGL/egl.h>
#include <jni.h>
#include "../egl/EGLThread.h"
#include "GLBaseRender.h"

class GLRenderContext {
public:
    EGLThread *eglThread;
    GLBaseRender *glRender;
    ANativeWindow *aNativeWindow;

    GLRenderContext();
    ~GLRenderContext();

    void init(JNIEnv *env, jobject surface, GLBaseRender *render);
    void windowSizeChanged(int width,int height);
    void release();
};

void onRenderInitCallback(void *ctx);
void onWindowSizeChangedCallback(void *ctx, int width, int height);
void onRenderReleaseCallback(void *ctx);
void onDrawCallback(void *ctx);
void onFilterChangedCallback(void *ctx, int width, int height);

#endif //LEARNOPENGL_GLRENDERCONTEXT_H
