//
// Created by zqlxt on 2020/10/2.
//

#ifndef LEARNOPENGL_TRIANGLERENDER_H
#define LEARNOPENGL_TRIANGLERENDER_H


#include "../gl/GLBaseRender.h"
#include <GLES3/gl3.h>
class TriangleRender : public GLBaseRender {
private:
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
public:
    TriangleRender();
    ~TriangleRender();
    void processProgram();

    void processShader();

    void draw();

    void release();
};


#endif //LEARNOPENGL_TRIANGLERENDER_H
