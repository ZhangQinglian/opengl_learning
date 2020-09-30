//
// Created by zqlxt on 2020/9/26.
//

#ifndef LEARNOPENGL_GLHELPER_H
#define LEARNOPENGL_GLHELPER_H

#include <GLES3/gl3.h>
#include "../egl/EGLThread.h"

class GLHelper {
public:
    EGLThread *eglThread;
    ANativeWindow *aNativeWindow;
public:
    GLHelper();

    ~GLHelper();

    void onSurfaceCreated(JNIEnv *env, jobject surface);

    void onSurfaceChanged(int width, int height);

    void onSurfaceDestroy();

    GLuint loadShader(GLenum type, const char *shaderSrc);

    GLuint loadProgram(GLuint vertextShader, GLuint fragmentShader);

    void singleDrawColor(JNIEnv *env, jobject surface, float, float, float, float);

    void singleDrawTriangle(JNIEnv *env, jobject surface);

    void singleDrawColorTriangle(JNIEnv *env, jobject surface);

    void drawColorTriangleWithThread(JNIEnv *env, jobject surface);

    GLint checkShaderCompiled(GLuint shader);

    GLint checkProgramLinked(GLuint program);

};
void onSurfaceCreatedCallback(void *ctx);
void onSurfaceChangedCallback(void *ctx, int width, int height);
void onSurfaceDestroyCallback(void *ctx);
void onFilterChangedCallback(void *ctx, int width, int height);
void onDrawCallback(void *ctx);
#endif //LEARNOPENGL_GLHELPER_H
