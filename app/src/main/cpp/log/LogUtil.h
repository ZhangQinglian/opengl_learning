//
// Created by 番茄沙司 on 2020/9/24.
//

#ifndef LEARNOPENGL_LOGUTIL_H
#define LEARNOPENGL_LOGUTIL_H

#include <android/log.h>

#define LOGD(FORMAT,...) __android_log_print(ANDROID_LOG_DEBUG,"learning_opengl",FORMAT,##__VA_ARGS__)
#define LOGI(FORMAT,...) __android_log_print(ANDROID_LOG_INFO,"learning_opengl",FORMAT,##__VA_ARGS__)
#define LOGE(FORMAT,...) __android_log_print(ANDROID_LOG_ERROR,"learning_opengl",FORMAT,##__VA_ARGS__)

#endif //LEARNOPENGL_LOGUTIL_H
