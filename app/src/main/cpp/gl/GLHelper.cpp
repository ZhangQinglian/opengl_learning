//
// Created by zqlxt on 2020/9/26.
//

#include <EGL/egl.h>
#include <jni.h>
#include <android/native_window_jni.h>
#include <iostream>
#include "GLHelper.h"
#include "../egl/EGLHelper.h"
#include "../log/LogUtil.h"
#include "../egl/EGLThread.h"


void GLHelper::singleDrawColor(JNIEnv *env, jobject surface, float red, float green, float blue,
                               float alpha) {
    ANativeWindow *aNativeWindow = ANativeWindow_fromSurface(env, surface);
    auto *eglHelper = new EGLHelper();
    eglHelper->initEGL(aNativeWindow);
    glClearColor(red, green, blue, alpha);
    glClear(GL_COLOR_BUFFER_BIT);
    eglHelper->swapBuffers();
    ANativeWindow_release(aNativeWindow);
    delete eglHelper;
}

void GLHelper::singleDrawTriangle(JNIEnv *env, jobject surface) {
    ANativeWindow *aNativeWindow = ANativeWindow_fromSurface(env, surface);
    auto *eglHelper = new EGLHelper();
    eglHelper->initEGL(aNativeWindow);

    glClearColor(1, 1, 1, 1);
    glClear(GL_COLOR_BUFFER_BIT);
    float vertices[] = {
            -0.5f, -0.5f, 0.0f,
            0.5f, -0.5f, 0.0f,
            0.0f, 0.5f, 0.0f
    };
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    const char *vertexShaderSource =
            "#version 300 es                            \n"
            "layout(location = 0) in vec4 vPosition;    \n"
            "void main()                                \n"
            "{                                          \n"
            " gl_Position = vPosition;                  \n"
            "}                                          \n";

    const char *fragmentShaderSource =
            "#version 300 es                            \n"
            "precision mediump float;                   \n"
            "out vec4 fragColor;                        \n"
            "void main()                                \n"
            "{                                          \n"
            " fragColor = vec4 ( 1.0, 0.0, 0.0, 1.0 );  \n"
            "}                                          \n";
    GLuint vertexShader = loadShader(GL_VERTEX_SHADER, vertexShaderSource);
    GLuint fragmentShader = loadShader(GL_FRAGMENT_SHADER, fragmentShaderSource);
    GLuint shaderProgram = loadProgram(vertexShader, fragmentShader);
    glUseProgram(shaderProgram);

    glVertexAttribPointer(0, 3, GL_FLOAT, EGL_FALSE, 0, vertices);
    glEnableVertexAttribArray(0);

    glDrawArrays(GL_TRIANGLES, 0, 3);
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
    glDeleteProgram(shaderProgram);

    eglHelper->swapBuffers();
    ANativeWindow_release(aNativeWindow);
    delete eglHelper;
}


void GLHelper::singleDrawColorTriangle(JNIEnv *env, jobject surface) {

    ANativeWindow *aNativeWindow = ANativeWindow_fromSurface(env, surface);
    auto *eglHelper = new EGLHelper();
    eglHelper->initEGL(aNativeWindow);

    glClearColor(1, 1, 1, 1);
    glClear(GL_COLOR_BUFFER_BIT);
    float vertices[] = {
            -0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f,
            0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f,
            0.0f, 0.5f, 0.0f, 0.0f, 0.0f, 1.0f
    };

    const char *vertexShaderSource =
            "#version 300 es                            \n"
            "layout(location = 0) in vec3 vPosition;    \n"
            "layout(location = 1) in vec3 vColor;    \n"
            "out vec3 fColor;    \n"
            "void main()                                \n"
            "{                                          \n"
            " gl_Position = vec4(vPosition, 1.0);                  \n"
            " fColor = vColor;                  \n"
            "}                                          \n";

    const char *fragmentShaderSource =
            "#version 300 es                            \n"
            "out vec4 fragColor;                        \n"
            "in vec3 fColor;                        \n"
            "void main()                                \n"
            "{                                          \n"
            " fragColor = vec4 (fColor, 1.0f);  \n"
            "}                                          \n";
    GLuint vertexShader = loadShader(GL_VERTEX_SHADER, vertexShaderSource);
    GLuint fragmentShader = loadShader(GL_FRAGMENT_SHADER, fragmentShaderSource);
    GLuint shaderProgram = loadProgram(vertexShader, fragmentShader);
    glUseProgram(shaderProgram);

    glVertexAttribPointer(0, 3, GL_FLOAT, EGL_FALSE, sizeof(float) * 6, vertices);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 6,
                          vertices + 3);
    glEnableVertexAttribArray(1);

    glDrawArrays(GL_TRIANGLES, 0, 3);
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
    glDeleteProgram(shaderProgram);

    eglHelper->swapBuffers();
    ANativeWindow_release(aNativeWindow);
    delete eglHelper;
}

GLHelper::GLHelper() = default;

GLHelper::~GLHelper() = default;

GLuint GLHelper::loadShader(GLenum type, const char *shaderSrc) {
    GLuint shader;
    // create the shader object
    shader = glCreateShader(type);
    if (shader == 0) {
        //create the shader error
        return GL_FALSE;
    }

    // load the shader source
    glShaderSource(shader, 1, &shaderSrc, nullptr);

    //compile the shader
    glCompileShader(shader);

    // check the compile state
    if (checkShaderCompiled(shader)) {
        return shader;
    } else {
        return GL_FALSE;
    }
}

GLint GLHelper::checkShaderCompiled(GLuint shader) {
    GLint compiled;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &compiled);
    if (!compiled) {
        GLint infoLen = 0;
        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLen);
        if (infoLen > 0) {
            char *infoLog = new char[infoLen];
            glGetShaderInfoLog(shader, infoLen, nullptr, infoLog);
            LOGE("gl: error compile shader:\n %s \n", infoLog);
            delete[]infoLog;
        }
        glDeleteShader(shader);
        return GL_FALSE;
    }
    return GL_TRUE;
}

GLuint GLHelper::loadProgram(GLuint vertextShader, GLuint fragmentShader) {
    GLuint program;
    program = glCreateProgram();
    if (program == 0) {
        return GL_FALSE;
    }
    glAttachShader(program, vertextShader);
    glAttachShader(program, fragmentShader);
    glLinkProgram(program);
    if (checkProgramLinked(program)) {
        return program;
    } else {
        return GL_FALSE;
    }
}

GLint GLHelper::checkProgramLinked(GLuint program) {
    GLint linked;
    glGetProgramiv(program, GL_LINK_STATUS, &linked);
    if (!linked) {
        GLint infoLen = 0;
        glGetProgramiv(program, GL_INFO_LOG_LENGTH, &infoLen);
        if (infoLen > 1) {
            char *infoLog = new char[infoLen];
            glGetProgramInfoLog(program, infoLen, nullptr, infoLog);
            LOGE("gl: error link program:\n %s \n", infoLog);
            delete[]infoLog;
        }
        glDeleteProgram(program);
        return GL_FALSE;
    }
    return GL_TRUE;
}

void GLHelper::drawColorTriangleWithThread(JNIEnv *env, jobject surface) {
    aNativeWindow = ANativeWindow_fromSurface(env, surface);
}

void GLHelper::onSurfaceCreated(JNIEnv *env, jobject surface) {
    eglThread = new EGLThread();
    eglThread->setRenderType(OPENGL_RENDER_MANUAL);
    eglThread->setOnSurfaceCreatedCallback(onSurfaceCreatedCallback, this);
    eglThread->setOnSurfaceChangedCallback(onSurfaceChangedCallback, this);
    eglThread->setOnSurfaceDestroyCallback(onSurfaceDestroyCallback, this);
    eglThread->setOnFilterChangedCallback(onFilterChangedCallback, this);
    eglThread->setOnDrawCallback(onDrawCallback, this);
    eglThread->onSurfaceCreated(aNativeWindow);
}

void GLHelper::onSurfaceChanged(int width, int height) {
    eglThread->onSurfaceChanged(width, height);
}

void GLHelper::onSurfaceDestroy() {
    eglThread->onSurfaceDestroy();
}

void onSurfaceCreatedCallback(void *ctx) {
    LOGI("gl: onSurfaceCreatedCallback");
}

void onSurfaceChangedCallback(void *ctx, int width, int height) {
    LOGI("gl: onSurfaceChangedCallback");
}

void onSurfaceDestroyCallback(void *ctx) {
    LOGI("gl: onSurfaceDestroyCallback");
    auto *glHelper = static_cast<GLHelper *>(ctx);
    if (glHelper != nullptr) {
        delete glHelper->eglThread;
        glHelper->eglThread = nullptr;
    }
}

void onFilterChangedCallback(void *ctx, int width, int height) {
    LOGI("gl: onFilterChangedCallback");
}

void onDrawCallback(void *ctx) {
    LOGI("gl: onDrawCallback");
    auto *glHelper = static_cast<GLHelper *>(ctx);
    LOGI("gl: onSurfaceCreatedCallback");
    glClearColor(1, 1, 1, 1);
    glClear(GL_COLOR_BUFFER_BIT);
    float vertices[] = {
            -0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f,
            0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f,
            0.0f, 0.5f, 0.0f, 0.0f, 0.0f, 1.0f
    };

    const char *vertexShaderSource =
            "#version 300 es                            \n"
            "layout(location = 0) in vec3 vPosition;    \n"
            "layout(location = 1) in vec3 vColor;    \n"
            "out vec3 fColor;    \n"
            "void main()                                \n"
            "{                                          \n"
            " gl_Position = vec4(vPosition, 1.0);                  \n"
            " fColor = vColor;                  \n"
            "}                                          \n";

    const char *fragmentShaderSource =
            "#version 300 es                            \n"
            "out vec4 fragColor;                        \n"
            "in vec3 fColor;                        \n"
            "void main()                                \n"
            "{                                          \n"
            " fragColor = vec4 (fColor, 1.0f);  \n"
            "}                                          \n";
    GLuint vertexShader = glHelper->loadShader(GL_VERTEX_SHADER, vertexShaderSource);
    GLuint fragmentShader = glHelper->loadShader(GL_FRAGMENT_SHADER, fragmentShaderSource);
    GLuint shaderProgram = glHelper->loadProgram(vertexShader, fragmentShader);
    glUseProgram(shaderProgram);

    glVertexAttribPointer(0, 3, GL_FLOAT, EGL_FALSE, sizeof(float) * 6, vertices);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 6,
                          vertices + 3);
    glEnableVertexAttribArray(1);

    glDrawArrays(GL_TRIANGLES, 0, 3);
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
    glDeleteProgram(shaderProgram);
}