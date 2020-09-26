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

    GLuint loadShader(GLenum type,const char *shaderSrc);

    void singleDrawColor(float, float, float, float);

    void singleDrawTriangle();
};


#endif //LEARNOPENGL_GLHELPER_H
