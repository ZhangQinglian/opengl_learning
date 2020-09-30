//
// Created by zqlxt on 2020/9/26.
//

#ifndef LEARNOPENGL_GLHELPER_H
#define LEARNOPENGL_GLHELPER_H

#include <GLES3/gl3.h>

class GLHelper {
public:
    GLHelper();

    ~GLHelper();

    GLuint loadShader(GLenum type, const char *shaderSrc);

    GLuint loadProgram(GLuint vertextShader, GLuint fragmentShader);

    void singleDrawColor(JNIEnv *env,jobject surface,float, float, float, float);

    void singleDrawTriangle(JNIEnv *env,jobject surface);

    void singleDrawColorTriangle(JNIEnv *env,jobject surface);

    void drawColorTriangleWithThread();
    GLint checkShaderCompiled(GLuint shader);
    GLint checkProgramLinked(GLuint program);
};


#endif //LEARNOPENGL_GLHELPER_H
