//
// Created by zqlxt on 2020/10/2.
//

#include <android/native_window_jni.h>
#include "GLRenderContext.h"

GLRenderContext::GLRenderContext() = default;

GLRenderContext::~GLRenderContext() {
    delete eglThread;
    delete glRender;
    ANativeWindow_release(aNativeWindow);
}

void GLRenderContext::init(JNIEnv *env, jobject surface, GLBaseRender *render) {
    glRender = render;
    aNativeWindow = ANativeWindow_fromSurface(env, surface);
    eglThread = new EGLThread();
    eglThread->setRenderType(OPENGL_RENDER_MANUAL);
    eglThread->setOnRenderInitCallback(onRenderInitCallback, this);
    eglThread->setOnWindowSizeChangedCallback(onWindowSizeChangedCallback, this);
    eglThread->setOnRenderReleaseCallback(onRenderReleaseCallback, this);
    eglThread->setOnFilterChangedCallback(onFilterChangedCallback, this);
    eglThread->setOnDrawCallback(onDrawCallback, this);
    eglThread->initRenderThread(aNativeWindow);
}

void GLRenderContext::windowSizeChanged(int width, int height) {
    if (eglThread != nullptr) {
        eglThread->windowSizeChanged(width, height);
    }
}

void GLRenderContext::release() {
    if (eglThread != nullptr) {
        eglThread->releaseThread();
    }
}


void onRenderInitCallback(void *ctx) {
    auto glRenderContext = static_cast<GLRenderContext *>(ctx);
    auto render = glRenderContext->glRender;
    if (render != nullptr) {
        render->renderInit();
    }
}

void onWindowSizeChangedCallback(void *ctx, int width, int height) {
    auto glRenderContext = static_cast<GLRenderContext *>(ctx);
    auto render = glRenderContext->glRender;
    if (render != nullptr) {
        render->changeWindowSize(width, height);
    }
}

void onRenderReleaseCallback(void *ctx) {
    auto glRenderContext = static_cast<GLRenderContext *>(ctx);
    auto render = glRenderContext->glRender;
    delete glRenderContext->eglThread;
    glRenderContext->eglThread = nullptr;
    if (render != nullptr) {
        render->release();
    }
}

void onDrawCallback(void *ctx) {
    auto glRenderContext = static_cast<GLRenderContext *>(ctx);
    auto render = glRenderContext->glRender;
    if (render != nullptr) {
        render->draw();
    }
}

void onFilterChangedCallback(void *ctx, int width, int height) {

}