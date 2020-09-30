#include <jni.h>
#include <string>
#include "egl/EGLHelper.h"
#include "gl/GLHelper.h"
#include <android/native_window.h>
#include <android/native_window_jni.h>

extern "C"
JNIEXPORT void JNICALL
Java_com_zqlxtt_learnopengl_BaseSurfaceFragment_drawColor(JNIEnv *env, jobject thiz, jfloat red,
                                                          jfloat green, jfloat blue,
                                                          jfloat alpha, jobject surface) {
    auto *glHelper = new GLHelper();
    glHelper->singleDrawColor(env, surface, red, green, blue, alpha);
    delete glHelper;
}extern "C"
JNIEXPORT void JNICALL
Java_com_zqlxtt_learnopengl_BaseSurfaceFragment_drawTriangle(JNIEnv *env, jobject thiz,
                                                             jobject surface) {
    auto *glHelper = new GLHelper();
    glHelper->singleDrawTriangle(env, surface);
    delete glHelper;
}extern "C"
JNIEXPORT void JNICALL
Java_com_zqlxtt_learnopengl_BaseSurfaceFragment_drawColorTriangle(JNIEnv *env, jobject thiz,
                                                                  jobject surface) {
    auto *glHelper = new GLHelper();
    glHelper->singleDrawColorTriangle(env, surface);
    delete glHelper;
}