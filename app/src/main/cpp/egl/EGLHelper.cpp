//
// Created by 番茄沙司 on 2020/9/24.
//

#include "EGLHelper.h"
#include <GLES2/gl2.h>
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
        LOGE("EGL: get display error !!!");
        return -1;
    }

    //2. 初始化默认显示设备
    EGLint *version = new EGLint[2];
    if (!eglInitialize(mEGLDisplay, &version[0], &version[1])) {
        LOGE("EGL: init display error !!!");
        return -1;
    }
    LOGI("egl: version major: %d, minor : %d", version[0], version[1]);

    //3. 设置显示设备属性
    const EGLint attr[] = {
            EGL_RED_SIZE, 8,
            EGL_GREEN_SIZE, 8,
            EGL_BLUE_SIZE, 8,
            EGL_ALPHA_SIZE, 8,
            EGL_DEPTH_SIZE, 8,
            EGL_STENCIL_SIZE, 8,
            EGL_RENDERABLE_TYPE, EGL_OPENGL_ES2_BIT,
            EGL_NONE
    };
    EGLint num_config;
    if (!eglChooseConfig(mEGLDisplay, attr, NULL, 1, &num_config)) {
        LOGE("EGL: choose config error1!!!");
        return -1;
    }

    //4. 从系统中获取对应属性的配置
    if (!eglChooseConfig(mEGLDisplay, attr, &mEGLConfig, num_config, &num_config)) {
        LOGE("EGL: choose config error2!!!");
        return -1;
    }

    //5. 创建 EGLContext
    int attr_list[] = {EGL_CONTEXT_CLIENT_VERSION, 2, EGL_NONE};
    mEGLContext = eglCreateContext(mEGLDisplay, mEGLConfig, EGL_NO_CONTEXT, attr_list);
    if (mEGLContext == EGL_NO_CONTEXT) {
        LOGE("EGL: create egl context error!!!");
        return -1;
    }

    //6. 创建渲染的 surface
    mEGLSurface = eglCreateWindowSurface(mEGLDisplay, mEGLConfig, windowType, nullptr);
    if (mEGLSurface == EGL_NO_SURFACE) {
        LOGE("EGL: create surface error!!!");
        return -1;
    }

    //7. 绑定 EGLContext 和 Surface 到设备显示器
    if (!eglMakeCurrent(mEGLDisplay, mEGLSurface, mEGLSurface, mEGLContext)) {
        LOGE("EGL: make current error!!!");
        return -1;
    }

    LOGI("egl init success!!!");

    return 0;
}

int EGLHelper::swapBuffers() {
    if (mEGLDisplay != EGL_NO_DISPLAY && mEGLSurface != EGL_NO_SURFACE) {
        if (eglSwapBuffers(mEGLDisplay, mEGLSurface)) {
            return 0;
        }
    }
    return -1;
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

void EGLHelper::singleDrawColor(float red, float green, float blue, float alpha) {
    glClearColor(red, green, blue, alpha);
    glClear(GL_COLOR_BUFFER_BIT);
}

void EGLHelper::singleDrawTriangle() {
    glClearColor(1, 1, 1, 1);
    glClear(GL_COLOR_BUFFER_BIT);
    float vertices[] = {
            -0.5f, -0.5f, 0.0f,
            0.5f, -0.5f, 0.0f,
            0.0f, 0.5f, 0.0f
    };
    unsigned int VBO;
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    const char *vertexShaderSource = "layout (location = 0) in vec3 aPos;\n"
                                     "void main()\n"
                                     "{\n"
                                     " gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
                                     "}\0";

    const char *fragmentShaderSource = "out vec4 FragColor;\n"
                                       "void main()\n"
                                       "{\n"
                                       "FragColor = vec4(0.0f, 0.0f, 0.0f, 0.0f);\n"
                                       "}";
    unsigned int vertexShader;
    unsigned int fragmentShader;
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, nullptr);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, nullptr);
    glCompileShader(vertexShader);
    glCompileShader(fragmentShader);

    unsigned int shaderProgram;
    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);

    glVertexAttribPointer(0, 3, GL_FLOAT, EGL_FALSE, 3 * sizeof(float), nullptr);
    glEnableVertexAttribArray(0);
    glUseProgram(shaderProgram);

    glDrawArrays(GL_TRIANGLES,0,3);
}
