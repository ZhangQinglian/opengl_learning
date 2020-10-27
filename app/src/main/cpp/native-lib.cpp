#include <jni.h>
#include <string>
#include "egl/EGLHelper.h"
#include "gl/GLHelper.h"
#include <android/native_window.h>
#include <android/native_window_jni.h>

GLHelper *glHelper;
extern "C"
JNIEXPORT void JNICALL
Java_com_zqlxtt_learnopengl_BaseSurfaceFragment_drawColor(JNIEnv *env, jobject thiz, jfloat red,
                                                          jfloat green, jfloat blue,
                                                          jfloat alpha, jobject surface) {
    glHelper = new GLHelper();
    glHelper->singleDrawColor(env, surface, red, green, blue, alpha);
    delete glHelper;
}extern "C"
JNIEXPORT void JNICALL
Java_com_zqlxtt_learnopengl_BaseSurfaceFragment_drawTriangle(JNIEnv *env, jobject thiz,
                                                             jobject surface) {
    glHelper = new GLHelper();
    glHelper->singleDrawTriangle(env, surface);
    delete glHelper;
}extern "C"
JNIEXPORT void JNICALL
Java_com_zqlxtt_learnopengl_BaseSurfaceFragment_drawColorTriangle(JNIEnv *env, jobject thiz,
                                                                  jobject surface) {
    glHelper = new GLHelper();
    glHelper->singleDrawColorTriangle(env, surface);
    delete glHelper;
}extern "C"
JNIEXPORT void JNICALL
Java_com_zqlxtt_learnopengl_l04_FragmentEGLThread_drawTriangleWithThread(JNIEnv *env, jobject thiz,
                                                                     jobject surface) {
    glHelper = new GLHelper();
    glHelper->drawColorTriangleWithThread(env, surface);
}extern "C"
JNIEXPORT void JNICALL
Java_com_zqlxtt_learnopengl_BaseSurfaceFragment_onSurfaceCreatedN(JNIEnv *env, jobject thiz,
                                                                  jobject surface) {
    if (glHelper != nullptr) {
        glHelper->onSurfaceCreated(env, surface);
    }
}extern "C"
JNIEXPORT void JNICALL
Java_com_zqlxtt_learnopengl_BaseSurfaceFragment_onSurfaceChangedN(JNIEnv *env, jobject thiz,
                                                                  jint width, jint height) {
    if (glHelper != nullptr) {
        glHelper->onSurfaceChanged(width, height);
    }
}extern "C"
JNIEXPORT void JNICALL
Java_com_zqlxtt_learnopengl_BaseSurfaceFragment_onSurfaceDestroyN(JNIEnv *env, jobject thiz) {
    if (glHelper != nullptr) {
        glHelper->onSurfaceDestroy();
    }
    delete glHelper;
}