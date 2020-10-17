//
// Created by 番茄沙司 on 2020/9/30.
//

#include "EGLThread.h"
#include <unistd.h>
#include <GLES3/gl3.h>
#include "../log/LogUtil.h"

EGLThread::EGLThread() {
    pthread_mutex_init(&pthreadMutex, nullptr);
    pthread_cond_init(&pthreadCond, nullptr);
}

EGLThread::~EGLThread() {
    pthread_mutex_destroy(&pthreadMutex);
    pthread_cond_destroy(&pthreadCond);
}

void *eglThreadRunnable(void *ctx) {
    auto *eglThread = static_cast<EGLThread *>(ctx);
    if (eglThread != nullptr) {
        auto *eglHelper = new EGLHelper();
        eglHelper->initEGL(eglThread->nativeWindow);
        eglThread->isExit = false;
        while (true) {
            if (eglThread->isCreated) {
                LOGI("egl thread: isCreated");
                eglThread->onRenderInitCallback(eglThread->onRenderInitCallbackCtx);
                eglThread->isCreated = false;
            }
            if (eglThread->isChanged) {
                LOGI("egl thread: isChanged");
                eglThread->onWindowSizeChangedCallback(eglThread->onRenderInitCallbackCtx,
                                                       eglThread->surfaceWidth,
                                                       eglThread->surfaceHeight);
                eglThread->isChanged = false;
                eglThread->isDrawStart = true;
            }
            if (eglThread->isDrawStart) {
                LOGI("egl thread: isDrawStart");
                eglThread->onDrawCallback(eglThread->onDrawCallbackCtx);
                eglHelper->swapBuffers();
            }
            if (eglThread->isFilterChanged) {
                LOGI("egl thread: isFilterChanged");
                eglThread->isFilterChanged = false;
                eglThread->onFilterChangedCallback(eglThread->onFilterChangedCallbackCtx,
                                                   eglThread->surfaceWidth,
                                                   eglThread->surfaceHeight);
            }

            if (eglThread->renderType == OPENGL_RENDER_AUTO) {
                LOGI("egl thread: sleep");
                usleep(1000000);
            } else {
                pthread_mutex_lock(&eglThread->pthreadMutex);
                LOGI("egl thread: wait for next draw");
                pthread_cond_wait(&eglThread->pthreadCond, &eglThread->pthreadMutex);
                pthread_mutex_unlock(&eglThread->pthreadMutex);
            }
            if (eglThread->isExit) {
                LOGI("egl thread: exit()");
                eglThread->onRenderReleaseCallback(eglThread->onRenderReleaseCallbackCtx);
                eglHelper->destroyEGL();
                delete eglHelper;
                eglHelper = nullptr;
                break;
            }
        }
    }
    return nullptr;
}

void EGLThread::initRenderThread(EGLNativeWindowType win) {
    if (eglThreadId == -1) {
        isCreated = true;
        nativeWindow = win;
        pthread_create(&eglThreadId, nullptr, eglThreadRunnable, this);
    }
}

void EGLThread::windowSizeChanged(int width, int height) {
    isChanged = true;
    surfaceWidth = width;
    surfaceHeight = height;
    notifyRender();
}

void EGLThread::releaseThread() {
    isExit = true;
    notifyRender();
    pthread_join(eglThreadId, nullptr);
    nativeWindow = nullptr;
    eglThreadId = -1;
}

void EGLThread::onFilterChanged() {
    isFilterChanged = true;
    notifyRender();
}

void
EGLThread::setOnRenderInitCallback(EGLThread::OnRenderInitCallback onSurfaceCreatedCallback,
                                   void *ctx) {
    this->onRenderInitCallback = onSurfaceCreatedCallback;
    this->onRenderInitCallbackCtx = ctx;
}

void
EGLThread::setOnWindowSizeChangedCallback(EGLThread::OnWindowSizeChangedCallback onSurfaceChangedCallback,
                                          void *ctx) {
    this->onWindowSizeChangedCallback = onSurfaceChangedCallback;
    this->onWindowSizeChangedCallbackCtx = ctx;
}

void
EGLThread::setOnRenderReleaseCallback(EGLThread::OnRenderReleaseCallback onSurfaceDestroyCallback,
                                      void *ctx) {
    this->onRenderReleaseCallback = onSurfaceDestroyCallback;
    this->onRenderReleaseCallbackCtx = ctx;
}

void EGLThread::setOnDrawCallback(EGLThread::OnDrawCallback onDrawCallback, void *ctx) {
    this->onDrawCallback = onDrawCallback;
    this->onDrawCallbackCtx = ctx;
}

void
EGLThread::setOnFilterChangedCallback(EGLThread::OnFilterChangedCallback onFilterChangedCallback,
                                      void *ctx) {
    this->onFilterChangedCallback = onFilterChangedCallback;
    this->onFilterChangedCallbackCtx = ctx;
}

void EGLThread::setRenderType(int renderType) {
    this->renderType = renderType;
}

void EGLThread::notifyRender() {
    pthread_mutex_lock(&pthreadMutex);
    pthread_cond_signal(&pthreadCond);
    pthread_mutex_unlock(&pthreadMutex);
}
