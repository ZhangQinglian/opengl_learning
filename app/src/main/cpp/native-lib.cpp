#include <jni.h>
#include <string>
#include "egl/EGLHelper.h"
#include <android/native_window.h>
#include <android/native_window_jni.h>

EGLHelper *eglHelper;
extern "C"
JNIEXPORT void JNICALL
Java_com_zqlxtt_learnopengl_L1_FragmentInitOpenGLES_init_1opengl_1es(JNIEnv *env, jobject thiz,
                                                                     jobject surface) {
    ANativeWindow *aNativeWindow = ANativeWindow_fromSurface(env, surface);
    eglHelper = new EGLHelper();
    eglHelper->initEGL(aNativeWindow);
    eglHelper->singleDrawColor();
    eglHelper->swapBuffers();
}extern "C"
JNIEXPORT void JNICALL
Java_com_zqlxtt_learnopengl_L1_FragmentInitOpenGLES_destroy_1opengl_1es(JNIEnv *env, jobject thiz) {
    if (eglHelper != nullptr) {
        eglHelper->destroyEGL();
    }
}