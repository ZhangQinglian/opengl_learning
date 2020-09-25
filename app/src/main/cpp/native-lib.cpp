#include <jni.h>
#include <string>
#include "egl/EGLHelper.h"
#include <android/native_window.h>
#include <android/native_window_jni.h>

EGLHelper *eglHelper;
extern "C"
JNIEXPORT void JNICALL
Java_com_zqlxtt_learnopengl_BaseSurfaceFragment_init_1opengl_1es(JNIEnv *env, jobject thiz,
                                                                 jobject surface) {
    ANativeWindow *aNativeWindow = ANativeWindow_fromSurface(env, surface);
    eglHelper = new EGLHelper();
    eglHelper->initEGL(aNativeWindow);
}extern "C"
JNIEXPORT void JNICALL
Java_com_zqlxtt_learnopengl_BaseSurfaceFragment_destroy_1opengl_1es(JNIEnv *env, jobject thiz) {
    if (eglHelper != nullptr) {
        eglHelper->destroyEGL();
        delete eglHelper;
    }
}extern "C"
JNIEXPORT void JNICALL
Java_com_zqlxtt_learnopengl_BaseSurfaceFragment_drawColor(JNIEnv *env, jobject thiz, jfloat red,
                                                          jfloat green, jfloat blue,
                                                          jfloat alpha) {
    eglHelper->singleDrawColor(red, green, blue, alpha);
    eglHelper->swapBuffers();
}extern "C"
JNIEXPORT void JNICALL
Java_com_zqlxtt_learnopengl_BaseSurfaceFragment_drawTriangle(JNIEnv *env, jobject thiz) {
    eglHelper->singleDrawTriangle();
    eglHelper->swapBuffers();
}