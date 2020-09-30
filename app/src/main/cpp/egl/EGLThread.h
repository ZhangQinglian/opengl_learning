//
// Created by 番茄沙司 on 2020/9/30.
//

#ifndef LEARNOPENGL_EGLTHREAD_H
#define LEARNOPENGL_EGLTHREAD_H

#include <pthread.h>
#include <EGL/egl.h>
#include "EGLHelper.h"

#define OPENGL_RENDER_AUTO 1
#define OPENGL_RENDER_MANUAL 2

class EGLThread {

public:
    pthread_t eglThreadId = -1;
    ANativeWindow *nativeWindow = nullptr;
    bool isCreated = false;
    bool isChanged = false;
    bool isExit = false;
    bool isDrawStart = false;
    bool isFilterChanged = false;

    int surfaceWidth = 0;
    int surfaceHeight = 0;

    typedef void(*OnSurfaceCreatedCallback)(void *ctx);

    typedef void(*OnSurfaceChangedCallback)(void *ctx, int surfaceWidth, int surfaceHeight);

    typedef void(*OnSurfaceDestroyCallback)(void *ctx);

    typedef void(*OnDrawCallback)(void *ctx);

    typedef void(*OnFilterChangedCallback)(void *ctx, int surfaceWidth, int surfaceHeight);

    OnSurfaceCreatedCallback onSurfaceCreatedCallback{};
    void *onSurfaceCreatedCallbackCtx{};

    OnSurfaceChangedCallback onSurfaceChangedCallback{};
    void *onSurfaceChangedCallbackCtx{};

    OnSurfaceDestroyCallback onSurfaceDestroyCallback{};
    void *onSurfaceDestroyCallbackCtx{};

    OnDrawCallback onDrawCallback{};
    void *onDrawCallbackCtx{};

    OnFilterChangedCallback onFilterChangedCallback{};
    void *onFilterChangedCallbackCtx{};

    int renderType = OPENGL_RENDER_MANUAL;

    pthread_mutex_t pthreadMutex{};
    pthread_cond_t pthreadCond{};

public:
    EGLThread();

    ~EGLThread();

    void onSurfaceCreated(EGLNativeWindowType win);

    void onSurfaceChanged(int width, int height);

    void onSurfaceDestroy();

    void onFilterChanged();

    void setOnSurfaceCreatedCallback(OnSurfaceCreatedCallback onSurfaceCreatedCallback, void *ctx);

    void setOnSurfaceChangedCallback(OnSurfaceChangedCallback onSurfaceChangedCallback, void *ctx);

    void setOnSurfaceDestroyCallback(OnSurfaceDestroyCallback onSurfaceDestroyCallback, void *ctx);

    void setOnDrawCallback(OnDrawCallback onDrawCallback, void *ctx);

    void setOnFilterChangedCallback(OnFilterChangedCallback onFilterChangedCallback, void *ctx);

    void setRenderType(int renderType);

    void notifyRender();

};


#endif //LEARNOPENGL_EGLTHREAD_H
