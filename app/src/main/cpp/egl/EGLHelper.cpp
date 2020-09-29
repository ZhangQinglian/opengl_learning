//
// Created by 番茄沙司 on 2020/9/24.
//

#include "EGLHelper.h"
#include <GLES3/gl3.h>
#include "../log/LogUtil.h"

EGLHelper::EGLHelper() {
    mEGLDisplay = EGL_NO_DISPLAY;
    mEGLSurface = EGL_NO_SURFACE;
    mEGLConfig = nullptr;
    mEGLContext = EGL_NO_CONTEXT;
}

EGLHelper::~EGLHelper() {
    // todo 释放资源
}

int EGLHelper::initEGL(EGLNativeWindowType windowType) {
    //1. 获取默认显示设备
    mEGLDisplay = eglGetDisplay(EGL_DEFAULT_DISPLAY);
    if (mEGLDisplay == EGL_NO_DISPLAY) {
        // Unable to open connection to local windowing system
        LOGE("EGL: get display error !!!");
        return EGL_FALSE;
    }

    //2. 初始化默认显示设备
    EGLint majorVersion,minorVersion;
    if (!eglInitialize(mEGLDisplay, &majorVersion, &minorVersion)) {
        // Unable to initialize EGL; handle and recover
        LOGE("EGL: init display error !!!");
        return EGL_FALSE;
    }

    LOGI("egl: version major: %d, minor : %d", majorVersion, minorVersion);

    //3. 设置显示设备属性
    const EGLint attr[] = {
            EGL_RED_SIZE, 8,
            EGL_GREEN_SIZE, 8,
            EGL_BLUE_SIZE, 8,
            EGL_ALPHA_SIZE, 8,
            EGL_DEPTH_SIZE, 8,
            EGL_STENCIL_SIZE, 8,
            EGL_RENDERABLE_TYPE, EGL_OPENGL_ES3_BIT,
            EGL_NONE
    };
    EGLint num_config;
    if (!eglChooseConfig(mEGLDisplay, attr, nullptr, 1, &num_config)) {
        LOGE("EGL: choose config error1!!!");
        return EGL_FALSE;
    }

    //4. 从系统中获取对应属性的配置
    if (!eglChooseConfig(mEGLDisplay, attr, &mEGLConfig, num_config, &num_config)) {
        LOGE("EGL: choose config error2!!!");
        return EGL_FALSE;
    }

    //5. 创建 EGLContext
    int attr_list[] = {EGL_CONTEXT_CLIENT_VERSION,3, EGL_NONE};
    mEGLContext = eglCreateContext(mEGLDisplay, mEGLConfig, EGL_NO_CONTEXT, attr_list);
    if (mEGLContext == EGL_NO_CONTEXT) {
        LOGE("EGL: create egl context error!!!");
        return EGL_FALSE;
    }

    //6. 创建渲染的 surface
    mEGLSurface = eglCreateWindowSurface(mEGLDisplay, mEGLConfig, windowType, nullptr);
    if (mEGLSurface == EGL_NO_SURFACE) {
        LOGE("EGL: create surface error!!!");
        return EGL_FALSE;
    }

    //7. 绑定 EGLContext 和 Surface 到设备显示器
    if (!eglMakeCurrent(mEGLDisplay, mEGLSurface, mEGLSurface, mEGLContext)) {
        LOGE("EGL: make current error!!!");
        return EGL_FALSE;
    }

    LOGI("egl init success!!!");

    return EGL_TRUE;
}

int EGLHelper::swapBuffers() {
    if (mEGLDisplay != EGL_NO_DISPLAY && mEGLSurface != EGL_NO_SURFACE) {
        if (eglSwapBuffers(mEGLDisplay, mEGLSurface)) {
            return EGL_TRUE;
        }
    }
    return EGL_FALSE;
}

void EGLHelper::destroyEGL() {
    if (mEGLDisplay != EGL_NO_DISPLAY) {
        eglMakeCurrent(mEGLDisplay, EGL_NO_SURFACE, EGL_NO_SURFACE, EGL_NO_CONTEXT);
    }
    if (mEGLDisplay != EGL_NO_DISPLAY && mEGLSurface != EGL_NO_SURFACE) {
        eglDestroySurface(mEGLDisplay, mEGLSurface);
        mEGLSurface = EGL_NO_SURFACE;
    }

    if (mEGLDisplay != EGL_NO_DISPLAY && mEGLContext != EGL_NO_CONTEXT) {
        eglDestroyContext(mEGLDisplay, mEGLContext);
        mEGLContext = EGL_NO_CONTEXT;
    }
    if (mEGLDisplay != EGL_NO_DISPLAY) {
        eglTerminate(mEGLDisplay);
    }
    LOGI("egl: destroy egl success!!!");
}
