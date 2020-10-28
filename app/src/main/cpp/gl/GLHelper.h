//
// Created by zqlxt on 2020/9/26.
//

#ifndef LEARNOPENGL_GLHELPER_H
#define LEARNOPENGL_GLHELPER_H

#include <jni.h>
#include <GLES3/gl3.h>
#include "../egl/EGLThread.h"

class GLHelper {
public:
    EGLThread *eglThread{};
    ANativeWindow *aNativeWindow{};
public:
    GLHelper();

    ~GLHelper();

    void onSurfaceCreated(JNIEnv *env, jobject surface);

    void onSurfaceChanged(int width, int height);

    void onSurfaceDestroy();

    GLuint loadShader(GLenum type, const char *shaderSrc);

    GLuint loadProgram(GLuint vertexShader, GLuint fragmentShader);

    void singleDrawColor(JNIEnv *env, jobject surface, float, float, float, float);

    void singleDrawTriangle(JNIEnv *env, jobject surface);

    void singleDrawColorTriangle(JNIEnv *env, jobject surface);

    void drawColorTriangleWithThread(JNIEnv *env, jobject surface);

    static GLint checkShaderCompiled(GLuint shader);

    static GLint checkProgramLinked(GLuint program);

};
void onSurfaceCreatedCallback(void *ctx);
void onSurfaceChangedCallback(void *ctx, int width, int height);
void onSurfaceDestroyCallback(void *ctx);
void onHelperFilterChangedCallback(void *ctx, int width, int height);
void onHelperDrawCallback(void *ctx);
#endif //LEARNOPENGL_GLHELPER_H
