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

    typedef void(*OnRenderInitCallback)(void *ctx);

    typedef void(*OnWindowSizeChangedCallback)(void *ctx, int surfaceWidth, int surfaceHeight);

    typedef void(*OnRenderReleaseCallback)(void *ctx);

    typedef void(*OnDrawCallback)(void *ctx);

    typedef void(*OnFilterChangedCallback)(void *ctx, int surfaceWidth, int surfaceHeight);

    OnRenderInitCallback onRenderInitCallback{};
    void *onRenderInitCallbackCtx{};

    OnWindowSizeChangedCallback onWindowSizeChangedCallback{};
    void *onWindowSizeChangedCallbackCtx{};

    OnRenderReleaseCallback onRenderReleaseCallback{};
    void *onRenderReleaseCallbackCtx{};

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

    /**
     * 初始化 EGLThread，此时 opengl 渲染还没有真正开始，需要调用 @see ::windowSizeChanged 来触发渲染
     * @param win 本地窗口，@see ANativeWindow_fromSurface
     */
    void initRenderThread(EGLNativeWindowType win);

    /**
     * 指定 opengl 中 viewport 大小，此方法调用后会触发 opengl 真正的渲染流程
     * @param width
     * @param height
     */
    void windowSizeChanged(int width, int height);

    void releaseThread();

    void onFilterChanged();

    void setOnRenderInitCallback(OnRenderInitCallback onSurfaceCreatedCallback, void *ctx);

    void setOnWindowSizeChangedCallback(OnWindowSizeChangedCallback onSurfaceChangedCallback, void *ctx);

    void setOnRenderReleaseCallback(OnRenderReleaseCallback onSurfaceDestroyCallback, void *ctx);

    void setOnDrawCallback(OnDrawCallback onDrawCallback, void *ctx);

    void setOnFilterChangedCallback(OnFilterChangedCallback onFilterChangedCallback, void *ctx);

    void setRenderType(int renderType);

    void notifyRender();

};


#endif //LEARNOPENGL_EGLTHREAD_H
